#!/usr/bin/env bash

current_dir=`pwd`

echo -n "please input install absolute path: "
read install_path 
echo "install path: ${install_path}"

echo -en "\nplease input build path: "
read build_path 
echo "build path: ${build_path}"

echo -e "\nsupport platform: \n"
echo -e "\tlinux  1"
echo -e "\trtt    2"
echo -en "\nplease select platform: "
read  num
if [[ $num =~ ^-?[0-9]+$ ]]; then
    if [[ $num = 1 ]]; then
        echo -en "\nwhether to support tinyalsa[yes/no, default no]: "
        read support_tinyalsa
        if [[ ${support_tinyalsa} = yes ]]; then
            echo -en "\ntinyalsa install path: "
            read tinyalsa_install_path
            config_str="${config_str} --enable-audio --with-libtinyalsa=${tinyalsa_install_path}"
        fi

        config_str="${config_str} --enable-linux"
        program_prefix=linux-
    elif [[ $num = 2 ]]; then
        echo -en "\nthe toolchains path[/dirs/bin/arm-none-eabi-]: "
        read toolchains_dir
        GCC=${toolchains_dir}gcc
        CXX=${toolchains_dir}g++

        config_str="${config_str} CC=${GCC} --enable-rtt"
        program_prefix=rtt-
    fi
else
    echo "please input number"
    exit -1
fi


echo "---------------------------------------------"
echo "detect system, initialize basic configuration"
echo "---------------------------------------------"
./autogen.sh

echo "-----------------------------------"
echo "run configure for generate Makefile"
echo "-----------------------------------"
mkdir -p ${build_path}
cd ${build_path}
${current_dir}/configure \
    --prefix=${install_path} \
    --program-prefix=${program_prefix} \
    ${config_str}

echo "----------------------"
echo " make and make install"
echo "----------------------"
make ; make install

