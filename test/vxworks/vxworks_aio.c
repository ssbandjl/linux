/* aioEx.c - example code for using asynchronous I/O */
/* includes */
#include <vxWorks.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <aio.h>
/* defines */
#define BUFFER_SIZE 200
struct aiocb aiocb_read; /* read aiocb */
struct aiocb aiocb_write; /* write aiocb */
/************************************************************************
* aioExample - use AIO library * This example shows the basic functions of
the AIO library.
* RETURNS: OK if successful, otherwise ERROR.
*/
STATUS aioExample (const char *exFile)
 {
 int fd;
 char buffer [BUFFER_SIZE]; /* buffer for read aiocb */
 static char * test_string = "testing 1 2 3";
 int error;
 if ((fd = open (exFile, O_CREAT | O_TRUNC | O_RDWR, 0666)) ==
ERROR)
{
printf ("aioExample: cannot open %s for writing. errno 0x%x\n", exFile,
errno);
return (ERROR);
}
 printf ("aioExample: Example file = %s\tFile descriptor = %d\n",
exFile, fd);
 /* initialize read and write aiocbs */

 memset ( &aiocb_read, 0, sizeof (struct aiocb));
 memset ( buffer, 0, sizeof (buffer));
 aiocb_read.aio_fildes = fd;
 aiocb_read.aio_buf = buffer;
 aiocb_read.aio_nbytes = BUFFER_SIZE;
 aiocb_read.aio_reqprio = 0;
 memset ( &aiocb_write, 0, sizeof (struct aiocb));
 aiocb_write.aio_fildes = fd;
 aiocb_write.aio_buf = test_string;
 aiocb_write.aio_nbytes = strlen (test_string);
 aiocb_write.aio_reqprio = 0;
 /* initiate the read */
 if (aio_read (&aiocb_read) == -1)
printf ("aioExample: aio_read failed\n");
 /* verify that it is in progress */
 if (aio_error (&aiocb_read) == EINPROGRESS)
printf ("aioExample: read is still in progress\n");
 /* write to pipe - the read should be able to complete */
 printf ("aioExample: getting ready to initiate the write\n");
 if (aio_write (&aiocb_write) == -1)
printf ("aioExample: aio_write failed\n");
 /* wait til both read and write are complete */
 while ((error = aio_error (&aiocb_read) == EINPROGRESS) ||
(aio_error (&aiocb_write) == EINPROGRESS))
sleep (1);
 printf ("aioExample: error = %d\n", error);
 /* print out what was read */
 printf ("aioExample: message = %s\n", buffer);
/* clean up */
 if (aio_return (&aiocb_read) == -1)
printf ("aioExample: aio_return for aiocb_read failed\n");
 if (aio_return (&aiocb_write) == -1)
printf ("aioExample: aio_return for aiocb_write failed\n");
 close (fd);
 return (OK);
 }

 