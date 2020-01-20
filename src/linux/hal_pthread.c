/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_pthread.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/01 2020 20:59
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/01 2020      create the file
 * 
 *     last modified: 10/01 2020 20:59
 */
#include <stdio.h>

#define LIBHAL_INCLUDE_HAL_PTHREAD_GB
#include "hal_pthread.h"
#undef LIBHAL_INCLUDE_HAL_PTHREAD_GB

void hello_world(void)
{
    printf("hello world \n");
}

