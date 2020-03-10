/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_pthread.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/01 2020 21:01
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/01 2020      create the file
 * 
 *     last modified: 10/01 2020 21:01
 */
#ifndef __LIBHAL_INCLUDE_HAL_THREAD_H_
#define __LIBHAL_INCLUDE_HAL_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_config.h"

/* THREAD STACK SIZE */
#define STACK_SIZE                  (1024 * 1024 * 8)

#define STACK_SMALL_SIZE            STACK_SIZE * 1
#define STACK_NORMAL_SIZE           STACK_SIZE * 1
#define STACK_MIDDLE_SIZE           STACK_SIZE * 1
#define STACK_LARGE_SIZE            STACK_SIZE * 1

typedef enum {
    HAL_THREAD_PRIORITY_NORMAL,
    HAL_THREAD_PRIORITY_LOW,
    HAL_THREAD_PRIORITY_HIGH,
    HAL_THREAD_PRIORITY_REALTIME,
    HAL_THREAD_PRIORITY_IDLE,
} HalThreadPriority_t;

typedef enum {
    HAL_THREAD_PARAM_NAME,
    HAL_THREAD_PARAM_MAX,
} HalThreadParam_t;

typedef void (*HalThreadLoop_t)(void *args);

typedef struct {
    HalThreadLoop_t     loop;
    void                *args;
} HalThreadLoopConfig_t;
#define HAL_THREAD_LOOP_CONFIG_LEN (sizeof(HalThreadLoopConfig_t))

typedef struct HalThreadConfig {
    const hal_int8_t        *name;

    hal_uint32_t            stack_size;
    HalThreadPriority_t     priority;
    hal_uint32_t            tick;

    HalThreadLoopConfig_t   *loop_config;
} HalThreadConfig_t;
#define HAL_THREAD_CONFIG_LEN (sizeof(HalThreadConfig_t))

typedef void * ThreadHandle_t;

void *HalThreadCreate(HalThreadConfig_t *config);
void HalThreadDestroy(ThreadHandle_t handle);

hal_int32_t HalThreadParamSet(ThreadHandle_t handle, HalThreadParam_t type, void *args);
hal_int32_t HalThreadParamGet(ThreadHandle_t handle, HalThreadParam_t type, void *args);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_THREAD_H_

