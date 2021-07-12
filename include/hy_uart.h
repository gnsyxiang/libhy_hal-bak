/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_uart.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/07 2021 17:15
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/07 2021      create the file
 * 
 *     last modified: 09/07 2021 17:15
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_UART_H_
#define __LIBHY_HAL_INCLUDE_HY_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

typedef enum {
    HY_HAL_UART_0,
    HY_HAL_UART_1,
    HY_HAL_UART_2,
    HY_HAL_UART_3,
    HY_HAL_UART_4,
    HY_HAL_UART_5,

    HY_HAL_UART_MAX
} HyHalUartNum_t;

typedef struct {
    void (*read_cb)(char byte, void *args);
    void *args;
} HyHalUartConfigSave_t;

typedef struct {
    HyHalUartNum_t num;
    uint32_t    rate;

    HyHalUartConfigSave_t config_save;
} HyHalUartConfig_t;

void *HyHalUartCreate(HyHalUartConfig_t *uart_config);
void HyHalUartDestroy(void **handle);

int HyHalUartWrite(void *handle, void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif

