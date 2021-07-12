/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    socket.c
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

#include "socket.h"

#include "hy_type.h"
#include "hy_error.h"
#include "utils.h"
#include "log.h"

#define ALONE_DEBUG 1

typedef struct {
    int fd;

    HySocketConfigSave_t config_save;
} socket_context_t;

static inline void _socket_destroy(socket_context_t *context)
{
    if (context->fd > 0) {
        close(context->fd);
    }
}

static int _socket_create(socket_context_t *context,
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
            context->config_save.event_cb(context,
                    HY_SOCKET_STATE_CONNECTING, context->config_save.args);
        }

        if (0 != connect(context->fd,
                    (struct sockaddr*)&servaddr, sizeof(servaddr))) {
            LOGE("connect faild \n");
            break;
        }

        if (context->config_save.event_cb) {
            context->config_save.event_cb(context,
                    HY_SOCKET_STATE_CONNECTED, context->config_save.args);
        }

        LOGI("fd: %d, ip: %s, port: %d \n",
                context->fd, socket_config->ip, socket_config->port);

        return HY_ERR_OK;
    } while (0);

    _socket_destroy(context);

    return HY_ERR_OK;
}

void socket_destroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    socket_context_t **context = (socket_context_t **)handle;

    _socket_destroy(*context);

    FREE(context);
}

void *socket_create(HySocketConfig_t *socket_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    socket_context_t *context = NULL;

    do {
        context = malloc(sizeof(*context));
        if (!context) {
            LOGE("calloc faild \n");
            break;
        }
        memset(context, '\0', sizeof(*context));

        memcpy(&context->config_save, &socket_config->config_save,
                sizeof(context->config_save));

        if (HY_ERR_OK != _socket_create(context, socket_config)) {
            LOGE("_socket_create faild \n");
            break;
        }

        return context;
    } while (0);

    socket_destroy((void **)&context);

    return context;
}

int socket_process(void *handle)
{
    socket_context_t *context = handle;
    HySocketConfigSave_t *config_save = &context->config_save;

#define BUF_LEN (1024)
    char buf[BUF_LEN] = {0};
    int ret = recv(context->fd, buf, BUF_LEN, 0);
    if (ret <= 0) {
        if (0 == ret) {
            if (config_save->event_cb) {
                config_save->event_cb(context,
                        HY_SOCKET_STATE_DISCONNECT, config_save->args);
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
            config_save->read_cb(context, buf, ret, config_save->args);
        }
    }

    return 0;
}

int socket_write(void *handle, void *buf, size_t len)
{
    socket_context_t *context = handle;
    HySocketConfigSave_t *config_save = &context->config_save;

    int ret = send(context->fd, buf, len, 0);
    if (ret <= 0) {
        if (0 == ret) {
            if (config_save->event_cb) {
                config_save->event_cb(context,
                        HY_SOCKET_STATE_DISCONNECT, config_save->args);
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

