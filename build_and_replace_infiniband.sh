# cat ~/project/linux/v5.15/linux/Makefile | grep '^VERSION\|^PATCHLEVEL\|^SUBLEVEL'
# uname -r

cd drivers/infiniband/
# make -C /lib/modules/$(uname -r)/build M=$(pwd) clean
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
# ls -alh /lib/modules/$(uname -r)/build/
cp /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_core.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_core.ko.bak
cp /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_uverbs.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_uverbs.ko.bak
cp core/ib_core.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_core.ko
cp core/ib_uverbs.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_uverbs.ko
cd -

echo -e "Build and replace ib_core, ib_uverbs ok"