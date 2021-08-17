/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_system.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 20:33
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 20:33
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_SYSTEM_H_
#define __LIBHY_HAL_INCLUDE_HY_SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

typedef struct {
    void (*sys_tick_cb)(void *args);
    void *args;
} HySystemConfigSave_t;

typedef struct {
    HySystemConfigSave_t config_save;
} HySystemConfig_t;

void *HySystemCreate(HySystemConfig_t *system_config);
void HySystemDestroy(void **handle);

// #define USE_SYSTICK_DELAY

#ifdef USE_SYSTICK_DELAY
void HySystemDelayUs(uint32_t us);
void HySystemDelayMs(uint32_t ms);
void HySystemDelayS(uint32_t s);
#endif

#ifdef __cplusplus
}
#endif

#endif

