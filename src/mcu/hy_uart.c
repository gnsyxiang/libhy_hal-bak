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

#include "hy_uart.h"

void *HyUartCreate(HyUartConfig_t *uart_config)
{
    return NULL;
}
void HyUartDestroy(void **handle)
{

}

hy_s32_t HyUartProcess(void *handle)
{
    return 0;
}

hy_s32_t HyUartWrite(void *handle, void *buf, size_t len)
{
    return 0;
}

