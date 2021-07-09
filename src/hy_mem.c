/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hy_mem.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    22/02 2020 16:42
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        22/02 2020      create the file
 * 
 *     last modified: 22/02 2020 16:42
 */
#include <stdio.h>

#include "hy_mem.h"
#include "hy_mem_wrapper.h"

#include "log.h"

#define ALONE_DEBUG 1

void *HyMalloc(size_t size)
{
    return malloc_wrapper(size);
}

void HyFree(void *ptr)
{
    if (ptr) {
        free_wrapper(ptr);
    }
}

void *HyCalloc(size_t nmemb, size_t size)
{
    return calloc_wrapper(nmemb, size);
}

void *HyRealloc(void *ptr, size_t size)
{
    if (ptr) {
        return realloc_wrapper(ptr, size);
    } else {
        return NULL;
    }
}

