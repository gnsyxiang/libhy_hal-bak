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

#include <stdio.h>
#include <stdint.h>

#include "hy_utils/hy_type.h"

typedef enum {
    HY_TIME_0,
    HY_TIME_1,
    HY_TIME_2,
    HY_TIME_3,
    HY_TIME_4,
    HY_TIME_5,
    HY_TIME_6,
    HY_TIME_7,

    HY_TIME_SYSTICK,

    HY_TIME_MAX,
} HyTimeNum_t;

typedef enum {
    HY_TIME_DISABLE,
    HY_TIME_ENABLE,
} HytimeFlag_t;

typedef struct {
    void (*time_cb)(void *args);
    void *args;
} HyTimeConfigSave_t;

typedef struct {
    HyTimeConfigSave_t  config_save;

    HyTimeNum_t         num;
    uint32_t            us;
    HytimeFlag_t        flag;
} HyTimeConfig_t;

void *HyTimeCreate(HyTimeConfig_t *time_config);
void HyTimeDestroy(void **handle);

void HyTimeEnable(void *handle);
void HyTimeDisable(void *handle);

#if 0
#include <stdio.h>
#include <sys/time.h>

/**
 * @brief 在特定tick下，1s要多少个tick表示
 *
 * note: 默认1(tick) = 1(ms)，如果tick不是1ms，则需要修改tick个数
 */
#define HY_TIME_1S_REF_TICK (1000)

time_t HyTimeGetTick(void);

time_t HyTimeGetCurUs(void);
time_t HyTimeGetCurMs(void);
#endif

void HyTimeDelayMs(size_t ms);

void HyTimeDelayUs(size_t us);

#ifdef __cplusplus
}
#endif

#endif

