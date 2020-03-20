/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    thread.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/03 2020 16:55
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/03 2020      create the file
 * 
 *     last modified: 20/03 2020 16:55
 */
#include "config.h"
#include "hal_config.h"

#define STACK_SIZE                  (1024 * 1024 * 8)

static void _thread_test_loop(void *args)
{
    Hal_LogT("the str: %s \n", (hal_char *)args);
}

hal_int32_t main(hal_int32_t argc, const hal_int8_t *argv[])
{
    static hal_char *test_str = "test thread str";

    HalThreadLoopConfig_t loop_config;
    loop_config.args = test_str;
    loop_config.loop = _thread_test_loop;

    HalThreadConfig_t config;
    config.name         = "thread_test";
    config.stack_size   = STACK_SIZE;
    config.priority     = HAL_THREAD_PRIORITY_NORMAL;
    config.loop_config  = &loop_config;

    ThreadHandle_t handle = HalThreadCreate(&config);

    int cnt = 5;
    while (cnt-- > 0) {
        Hal_LogT("main loop \n");
        Hal_sleep(1);
    }

    HalThreadDestroy(handle);

    return 0;
}
