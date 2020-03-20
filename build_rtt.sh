#!/usr/bin/env bash

if [ $# != 1 ] ; then
    echo "usage: $0 absolute_install_path"
    echo " e.g.: $0 "'`pwd`/install'
    exit 1;
fi

echo "---------------------------------------------"
echo "detect system, initialize basic configuration"
echo "---------------------------------------------"
./autogen.sh

TOOLCHAINS_DIR=/opt/toolchains/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-
HOST=arm-linux

GCC=${TOOLCHAINS_DIR}gcc
CXX=${TOOLCHAINS_DIR}g++

echo "-----------------------------------"
echo "run configure for generate Makefile"
echo "-----------------------------------"
./configure \
    --enable-rtt \
    CC=${GCC} \
    --prefix=${1} \
    --program-prefix=rtt-

echo "----------------------"
echo " make and make install"
echo "----------------------"
make ; make install
