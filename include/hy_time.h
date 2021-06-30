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

time_t HyTimeGetTick(void);

time_t HyTimeGetCurUs(void);

void HyTimeDelayMs(hy_uint32_t ms);

void HyTimeDelayUs(hy_uint32_t us);

#ifdef __cplusplus
}
#endif

#endif

