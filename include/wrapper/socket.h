/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    socket.h
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
#ifndef __LIBHY_HAL_INCLUDE_WRAPPER_SOCKET_H_
#define __LIBHY_HAL_INCLUDE_WRAPPER_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hy_socket.h"

void *socket_create(HySocketConfig_t *socket_config);
void socket_destroy(void **handle);

int socket_process(void *handle);
int socket_write(void *handle, void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif

