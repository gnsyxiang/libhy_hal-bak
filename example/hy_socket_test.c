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

#include "hy_socket.h"

#include "log.h"

typedef struct {
    void *socket_handle;
} _main_context_t;

static _main_context_t context;

static void _socket_event_cb(int state, void *args)
{
    LOGD("state: %d \n", state);
}

static void _socket_read_cb(void *buf, size_t len, void *args)
{
    LOGD("buf: %s \n", (char *)buf);
}

int main(int argc, char *argv[])
{
    HySocketConfig_t socket_config;
    socket_config.ip = "192.168.1.57";
    socket_config.port = 7809;
    socket_config.config_save.event_cb  = _socket_event_cb;
    socket_config.config_save.read_cb   = _socket_read_cb;
    socket_config.config_save.args      = &context;

    context.socket_handle = HySocketCreate(&socket_config);
    if (!context.socket_handle) {
        LOGE("HySocketCreate faild \n");
        return -1;
    }

    while (1) {
        if (-1 == HySocketProcess(context.socket_handle)) {
            break;
        }
    }

    HySocketDestroy(&context.socket_handle);

    return 0;
}
