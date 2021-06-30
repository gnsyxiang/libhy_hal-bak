/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_mem_linux.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    30/06 2021 16:54
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        30/06 2021      create the file
 * 
 *     last modified: 30/06 2021 16:54
 */
#include <stdlib.h>

#include "hy_mem_wrapper.h"

void *malloc_wrapper(size_t size)
{
    return malloc(size);
}

void free_wrapper(void *ptr)
{
    return free(ptr);
}

void *calloc_wrapper(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

void *realloc_wrapper(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

