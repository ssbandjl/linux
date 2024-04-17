make drivers/infiniband/
# cp -i drivers/infiniband/xxx.ko /lib/modules/$(uname -r)/kernel/xxx
cp -i drivers/infiniband/core/ib_core.ko /lib/modules/$(uname -r)/kernel/drivers/infiniband/core/ib_core.ko
cp -i drivers/infiniband/core/ib_uverbs.ko /lib/modules/$(uname -r)/kernel/drivers/infiniband/core/ib_uverbs.ko


