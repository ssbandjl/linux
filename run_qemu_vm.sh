#ok
echo -e """
gdb
file ./kernel.sym
target remote:1234
"""

#connect spdk vhost target
sudo /home/xb/project/virt/qemu/build/qemu-system-x86_64 \
    -enable-kvm -cpu host -smp cores=4,sockets=1 \
    -m 1G -object memory-backend-file,id=mem0,size=1G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem0 \
    -drive file=/root/big/qemu/ubuntu20.04.6_new.img,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.15 \
    -chardev socket,id=spdk_vhost_scsi0,path=/var/tmp/vhost.0 \
    -device vhost-user-scsi-pci,id=scsi0,chardev=spdk_vhost_scsi0,num_queues=2 \
    -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio

/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4096 -enable-kvm -cpu host -smp cores=8,sockets=1 -drive file=/root/big/qemu/ubuntu20.04.6_new.img,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.15 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -S -s -vnc :75 -monitor stdio

# install kernel and module
/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4096 -enable-kvm -cpu host -smp cores=8,sockets=1 -drive file=/root/big/qemu/ubuntu20.04.6_new.img,if=virtio -nic user,hostfwd=tcp::2222-:22 -fsdev local,security_model=passthrough,id=fsdev0,path=/root/project/linux/linux-5.15 -device virtio-9p-pci,fsdev=fsdev0,mount_tag=kernelmake -device usb-ehci,id=usb,bus=pci.0,addr=0x8 -device usb-tablet -vnc :75


# ssh to vm
ssh-copy-id root@localhost -p2222
ssh -p 2222 root@localhost


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



make modules_install
make install
echo -e """
cat /boot/grub/grub.cfg
vim /etc/default/grub
add: GRUB_DEFAULT='Advanced options for Ubuntu>Ubuntu, with Linux 5.15.0'
update-grub
"""


# mount -t 9p -o trans=virtio kernelmake /root/project/linux/v5.15/linux
make modules_install
make install
update-grub
echo -e """

cat /boot/grub/grub.cfg
grep submenu /boot/grub/grub.cfg
grep 5.15 /boot/grub/grub.cfg


vim /etc/default/grub
REF: GRUB_DEFAULT=gnulinux-advanced-9cf7073a-6786–43dc-895e-8bbebe712a1e>gnulinux-4.15.0–136-lowlatency-advanced-9cf7073a-6786–43dc-895e-8bbebe712a1e
add: GRUB_DEFAULT='Advanced options for Ubuntu>Ubuntu, with Linux 5.15.0'
ref: GRUB_CMDLINE_LINUX_DEFAULT="console=tty1 console=ttyS0 nvme_core.io_timeout=4294967295 nokaslr"
update-grub
"""

remvoe kernel:
ls -alh /boot
dpkg --list|grep linux-image
apt --purge remove linux-image-5.15.0-67-generic



