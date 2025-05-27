cd drivers/infiniband/
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
ls -alh /lib/modules/$(uname -r)/build/
cd -

