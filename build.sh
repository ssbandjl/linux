#   a. make menuconfig
#         i. 选中Processor type and features
#             1. 取消勾选EFI runtime service support（取消勾选这一项会自动给module签名）

#make menuconfig
make -j64
