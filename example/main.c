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
static void _test_thread_loop(void *args)
{
    HalLogT("nihao \n");
    hal_int8_t *string = (hal_int8_t *)args;

    HalLogD("--------%s \n", string);
}

static hal_int8_t *test_string = "hello test string";

hal_int32_t main(hal_int32_t argc, const hal_int8_t *argv[])
{
    HalLogT("hello world \n");

    HalThreadLoopConfig_t   loop_config;
    loop_config.loop = _test_thread_loop;
    loop_config.args = test_string;

    HalThreadConfig_t hal_thread_config;
    hal_thread_config.name        = "test";
    hal_thread_config.stack_size  = STACK_NORMAL_SIZE;
    hal_thread_config.priority    = HAL_THREAD_PRIORITY_HIGH;
    hal_thread_config.loop_config = &loop_config;

    void *test_thead_handle = HalThreadCreate(&hal_thread_config);

    HalSleep(1);

    HalThreadDestroy(test_thead_handle);

    return 0;
}
#endif

