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
#include "hal_config.h"
#include "hal_thread_internal.h"

typedef hal_int32_t (*hal_thread_init_t)(HalThreadConfig_t *config, hal_thread_context_t *context);
typedef void (*hal_thhread_final_t)(hal_thread_context_t *context);
typedef void (*hal_thread_param_t)(hal_thread_context_t *context, HalThreadParam_t type, void *args);

typedef struct {
    hal_thread_init_t   init;
    hal_thhread_final_t final;
    hal_thread_param_t  set;
    hal_thread_param_t  get;
} func_call_t;

#ifdef HAVE_RTT_HAL
static func_call_t g_func_call = {
    NULL, NULL, NULL, NULL
};
#endif

#ifdef HAVE_LINUX_HAL
#include "hal_linux_thread.h"
static func_call_t g_func_call = {
    HalLinuxThreadInit, HalLinuxThreadFinal, HalLinuxThreadParamSet, HalLinuxThreadParamGet
};
#endif

static inline hal_thread_context_t *_context_init(void)
{
    hal_thread_context_t *context = HalCalloc(1, sizeof(hal_thread_context_t));
    if (NULL == context) {
        HalLogE("hal calloc faild \n");
        return NULL;
    }
    return context;
}

static inline void _context_final(hal_thread_context_t *context)
{
    if (NULL != context) {
        HalFree(context);
    }
}

void *HalThreadInit(HalThreadConfig_t *config)
{
    hal_thread_context_t *context = _context_init();
    if (NULL == context) {
        HalLogE("context init faild \n");
        return NULL;
    }

    if (NULL != config->name) {
        hal_int32_t len = HalStrlen(config->name) < HAL_THREAD_NAME_MAX_LEN ?
                          HalStrlen(config->name) : HAL_THREAD_NAME_MAX_LEN;
        HalStrncpy(context->name, config->name, len);
        context->name[len] = '\0';
    }

    if (NULL != config->loop_config) {
        context->loop_config = *config->loop_config;
    }

    if (NULL == g_func_call.init) {
        HalLogE("init func is NULL \n");
        goto L_ERROR;
    }

    hal_int32_t ret = g_func_call.init(config, context);
    if (0 != ret) {
        HalLogE("call init faild \n");
        goto L_ERROR;
    }

    HalLogT("creat thread success \n");

    return context;
L_ERROR:
    _context_final(context);
    return NULL;
}

void HalThreadFinal(void *handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return ;
    }

    hal_thread_context_t *context = (hal_thread_context_t *)handle;

    if (NULL != g_func_call.final) {
        g_func_call.final(context);
    }

    _context_final(context);
}

static void _hal_thread_param_common(void *handle,
                                     HalThreadParam_t type,
                                     void *args,
                                     hal_thread_index_t index)
{
    if (NULL == handle) {
        HalLogE("the hal thread handle is NULL \n");
        return;
    }

    hal_thread_context_t *context = (hal_thread_context_t *) handle;

    if (HAL_THREAD_RUNNING != context->state) {
        HalLogE("can't set hal thread param with wrong state");
        return;
    }

    if (index == HAL_THREAD_INDEX_GET) {
        if (NULL != g_func_call.get) {
            return g_func_call.get(context, type, args);
        }
    } else {
        if (NULL != g_func_call.set) {
            return g_func_call.set(context, type, args);
        }
    }
}

void HalThreadParamSet(void *handle, HalThreadParam_t type, void *args)
{
    _hal_thread_param_common(handle, type, args, HAL_THREAD_INDEX_SET);
}

void HalThreadParamGet(void *handle, HalThreadParam_t type, void *args)
{
    _hal_thread_param_common(handle, type, args, HAL_THREAD_INDEX_GET);
}

