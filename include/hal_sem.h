/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_sem.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/03 2020 16:37
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/03 2020      create the file
 * 
 *     last modified: 10/03 2020 16:37
 */
#ifndef __LIBHAL_INCLUDE_HAL_SEM_H_
#define __LIBHAL_INCLUDE_HAL_SEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_type.h"

typedef void * ThreadSemHandle_t;

ThreadSemHandle_t HalSemInit(hal_int32_t pshared, hal_uint32_t value);
hal_int32_t HalSemDestroy(ThreadSemHandle_t handle);

hal_int32_t HalSemPost(ThreadSemHandle_t handle);
hal_int32_t HalSemWait(ThreadSemHandle_t handle);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_SEM_H_

