# cat ~/project/linux/v5.15/linux/Makefile | grep '^VERSION\|^PATCHLEVEL\|^SUBLEVEL'
# uname -r

cd drivers/infiniband/
# make -C /lib/modules/$(uname -r)/build M=$(pwd) clean
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
# ls -alh /lib/modules/$(uname -r)/build/
cp /lib/modules/`uname -r`/kernel/drivers/infiniband/core/ib_core.ko /lib/modules/`uname -r`/kernel/drivers/infiniband/core/ib_core.ko.bak
cp /lib/modules/`uname -r`/kernel/drivers/infiniband/core/ib_uverbs.ko /lib/modules/`uname -r`/kernel/drivers/infiniband/core/ib_uverbs.ko.bak
cp /lib/modules/`uname -r`/kernel/drivers/infiniband/core/iw_cm.ko /lib/modules/`uname -r`/kernel/drivers/infiniband/core/iw_cm.ko.bak
cp core/ib_core.ko /lib/modules/`uname -r`/kernel/drivers/infiniband/core/ib_core.ko
cp core/ib_uverbs.ko /lib/modules/`uname -r`/kernel/drivers/infiniband/core/ib_uverbs.ko
cp core/iw_cm.ko /lib/modules/`uname -r`/kernel/drivers/infiniband/core/iw_cm.ko
depmod -a
cd -

echo -e "Build and replace ib_core, ib_uverbs ok"