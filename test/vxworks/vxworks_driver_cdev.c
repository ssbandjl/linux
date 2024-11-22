/*
* xxDrv - driver initialization routine
* xxDrv() init’s the driver. It installs the driver via iosDrvInstall.
* It may allocate data structures, connect ISRs, and initialize hardware
*/
STATUS xxDrv ()
{
xxDrvNum = iosDrvInstall (xxCreat, 0, xxOpen, 0, xxRead, xxWrite, xxIoctl)
;
(void) intConnect (intvec, xxInterrupt, ...);
...
}
/************************************************************************
* xxDevCreate - device creation routine
*
* Called to add a device called <name> to be svced by this driver. Other
* driver-dependent arguments may include buffer sizes, device addresses.
* The routine adds the device to the I/O system by calling iosDevAdd.
* It may also allocate and initialize data structures for the device,
* initialize semaphores, initialize device hardware, and so on.
*/
STATUS xxDevCreate (name, ...)
char * name;
...
{
status = iosDevAdd (xxDev, name, xxDrvNum);
...
}
/*
*
* The following routines implement the basic I/O functions.
* The xxOpen() return value is meaningful only to this driver,
* and is passed back as an argument to the other I/O routines.
*/
int xxOpen (xxDev, remainder, mode)
XXDEV * xxDev;
char * remainder;
int mode;
{
/* serial devices should have no file name part */
if (remainder[0] != 0)
return (ERROR);
else
return ((int) xxDev);
}
int xxRead (xxDev, buffer, nBytes)
XXDEV * xxDev;
char * buffer;
int nBytes;
...
int xxWrite (xxDev, buffer, nBytes)
...
int xxIoctl (xxDev, requestCode, arg)
...
/*
* xxInterrupt - interrupt service routine
*
* Most drivers have routines that handle interrupts from the devices
* serviced by the driver. These routines are connected to the interrupts
* by calling intConnect (usually in xxDrv above). They can receive a
* single argument, specified in the call to intConnect (see intLib).
*/
VOID xxInterrupt (arg)
