/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_timer.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    23/08 2021 17:05
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        23/08 2021      create the file
 * 
 *     last modified: 23/08 2021 17:05
 */
#include <stdio.h>

#include "hy_timer.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_list.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HyTimerConfig_t     timer;
    struct list_head    list;
} _timer_list_t;

typedef struct {
    hy_u32_t            tick;
    hy_u32_t            timer_tick;
    struct list_head    list;
} _timer_context_t;

void HyTimerStart(void *timer_handle)
{

}

void HyTimerStop(void *timer_handle)
{
    HY_ASSERT_NULL_RET(!timer_handle);

    _timer_list_t *timer_list = timer_handle;

    timer_list->timer.repeat_flag = HY_TIMER_FLAG_DISABLE;
}

void *HyTimerAdd(void *handle, HyTimerConfig_t *timer_config)
{
    HY_ASSERT_NULL_RET_VAL(!handle || !timer_config, NULL);
    _timer_context_t *context = handle;

    do {
        _timer_list_t *timer_list = (_timer_list_t *)HY_MALLOC_BREAK(sizeof(*timer_list));
        HY_MEMCPY(&timer_list->timer, timer_config);

        timer_list->timer.cur_tick = context->tick;
        list_add_tail(&timer_list->list, &context->list);

        return timer_list;
    } while (0);

    return NULL;
}

void HyTimerDel(void *handle, void *timer_handle)
{
    HY_ASSERT_NULL_RET(!handle || !timer_handle);

    _timer_context_t *context = handle;

    _timer_list_t *pos, *n;
    list_for_each_entry_safe(pos, n, &context->list, list) {
        if (pos == timer_handle) {
            list_del(&pos->list);
            HY_FREE(&pos);

            break;
        }
    }
}

void HyTimerTickUpdate(void *handle, hy_u32_t ms)
{
    HY_ASSERT_NULL_RET(!handle);

    _timer_context_t *context = handle;

    context->tick += ms;
}

void HyTimerProcess(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _timer_context_t *context = handle;

    _timer_list_t *pos, *n;
    list_for_each_entry_safe(pos, n, &context->list, list) {
        HyTimerConfig_t *timer = &pos->timer;
        if (context->tick - timer->cur_tick >= timer->expired_ms) {
            if (timer->timer_cb) {
                timer->timer_cb(timer, timer->args);
            }
            if (timer->repeat_flag == HY_TIMER_FLAG_DISABLE) {
                list_del(&pos->list);
                HY_FREE(&pos);
            } else {
                timer->cur_tick = context->tick;
            }
        }
    }
}

void HyTimerDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    _timer_context_t *context = *handle;

    _timer_list_t *pos, *n;
    list_for_each_entry_safe(pos, n, &context->list, list) {
        list_del(&pos->list);

        HY_FREE(&pos);
    }

    HY_FREE(handle);
}

void *HyTimerCreate(void *config)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    _timer_context_t *context = NULL;

    do {
        context = (_timer_context_t*)HY_MALLOC_BREAK(sizeof(*context));

        INIT_LIST_HEAD(&context->list);

        return context;
    } while (0);

    HyTimerDestroy((void **)&context);
    return NULL;
}

