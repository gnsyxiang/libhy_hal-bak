/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_string.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    21/02 2020 16:46
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        21/02 2020      create the file
 * 
 *     last modified: 21/02 2020 16:46
 */
#ifndef __LIBHAL_INCLUDE_HAL_STRING_H_
#define __LIBHAL_INCLUDE_HAL_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_config.h"

hal_int8_t *HalStrcpy(hal_int8_t *dest, const hal_int8_t *src);
hal_int8_t *HalStrncpy(hal_int8_t *dest, const hal_int8_t *src, size_t n);
size_t HalStrlen(const hal_int8_t *s);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_STRING_H_

