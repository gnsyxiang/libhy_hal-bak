/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_gpio_int.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 20:22
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 20:22
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_GPIO_INT_H_
#define __LIBHY_HAL_INCLUDE_HY_GPIO_INT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hy_gpio.h"

typedef enum {
    HY_INT_TRIGGER_LEVEL_LOW,
    HY_INT_TRIGGER_LEVEL_HIGH,

    HY_INT_TRIGGER_EDGE_RISING,
    HY_INT_TRIGGER_EDGE_FALLING,
    HY_INT_TRIGGER_EDGE_BILATERAL,
} HyIntTriggerMode_t;

typedef struct {
    HyGpio_t gpio;
    void (*int_cb)(void *args);
    void *args;
} HyIntConfigSave_t;

typedef struct {
    HyIntConfigSave_t config_save;

    HyIntTriggerMode_t  trigger_mode;
} HyIntConfig_t;

void *HyIntCreate(HyIntConfig_t *int_config);
void HyIntDestroy(void **handle);

#ifdef __cplusplus
}
#endif

#endif

