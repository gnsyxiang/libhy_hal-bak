/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_key.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    21/08 2021 17:08
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        21/08 2021      create the file
 * 
 *     last modified: 21/08 2021 17:08
 */
#include <stdio.h>

#include "hy_key.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_list.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HyKeyConfig_t       key;
    HyKeyEventCb_t      cb[HY_KEY_EVENT_MAX];
    struct list_head    list;
} _key_config_t;

typedef struct {
    struct list_head    list;

    hy_u8_t             tick;
    hy_u8_t             state;
    hy_u8_t             repeat;
    hy_u8_t             debounce_cnt;
    HyKeyLevel_t        active_level;
    HyKeyLevel_t        button_level;
} _key_context_t;

void *HyKeyPinAssign(void *handle, HyKeyConfig_t *key_config)
{
    HY_ASSERT_NULL_RET_VAL(!handle || !key_config, NULL);

    _key_context_t *context = handle;
    do {
        _key_config_t *key = (_key_config_t *)HY_MALLOC_BREAK(sizeof(*key));
        HY_MEMCPY(&key->key, key_config);

        list_add_tail(&key->list, &context->list);

        return key;
    } while (0);

    return NULL;
}

void HyKeyPinEventAttach(void *key_handle, HyKeyEventAdd_t *event_add)
{
    HY_ASSERT_NULL_RET(!key_handle || !event_add);

    _key_config_t *key = key_handle;

    HY_MEMCPY(&key->cb[event_add->event], &event_add->event_cb);
}

#define _EVENT_KEY_CB(event)                        \
    if (key_config->cb[event].event_cb) {           \
        key_config->cb[event].event_cb(key->args);  \
    }

static void _key_process_com(_key_context_t *context, _key_config_t *key_config)
{
    HyKeyConfig_t *key = &key_config->key;
    HyKeyLevel_t level;

    // 获取电平
    if (key->read_pin) {
        level = key->read_pin(key->args);
    } else {
        return ;
    }

    // 电平跟随，去抖处理
    if (level != context->button_level) {
        if (++context->debounce_cnt >= HY_KEY_TICK_DEBOUNCE) {
            context->button_level = level;
            context->debounce_cnt = 0;
        }
    } else {
        context->debounce_cnt = 0;
    }

    if (context->state > 0) {
        context->tick++;
    }

    switch (context->state) {
        case 0:
            if (context->button_level == key->active_level) {   // 按下
                _EVENT_KEY_CB(HY_KEY_EVENT_DOWN);
                context->tick = 0;
                context->state = 1;
                context->repeat = 1;
            }
            break;
        case 1:
            if (context->button_level != key->active_level) {   // 松开
                _EVENT_KEY_CB(HY_KEY_EVENT_UP);
                context->tick = 0;
                context->state = 2;
            } else if (context->tick > HY_KEY_TICK_LONG) {      // 长按
                _EVENT_KEY_CB(HY_KEY_EVENT_LONG_PRESS_START);
                context->state = 5;
            }
            break;
        case 2:
            if (context->button_level == key->active_level) {   // 再次按下
                _EVENT_KEY_CB(HY_KEY_EVENT_DOWN);
                context->repeat++;
                _EVENT_KEY_CB(HY_KEY_EVENT_REPEAT);
                context->tick = 0;
                context->state = 3;
            } else if (context->tick > HY_KEY_TICK_SHORT) {
                if (context->repeat == 1) {
                    _EVENT_KEY_CB(HY_KEY_EVENT_CLICK_SINGLE);   // 单击
                } else if (context->repeat == 2) {
                    _EVENT_KEY_CB(HY_KEY_EVENT_CLICK_DOUBLE);   // 双击
                } else {
                    LOGI("multiple clicks \n");
                }
                context->state = 0;
            }
            break;
        case 3:
            if (context->button_level != key->active_level) {   // 松开
                _EVENT_KEY_CB(HY_KEY_EVENT_UP);
                if (context->tick < HY_KEY_TICK_SHORT) {
                    context->tick = 0;
                    context->state = 2;
                } else {
                    context->state = 0;
                }
            }
            break;
        case 5:
            if (context->button_level == key->active_level) {   // 按下
                _EVENT_KEY_CB(HY_KEY_EVENT_LONG_PRESS_HOLD);    // 长按保持
            } else {
                _EVENT_KEY_CB(HY_KEY_EVENT_UP);
                context->state = 0;
            }
        default:
            break;
    }
}

void HyKeyProcess(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _key_context_t *context = handle;

    _key_config_t *pos;
    list_for_each_entry(pos, &context->list, list) {
        _key_process_com(context, pos);
    }
}

void HyKeyDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    HY_FREE(handle);
}

void *HyKeyCreate(void *config)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    _key_context_t *context = NULL;

    do {
        context = (_key_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        INIT_LIST_HEAD(&context->list);

        return context;
    } while (0);

    HyKeyDestroy((void **)&context);
    return NULL;
}

