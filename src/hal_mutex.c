/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_mutex.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/04 2020 17:42
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/04 2020      create the file
 * 
 *     last modified: 09/04 2020 17:42
 */
#include "config.h"

#include "hal_mutex.h"
#include "hal_mem.h"
#include "hal_log.h"

#ifdef HAVE_LINUX_HAL
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
} hal_mutex_context_t;
#define HAL_MUTEX_CONTEXT_LEN (sizeof(hal_mutex_context_t))

static inline hal_mutex_context_t *_context_init(void)
{
    hal_mutex_context_t *context = Hal_calloc(1, HAL_MUTEX_CONTEXT_LEN);
    if (NULL == context) {
        HalLogE("hal calloc faild \n");
        return NULL;
    }
    return context;
}

static inline void _context_final(hal_mutex_context_t **context)
{
    if (NULL != *context) {
        Hal_free(*context);
        *context = NULL;
    }
}

ThreadMutexHandle_t HalMutexInit(void)
{
    hal_mutex_context_t *context = _context_init();
    if (NULL == context) {
        HalLogE("context init faild \n");
        return NULL;
    }

    pthread_mutex_init(&context->mutex, NULL);

    return context;
}

hal_int32_t HalMutexDestroy(ThreadMutexHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_mutex_context_t *context = handle;

    pthread_mutex_destroy(&context->mutex);

    return 0;
}

hal_int32_t HalMutexLock(ThreadMutexHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_mutex_context_t *context = handle;

    pthread_mutex_lock(&context->mutex);

    return 0;
}

hal_int32_t HalMutexTryLock(ThreadMutexHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_mutex_context_t *context = handle;

    pthread_mutex_trylock(&context->mutex);

    return 0;
}

hal_int32_t HalMutexUnLock(ThreadMutexHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the handle is NULL \n");
        return -1;
    }
    hal_mutex_context_t *context = handle;

    pthread_mutex_unlock(&context->mutex);

    return 0;
}
#endif

