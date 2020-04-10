/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    producer_comsumer.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/04 2020 13:40
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/04 2020      create the file
 * 
 *     last modified: 10/04 2020 13:40
 */
#include "hal_log.h"
#include "hal_thread.h"
#include "hal_time.h"
#include "hal_mem.h"
#include "hal_assert.h"
#include "hal_mutex.h"
#include "hal_sem.h"
#include "hal_cond.h"

static ThreadMutexHandle_t mutex_handle;
static ThreadSemHandle_t sem_handle;
static ThreadCondHandle_t producer_exit_cond_handle;
static ThreadCondHandle_t consumer_exit_cond_handle;

static hal_int32_t cnt = 0;
static hal_int32_t is_running = 0;

static void _producer_loop(void *args)
{
    while (0 == is_running) {
        HalMutexLock(mutex_handle);
        cnt++;
        HalLogW("producer cnt: %d \n", cnt);
        HalMutexUnLock(mutex_handle);

        HalSemPost(sem_handle);
        Hal_sleep(1);
    }

    HalCondSignal(producer_exit_cond_handle);
}

static void _consumer_loop(void *args)
{
    while (0 == is_running) {
        HalSemWait(sem_handle);

        HalMutexLock(mutex_handle);
        HalLogW("-1-consumer cnt: %d \n", cnt);
        cnt--;
        HalLogW("-2-consumer cnt: %d \n", cnt);
        HalMutexUnLock(mutex_handle);
    }

    HalCondSignal(consumer_exit_cond_handle);
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

    sem_handle = HalSemInit(0, 0);

    mutex_handle = HalMutexInit();
    producer_exit_cond_handle = HalCondInit();
    consumer_exit_cond_handle = HalCondInit();

    ThreadHandle_t producer_handle = NULL;
    ThreadHandle_t consumer_handle = NULL;

    producer_handle = _create_thread("producer", _producer_loop, NULL);
    consumer_handle = _create_thread("consumer", _consumer_loop, NULL);

    int cnt = 3;
    while (cnt-- > 0) {
        Hal_sleep(1);
    }
    is_running = 1;
    hal_int32_t ret = 0;

    HalMutexLock(mutex_handle);
    ret = HalCondWait(producer_exit_cond_handle, mutex_handle, 3000);
    HalMutexUnLock(mutex_handle);

    HalSemPost(sem_handle);

    HalMutexLock(mutex_handle);
    ret = HalCondWait(consumer_exit_cond_handle, mutex_handle, 3000);
    HalMutexUnLock(mutex_handle);

    HalMutexDestroy(mutex_handle);
    HalCondDestroy(producer_exit_cond_handle);
    HalCondDestroy(consumer_exit_cond_handle);

    _destroy_thread(producer_handle);
    _destroy_thread(consumer_handle);

    HalSemDestroy(sem_handle);

    HalLogFinal();

    return 0;
}

