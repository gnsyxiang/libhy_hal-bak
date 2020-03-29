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
#define ANSI_COLOR_WHITE   "\x1b[39m"
#define ANSI_COLOR_RESET   "\x1b[0m"
/*printf("\033[字体高亮;字背景颜色;字体颜色m字符串\033[0m"); */

typedef struct {
    LogConfig_t config;
    hal_int32_t double_line;
    hal_char_t  *buf;
} log_context_t;
#define LOG_CONTEXT_LEN (sizeof(log_context_t))

static log_context_t *l_context;
static hal_int32_t log_init_flag = 0;

static inline void _context_init(LogConfig_t *log_config)
{
    l_context = Hal_calloc(1, LOG_CONTEXT_LEN);
    if (NULL == l_context) {
        printf("calloc is failed \n");
        return ;
    }

    l_context->config = *log_config;

    l_context->buf = Hal_calloc(1, l_context->config.buf_len);
    if (NULL == l_context->buf) {
        printf("calloc is failed \n");
        return ;
    }
}

static inline void _context_final(log_context_t **context_tmp)
{
    log_context_t *context = *context_tmp;
    if (NULL != context) {
        if (NULL != context->buf) {
            Hal_free(context->buf);
            context->buf = NULL;
        }

        Hal_free(context);
        *context_tmp = NULL;
    }
}

void HalLogInit(LogConfig_t *log_config)
{
    if (NULL == log_config) {
        printf("the log param is NULL \n");
        return ;
    }

    if (log_init_flag != 0) {
        HalLogE("hal log init already \n");
        return ;
    }

    _context_init(log_config);
}

void HalLogFinal(void)
{
    _context_final(&l_context);
}

void HalLogSetLevel(LogLevel_t level)
{
    l_context->config.level = level;
}

void HalLogSetColor(LogColor_t color_flag)
{
    l_context->config.color_flag = color_flag;
}

void HalLogSetDoubleLine(void)
{
    l_context->double_line = 1;
}

static inline void log_output(hal_char_t *buf)
{
    printf("%s", buf);
}

void HalLogDebug(LogLevel_t level, hal_int32_t num,
                 const hal_char_t *file, hal_uint32_t line, 
                 const hal_char_t *fmt, ...)
{
    hal_uint32_t size = 0;
    hal_char_t *buf = l_context->buf;
    hal_uint32_t buf_len = l_context->config.buf_len;

    if (level < l_context->config.level) {
        return;
    }

    hal_char_t *color[][2] = {
        {"V", ANSI_COLOR_WHITE   },
        {"T", ANSI_COLOR_WHITE   },
        {"D", ANSI_COLOR_BLUE    },
        {"W", ANSI_COLOR_YELLOW  },
        {"E", ANSI_COLOR_RED     },
        {" ", ANSI_COLOR_GREEN   },
        {" ", ANSI_COLOR_MAGENTA },
        {" ", ANSI_COLOR_CYAN    },
    };

    if (l_context->double_line) {
        size += snprintf(buf + size, buf_len - size, "\n");
    }

    if (l_context->config.color_flag) {
        size += snprintf(buf + size, buf_len - size, "%s[%s]", color[level][1], color[level][0]);
    } else {
        size += snprintf(buf + size, buf_len - size, "[%s]", color[level][0]);
    }
    // size = sprintf(buf, "[%.03f]", get_sec_clk_with_boottime());
    if (level == LOG_LEVEL_ERROR) {
        size += sprintf(buf + size, "[%s +%d, err_str: %s]: ", file, line, strerror(num));
    } else {
        size += sprintf(buf + size, "[%s +%d]: ", file, line);
    }

    va_list var_args;
    va_start(var_args, fmt);
    size += vsnprintf(buf + size, buf_len - size, fmt, var_args);
    va_end(var_args);

    if (l_context->config.color_flag) {
        size += snprintf(buf + size, buf_len - size, "%s", color[0][1]);
    }

    if (l_context->double_line) {
        size += snprintf(buf + size, buf_len - size, "\n");
    }

    log_output(buf);
}

