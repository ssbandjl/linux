#virtio_blk
echo "add-symbol-file ./drivers/block/virtio_blk.ko `cat /sys/module/virtio_blk/sections/.text` -s .data `cat /sys/module/virtio_blk/sections/.data` -s .bss `cat /sys/module/virtio_blk/sections/.bss`"
b virtblk_probe

#echo 1 > /sys/bus/pci/devices/0000\:00\:05.0/remove 
#lsblk
#echo 1 > /sys/bus/pci/rescan


#virtio_scsi
linux_root
echo "add-symbol-file ./drivers/scsi/virtio_scsi.ko `cat /sys/module/virtio_scsi/sections/.text` -s .data `cat /sys/module/virtio_scsi/sections/.data` -s .bss `cat /sys/module/virtio_scsi/sections/.bss`"

