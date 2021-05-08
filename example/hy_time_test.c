/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_time_test.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    08/05 2021 14:02
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        08/05 2021      create the file
 * 
 *     last modified: 08/05 2021 14:02
 */
#include <stdio.h>

#include "hy_time.h"

int main(int argc, char *argv[])
{
    hy_uint64_t start_us = HyTimeGetCurrentTime2Us();

    for (int i = 0; i < 10; ++i) {
        printf("ha");
    }
    printf("\n");

    hy_uint64_t interval = HyTimeGetTimeInterval(start_us);

    printf("interval: %lldus\n", interval);

    return 0;
}
