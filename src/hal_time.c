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
#include "config.h"
#include "hal_config.h"

#ifdef HAVE_RTT_HAL
#include <rtthread.h>

hal_uint32_t HalSleep(hal_uint32_t seconds)
{
    return rt_thread_mdelay(1000 * seconds);
}
#endif

#ifdef HAVE_LINUX_HAL
#include <unistd.h>

hal_uint32_t HalSleep(hal_uint32_t seconds)
{
    return sleep(seconds);
}
#endif

