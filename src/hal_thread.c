/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_thread.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/01 2020 16:51
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/01 2020      create the file
 * 
 *     last modified: 20/01 2020 16:51
 */
#include "config.h"
#include "hal_config.h"

#ifdef HAVE_RTT_HAL
#include "hal_rtt_thread.h"
#endif
#ifdef HAVE_LINUX_HAL
#include "hal_linux_thread.h"
#endif

static hal_system_init_cb_t g_system_cb;
static hal_int32_t g_init_flag = 0;

static inline hal_thread_context_t *_context_init(void)
{
    hal_thread_context_t *context = Hal_calloc(1, HAL_THREAD_CONTEXT_LEN);
    if (NULL == context) {
        HalLogE("hal calloc faild \n");
        return NULL;
    }
    return context;
}

static inline void _context_final(hal_thread_context_t **context)
{
    if (NULL != *context) {
        Hal_free(*context);
        *context = NULL;
    }
}

void *HalThreadCreate(HalThreadConfig_t *config)
{
    Hal_assert(NULL != config);

    if (0 == g_init_flag) {
        g_init_flag = 1;
        ThreadSystemInit(&g_system_cb);
    }

    hal_thread_context_t *context = _context_init();
    if (NULL == context) {
        HalLogE("context init faild \n");
        goto L_ERROR_INIT_1;
    }

    if (NULL != config->name) {
        hal_int32_t len = Hal_strlen(config->name) < HAL_THREAD_NAME_MAX_LEN ?
                          Hal_strlen(config->name) : HAL_THREAD_NAME_MAX_LEN;
        Hal_strncpy(context->name, config->name, len);
        context->name[len] = '\0';
    }
    if (NULL != config->loop_config) {
        context->loop_config = *config->loop_config;
    }
    context->config = config;

    if (NULL == g_system_cb.create || 0 != g_system_cb.create(context)) {
        HalLogE("call init faild \n");
        goto L_ERROR_INIT_2;
    }

    HalLogT("creat %s thread success \n", context->name);

    return context;
L_ERROR_INIT_2:
    _context_final(&context);
L_ERROR_INIT_1:
    return NULL;
}

void HalThreadDestroy(ThreadHandle_t handle)
{
    Hal_assert(NULL != handle);

    hal_thread_context_t *context = (hal_thread_context_t *)handle;

    if (NULL == g_system_cb.destroy || 0 != g_system_cb.destroy(context)) {
        HalLogE("call final faild \n");
    }

    _context_final(&context);
}

static hal_int32_t _hal_thread_param_common(ThreadHandle_t handle,
                                            HalThreadParam_t type,
                                            void *args,
                                            hal_thread_index_t index)
{
    Hal_assert(NULL != handle);

    hal_thread_context_t *context = (hal_thread_context_t *) handle;

    if (HAL_THREAD_RUNNING != context->state) {
        HalLogE("can't set hal thread param with wrong state");
        return HAL_INVALID_STATE_ERR;
    }

    if (index == HAL_THREAD_INDEX_GET) {
        if (NULL == g_system_cb.get || 0 != g_system_cb.get(context, type, args)) {
            HalLogE("call get faild \n");
            return HAL_INVALID_HANDLE_ERR;
        }
    } else {
        if (NULL == g_system_cb.set || 0 != g_system_cb.set(context, type, args)) {
            HalLogE("call set faild \n");
            return HAL_INVALID_HANDLE_ERR;
        }
    }
    return HAL_NO_ERR;
}

hal_int32_t HalThreadParamSet(ThreadHandle_t handle, HalThreadParam_t type, void *args)
{
    return _hal_thread_param_common(handle, type, args, HAL_THREAD_INDEX_SET);
}

hal_int32_t HalThreadParamGet(ThreadHandle_t handle, HalThreadParam_t type, void *args)
{
    return _hal_thread_param_common(handle, type, args, HAL_THREAD_INDEX_GET);
}

