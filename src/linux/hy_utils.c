/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_utils.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    05/08 2021 17:39
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        05/08 2021      create the file
 * 
 *     last modified: 05/08 2021 17:39
 */
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#include "hy_utils.h"

#include "hy_utils/hy_type.h"

/* 栈的开口方向：
 * 开口向下的栈先分配大地址，从下到上地址编号依次变大
 * 开口向上的栈先分配小地址
 *
 * 一般情况下，操作系统提供的栈都是向下的
 *
 * 不管栈的开口朝向，数组buf的内存地址buf+1永远向上
 */
void HyStackDetection(void)
{
    hy_s32_t a;
    hy_s32_t b;
    char buf[3];

    printf("%p \n", &a);
    printf("%p \n", &b);

    for (int i = 0; i < 3; i++)
        printf("%p \n", &buf[i]);
}

hy_u32_t HyRandomNum(hy_u32_t range)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);

    return (1 + (hy_u32_t)(1.0 * range * rand() / (RAND_MAX + 1.0)));
}

