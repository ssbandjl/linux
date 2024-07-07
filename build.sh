# apt-get install aptitude -y
# aptitude install zstd
# sudo apt-get install -y libzstd-dev libncurses5-dev libssl-dev bison flex libelf-dev gcc make openssl libc6-dev 

sed -i s/CONFIG_SYSTEM_TRUSTED_KEYS.*/CONFIG_SYSTEM_TRUSTED_KEYS=\"\"/g .config
sed -i s/CONFIG_SYSTEM_REVOCATION_KEYS.*/CONFIG_SYSTEM_REVOCATION_KEYS=\"\"/g .config

make -j64
objcopy --only-keep-debug vmlinux kernel.sym
