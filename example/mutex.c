/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    mutex.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/04 2020 17:46
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/04 2020      create the file
 * 
 *     last modified: 09/04 2020 17:46
 */
#include "hal_log.h"
#include "hal_thread.h"
#include "hal_time.h"
#include "hal_mem.h"
#include "hal_assert.h"
#include "hal_mutex.h"

static ThreadMutexHandle_t mutex_handle;

static void _producer_loop(void *args)
{
    while (1) {
        HalMutexLock(mutex_handle);
        HalLogW("producer loop \n");
        HalMutexUnLock(mutex_handle);
        Hal_sleep(1);
    }
}

static void _consumer_loop(void *args)
{
    while (1) {
        HalMutexLock(mutex_handle);
        HalLogE("consumer loop \n");
        HalMutexUnLock(mutex_handle);
        Hal_sleep(1);
    }
}

static ThreadHandle_t _create_thread(hal_char_t *name, HalThreadLoop_t loop, void *args)
{
    Hal_assert(NULL != name);
    Hal_assert(NULL != loop);

    HalThreadLoopConfig_t loop_config;
    Hal_memset(&loop_config, '\0', HAL_THREAD_LOOP_CONFIG_LEN);
    loop_config.loop = loop;
    loop_config.args = args;

    HalThreadConfig_t config;
    Hal_memset(&config, '\0', HAL_THREAD_CONFIG_LEN);
    config.name         = name;
    config.stack_size   = STACK_SIZE;
    config.priority     = HAL_THREAD_PRIORITY_NORMAL;
    config.loop_config  = &loop_config;

    return HalThreadCreate(&config);
}

static inline void _destroy_thread(ThreadHandle_t handle)
{
    Hal_assert(NULL != handle);

    HalThreadDestroy(handle);
}

hal_int32_t main(hal_int32_t argc, const hal_char_t *argv[])
{
    LogConfig_t log_config;
    log_config.level        = LOG_LEVEL_VERBOSE;
    log_config.color_flag   = LOG_COLOR_ON;
    log_config.buf_len      = 1024;

    HalLogInit(&log_config);

    mutex_handle = HalMutexInit();
    if (NULL == mutex_handle) {
        HalLogE("init mutex failed \n");
        goto L_MAIN_1;
    }

    ThreadHandle_t producer_handle = NULL;
    ThreadHandle_t consumer_handle = NULL;

    producer_handle = _create_thread("producer", _producer_loop, NULL);
    if (NULL == producer_handle) {
        HalLogE("create thread failed \n");
        goto L_MAIN_2;
    }

    consumer_handle = _create_thread("consumer", _consumer_loop, NULL);
    if (NULL == consumer_handle) {
        HalLogE("create thread failed \n");
        goto L_MAIN_3;
    }

    int cnt = 5;
    while (cnt-- > 0) {
        HalMutexLock(mutex_handle);
        HalLogT("main loop \n");
        HalMutexUnLock(mutex_handle);
        Hal_sleep(1);
    }

    _destroy_thread(producer_handle);
    _destroy_thread(consumer_handle);

    HalMutexDestroy(mutex_handle);

    HalLogFinal();

    return 0;
L_MAIN_3:
    _destroy_thread(producer_handle);
L_MAIN_2:
    HalMutexDestroy(mutex_handle);
L_MAIN_1:
    HalLogFinal();
    return -1;
}

