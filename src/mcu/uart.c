/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    uart.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/07 2021 17:32
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/07 2021      create the file
 * 
 *     last modified: 09/07 2021 17:32
 */
#include <stdio.h>

#include "uart.h"

#include "hy_mcu/hy_uart.h"

void *uart_create(HyHalUartConfig_t *uart_config)
{
    return HyUartCreate((HyUartConfig_t *)uart_config);
}

void uart_destroy(void **handle)
{
    HyUartDestroy(handle);
}

int uart_write(void *handle, void *buf, size_t len)
{
    return HyUartSendBuf(handle, buf, len);
}

