Example 7-4 Formatting a Device for TRFS
/* Create a RAM disk with 512 byte sized sectors and 1024 sectors.*/
if (xbdRamDiskDevCreate (512, 1024 * 512, 0, "/trfs") == NULL)
{
printf ("Could not create RAM disk\n");
return;
}
/* Put TRFS on the RAM disk */
if (usrFormatTrans ("/trfs", 100, 0) != OK)
{
printf ("Could not format\n");
return;
}
/* Now put dosFs on TRFS */
if (dosFsVolFormat ("/trfs", DOS_OPT_BLANK, 0) != OK)
{
printf ("Could not format for dos\n");
return;
}
/* Create a file on the TRFS/DosFS volume */
fd = open ("/trfs/myfile", O_CREAT | O_RDWR, 0666);
if (fd < 0)
{
printf ("Couldn't create file\n");
return;
}
/* Commit the file creation to media */
ioctl (fd, CBIO_TRANS_COMMIT, 0);
