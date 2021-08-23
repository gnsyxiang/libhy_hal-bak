/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_key.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2021 14:06
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2021      create the file
 * 
 *     last modified: 18/08 2021 14:06
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_KEY_H_
#define __LIBHY_HAL_INCLUDE_HY_KEY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hy_utils/hy_type.h"

#define HY_KEY_TICK_MS          (5)
#define HY_KEY_TICK_DEBOUNCE    (3)
#define HY_KEY_TICK_SHORT       (300 / HY_KEY_TICK_MS)
#define HY_KEY_TICK_LONG        (1000 / HY_KEY_TICK_MS)

typedef enum {
    HY_KEY_LEVEL_LOW,
    HY_KEY_LEVEL_HIGH,

    HY_KEY_LEVEL_MAX,
} HyKeyLevel_t;

typedef enum {
    HY_KEY_EVENT_DOWN,
    HY_KEY_EVENT_UP,
    HY_KEY_EVENT_REPEAT,

    HY_KEY_EVENT_CLICK_SINGLE,
    HY_KEY_EVENT_CLICK_DOUBLE,

    HY_KEY_EVENT_LONG_PRESS_START,
    HY_KEY_EVENT_LONG_PRESS_HOLD,

    HY_KEY_EVENT_MAX,
} HyKeyEvent_t;

typedef enum {
    HY_KEY_NUM_0,
    HY_KEY_NUM_1,
    HY_KEY_NUM_2,
    HY_KEY_NUM_3,
    HY_KEY_NUM_4,
    HY_KEY_NUM_5,
    HY_KEY_NUM_6,
    HY_KEY_NUM_7,

    HY_KEY_NUM_MAX,
} HyKeyNum_t;

typedef struct {
    void (*event_cb)(void *args);
    void *args;
} HyKeyEventCb_t;

typedef struct {
    HyKeyEvent_t event;
    HyKeyEventCb_t event_cb;
} HyKeyEventAdd_t;

typedef struct {
    HyKeyNum_t num;
    HyKeyLevel_t active_level;
    HyKeyLevel_t (*read_pin)(void *args);
    void *args;
} HyKeyConfig_t;

void *HyKeyCreate(void *config);
void HyKeyDestroy(void **handle);

void *HyKeyPinAssign(void *handle, HyKeyConfig_t *pin_config);
void HyKeyPinEventAttach(void *key_handle, HyKeyEventAdd_t *event_add);

/**
 * @brief 按键处理函数
 *
 * @param handle 句柄
 *
 * @note: 该函数放在5ms的定时回调中
 */
void HyKeyProcess(void *handle);

#ifdef __cplusplus
}
#endif

#endif

