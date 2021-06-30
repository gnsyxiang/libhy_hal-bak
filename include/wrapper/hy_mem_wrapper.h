/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_mem_wrapper.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    30/06 2021 17:01
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        30/06 2021      create the file
 * 
 *     last modified: 30/06 2021 17:01
 */
#ifndef __LIBHY_HAL_INCLUDE_WRAPPER_HY_MEM_WRAPPER_H_
#define __LIBHY_HAL_INCLUDE_WRAPPER_HY_MEM_WRAPPER_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void *malloc_wrapper(size_t size);

void free_wrapper(void *ptr);

void *calloc_wrapper(size_t nmemb, size_t size);

void *realloc_wrapper(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif

