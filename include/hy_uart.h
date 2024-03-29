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

/**
 * @brief 打开该宏后，可以直接使用printf输出调试信息
 */
#define DEBUG_UART

typedef enum {
    HY_UART_NUM_0,
    HY_UART_NUM_1,
    HY_UART_NUM_2,
    HY_UART_NUM_3,
    HY_UART_NUM_4,
    HY_UART_NUM_5,
    HY_UART_NUM_6,
    HY_UART_NUM_7,
    HY_UART_NUM_8,

    HY_UART_NUM_MAX
} HyUartNum_t;

typedef enum {
    HY_UART_RATE_1200,
    HY_UART_RATE_2400,
    HY_UART_RATE_4800,
    HY_UART_RATE_9600,
    HY_UART_RATE_19200,
    HY_UART_RATE_38400,
    HY_UART_RATE_57600,
    HY_UART_RATE_115200,

    HY_UART_RATE_MAX,
} HyUartRate_t;

typedef enum {
    HY_UART_FLOW_CONTROL_NONE,
    HY_UART_FLOW_CONTROL_RTS,
    HY_UART_FLOW_CONTROL_CTS,
    HY_UART_FLOW_CONTROL_RTS_CTS,
} HyUartFlowControl_t;

typedef enum {
    HY_UART_BITS_5,
    HY_UART_BITS_6,
    HY_UART_BITS_7,
    HY_UART_BITS_8,
    HY_UART_BITS_9,

    HY_UART_BITS_MAX,
} HyUartBits_t;

typedef enum {
    HY_UART_PARITY_N,
    HY_UART_PARITY_O,
    HY_UART_PARITY_E,
} HyUartParity_t;

typedef enum {
    HY_UART_STOP_0_5,
    HY_UART_STOP_1,
    HY_UART_STOP_1_5,
    HY_UART_STOP_2,

    HY_UART_STOP_MAX,
} HyUartStop_t;

typedef enum {
    HY_UART_BLOCK,
    HY_UART_NONBLOCK,
} HyUartBlock_t;

typedef struct {
    HyUartBlock_t is_block;

    void (*read_cb)(void *buf, size_t len, void *args);
    void *args;
} HyUartConfigSave_t;

/**
 * @struct HyUartConfig_t
 *
 * @brief 串口配置结构体
 *
 * @note 注意linux和单片机的区别: \n
 *       dev_name只用于linux, \n
 *       num只用于单片机
 */
typedef struct {
    char                *dev_name;
    HyUartNum_t         num;

    HyUartRate_t        rate;
    HyUartFlowControl_t flow_control;

    HyUartBits_t        bits;
    HyUartParity_t      parity;
    HyUartStop_t        stop;

    HyUartConfigSave_t  config_save;
} HyUartConfig_t;

void *HyUartCreate(HyUartConfig_t *uart_config);
void HyUartDestroy(void **handle);

/**
 * @brief 过程处理函数
 *
 * @param handle 操作句柄
 *
 * @return -1表示出错
 *
 * @note 单片机未实现该函数，使用中断回调函数
 */
hy_s32_t HyUartProcess(void *handle);

hy_s32_t HyUartWrite(void *handle, void *buf, size_t len);

#ifdef DEBUG_UART
#define DEBUG_UART_NUM (HY_UART_NUM_1)
#define HyUartDebugCreate HyUartCreate
#define HyUartDebugDestroy HyUartDestroy
#endif

#ifdef __cplusplus
}
#endif

#endif

