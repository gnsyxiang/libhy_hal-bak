/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_mem.c
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
#include "config.h"
#include "hal_mem.h"

#ifdef HAVE_RTT_HAL
#include <rtthread.h>

void *Hal_malloc(size_t size)
{
    return rt_malloc(size);
}

void Hal_free(void *ptr)
{
    return rt_free(ptr);
}

void *Hal_calloc(size_t nmemb, size_t size)
{
    return rt_calloc(nmemb, size);
}

void *Hal_realloc(void *ptr, size_t size)
{
    return rt_realloc(ptr, size);
}
#endif

#ifdef HAVE_LINUX_HAL
#include <stdlib.h>

void *Hal_malloc(size_t size)
{
    return malloc(size);
}

void Hal_free(void *ptr)
{
    return free(ptr);
}

void *Hal_calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

void *Hal_realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

#endif

