/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_socket.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    01/07 2021 18:56
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        01/07 2021      create the file
 * 
 *     last modified: 01/07 2021 18:56
 */
#include <stdio.h>

#include "hy_socket.h"
#include "socket.h"

#include "utils.h"
#include "log.h"

#define ALONE_DEBUG 1

void *HySocketCreate(HySocketConfig_t *socket_config)
{
    JUDGE_NULL_RET(!socket_config, NULL);
    return socket_create(socket_config);
}

void HySocketDestroy(void **handle)
{
    JUDGE_NULL(!handle || !*handle);
    socket_destroy(handle);
}

int HySocketProcess(void *handle)
{
    JUDGE_NULL_RET(!handle, -1);
    return socket_process(handle);
}

int HySocketWrite(void *handle, void *buf, size_t len)
{
    JUDGE_NULL_RET(!handle || !buf, -1);
    return socket_write(handle, buf, len);
}

