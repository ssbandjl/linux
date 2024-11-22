#include "sioLib.h"
#include "stdio.h"
#include "iosLib.h"
#include "string.h"


typedef struct {
    DEV_HDR pDevHdr;
    char buf[256];
} CHR_DEV;

LOCAL CHR_DEV chrDev;
LOCAL int chrDrvNum = -1;
LOCAL int chrOpen(DEV_HDR *pDevHdr, char *name, int flags, int mode)
{
    return (int)pDevHdr;
}

LOCAL STATUS chrClose(DEV_HDR *pChrDev)
{
    return OK;
}

LOCAL int chrRead(CHR_DEV *pChrDev, char *buffer, int nbytes)
{
    int len;
    len = nbytes > 256 ? 256 : nbytes;
    memcpy(buffer, pChrDev->buf, len);
    return len;
}

LOCAL int chrWrite(CHR_DEV *pChrDev, char *buffer, int nbytes)
{
    int len;
    len = nbytes > 256 ? 256 : nbytes;
    memcpy(pChrDev->buf, buffer, len);
    return len;
}

LOCAL STATUS chrDrv(void)
{
    if (chrDrvNum != -1) {
        printf("fschr: driver has already been installed\n");
        return (OK);
    }
    chrDrvNum = iosDrvInstall(NULL,
    NULL,
    chrOpen,
    chrClose,
    chrRead,
    chrWrite,
    NULL);

    if (chrDrvNum == ERROR) {
        printf("fschr: install driver failed\n");
        return (ERROR);
    } else {
        printf("fschr: install driver success\n");
        return (OK);
    }
}

LOCAL STATUS chrDeviceCreate(void)
{
    if (iosDevAdd(&chrDev.pDevHdr, "/dev/fsdev", chrDrvNum) == ERROR) {
        printf("fschr: add device failed\n");
        return (ERROR);
    } else {
        printf("fschr: add device success\n");
        return (OK);
    }

}


STATUS fsChrProbe(void)
{
    if (chrDrv() == ERROR) {
        return (ERROR);
    } else {
        return chrDeviceCreate();
    }
}


