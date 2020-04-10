/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_cond.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/04 2020 09:43
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/04 2020      create the file
 * 
 *     last modified: 10/04 2020 09:43
 */
#include "hal_cond.h"

#ifdef HAVE_LINUX_HAL
#include <pthread.h>

typedef struct {
    pthread_cond_t cond;
} hal_cond_context_t;
#define HAL_COND_CONTEXT_LEN (sizeof(hal_cond_context_t))

static inline hal_cond_context_t *_context_init(void)
{
    hal_cond_context_t *context = Hal_calloc(1, HAL_COND_CONTEXT_LEN);
    if (NULL == context) {
        HalLogE("hal calloc faild \n");
        return NULL;
    }
    return context;
}

static inline void _context_final(hal_cond_context_t **context)
{
    if (NULL != *context) {
        Hal_free(*context);
        *context = NULL;
    }
}

ThreadCondHandle_t HalCondInit(void)
{
    hal_cond_context_t *context = _context_init();
    if (NULL == context) {
        HalLogE("context init faild \n");
        return NULL;
    }

    pthread_cond_init(&context->cond, NULL);

    return context;
}

hal_int32_t HalCondDestroy(ThreadCondHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_cond_context_t *context = handle;

    pthread_mutex_destroy(&context->cond);

    return 0;
}

hal_int32_t HalCondSignal(ThreadCondHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_cond_context_t *context = handle;

    pthread_cond_signal(&context->cond);

    return 0;
}

hal_int32_t HalCondBroadcast(ThreadCondHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_cond_context_t *context = handle;

    pthread_cond_broadcast(&context->cond);

    return 0;
}

hal_int32_t HalCondWait(ThreadCondHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_cond_context_t *context = handle;

    pthread_cond_wait(&context->cond);

    return 0;
}
#endif
