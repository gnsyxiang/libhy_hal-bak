/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_thread_internal.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/01 2020 17:29
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/01 2020      create the file
 * 
 *     last modified: 20/01 2020 17:29
 */
#ifndef __LIBHAL_INCLUDE_HAL_THREAD_INTERNAL_H_
#define __LIBHAL_INCLUDE_HAL_THREAD_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "hal_type.h"
#include "hal_thread.h"

#ifdef HAVE_LINUX_HAL
#include <pthread.h>
#include <sched.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <sys/prctl.h>
#endif

#ifdef HAVE_RTT_HAL
#include <rtdef.h>
#include <rtthread.h>
#endif

typedef enum {
    HAL_THREAD_INIT,
    HAL_THREAD_IDLE,
    HAL_THREAD_RUNNING
} hal_thread_state_t;

typedef enum {
    HAL_THREAD_INDEX_SET,
    HAL_THREAD_INDEX_GET,
    HAL_THREAD_INDEX_MAX,
} hal_thread_index_t;

#define HAL_THREAD_NAME_MAX_LEN (16)
typedef struct {
    hal_char_t                  name[HAL_THREAD_NAME_MAX_LEN];
    HalThreadLoopConfig_t       loop_config;

#ifdef HAVE_LINUX_HAL
    pthread_t                   id;
    pid_t                       pid;
#endif
#ifdef HAVE_RTT_HAL
    rt_thread_t                 id;
#endif
    hal_thread_state_t          state;
} hal_thread_context_t;
#define HAL_THREAD_CONTEXT_LEN (sizeof(hal_thread_context_t))

typedef hal_int32_t (*hal_thread_param_cb_t)(hal_thread_context_t *context, void *args);

typedef struct {
    hal_thread_param_cb_t set_param_cb;
    hal_thread_param_cb_t get_param_cb;
} hal_linux_thread_param_cb_t;

#define hal_thread_param_common(hal_thread_param, context, type, args, index) \
  ({                                                                          \
   hal_int32_t ret = -1;                                                      \
    for (hal_int32_t i = 0; i < HAL_THREAD_PARAM_MAX; i++) {                  \
        if (type == i) {                                                      \
            if (HAL_THREAD_INDEX_SET == index) {                              \
                ret = hal_thread_param[i].set_param_cb(context, args);        \
            } else {                                                          \
                ret = hal_thread_param[i].get_param_cb(context, args);        \
            }                                                                 \
            break;                                                            \
        }                                                                     \
    }                                                                         \
    ret;                                                                      \
  })

#ifdef __cplusplus
}
#endif

#endif //__LIBHAL_INCLUDE_HAL_THREAD_INTERNAL_H_

