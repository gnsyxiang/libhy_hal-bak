/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_time.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    22/02 2020 16:55
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        22/02 2020      create the file
 * 
 *     last modified: 22/02 2020 16:55
 */
#include <stdio.h>

#include "hy_time.h"
#include <sys/time.h>


#ifdef HAVE_RTT_HAL
#include <rtthread.h>

hal_uint32_t Hal_sleep(hal_uint32_t seconds)
{
    return rt_thread_mdelay(1000 * seconds);
}
#endif

#ifdef HAVE_LINUX_HAL
#include <unistd.h>

hal_uint32_t Hal_sleep(hal_uint32_t seconds)
{
    return sleep(seconds);
}

struct timespec HalGetTimespecOut(hal_uint32_t timeout_ms)
{
    struct timeval nowTime;
    struct timespec timeout;

    gettimeofday(&nowTime,NULL);

    hal_uint32_t timeout_s  = timeout_ms / 1000;
    hal_uint32_t timeout_us = (timeout_ms % 1000) * 1000;

    timeout.tv_sec  = nowTime.tv_sec + timeout_s;
    timeout.tv_nsec = nowTime.tv_usec + timeout_us;

    return timeout;
}

#endif

hy_uint64_t HyTimeGetCurrentTime2Us(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);

    return (time.tv_sec * 1000 * 1000 + time.tv_usec);
}

hy_uint64_t HyTimeGetTimeInterval(hy_uint64_t us)
{
    struct timeval time;
    gettimeofday(&time, NULL);

    return (time.tv_sec * 1000 * 1000 + time.tv_usec - us);
}

