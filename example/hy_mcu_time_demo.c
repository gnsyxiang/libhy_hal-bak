/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_mcu_time_test.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 20:39
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 20:39
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#include "hy_system.h"
#include "hy_uart.h"
#include "hy_time.h"
#include "hy_gpio.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_module.h"
#include "hy_utils/hy_mem.h"

#define ALONE_DEBUG 1

typedef struct {
    void    *system_handle;
    void    *uart_handle;
    void    *log_handle;
    void    *time_handle;
} _main_context_t;

static void _sys_tick_cb(void *args)
{
#if 1
    static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;
        LOGD("--------tick\n");
    }
#endif
}


static void _time_cb(void *args)
{
    LOGE("------------haha\n");
#if 0
    static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;
        LOGD("--time\n");
    }
#endif
}

static void _module_destroy(_main_context_t **context_pp)
{
    _main_context_t *context = *context_pp;

    // note: 增加或删除要同步到module_create_t中
    module_destroy_t module[] = {
        {"system",      &context->system_handle,    HySystemDestroy},
        {"debug uart",  &context->uart_handle,      HyUartDebugDestroy},
        {"log",         &context->log_handle,       HyLogDestroy},
        {"time",        &context->time_handle,      HyTimeDestroy},
    };

    RUN_DESTROY(module);

    HY_FREE(context_pp);
}

static _main_context_t *_module_create(void)
{
    _main_context_t *context = HY_MALLOC_RET_VAL(sizeof(*context), NULL);

    HySystemConfig_t system_config;
    system_config.config_save.sys_tick_cb   = _sys_tick_cb;
    system_config.config_save.args          = context;

    HyUartConfig_t uart_config;
    // uart_config.dev_name                = "/dev/ttyUSB1";
    uart_config.num                     = HY_UART_NUM_1;
    uart_config.rate                    = HY_UART_RATE_115200;
    uart_config.flow_control            = HY_UART_FLOW_CONTROL_NONE;
    uart_config.bits                    = HY_UART_BITS_8;
    uart_config.parity                  = HY_UART_PARITY_N;
    uart_config.stop                    = HY_UART_STOP_1;
    // uart_config.config_save.is_block    = HY_UART_BLOCK;
    // uart_config.config_save.read_cb     = _uart1_read_cb;
    // uart_config.config_save.args        = context;

    HyLogConfig_t log_config;
    log_config.buf_len                  = 256;
    log_config.level                    = HY_LOG_LEVEL_TRACE;
    log_config.config_file              = NULL;

    HyTimeConfig_t time_config;
    time_config.num                     = HY_TIME_NUM_2;
    time_config.us                      = 1000;
    time_config.flag                    = HY_TIME_FLAG_ENABLE;
    time_config.config_save.time_cb     = _time_cb;
    time_config.config_save.args        = context;

    // note: 增加或删除要同步到module_destroy_t中
    module_create_t module[] = {
        {"system",      &context->system_handle,    &system_config,     (create_t)HySystemCreate,       HySystemDestroy},
        {"debug uart",  &context->uart_handle,      &uart_config,       (create_t)HyUartDebugCreate,    HyUartDebugDestroy},
        {"log",         &context->log_handle,       &log_config,        (create_t)HyLogCreate,          HyLogDestroy},
        // {"time",        &context->time_handle,      &time_config,       (create_t)HyTimeCreate,         HyTimeDestroy},
    };

    RUN_CREATE(module);

    return context;
}

int main(int argc, char const* argv[])
{
    _main_context_t *context = _module_create();
    if (!context) {
        LOGE("_module_create faild \n");
        return -1;
    }

    LOGI("version: %s, date: %s, time: %s \n", VERSION, __DATE__, __TIME__);

    HyGpio_t gpio;
    gpio.group = HY_GPIO_GROUP_PD;
    gpio.pin = HY_GPIO_PIN_13;
    HyGpioSetOutput(&gpio, HY_GPIO_LEVEL_LOW);

    gpio.group = HY_GPIO_GROUP_PD;
    gpio.pin = HY_GPIO_PIN_14;
    HyGpioSetOutput(&gpio, HY_GPIO_LEVEL_LOW);

    gpio.group = HY_GPIO_GROUP_PD;
    gpio.pin = HY_GPIO_PIN_15;
    HyGpioSetOutput(&gpio, HY_GPIO_LEVEL_LOW);

    HyGpio_t key;
    key.group = HY_GPIO_GROUP_PA;
    key.pin = HY_GPIO_PIN_0;
    HyGpioSetInput(&key);

    while (1) {
        // if (HyGpioGetLevel(&key) == HY_GPIO_LEVEL_HIGH) {
            // HyGpioSetLevel(&gpio, HY_GPIO_LEVEL_HIGH);
        // } else {
            // HyGpioSetLevel(&gpio, HY_GPIO_LEVEL_LOW);
        // }
    }

    LOGI("version: %s, date: %s, time: %s \n", VERSION, __DATE__, __TIME__);

    while (1) {
#ifdef USE_SYSTICK_DELAY
        HySystemDelayS(1);
        LOGD("delay 1s\n");
#endif
    }

    _module_destroy(&context);

    return 0;
}

