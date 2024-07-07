make clean
cd drivers/scsi/
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
