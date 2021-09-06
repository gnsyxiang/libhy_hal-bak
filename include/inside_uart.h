/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    inside_uart.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/08 2021 19:19
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/08 2021      create the file
 * 
 *     last modified: 20/08 2021 19:19
 */
#ifndef __LIBHY_HAL_INCLUDE_INSIDE_UART_H_
#define __LIBHY_HAL_INCLUDE_INSIDE_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _HY_UART_NUM_2_STR(_buf, val)                               \
    ({                                                              \
     if      ((val) == HY_UART_NUM_0)   _buf = "HY_UART_NUM_0";     \
     else if ((val) == HY_UART_NUM_1)   _buf = "HY_UART_NUM_1";     \
     else if ((val) == HY_UART_NUM_2)   _buf = "HY_UART_NUM_2";     \
     else if ((val) == HY_UART_NUM_3)   _buf = "HY_UART_NUM_3";     \
     else if ((val) == HY_UART_NUM_4)   _buf = "HY_UART_NUM_4";     \
     else if ((val) == HY_UART_NUM_5)   _buf = "HY_UART_NUM_5";     \
     else if ((val) == HY_UART_NUM_6)   _buf = "HY_UART_NUM_6";     \
     else if ((val) == HY_UART_NUM_7)   _buf = "HY_UART_NUM_7";     \
     else                               _buf = "HY_UART_NUM_MAX";   \
     _buf;                                                          \
     })
#define HY_UART_NUM_2_STR(val) ({char *_buf = NULL; _HY_UART_NUM_2_STR(_buf, val);})

#ifdef __cplusplus
}
#endif

#endif

