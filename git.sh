git format-patch -1 HEAD
scp 0001-update.patch root@s96:/root/project/linux/v5.15/linux/

remote:
git apply --verbose 0001-update.patch

