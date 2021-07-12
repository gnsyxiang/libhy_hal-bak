/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_socket.h
 * @brief   封装网络操作函数
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    05/12 2020 09:48
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        05/12 2020      create the file
 * 
 *     last modified: 05/12 2020 09:48
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_SOCKET_H_
#define __LIBHY_HAL_INCLUDE_HY_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

typedef enum {
    HY_SOCKET_STATE_DISCONNECT,
    HY_SOCKET_STATE_CONNECTING,
    HY_SOCKET_STATE_CONNECTED,

    HY_SOCKET_STATE_MAX,
} HySocketState_t;

typedef struct {
    void (*event_cb)(void *handle, int state, void *args);
    void (*read_cb)(void *handle, void *buf, size_t len, void *args);
    void *args;
} HySocketConfigSave_t;

typedef struct {
    char                *ip;
    uint16_t            port;

    HySocketConfigSave_t config_save;
} HySocketConfig_t;

void *HySocketCreate(HySocketConfig_t *socket_config);
void HySocketDestroy(void **handle);

int HySocketProcess(void *handle);
int HySocketWrite(void *handle, void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif

