/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_socket.c
 * @brief   封装网络操作函数
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

#include "hy_socket_wrapper.h"

#include "hy_type.h"
#include "hy_error.h"
#include "hy_log.h"

#define ALONE_DEBUG 1

static int _socket_init(socket_context_t *context, HySocketConfig_t *socket_config)
{
    context->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (context->fd < 0) {
        LOGE("socket faild \n");
        return HY_ERR_FAILD;
    }

    struct sockaddr_in    servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(socket_config->port);
    if (inet_pton(AF_INET, socket_config->ip, &servaddr.sin_addr) <= 0) {
        LOGE("inet_pton faild for %s \n", socket_config->ip);
        close(context->fd);
        return HY_ERR_FAILD;
    }
    LOGI("ip: %s, port: %d \r\n", socket_config->ip, socket_config->port);

    if (connect(context->fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        LOGE("connect faild \n");
        close(context->fd);
        return HY_ERR_FAILD;
    }

    LOGD("fd: %d \n", context->fd);
    return HY_ERR_OK;
}

int socket_read(socket_context_t *context, char *buf, uint32_t len)
{
    int ret = recv(context->fd, buf, len, 0);
    if (ret <= 0) {
        if (0 == ret) {
            LOGE("recv data error, err: %d<%s> \n", errno, strerror(errno));
        } else if (ret < 0) {
            if (errno == EINTR) {
                ret = 0;
            }
        }
    }

    return ret;
}

int socket_write(socket_context_t *context, const char *buf, uint32_t len)
{
    int ret = send(context->fd, buf, len, 0);
    if (ret <= 0) {
        if (0 == ret) {
            LOGE("send data error, err: %d<%s> \n", errno, strerror(errno));
        } else if (ret < 0) {
            if (errno == EINTR) {
                ret = 0;
            }
        }
    }

    return ret;
}

void *socket_create(HySocketConfig_t *socket_config)
{
    socket_context_t *context = calloc(1, sizeof(*context));
    if (!context) {
        LOGE("calloc faild \n");
        return NULL;
    }

    if (HY_ERR_OK != _socket_init(context, socket_config)) {
        LOGE("init socket faild \n");
        free(context);
        return NULL;
    }

    LOGI("hy_socket create successful \n");
    return context;
}

void socket_destroy(socket_context_t *context)
{
    close(context->fd);
    free(context);
}

