#include <vxWorks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <hrFsLib.h>
#include <xbdPartition.h>
#include <xbdRamDisk.h>
#define DEVNAME "/myram" /* name of the RAM disk */
#define BLOCKSIZE 512
#define DISKSIZE (BLOCKSIZE * 2000)
STATUS hrfsSetup
 (
 void
 )
 {
 STATUS error;
 device_t xbd;
 /* Create a RAM disk. Don’t support partitions */
 xbd = xbdRamDiskDevCreate (BLOCKSIZE, DISKSIZE, 0, DEVNAME);
 if (xbd == NULLDEV)
 {
 printf("Failed to create RAM disk. errno = 0x%x\n", errno);
 return (ERROR);
 }
 /*
 * Format the RAM disk for HRFS. Allow for upto a 1000 files/directories
 * and let HRFS determine the logical block size.
 */
 error = hrfsFormat (DEVNAME, 0ll, 0, 1000);
 if (error != OK)
 {
 printf("Failed to format RAM disk. errno = 0x%x\n", errno);
 return (ERROR);
 }
 printf ("%s now ready for use.\n", DEVNAME);
 return (OK);
 }
 STATUS hrfsFileExample
 (
 void
 )
 {
 int fd;
 char path[PATH_MAX];
 char *testString = "hello world";
 int size = strlen (testString) + 1; /* size of test string including EOS */
 int len;
 /* Create a file under the root directory */
 /* First build the path */
 sprintf (path, "%s/myfile", DEVNAME);
 fd = open (path, O_RDWR | O_CREAT, 0777);
 if (fd < 0)
 {
 printf ("Couldn’t create file %s. errno = 0x%x\n", path, errno);
 return (ERROR);
 }

 /* Write to the file */
 printf("Writing %d bytes to file.\n", size);
 len = write (fd, testString, size);
 if (len != size)
 {
 printf ("Couldn’t write to file %s. errno = 0x%x\n", path, errno);
 close (fd);
 return (ERROR);
 }
 /* Close and re-open file */
 close (fd);
 fd = open (path, O_RDWR, 0777);
 if (fd < 0)
 {
 printf ("Couldn’t re-open file %s. errno = 0x%x\n", path, errno);
 return (ERROR);
 }
 /* Now read back what we wrote */
 printf("Reading %d bytes from file.\n", size);
 len = read (fd, path, size);
 if (len != 12)
 {
 printf ("Couldn’t read from file %s. errno = 0x%x\n", path, errno);
 close (fd);
 return (ERROR);
 }

 /* Make sure we read what we wrote */
 if ((len = strcmp (path, testString)) != 0)
 {
 printf ("Read data different from written data. errno = 0x%x, %d\n", errno, len);
 close (fd);
 return (ERROR);
 }
 close (fd);
 return (OK);
 }

 