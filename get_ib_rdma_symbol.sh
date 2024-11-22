echo "add-symbol-file ./drivers/infiniband/sw/rxe/rdma_rxe.ko `cat /sys/module/rdma_rxe/sections/.text` -s .data `cat /sys/module/rdma_rxe/sections/.data` -s .bss `cat /sys/module/rdma_rxe/sections/.bss`"
echo "add-symbol-file ./drivers/infiniband/core/ib_core.ko `cat /sys/module/ib_core/sections/.text` -s .data `cat /sys/module/ib_core/sections/.data` -s .bss `cat /sys/module/ib_core/sections/.bss`"
echo "add-symbol-file ./drivers/infiniband/core/ib_uverbs.ko `cat /sys/module/ib_uverbs/sections/.text` -s .data `cat /sys/module/ib_uverbs/sections/.data` -s .bss `cat /sys/module/ib_uverbs/sections/.bss`"
echo "add-symbol-file ./drivers/infiniband/hw/irdma/irdma.ko `cat /sys/module/irdma/sections/.text` -s .data `cat /sys/module/irdma/sections/.data` -s .bss `cat /sys/module/irdma/sections/.bss`"

echo -e """
b do_init_module
p mod
p mod->name
p *(mod ptr)
print *mod->sect_attrs->attrs@mod->sect_attrs->nsections
add-symbol-file ./drivers/infiniband/core/ib_core.ko 0xffffffffc07cb000 -s .data 0xffff888100abdf50 -s .bss 0xffff888100a7e8f8 -s .init.text 0xffff888116b16020 -s .init.data 0xffff888116b16820
"""
