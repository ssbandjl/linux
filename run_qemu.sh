# qemu-system-x86_64 -m 4096 -enable-kvm -cpu host -smp cores=8,sockets=1 -kernel ./arch/x86/boot/bzImage -append "nokaslr" -drive file=/root/big/qemu/ubuntu20.04.6.img,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.4.18 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio

# qemu-system-x86_64 -m 4096 -enable-kvm -cpu host -smp cores=8,sockets=1 -drive file=/root/big/qemu/ubuntu20.04.6.img,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.4.18 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio


# qemu-system-x86_64 -m 4096 -enable-kvm -cpu host -smp cores=8,sockets=1 -kernel ./arch/x86/boot/bzImage -hda /root/big/qemu/ubuntu20.04.6.img -append "root=/dev/vda5 rw" -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.4.18 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio


qemu-system-x86_64 -m 4096 -enable-kvm -cpu host -smp cores=8,sockets=1 -drive file=/root/big/qemu/ubuntu20.04.6.img,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.4.18 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio



