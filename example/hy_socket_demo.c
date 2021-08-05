/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_socket_test.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    12/07 2021 10:58
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        12/07 2021      create the file
 * 
 *     last modified: 12/07 2021 10:58
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hy_socket.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_module.h"
#include "hy_utils/hy_utils.h"
#include "hy_utils/hy_mem.h"

#define ALONE_DEBUG 1

typedef struct {
    void *log_handle;
    void *socket_handle;
} _main_context_t;

static void _socket_event_cb(HySocketState_t state, void *args)
{
    LOGD("state: %d \n", state);
}

static void _socket_read_cb(void *buf, size_t len, void *args)
{
    LOGD("buf: %s \n", (char *)buf);
}

static void _module_destroy(_main_context_t **context_pp)
{
    _main_context_t *context = *context_pp;

    // note: 增加或删除要同步到module_create_t中
    module_destroy_t module[] = {
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

    HySocketConfig_t socket_config;
    socket_config.ip                    = "192.168.1.57";
    socket_config.port                  = 7809;
    socket_config.config_save.event_cb  = _socket_event_cb;
    socket_config.config_save.read_cb   = _socket_read_cb;
    socket_config.config_save.args      = &context;

    // note: 增加或删除要同步到module_destroy_t中
    module_create_t module[] = {
        {"log",     &context->log_handle,       &log_config,    (create_t)HyLogCreate,      HyLogDestroy},
        {"socket",  &context->socket_handle,    &socket_config, (create_t)HySocketCreate,   HySocketDestroy},
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
        if (-1 == HySocketProcess(context->socket_handle)) {
            break;
        }
    }

    _module_destroy(&context);

    return 0;
}

