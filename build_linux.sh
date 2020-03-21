#!/usr/bin/env bash

if [ $# != 2 ] ; then
    echo "usage: $0 absolute_install_path 3rd_lib_path"
    echo " e.g.: $0 "'`pwd`/install `pwd`/3rd_lib'
    exit 1;
fi

echo "---------------------------------------------"
echo "detect system, initialize basic configuration"
echo "---------------------------------------------"
./autogen.sh

echo "-----------------------------------"
echo "run configure for generate Makefile"
echo "-----------------------------------"
./configure \
    --enable-linux \
    --with-libtinyalsa=${2}/tinyalsa \
    --prefix=${1} \
    --program-prefix=linux-

echo "----------------------"
echo " make and make install"
echo "----------------------"
make ; make install
