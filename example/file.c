/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    file.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    06/04 2020 18:45
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        06/04 2020      create the file
 * 
 *     last modified: 06/04 2020 18:45
 */
#include "hal_type.h"
#include "hal_log.h"
#include "hal_file.h"

#define FILE_NAME "haha.test"

hal_int32_t main(hal_int32_t argc, const hal_char_t *argv[])
{
    LogConfig_t log_config;
    log_config.level        = LOG_LEVEL_VERBOSE;
    log_config.color_flag   = LOG_COLOR_ON;
    log_config.buf_len      = 1024;

    HalLogInit(&log_config);

    hal_int32_t fd = Hal_open(FILE_NAME, O_RDWR, 0664);
    // hal_int32_t fd = Hal_open(FILE_NAME, O_RDWR | O_CREAT, 0664);
    if (fd < 0) {
        HalLogE("open failed \n");
        return -1;
    }

    Hal_close(fd);

    HalLogFinal();
    
    return 0;
}

