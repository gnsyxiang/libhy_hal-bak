/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_time_linux.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    30/06 2021 17:31
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        30/06 2021      create the file
 * 
 *     last modified: 30/06 2021 17:31
 */
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>

#include "hy_time_wrapper.h"

#define BASE_NUM	(1000)
#define BASE_NUM_2	(1000 * 1000)
#define BASE_NUM_3	(1000 * 1000 * 1000)

#define take_integet_1000(num)		((num) / BASE_NUM)
#define take_remainder_1000(num)	((num) % BASE_NUM)
#define take_multiplier_1000(num)	((num) * BASE_NUM)

static void _delay_com(uint32_t us)
{
    struct timeval tv;
    tv.tv_sec   = 0;
    tv.tv_usec  = us;

    int err;
    do {
        err = select(0, NULL, NULL, NULL, &tv);
    } while(err < 0 && errno == EINTR);
}

time_t time_get_tick(void)
{
    return 0;
}

time_t time_get_cur_us(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
}

void time_delay_ms(hy_uint32_t ms)
{
    _delay_com(ms * BASE_NUM);
}

void time_delay_us(hy_uint32_t us)
{
    _delay_com(us);
}

