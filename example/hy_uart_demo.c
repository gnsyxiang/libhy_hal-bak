/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_uart_demo.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    05/08 2021 14:12
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        05/08 2021      create the file
 * 
 *     last modified: 05/08 2021 14:12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hy_uart.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_module.h"
#include "hy_utils/hy_utils.h"
#include "hy_utils/hy_mem.h"

#define ALONE_DEBUG 1

typedef struct {
    void *log_handle;
    void *uart_handle;
} _main_context_t;

static void _uart_read_cb(void *buf, size_t len, void *args)
{
    LOGE("len: %zu, buf: %s \n", len, buf);
}

static void _module_destroy(_main_context_t **context_pp)
{
    _main_context_t *context = *context_pp;

    // note: 增加或删除要同步到module_create_t中
    module_destroy_t module[] = {
        {"uart",    &context->uart_handle,  HyUartDestroy},
        {"log",     &context->log_handle,   HyLogDestroy},
    };

    RUN_DESTROY(module);

    HY_FREE(context_pp);
}

static _main_context_t *_module_create(void)
{
    _main_context_t *context = (_main_context_t *)HY_MALLOC_RET_VAL(sizeof(*context), NULL);

    HyLogConfig_t log_config;
    log_config.buf_len                  = 512;
    log_config.level                    = HY_LOG_LEVEL_INFO;
    log_config.config_file              = "./res/config/log4cplus.rc";

    HyUartConfig_t uart_config;
    uart_config.dev_name                = "/dev/ttyUSB0";
    uart_config.is_block                = HY_UART_BLOCK;
    uart_config.rate                    = HY_RATE_115200;
    uart_config.flow_control            = HY_UART_FLOW_CONTROL_DISABLE;
    uart_config.bits                    = HY_UART_BITS_8;
    uart_config.parity                  = HY_UART_PARITY_N;
    uart_config.stop                    = HY_UART_STOP_1;
    uart_config.config_save.read_cb     = _uart_read_cb;
    uart_config.config_save.args        = context;

    // note: 增加或删除要同步到module_destroy_t中
    module_create_t module[] = {
        {"log",     &context->log_handle,   &log_config,    (create_t)HyLogCreate,  HyLogDestroy},
        {"uart",    &context->uart_handle,  &uart_config,   (create_t)HyUartCreate, HyUartDestroy},
    };

    RUN_CREATE(module);

    return context;
}

int main(int argc, char *argv[])
{
    _main_context_t *context = _module_create();
    if (!context) {
        LOGE("_module_create faild \n");
        return -1;
    }

    while (1) {
        HyUartProcess(context->uart_handle);
    }

    _module_destroy(&context);

    return 0;
}

