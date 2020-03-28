#!/usr/bin/env bash

top_dir=`pwd`/../..
src_dir=${top_dir}/src
inc_dir=${top_dir}/include

# handle *.c
c_files=$(find ${src_dir} -name "*.c")
for file in ${c_files} ; do
    sed -i s/Hal_LogV/HalLogV/g ${file}
    sed -i s/Hal_LogD/HalLogD/g ${file}
    sed -i s/Hal_LogT/HalLogT/g ${file}
    sed -i s/Hal_LogW/HalLogW/g ${file}
    sed -i s/Hal_LogE/HalLogE/g ${file}
done

# handle *.h
h_files=$(find ${inc_dir} -name "*.h")
for file in ${h_files} ; do
    sed -i s/Hal_LogV/HalLogV/g ${file}
    sed -i s/Hal_LogD/HalLogD/g ${file}
    sed -i s/Hal_LogT/HalLogT/g ${file}
    sed -i s/Hal_LogW/HalLogW/g ${file}
    sed -i s/Hal_LogE/HalLogE/g ${file}
done

