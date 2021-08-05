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

#include "hy_utils/hy_type.h"

typedef enum {
    HY_UART_0,
    HY_UART_1,
    HY_UART_2,
    HY_UART_3,
    HY_UART_4,
    HY_UART_5,

    HY_UART_MAX
} HyUartNum_t;

typedef enum {
    HY_RATE_1200,
    HY_RATE_2400,
    HY_RATE_4800,
    HY_RATE_9600,
    HY_RATE_19200,
    HY_RATE_38400,
    HY_RATE_57600,
    HY_RATE_115200,

    HY_RATE_MAX,
} HyUartRate_t;

typedef enum {
    HY_UART_FLOW_CONTROL_DISABLE,
    HY_UART_FLOW_CONTROL_HARD_ENABLE,
    HY_UART_FLOW_CONTROL_SOFT_ENABLE,
} HyUartFlowControl_t;

typedef enum {
    HY_UART_BITS_5,
    HY_UART_BITS_6,
    HY_UART_BITS_7,
    HY_UART_BITS_8,
} HyUartBits_t;

typedef enum {
    HY_UART_PARITY_N,
    HY_UART_PARITY_S,
    HY_UART_PARITY_O,
    HY_UART_PARITY_E,
} HyUartParity_t;

typedef enum {
    HY_UART_STOP_1,
    HY_UART_STOP_2,
} HyUartStop_t;

typedef struct {
    void (*read_cb)(void *buf, size_t len, void *args);
    void *args;
} HyUartConfigSave_t;

typedef struct {
    HyUartNum_t num;
    char *dev_name;

    HyUartRate_t rate;
    HyUartFlowControl_t flow_control;

    HyUartBits_t bits;
    HyUartParity_t parity;
    HyUartStop_t stop;

    HyUartConfigSave_t config_save;
} HyUartConfig_t;

void *HyUartCreate(HyUartConfig_t *uart_config);
void HyUartDestroy(void **handle);

hy_s32_t HyUartProcess(void *handle);
hy_s32_t HyUartWrite(void *handle, void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif

