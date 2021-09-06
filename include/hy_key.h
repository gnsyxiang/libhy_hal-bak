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

/**
 * @brief 按键处理函数调用的频率
 */
#define HY_KEY_TICK_MS              (5)

/**
 * @brief 按键去抖时间
 *
 * @note 去抖时间为: HY_KEY_TICK_MS * HY_KEY_TICK_DEBOUNCE_CNT
 */
#define HY_KEY_TICK_DEBOUNCE_CNT    (3)

/**
 * @brief 触发长按的最短时间
 *
 * @note 需要是HY_KEY_TICK_MS的倍数
 */
#define HY_KEY_TICK_MS_LONG         (1000)

/**
 * @enum HyKeyLevel_t
 * @brief 定义按键的高低电平
 */
typedef enum {
    HY_KEY_LEVEL_LOW,
    HY_KEY_LEVEL_HIGH,

    HY_KEY_LEVEL_MAX,
} HyKeyLevel_t;

/**
 * @enum HyKeyEvent_t
 * @brief 定义按键触发的事件
 */
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

typedef struct {
    void (*event_cb)(void *args);
    void *args;
} HyKeyEventCb_t;

typedef struct {
    HyKeyEvent_t event;
    HyKeyEventCb_t event_cb;
} HyKeyEventAdd_t;

typedef struct {
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
 * @note: 该函数放在HY_KEY_TICK_MS的定时回调中
 */
void HyKeyProcess(void *handle);

#ifdef __cplusplus
}
#endif

#endif

