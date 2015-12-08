#!/bin/bash
FILE="${1}.s"

echo "Compiling..."
arm-linux-gnueabi-gcc -o $1 -mcpu=arm1176jzf-s -mtune=arm1176jzf-s $FILE
echo "Running..."
qemu-arm -L /usr/arm-linux-gnueabi/ $1
echo $?
rm $1
