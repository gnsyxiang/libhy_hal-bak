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
#include "hal_config.h"

#ifdef HAVE_RTT_HAL
#else

#include <stdlib.h>

void *HalMalloc(size_t size)
{
    return malloc(size);
}

void HalFree(void *ptr)
{
    return free(ptr);
}

void *HalCalloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

void *HalRealloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

#endif

