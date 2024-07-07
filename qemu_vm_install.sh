# mount -t 9p -o trans=virtio kernelmake /root/project/linux/v5.15/linux
make modules_install
make install
echo -e """
cat /boot/grub/grub.cfg
vim /etc/default/grub
add: GRUB_DEFAULT='Advanced options for Ubuntu>Ubuntu, with Linux 5.15.0'
ref: GRUB_CMDLINE_LINUX_DEFAULT="console=tty1 console=ttyS0 nvme_core.io_timeout=4294967295 nokaslr"
update-grub
"""
