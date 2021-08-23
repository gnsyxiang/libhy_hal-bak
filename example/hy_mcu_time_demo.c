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
#include "hy_key.h"
#include "hy_timer.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_module.h"
#include "hy_utils/hy_mem.h"

#define ALONE_DEBUG 1

typedef struct {
    void    *system_handle;
    void    *debug_uart_handle;
    void    *log_handle;
    void    *time_handle;
    void    *key_handle;
    void    *timer_handle;

    HyGpio_t red_led;
    HyGpio_t key_gpio;
} _main_context_t;

static void _sys_tick_cb(void *args)
{
#if 0
    static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;
        LOGD("--------tick\n");
    }
#endif
}


static void _time_cb(void *args)
{
    _main_context_t *context = args;

    HyTimerTickUpdate(context->timer_handle, 1);

    static int cnt_5ms = 0;
    if (cnt_5ms++ == 5) {
        cnt_5ms = 0;

        HyKeyProcess(context->key_handle);
    }

#if 1
    static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;

        // LOGE("--haha\n");
        // HyGpioSetLevelToggle(&context->red_led);
    }
#endif
}

static void _gpio_init(_main_context_t *context)
{
    HyGpio_t *gpio = NULL;

    gpio = &context->red_led;
    gpio->group = HY_GPIO_GROUP_PD;
    gpio->pin = HY_GPIO_PIN_13;
    HyGpioSetOutput(gpio, HY_GPIO_LEVEL_HIGH);

    gpio = &context->key_gpio;
    gpio->group = HY_GPIO_GROUP_PA;
    gpio->pin = HY_GPIO_PIN_0;
    HyGpioSetInput(gpio);
}

static HyKeyLevel_t _read_key_pin_cb(void *args)
{
    _main_context_t *context = args;

    return (HyKeyLevel_t)HyGpioGetLevel(&context->key_gpio);
}

static void _key_num_0_down_cb(void *args)
{
    LOGE("---down \n");
}

static void _key_num_0_up_cb(void *args)
{
    LOGE("---up \n");
}

static void _key_num_0_repeat_cb(void *args)
{
    LOGE("---repeat \n");
}

static void _key_num_0_click_single_cb(void *args)
{
    LOGE("---click signal \n");
}

static void _key_num_0_click_double_cb(void *args)
{
    LOGE("---click double \n");
}

static void _key_num_0_long_start_cb(void *args)
{
    LOGE("---long start \n");
}

static void _key_num_0_long_hold_cb(void *args)
{
    LOGE("---long hole\n");
}

static void _key_init(_main_context_t *context)
{
    HyKeyConfig_t pin_config;
    pin_config.active_level = HY_KEY_LEVEL_HIGH;
    pin_config.read_pin     = _read_key_pin_cb;
    pin_config.args         = context;
    void *key_handle = HyKeyPinAssign(context->key_handle, &pin_config);

    HyKeyEventAdd_t event_add[] = {
        {HY_KEY_EVENT_DOWN,             {_key_num_0_down_cb,            context}},
        {HY_KEY_EVENT_UP,               {_key_num_0_up_cb,              context}},
        {HY_KEY_EVENT_REPEAT,           {_key_num_0_repeat_cb,          context}},
        {HY_KEY_EVENT_CLICK_SINGLE,     {_key_num_0_click_single_cb,    context}},
        {HY_KEY_EVENT_CLICK_DOUBLE,     {_key_num_0_click_double_cb,    context}},
        {HY_KEY_EVENT_LONG_PRESS_START, {_key_num_0_long_start_cb,      context}},
        {HY_KEY_EVENT_LONG_PRESS_HOLD,  {_key_num_0_long_hold_cb,       context}},
    };

    for (int i = 0; i < HyUtilsArrayCnt(event_add); ++i) {
        HyKeyPinEventAttach(key_handle, &event_add[i]);
    }
}

static void _module_destroy(_main_context_t **context_pp)
{
    _main_context_t *context = *context_pp;

    // note: 增加或删除要同步到module_create_t中
    module_destroy_t module[] = {
        {"timer",       &context->key_handle,           HyTimerDestroy},
        {"key",         &context->key_handle,           HyKeyDestroy},
        {"time",        &context->time_handle,          HyTimeDestroy},
        {"log",         &context->log_handle,           HyLogDestroy},
        {"debug uart",  &context->debug_uart_handle,    HyUartDebugDestroy},
        {"system",      &context->system_handle,        HySystemDestroy},
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

    HyUartConfig_t debug_uart_config;
    // debug_uart_config.dev_name              = "/dev/ttyUSB1";
    debug_uart_config.num                   = HY_UART_NUM_1;
    debug_uart_config.rate                  = HY_UART_RATE_115200;
    debug_uart_config.flow_control          = HY_UART_FLOW_CONTROL_NONE;
    debug_uart_config.bits                  = HY_UART_BITS_8;
    debug_uart_config.parity                = HY_UART_PARITY_N;
    debug_uart_config.stop                  = HY_UART_STOP_1;
    // debug_uart_config.config_save.is_block  = HY_UART_BLOCK;
    // debug_uart_config.config_save.read_cb   = _uart1_read_cb;
    // debug_uart_config.config_save.args      = context;

    HyLogConfig_t log_config;
    log_config.buf_len                      = 256;
    log_config.level                        = HY_LOG_LEVEL_TRACE;
    log_config.config_file                  = NULL;

    HyTimeConfig_t time_config;
    time_config.num                         = HY_TIME_NUM_2;
    time_config.us                          = 1000;
    time_config.flag                        = HY_TIME_FLAG_ENABLE;
    time_config.config_save.time_cb         = _time_cb;
    time_config.config_save.args            = context;

    // note: 增加或删除要同步到module_destroy_t中
    module_create_t module[] = {
        {"system",      &context->system_handle,        &system_config,         (create_t)HySystemCreate,       HySystemDestroy},
        {"debug uart",  &context->debug_uart_handle,    &debug_uart_config,     (create_t)HyUartDebugCreate,    HyUartDebugDestroy},
        {"log",         &context->log_handle,           &log_config,            (create_t)HyLogCreate,          HyLogDestroy},
        {"timer",       &context->timer_handle,         NULL,                   (create_t)HyTimerCreate,        HyTimerDestroy},
        {"key",         &context->key_handle,           NULL,                   (create_t)HyKeyCreate,          HyKeyDestroy},
        {"time",        &context->time_handle,          &time_config,           (create_t)HyTimeCreate,         HyTimeDestroy},
    };

    RUN_CREATE(module);

    return context;
}

static void _timer_cb(void *timer_handle, void *args)
{
    _main_context_t *context = args;

    HyGpioSetLevelToggle(&context->red_led);
}

int main(int argc, char const* argv[])
{
    _main_context_t *context = _module_create();
    if (!context) {
        LOGE("_module_create faild \n");
        return -1;
    }

    LOGI("version: %s, date: %s, time: %s \n", VERSION, __DATE__, __TIME__);

    _gpio_init(context);
    _key_init(context);

    HyTimerConfig_t timer_config;
    timer_config.repeat_flag = HY_TIMER_FLAG_ENABLE;
    timer_config.expired_ms = 500;
    timer_config.timer_cb = _timer_cb;
    timer_config.args = context;
    HyTimerAdd(context->timer_handle, &timer_config);

    while (1) {
        HyTimerProcess(context->timer_handle);

#ifdef USE_SYSTICK_DELAY
        HySystemDelayS(1);
        LOGD("delay 1s\n");
#endif
    }

    _module_destroy(&context);

    return 0;
}

