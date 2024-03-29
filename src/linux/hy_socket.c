/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_socket.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    05/12 2020 09:50
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        05/12 2020      create the file
 * 
 *     last modified: 05/12 2020 09:50
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "hy_socket.h"

#include "hy_utils/hy_type.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_error.h"
#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HySocketConfigSave_t config_save;

    hy_s32_t fd;
} socket_context_t;

hy_s32_t HySocketWrite(void *handle, void *buf, size_t len)
{
    HY_ASSERT_NULL_RET_VAL(!handle || !buf, -1);

    socket_context_t *context = handle;
    HySocketConfigSave_t *config_save = &context->config_save;

    hy_s32_t ret = send(context->fd, buf, len, 0);
    if (ret <= 0) {
        if (0 == ret) {
            if (config_save->event_cb) {
                config_save->event_cb(HY_SOCKET_STATE_DISCONNECT,
                        config_save->args);
            }
            LOGE("send data error, err: %d<%s> \n", errno, strerror(errno));
            return -1;
        } else if (ret < 0) {
            if (errno == EINTR) {
                ret = 0;
            }
        }
    }

    return ret;
}

hy_s32_t HySocketProcess(void *handle)
{
    HY_ASSERT_NULL_RET_VAL(!handle, -1);

    socket_context_t *context = handle;
    HySocketConfigSave_t *config_save = &context->config_save;

    char buf[BUF_LEN] = {0};
    hy_s32_t ret = recv(context->fd, buf, BUF_LEN, 0);
    if (ret <= 0) {
        if (0 == ret) {
            if (config_save->event_cb) {
                config_save->event_cb(HY_SOCKET_STATE_DISCONNECT,
                        config_save->args);
            }
            LOGE("recv data error, err: %d<%s> \n", errno, strerror(errno));
            return -1;
        } else if (ret < 0) {
            if (errno == EINTR) {
                ret = 0;
            }
        }
    } else {
        if (config_save->read_cb) {
            config_save->read_cb(buf, ret, config_save->args);
        }
    }

    return 0;
}

static inline hy_s32_t _set_nonblocking(hy_s32_t fd)
{
    hy_s32_t old_option = fcntl(fd, F_GETFL);
    hy_s32_t new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);

    return old_option;
}

static inline void _socket_destroy(socket_context_t *context)
{
    if (context->fd > 0) {
        close(context->fd);
    }
}

static hy_s32_t _socket_create(socket_context_t *context,
        HySocketConfig_t *socket_config)
{
    do {
        context->fd = socket(AF_INET, SOCK_STREAM, 0);
        if (context->fd < 0) {
            LOGE("socket faild \n");
            break;
        }

        struct sockaddr_in    servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(socket_config->port);
        if (1 != inet_pton(AF_INET, socket_config->ip, &servaddr.sin_addr)) {
            LOGE("inet_pton faild for %s \n", socket_config->ip);
            break;
        }

        if (context->config_save.event_cb) {
            context->config_save.event_cb(HY_SOCKET_STATE_CONNECTING,
                    context->config_save.args);
        }

        if (0 != connect(context->fd,
                    (struct sockaddr*)&servaddr, sizeof(servaddr))) {
            LOGE("connect faild \n");
            break;
        }

        // _set_nonblocking(context->fd);

        if (context->config_save.event_cb) {
            context->config_save.event_cb(HY_SOCKET_STATE_CONNECTED,
                    context->config_save.args);
        }

        LOGI("fd: %d, ip: %s, port: %d \n",
                context->fd, socket_config->ip, socket_config->port);

        return HY_ERR_OK;
    } while (0);

    _socket_destroy(context);
    return HY_ERR_OK;
}

void HySocketDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    socket_context_t *context = *handle;

    _socket_destroy(context);

    HY_FREE(handle);
}

void *HySocketCreate(HySocketConfig_t *socket_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!socket_config, NULL);

    socket_context_t *context = NULL;

    do {
        context = HY_MALLOC_BREAK(sizeof(*context));

        memcpy(&context->config_save, &socket_config->config_save,
                sizeof(context->config_save));

        if (HY_ERR_OK != _socket_create(context, socket_config)) {
            LOGE("_socket_create faild \n");
            break;
        }

        return context;
    } while (0);

    HySocketDestroy((void **)&context);
    return context;
}

