cp /boot/config-$(uname -r) .config
make olddefconfig  # auto-accept defaults for new options


# mount -t 9p -o trans=virtio kernelmake /root/project/linux/v5.15/linux
make modules_install
make install
echo -e """

cat /boot/grub/grub.cfg
grep submenu /boot/grub/grub.cfg
grep 5.15 /boot/grub/grub.cfg

show menu:
GRUB_TIMEOUT_STYLE=menu
GRUB_TIMEOUT=5

vim /etc/default/grub
REF: GRUB_DEFAULT=gnulinux-advanced-9cf7073a-6786–43dc-895e-8bbebe712a1e>gnulinux-4.15.0–136-lowlatency-advanced-9cf7073a-6786–43dc-895e-8bbebe712a1e
add: GRUB_DEFAULT='Advanced options for Ubuntu>Ubuntu, with Linux 5.15.0'
ref: GRUB_CMDLINE_LINUX_DEFAULT="console=tty1 console=ttyS0 nvme_core.io_timeout=4294967295 nokaslr"
update-grub
"""


makemeneconfig

CONFIG_MODULES=y
CONFIG_MODULE_UNLOAD=y
CONFIG_MODVERSIONS=y          # (optional: for versioned symbols)

enable cma ?
CONFIG_CMA=y

make -j32

make headers_install
make defconfig
make prepare
make modules_prepare
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



