/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    socket.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/07 2021 16:30
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/07 2021      create the file
 * 
 *     last modified: 09/07 2021 16:30
 */
#include <stdio.h>

#include "socket.h"

typedef struct {
    HySocketConfigSave_t config_save;
} socket_context_t;

void *socket_create(HySocketConfig_t *socket_config)
{
    return NULL;
}

void socket_destroy(void **handle)
{

}

int socket_process(void *handle)
{
    return 0;
}
int socket_write(void *handle, void *buf, size_t len)
{
    return 0;
}

