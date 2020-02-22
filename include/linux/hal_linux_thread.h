/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_linux_thread.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/01 2020 18:15
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/01 2020      create the file
 * 
 *     last modified: 20/01 2020 18:15
 */
#ifndef __LIBHAL_INCLUDE_LINUX_HAL_LINUX_THREAD_H_
#define __LIBHAL_INCLUDE_LINUX_HAL_LINUX_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_config.h"
#include "hal_thread_internal.h"

hal_int32_t HalLinuxThreadInit(HalThreadConfig_t *config, hal_thread_context_t *context);
void HalLinuxThreadFinal(hal_thread_context_t *context);
void HalLinuxThreadParamSet(hal_thread_context_t *context, HalThreadParam_t type, void *args);
void HalLinuxThreadParamGet(hal_thread_context_t *context, HalThreadParam_t type, void *args);

#ifdef __cplusplus
}
#endif

#endif //__LIBHAL_INCLUDE_LINUX_HAL_LINUX_THREAD_H_

