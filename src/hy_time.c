/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_time.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    30/06 2021 17:26
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        30/06 2021      create the file
 * 
 *     last modified: 30/06 2021 17:26
 */
#include <stdio.h>

#include "hy_time.h"
#include "hy_time_wrapper.h"

time_t HyTimeGetTick(void)
{
    return time_get_tick();
}

time_t HyTimeGetCurUs(void)
{
    return time_get_cur_us();
}

time_t HyTimeGetCurMs(void)
{
    return time_get_cur_ms();
}

void HyTimeDelayMs(hy_uint32_t ms)
{
    time_delay_ms(ms);
}

void HyTimeDelayUs(hy_uint32_t us)
{
    time_delay_us(us);
}
