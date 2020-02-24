#!/usr/bin/env bash

if [ $# != 2 ] ; then
    echo "usage: $0 system_name absolute_install_path"
    echo " e.g.: $0 linux/rtt "'`pwd`/install'
    exit 1;
fi

echo "---------------------------------------------"
echo "detect system, initialize basic configuration"
echo "---------------------------------------------"
./autogen.sh

echo "------------------------------------------------"
echo "configure gcc according to the selected system"
echo "------------------------------------------------"
case $1 in
    linux)
        echo "linux"
        SELECT_OPT=--enable-linux
        ;;
    rtt)
        TOOLCHAINS_DIR=/opt/toolchains/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-
        HOST=arm-linux
        SELECT_OPT=--enable-rtt
        ;;
    *)
        echo "error"
        exit 1;
esac

GCC=${TOOLCHAINS_DIR}gcc
CXX=${TOOLCHAINS_DIR}g++
PROGRAM_PREFIX=${1}-
PREFIX_PATH=${2}

echo "-----------------------------------"
echo "run configure for generate Makefile"
echo "-----------------------------------"
./configure \
    ${SELECT_OPT} \
    CC=${GCC} \
    --prefix=${PREFIX_PATH} \
    --program-prefix=${PROGRAM_PREFIX}


