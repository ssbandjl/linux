cd drivers/infiniband/
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
ls -alh /lib/modules/$(uname -r)/build/
cp /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_core.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_core.ko.bak
cp /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_uverbs.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_uverbs.ko.bak
cp core/ib_core.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_core.ko
cp core/ib_uverbs.ko /lib/modules/5.15.0+/kernel/drivers/infiniband/core/ib_uverbs.ko
cd -

