/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_log.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    22/02 2020 16:49
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        22/02 2020      create the file
 * 
 *     last modified: 22/02 2020 16:49
 */
#include <string.h>
#include <stdarg.h>

#include "hal_config.h"

#define ANSI_COLOR_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
/*printf("\033[字体高亮;字背景颜色;字体颜色m字符串\033[0m"); */

#define LOG_BUF_SIZE 2048

typedef struct {
    hal_uint32_t level;
    hal_uint32_t color_flag;
} log_context_t;

static log_context_t l_context;

void HalLogSetLevel(LogLevel_t level)
{
    l_context.level = level;
}

void HalLogSetColor(LogColor_t color_flag)
{
    l_context.color_flag = color_flag;
}

static inline void log_output(hal_char_t *buffer)
{
    printf("%s\n", buffer);
}

void HalLogDebug(LogLevel_t level, 
                 const hal_char_t *file, 
                 hal_uint32_t line, 
                 hal_int32_t num, 
                 const hal_char_t *fmt, 
                 ...)
{
    hal_char_t buffer[LOG_BUF_SIZE] = {0};
    hal_uint32_t size = 0;

    if (level < l_context.level) {
        return;
    }

	if (level <= LOG_LEVEL_ERROR) {
        size += snprintf(buffer + size, LOG_BUF_SIZE - size, ANSI_COLOR_MAGENTA);
        /*size += snprintf(buffer + size, LOG_BUF_SIZE - size, "\033[35m");*/
    }

    // size = sprintf(buffer, "[%.03f]", get_sec_clk_with_boottime());

    size += sprintf(buffer + size, "[%s +%d]: ", file, line);

	if (level <= LOG_LEVEL_ERROR)
		size += snprintf(buffer + size, LOG_BUF_SIZE - size, ANSI_COLOR_RED);

    va_list var_args;
    va_start(var_args, fmt);
    size += vsnprintf(buffer + size, LOG_BUF_SIZE - size, fmt, var_args);
    va_end(var_args);

	if (level <= LOG_LEVEL_ERROR) {
		size += snprintf(buffer + size, LOG_BUF_SIZE - size, "\033[0m");
		size += sprintf(buffer + size, " [errno string: %s]", strerror(num));
	}

    log_output(buffer);
}

