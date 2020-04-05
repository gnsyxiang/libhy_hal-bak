/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_dl_lib.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    28/03 2020 16:19
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        28/03 2020      create the file
 * 
 *     last modified: 28/03 2020 16:19
 */
#ifndef __LIBHAL_INCLUDE_HAL_DL_LIB_H_
#define __LIBHAL_INCLUDE_HAL_DL_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_type.h"

#define SYMBOL_NAME(symbol)   #symbol

typedef void* DLLibHandle_t;

DLLibHandle_t HalDllibOpen(const hal_char_t *libname);
void HalDllibExit(DLLibHandle_t handle);

void *HalDllLoadSymbol(DLLibHandle_t handle, const hal_char_t *symbol);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_DL_LIB_H_

