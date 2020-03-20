/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_module_cb.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/03 2020 16:46
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/03 2020      create the file
 * 
 *     last modified: 20/03 2020 16:46
 */
#ifndef __LIBHAL_INCLUDE_HAL_MODULE_CB_H_
#define __LIBHAL_INCLUDE_HAL_MODULE_CB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "hal_config.h"

typedef hal_int32_t (*hal_create_cb_t)(void *context);
typedef hal_int32_t (*hal_destroy_cb_t)(void *context);
typedef hal_int32_t (*hal_param_cb_t)(void *context, hal_int32_t type, void *args);

typedef struct {
    hal_create_cb_t     create;
    hal_destroy_cb_t    destroy;
    hal_param_cb_t      get;
    hal_param_cb_t      set;
} hal_system_init_cb_t;
#define HAL_SYSTEM_INIT_CB_LEN (sizeof(hal_system_init_cb_t))

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_MODULE_CB_H_

