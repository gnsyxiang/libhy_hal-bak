/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_timer.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    23/08 2021 16:56
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        23/08 2021      create the file
 * 
 *     last modified: 23/08 2021 16:56
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_TIMER_H_
#define __LIBHY_HAL_INCLUDE_HY_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hy_utils/hy_type.h"

typedef enum {
    HY_TIMER_FLAG_DISABLE,
    HY_TIMER_FLAG_ENABLE,

    HY_TIMER_FLAG_MAX,
} HyTimerFlag_t;

typedef struct {
    HyTimerFlag_t flag;
    HyTimerFlag_t repeat_flag;
    hy_u32_t expired_ms;
    hy_u32_t cur_tick;
    void (*timer_cb)(void *timer_handle, void *args);
    void *args;
} HyTimerConfig_t;

void *HyTimerCreate(void *config);
void HyTimerDestroy(void **handle);

void *HyTimerAdd(void *handle, HyTimerConfig_t *timer_config);
void HyTimerDel(void *handle, void *timer_handle);

void HyTimerStart(void *timer_handle);
void HyTimerStop(void *timer_handle);

void HyTimerProcess(void *handle);
void HyTimerTickUpdate(void *handle, hy_u32_t ms);

#ifdef __cplusplus
}
#endif

#endif

