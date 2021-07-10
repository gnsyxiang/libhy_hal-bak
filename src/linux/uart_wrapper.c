/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    uart_wrapper.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/07 2021 10:39
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/07 2021      create the file
 * 
 *     last modified: 10/07 2021 10:39
 */
#include <stdio.h>

#include "uart_wrapper.h"

void *uart_create(HyHalUartConfig_t *uart_config)
{
    return NULL;
}

void uart_destroy(void *handle)
{
}

int uart_write(void *handle, void *buf, size_t len)
{
    return 0;
}

