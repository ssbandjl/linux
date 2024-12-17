#!/bin/bash

gdb <<EOF
file ./kernel.sym
target remote:1234
EOF


