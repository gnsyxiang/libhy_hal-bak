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

#include "hy_utils/hy_type.h"

/**
 * @brief 获取当前时间的微秒数
 *
 * @return 微秒数
 */
hy_uint64_t HyTimeGetCurrentTime2Us(void);

/**
 * @brief 获取相对上次时间的时间间隔
 *
 * @param us 微秒数
 *
 * @return 返回时间间隔微秒数
 */
hy_uint64_t HyTimeGetTimeInterval(hy_uint64_t us);

#ifdef __cplusplus
}
#endif

#endif

