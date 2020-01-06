/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    demo.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/12 2019 20:40
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/12 2019      create the file
 * 
 *     last modified: 17/12 2019 20:40
 */
#include <stdio.h>

#include "demo.h"

#if HAVE_MY_PRINT
void my_print(void)
{
    printf("my print \n");
}
#endif

void hello_world(void)
{
    printf("hello world\n");
}
