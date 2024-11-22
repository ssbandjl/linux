/* selServer.c - select example
* In this example, a server task uses two pipes: one for normal-priority
* requests, the other for high-priority requests. The server opens both
* pipes and blocks while waiting for data to be available in at least one
* of the pipes.
*/
#include <vxWorks.h>
#include <selectLib.h>
#include <fcntl.h>
#define MAX_FDS 2
#define MAX_DATA 1024
#define PIPEHI "/pipe/highPriority"
#define PIPENORM "/pipe/normalPriority"
/************************************************************************
* selServer - reads data as it becomes available from two different pipes
*
* Opens two pipe fds, reading from whichever becomes available. The
* server code assumes the pipes have been created from either another
* task or the shell. To test this code from the shell do the following:
* -> ld < selServer.o
* -> pipeDevCreate ("/pipe/highPriority", 5, 1024)
* -> pipeDevCreate ("/pipe/normalPriority", 5, 1024)
* -> fdHi = open ("/pipe/highPriority", 1, 0)
* -> fdNorm = open ("/pipe/normalPriority", 1, 0)
* -> iosFdShow
* -> sp selServer
* -> i
* At this point you should see selServer’s state as pended. You can now
* write to either pipe to make the selServer display your message.
* -> write fdNorm, "Howdy", 6
* -> write fdHi, "Urgent", 7
*/
STATUS selServer (void)
{
struct fd_set readFds; /* bit mask of fds to read from */
int fds[MAX_FDS]; /* array of fds on which to pend */
int width; /* number of fds on which to pend */
int i; /* index for fd array */
char buffer[MAX_DATA]; /* buffer for data that is read */
/* open file descriptors */
if ((fds[0] = open (PIPEHI, O_RDONLY, 0)) == ERROR)
{
close (fds[0]);
return (ERROR);
}
if ((fds[1] = open (PIPENORM, O_RDONLY, 0)) == ERROR)
{
close (fds[0]);
close (fds[1]);
return (ERROR);
}
/* loop forever reading data and servicing clients */
FOREVER
{
/* clear bits in read bit mask */
FD_ZERO (&readFds);
/* initialize bit mask */
FD_SET (fds[0], &readFds);
FD_SET (fds[1], &readFds);
width = (fds[0] > fds[1]) ? fds[0] : fds[1];
width++;
/* pend, waiting for one or more fds to become ready */
if (select (width, &readFds, NULL, NULL, NULL) == ERROR)
{
close (fds[0]);
close (fds[1]);
return (ERROR);
}
/* step through array and read from fds that are ready */
for (i=0; i< MAX_FDS; i++)
{
/* check if this fd has data to read */
if (FD_ISSET (fds[i], &readFds))
{
/* typically read from fd now that it is ready */
read (fds[i], buffer, MAX_DATA);
/* normally service request, for this example print it */
printf ("SELSERVER Reading from %s: %s\n",
(i == 0) ? PIPEHI : PIPENORM, buffer);
}
}
}
}

