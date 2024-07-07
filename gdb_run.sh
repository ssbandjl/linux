#!/bin/bash

gdb <<EOF
file ./kernel.sym
target remote:1234
EOF


ref:
b do_init_module
p mod

