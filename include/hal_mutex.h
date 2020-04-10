/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_mutex.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/04 2020 17:43
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/04 2020      create the file
 * 
 *     last modified: 09/04 2020 17:43
 */
#ifndef __LIBHAL_INCLUDE_HAL_MUTEX_H_
#define __LIBHAL_INCLUDE_HAL_MUTEX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_type.h"

typedef void * ThreadMutexHandle_t;

ThreadMutexHandle_t HalMutexInit(void);
hal_int32_t HalMutexDestroy(ThreadMutexHandle_t handle);

hal_int32_t HalMutexLock(ThreadMutexHandle_t handle);
hal_int32_t HalMutexTryLock(ThreadMutexHandle_t handle);

hal_int32_t HalMutexUnLock(ThreadMutexHandle_t handle);

void *HalMutexGetLock(ThreadMutexHandle_t handle);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_MUTEX_H_

