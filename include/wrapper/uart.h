/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    uart.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/07 2021 17:27
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/07 2021      create the file
 * 
 *     last modified: 09/07 2021 17:27
 */
#ifndef __LIBHY_HAL_INCLUDE_WRAPPER_UART_H_
#define __LIBHY_HAL_INCLUDE_WRAPPER_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hy_uart.h"

void *uart_create(HyUartConfig_t *uart_config);
void uart_destroy(void **handle);

int uart_write(void *handle, void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif

