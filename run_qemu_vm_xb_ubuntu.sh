#ok
echo -e """
gdb
file ./kernel.sym
target remote:1234
"""

# start qemu
/root/project/virt/qemu/build/qemu-system-x86_64 -m 4096 -enable-kvm -cpu host -smp cores=8,sockets=1 -drive file=/root/big/qemu/ubuntu20.qcow2,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/v5.15/linux -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -vnc :75

# gdb
/root/project/virt/qemu/build/qemu-system-x86_64 \
    -enable-kvm -cpu host -smp cores=8,sockets=1 \
    -m 1G -object memory-backend-file,id=mem0,size=1G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem0 \
    -drive file=/root/big/qemu/ubuntu20.qcow2,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/v5.15/linux \
    -chardev socket,id=spdk_vhost_scsi0,path=/var/tmp/vhost.0 \
    -device vhost-user-scsi-pci,id=scsi0,chardev=spdk_vhost_scsi0,num_queues=2 \
    -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio


gdb --args /root/project/virt/qemu/build/qemu-system-x86_64 \
    -enable-kvm -cpu host -smp cores=8,sockets=1 \
    -m 1G -object memory-backend-file,id=mem0,size=1G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem0 \
    -drive file=/root/big/qemu/ubuntu20.qcow2,if=virtio \
    -chardev socket,id=spdk_vhost_scsi0,path=/var/tmp/vhost.0 \
    -device vhost-user-scsi-pci,id=scsi0,chardev=spdk_vhost_scsi0,num_queues=2 \
    -nic user,hostfwd=tcp::2222-:22  -device usb-ehci,id=usb,bus=pci.0,addr=0x8 \
    -device usb-tablet -vnc :75


# /home/xb/project/virt/qemu/build/qemu-system-x86_64 \
#     -m 4096 \
#     -hda /root/big/qemu/ubuntu20.04.6_new.img \
#     -kernel ./arch/x86/boot/bzImage \
#     -append "root=/dev/vda5 nokaslr" \
#     -initrd /root/project/linux/linux-5.4.18/initrd.img-5.4.18+ \
#     -enable-kvm -cpu host -smp cores=8,sockets=1 -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.4.18 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio


# /home/xb/project/virt/qemu/build/qemu-system-x86_64 \
#     -m 4096 \
#     -hda /root/big/qemu/ubuntu20.04.6_new.img \
#     -kernel ./arch/x86/boot/bzImage \
#     -append "root=/dev/vda5 nokaslr" \
#     -initrd /root/project/linux/linux-5.4.18/initrd.img-5.4.18 \
#     -enable-kvm -cpu host -smp cores=8,sockets=1 -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.4.18 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio

