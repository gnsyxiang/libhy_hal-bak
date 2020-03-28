/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    dl_lib.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    28/03 2020 16:24
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        28/03 2020      create the file
 * 
 *     last modified: 28/03 2020 16:24
 */
#include "hal_config.h"

#define LIBHAL_NAME     "install/lib/libhal.so"
#define STACK_SIZE      (1024 * 1024 * 8)

typedef void *(*HalThreadCreate_t)(HalThreadConfig_t *config);
typedef void  (*HalThreadDestroy_t)(ThreadHandle_t handle);

static void _thread_test_loop(void *args)
{
    Hal_LogT("the str: %s \n", (hal_char_t *)args);
}

static void *_create_thread(DLLibHandle_t handle)
{
    HalThreadCreate_t hal_thread_create = NULL;
    hal_thread_create = HalDllLoadSymbol(handle, SYMBOL_NAME(HalThreadCreate));
    if (NULL == hal_thread_create) {
        Hal_LogE("HalDllLoadSymbol symbol[%s] failed \n", SYMBOL_NAME(HalThreadCreate));
        return NULL;
    }

    static hal_char_t *test_str = "test thread str";

    HalThreadLoopConfig_t loop_config;
    loop_config.args = test_str;
    loop_config.loop = _thread_test_loop;

    HalThreadConfig_t config;
    config.name         = "thread_test";
    config.stack_size   = STACK_SIZE;
    config.priority     = HAL_THREAD_PRIORITY_NORMAL;
    config.loop_config  = &loop_config;

    return hal_thread_create(&config);
}

static void _destroy_thread(DLLibHandle_t handle, ThreadHandle_t thread_handle)
{
    HalThreadDestroy_t hal_thread_destroy = NULL;
    hal_thread_destroy = HalDllLoadSymbol(handle, SYMBOL_NAME(HalThreadDestroy));
    if (NULL == hal_thread_destroy) {
        Hal_LogE("HalDllLoadSymbol failed \n");
    }

    hal_thread_destroy(thread_handle);
}

hal_int32_t main(hal_int32_t argc, const hal_char_t *argv[])
{
    DLLibHandle_t handle = HalDllibOpen(LIBHAL_NAME);
    if (NULL == handle) {
        Hal_LogE("HalDllibOpen failed \n");
        return -1;
    }
    ThreadHandle_t thread_handle = _create_thread(handle);

    hal_uint32_t cnt = 5;
    while (cnt-- > 0) {
        Hal_LogT("main loop \n");
        Hal_sleep(1);
    }

    _destroy_thread(handle, thread_handle);
    HalDllibExit(handle);

    return 0;
}

