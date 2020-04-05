/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    log.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    28/03 2020 22:33
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        28/03 2020      create the file
 * 
 *     last modified: 28/03 2020 22:33
 */
#include "hal_type.h"
#include "hal_log.h"

hal_int32_t main(hal_int32_t argc, const hal_char_t *argv[])
{
    LogConfig_t log_config;
    log_config.level        = LOG_LEVEL_VERBOSE;
    log_config.color_flag   = LOG_COLOR_ON;
    log_config.buf_len      = 1024;

    HalLogInit(&log_config);
    HalLogSetLevel(LOG_LEVEL_VERBOSE);
    HalLogSetDoubleLine();

    HalLogV("demo test\n");
    HalLogT("demo test\n");
    HalLogD("demo test\n");
    HalLogW("demo test\n");
    HalLogE("demo test\n");

    HalLogFinal();

    return 0;
}

