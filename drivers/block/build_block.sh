make -C /lib/modules/$(uname -r)/build M=$(pwd) modules

#insmod virtio_blk.ko

#echo  'module virtio_blk +p' > /sys/kernel/debug/dynamic_debug/control
#echo  'module virtio +p' > /sys/kernel/debug/dynamic_debug/control
