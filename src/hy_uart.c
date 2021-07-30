/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_uart.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/07 2021 17:23
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/07 2021      create the file
 * 
 *     last modified: 09/07 2021 17:23
 */
#include <stdio.h>

#include "hy_uart.h"
#include "uart.h"

#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

void *HyHalUartCreate(HyHalUartConfig_t *uart_config)
{
    HY_ASSERT_NULL_RET_VAL(!uart_config, NULL);
    return uart_create(uart_config);
}

void HyHalUartDestroy(void **handle)
{
    HY_ASSERT_NULL_RET(!handle || !*handle);
    uart_destroy(handle);
}

int HyHalUartWrite(void *handle, void *buf, size_t len)
{
    HY_ASSERT_NULL_RET_VAL(!handle, -1);
    return uart_write(handle, buf, len);
}

