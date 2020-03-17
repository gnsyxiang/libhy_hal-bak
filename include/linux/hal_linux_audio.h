/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_linux_audio.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    12/03 2020 16:36
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        12/03 2020      create the file
 * 
 *     last modified: 12/03 2020 16:36
 */
#ifndef __LIBHAL_INCLUDE_LINUX_HAL_LINUX_AUDIO_H_
#define __LIBHAL_INCLUDE_LINUX_HAL_LINUX_AUDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_config.h"

typedef hal_int32_t (*hal_audio_create_t)(HalThreadConfig_t *config, hal_thread_context_t *context);
typedef hal_int32_t (*hal_thhread_destroy_t)(hal_thread_context_t *context);
typedef hal_int32_t (*hal_thread_param_t)(hal_thread_context_t *context, HalThreadParam_t type, void *args);

typedef struct {
    hal_thread_create_t create;
    hal_thhread_destroy_t destroy;
    hal_thread_param_t get;
    hal_thread_param_t set;
} hal_thread_system_cb_t;
#define HAL_THREAD_SYSTEM_CB_LEN (sizeof(hal_thread_system_cb_t))

void AudioSystemInit(hal_thread_system_cb_t *system_cb);

hal_int32_t LinuxThreadCreate(HalThreadConfig_t *config, hal_thread_context_t *context);
hal_int32_t LinuxThreadDestroy(hal_thread_context_t *context);

hal_int32_t LinuxThreadParamSet(hal_thread_context_t *context, HalThreadParam_t type, void *args);
hal_int32_t LinuxThreadParamGet(hal_thread_context_t *context, HalThreadParam_t type, void *args);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_LINUX_HAL_LINUX_AUDIO_H_

