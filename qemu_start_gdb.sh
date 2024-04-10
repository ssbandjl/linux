qemu-system-x86_64  \
 -kernel ./arch/x86/boot/bzImage  \
 -initrd ./rootfs  \
 -append "root=/dev/ram rdinit=/helloworld" \
 -smp 2  \
 -s -S
 