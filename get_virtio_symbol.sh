echo "add-symbol-file ./drivers/block/virtio_blk.ko `cat /sys/module/virtio_blk/sections/.text` -s .data `cat /sys/module/virtio_blk/sections/.data` -s .bss `cat /sys/module/virtio_blk/sections/.bss`"

b virtblk_probe
#echo 1 > /sys/bus/pci/devices/0000\:00\:05.0/remove 
#lsblk
#echo 1 > /sys/bus/pci/rescan

