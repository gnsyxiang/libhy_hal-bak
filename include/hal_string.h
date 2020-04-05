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

#include "hal_type.h"

hal_char_t *Hal_strcpy(hal_char_t *dest, const hal_char_t *src);
hal_char_t *Hal_strncpy(hal_char_t *dest, const hal_char_t *src, size_t n);
size_t Hal_strlen(const hal_char_t *s);
hal_char_t *Hal_strstr(const hal_char_t *haystack, const char *needle);
void *Hal_memcpy(void *dest, const void *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_STRING_H_

