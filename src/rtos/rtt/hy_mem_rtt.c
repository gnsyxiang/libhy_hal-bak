/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_mem_rtt.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    30/06 2021 16:56
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        30/06 2021      create the file
 * 
 *     last modified: 30/06 2021 16:56
 */
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

