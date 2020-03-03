/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_time.h
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
#ifndef __LIBHAL_INCLUDE_HAL_TIME_H_
#define __LIBHAL_INCLUDE_HAL_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_config.h"

hal_uint32_t Hal_sleep(hal_uint32_t seconds);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_TIME_H_

