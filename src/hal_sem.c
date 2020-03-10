/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_sem.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/03 2020 16:37
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/03 2020      create the file
 * 
 *     last modified: 10/03 2020 16:37
 */
#include "config.h"
#include "hal_config.h"

#ifdef HAVE_LINUX_HAL
#include <semaphore.h>

typedef struct {
    sem_t sem;
} hal_sem_context_t; 
#define HAL_SEM_CONTEXT_LEN (sizeof(hal_sem_context_t))

static hal_sem_context_t *_context_init(void)
{
    hal_sem_context_t *context = Hal_calloc(1, HAL_SEM_CONTEXT_LEN);
    if (NULL == context) {
        Hal_LogE("hal calloc faild \n");
        return NULL;
    }
    return context;
}

static inline void _context_final(hal_sem_context_t **context)
{
    if (NULL != *context) {
        Hal_free(*context);
        *context = NULL;
    }
}

ThreadSemHandle_t HalSemInit(hal_int32_t pshared, hal_uint32_t value)
{
    hal_sem_context_t *context = _context_init();
    if (NULL == context) {
        Hal_LogE("context init faild \n");
        return NULL;
    }

    sem_init(&context->sem, pshared, value);

    return context;
}

hal_int32_t HalSemDestroy(ThreadSemHandle_t handle)
{
    Hal_assert(NULL == handle);
    hal_sem_context_t *context = (hal_sem_context_t *)handle;

    sem_destroy(&context->sem);

    _context_final(&context);

    return HAL_NO_ERR;
}

hal_int32_t HalSemPost(ThreadSemHandle_t handle)
{
    Hal_assert(NULL == handle);
    hal_sem_context_t *context = (hal_sem_context_t *)handle;

    sem_post(&context->sem);

    return HAL_NO_ERR;
}

hal_int32_t HalSemWait(ThreadSemHandle_t handle)
{
    Hal_assert(NULL == handle);
    hal_sem_context_t *context = (hal_sem_context_t *)handle;

    sem_wait(&context->sem);

    return HAL_NO_ERR;
}
#endif

