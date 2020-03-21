/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_rtt_thread.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    27/02 2020 18:13
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        27/02 2020      create the file
 * 
 *     last modified: 27/02 2020 18:13
 */
#include "hal_config.h"
#include "hal_rtt_thread.h"

static void _loop_wrapper(void *args)
{
    hal_thread_context_t *context = (hal_thread_context_t *)args;

    if (NULL != context->loop_config.loop) {
        context->loop_config.loop(context->loop_config.args);
    }
    context->id = RT_NULL;
}

hal_int32_t RTTThreadCreate(void *args)
{
    hal_thread_context_t *context = args;

    hal_int32_t sched_priority[][2] = {
        {HAL_THREAD_PRIORITY_NORMAL,    RT_THREAD_PRIORITY_MAX - 4},
        {HAL_THREAD_PRIORITY_LOW,       RT_THREAD_PRIORITY_MAX - 3},
        {HAL_THREAD_PRIORITY_HIGH,      RT_THREAD_PRIORITY_MAX - 5},
        {HAL_THREAD_PRIORITY_REALTIME,  0},
        {HAL_THREAD_PRIORITY_IDLE,      RT_THREAD_PRIORITY_MAX - 2},
    };

    if (context->config->tick == 0) {
        context->config->tick = 5;
    }
    context->id = rt_thread_create(context->config->name,
                                   _loop_wrapper, (void *)context,
                                   context->config->stack_size,
                                   sched_priority[context->config->priority][1],
                                   context->config->tick);
    if (RT_NULL == context->id) {
        return HAL_THREAD_ERR;
    }
    rt_thread_startup(context->id);

    return HAL_NO_ERR;
}

hal_int32_t RTTThreadDestroy(void *args)
{
    hal_thread_context_t *context = args;
    rt_err_t ret = RT_EOK;
    if (RT_NULL != context->id) {
        ret = rt_thread_delete(context->id);
    }
    return ret;
}

hal_int32_t RTTThreadParamSet(void *context, hal_int32_t type, void *args)
{
    return 0;
}

hal_int32_t RTTThreadParamGet(void *context, hal_int32_t type, void *args)
{
    return 0;
}

void ThreadSystemInit(hal_system_init_cb_t *system_cb)
{
    Hal_assert(NULL != system_cb);

    system_cb->create  = RTTThreadCreate;
    system_cb->destroy = RTTThreadDestroy;
    system_cb->get     = RTTThreadParamGet;
    system_cb->set     = RTTThreadParamSet;
}

