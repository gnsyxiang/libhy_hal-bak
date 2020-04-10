/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_cond.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/04 2020 09:43
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/04 2020      create the file
 * 
 *     last modified: 10/04 2020 09:43
 */
#ifndef __LIBHAL_INCLUDE_HAL_COND_H_
#define __LIBHAL_INCLUDE_HAL_COND_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_type.h"

typedef void *ThreadCondHandle_t;

ThreadCondHandle_t HalCondInit(void);
hal_int32_t HalCondDestroy(ThreadCondHandle_t handle);

hal_int32_t HalCondSignal(ThreadCondHandle_t handle);
hal_int32_t HalCondBroadcast(ThreadCondHandle_t handle);
hal_int32_t HalCondWait(ThreadCondHandle_t handle);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_COND_H_

