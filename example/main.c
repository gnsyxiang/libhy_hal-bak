/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    main.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/12 2019 20:41
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/12 2019      create the file
 * 
 *     last modified: 17/12 2019 20:41
 */
#include "config.h"
#include "hal_config.h"

#ifdef HAVE_RTT_HAL
hal_int32_t main(hal_int32_t argc, const hal_int8_t *argv[])
{
    return 0;
}
#endif

#ifdef HAVE_LINUX_HAL
static void _producer_thread_loop(void *args)
{
    while (1) {
        Hal_sleep(1);
    }
}

static void _consumer_thread_loop(void *args)
{
    while (1) {
        Hal_sleep(1);
    }
}

hal_int32_t main(hal_int32_t argc, const hal_int8_t *argv[])
{
    HalThreadLoopConfig_t   loop_config;
    HalThreadConfig_t       thread_config;

    Hal_memset(&loop_config, '\0', HAL_THREAD_LOOP_CONFIG_LEN);
    loop_config.loop = _producer_thread_loop;

    Hal_memset(&thread_config, '\0', HAL_THREAD_CONFIG_LEN);
    thread_config.name        = "producer";
    thread_config.stack_size  = STACK_NORMAL_SIZE;
    thread_config.priority    = HAL_THREAD_PRIORITY_HIGH;
    thread_config.loop_config = &loop_config;

    void *producer_thread_handle = HalThreadCreate(&thread_config);

    loop_config.loop = _consumer_thread_loop;
    thread_config.name        = "consumer";

    void *consumer_thread_handle = HalThreadCreate(&thread_config);

    Hal_LogT("main while \n");

    while (1) {
        Hal_sleep(1);
    }

    HalThreadDestroy(producer_thread_handle);
    HalThreadDestroy(consumer_thread_handle);

    return 0;
}
#endif

