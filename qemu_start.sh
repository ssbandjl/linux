# Create a disk image Create a disk image in QCOW2 format (qcow2 is slower than the raw format, but uses less disk space).
# cd /home/xb/big/qemu;rm -f ubuntu-20.04.5-desktop.qcow2.bak;mv ubuntu-20.04.5-desktop.qcow2 ubuntu-20.04.5-desktop.qcow2.bak
# /home/xb/project/virt/qemu/build/qemu-img create -f qcow2 ubuntu-20.04.5-desktop.qcow2 16G


# install os
# /home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4096 -smp 2 --enable-kvm -drive file=/home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2,format=qcow2 -boot order=d -cdrom /home/xb/big/ubuntu-20.04.5-desktop-amd64_2.iso

# start vm, need filter log event
# /home/xb/project/virt/qemu/build/qemu-system-x86_64 -device edu -device dma_engine -m 4096 -smp 2 --enable-kvm -trace enable=* -D qemu.log /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2
/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm \
                   -display none \
                   -nic user,hostfwd=tcp::60022-:22 \
                   -device edu -device dma_engine \
                   /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2

or:
/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm -nic user,hostfwd=tcp::60022-:22  -device edu -device dma_engine /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2


/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm -nic user,hostfwd=tcp::60022-:22  -device edu -device dma_engine -virtfs local,path=/home/xb/Public,mount_tag=host_public,id=host0,security_model=mapped-xattr /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2

use bridge:
/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm -netdev bridge,id=hn0,br=br0  -device virtio-net-pci,netdev=hn0,id=nic1 -device edu -device dma_engine -virtfs local,path=/home/xb/Public,mount_tag=host_public,id=host0,security_model=mapped-xattr /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2

sudo /home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm -net nic,model=virtio,macaddr=52:54:00:00:00:01 -net bridge,br=br0 -device edu -device dma_engine -virtfs local,path=/home/xb/Public,mount_tag=host_public,id=host0,security_model=mapped-xattr /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2

no root:
/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm -net nic,model=virtio,macaddr=52:54:00:00:00:01 -net bridge,br=br0 -device edu -device dma_engine -virtfs local,path=/home/xb/Public,mount_tag=host_public,id=host0,security_model=mapped-xattr /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2

guest_mount share folder:
sudo mount -t 9p -o trans=virtio,version=9p2000.L host_public /home/xb/Public


gdb --args /home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm  -display none -D /home/xb/big/qemu_vm.log -net nic,model=virtio,macaddr=52:54:00:00:00:01 -net bridge,br=br0 -device edu -device dma_engine -virtfs local,path=/home/xb/Public,mount_tag=host_public,id=host0,security_model=mapped-xattr /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2




gdb --args /home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 4G -smp 2 -enable-kvm  -display none  -nographic -D /home/xb/big/qemu_vm.log -net nic,model=virtio,macaddr=52:54:00:00:00:01 -net bridge,br=br0 -device edu -device myedu -device dma_engine -virtfs local,path=/home/xb/Public,mount_tag=host_public,id=host0,security_model=mapped-xattr /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2


latest:
ps aux|grep qemu|grep -v grep|awk '{print$2}'|xargs -x kill
/home/xb/project/virt/qemu/build/qemu-system-x86_64 -m 8G -smp 2 -enable-kvm  -display none  -nographic -D /home/xb/big/qemu_vm.log -net nic,model=virtio,macaddr=52:54:00:00:00:01 -net bridge,br=br0 -device edu -device myedu,device_id=0x9038 -device dma_engine -virtfs local,path=/home/xb/Public,mount_tag=host_public,id=host0,security_model=mapped-xattr /home/xb/big/qemu/ubuntu-20.04.5-desktop.qcow2