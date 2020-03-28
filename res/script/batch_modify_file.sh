#!/usr/bin/env bash

top_dir=`pwd`/../..
src_dir=${top_dir}/src
include_dir=${top_dir}/include
example_dir=${top_dir}/example

for dir in ${src_dir} ${include_dir} ${example_dir}; do
    files=$(find ${dir} -name "*.[c|h]")
    for file in ${files} ; do
        sed -i s/Hal_LogV/HalLogV/g ${file}
        sed -i s/Hal_LogD/HalLogD/g ${file}
        sed -i s/Hal_LogT/HalLogT/g ${file}
        sed -i s/Hal_LogW/HalLogW/g ${file}
        sed -i s/Hal_LogE/HalLogE/g ${file}
    done
done

