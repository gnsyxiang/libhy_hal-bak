/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hy_time.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    22/02 2020 15:35
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        22/02 2020      create the file
 * 
 *     last modified: 22/02 2020 15:35
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_TIME_H_
#define __LIBHY_HAL_INCLUDE_HY_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "hy_type.h"


/**
 * @brief 在特定tick下，1s要多少个tick表示
 *
 * note: 默认1(tick) = 1(ms)，如果tick不是1ms，则需要修改tick个数
 */
#define HY_TIME_1S_REF_TICK (1000)

time_t HyTimeGetTick(void);

time_t HyTimeGetCurUs(void);
time_t HyTimeGetCurMs(void);

void HyTimeDelayMs(hy_uint32_t ms);

void HyTimeDelayUs(hy_uint32_t us);

#ifdef __cplusplus
}
#endif

#endif

