#   a. make menuconfig
#         i. 选中Processor type and features
#             1. 取消勾选EFI runtime service support（取消勾选这一项会自动给module签名）


# apt-get install aptitude
# sudo aptitude install zstd
#make menuconfig
make oldconfig
make prepare
make script
# CONFIG_MODULE_SIG=n
make -j64


# sed -i s/CONFIG_SYSTEM_TRUSTED_KEYS.*/CONFIG_SYSTEM_TRUSTED_KEYS=\"\"/g .config
# sed -i s/CONFIG_SYSTEM_REVOCATION_KEYS.*/CONFIG_SYSTEM_REVOCATION_KEYS=\"\"/g .config

# make -j64
# objcopy --only-keep-debug vmlinux kernel.sym


# build module, driver
make clean
cd drivers/scsi/
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
# make -C ../../ M=$(pwd) modules



# sed -i s/CONFIG_MODULE_SIG=y/CONFIG_MODULE_SIG=n/g .config
# # CONFIG_MODULE_SIG=n

