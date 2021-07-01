/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_socket_wrapper.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    01/07 2021 19:04
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        01/07 2021      create the file
 * 
 *     last modified: 01/07 2021 19:04
 */
#ifndef __LIBHY_HAL_INCLUDE_WRAPPER_HY_SOCKET_WRAPPER_H_
#define __LIBHY_HAL_INCLUDE_WRAPPER_HY_SOCKET_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hy_socket.h"

typedef struct {
    int fd;
} socket_context_t;

void *socket_create(HySocketConfig_t *socket_config);
void socket_destroy(socket_context_t *context);

int socket_read(socket_context_t *context, char *buf, uint32_t len);
int socket_write(socket_context_t *context, const char *buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif

