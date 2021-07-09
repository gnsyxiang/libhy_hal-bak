/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    time_wrapper.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    30/06 2021 17:28
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        30/06 2021      create the file
 * 
 *     last modified: 30/06 2021 17:28
 */
#ifndef __LIBHY_HAL_INCLUDE_WRAPPER_TIME_WRAPPER_H_
#define __LIBHY_HAL_INCLUDE_WRAPPER_TIME_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "hy_type.h"

time_t time_get_tick(void);

time_t time_get_cur_us(void);

time_t time_get_cur_ms(void);

void time_delay_ms(hy_uint32_t ms);

void time_delay_us(hy_uint32_t us);

#ifdef __cplusplus
}
#endif

#endif

