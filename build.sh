#!/usr/bin/env bash

if [ $# != 3 ] ; then
    echo "usage: $0 system_name absolute_install_path 3rd_lib_path"
    echo " e.g.: $0 linux/rtt "'`pwd`/install `pwd`/3rd_lib'
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
        SELECT_OPT="--enable-linux --with-libtinyalsa=${3}/tinyalsa"
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

echo "----------------------"
echo " make and make install"
echo "----------------------"
make ; make install
