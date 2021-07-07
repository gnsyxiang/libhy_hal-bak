/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_time_test.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    08/05 2021 14:02
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        08/05 2021      create the file
 * 
 *     last modified: 08/05 2021 14:02
 */
#include <stdio.h>

#include "hy_time.h"

#include "hy_log.h"

#define ALONE_DEBUG 1

int main(int argc, char *argv[])
{
    time_t start = HyTimeGetCurUs();

    for (int i = 0; i < 10; ++i) {
        LOGD("haha");
    }
    LOGD("\n");

    time_t end = HyTimeGetCurUs();

    LOGD("interval: %ldus \n", end - start);

    return 0;
}
