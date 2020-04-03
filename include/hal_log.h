/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_log.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/01 2020 17:55
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/01 2020      create the file
 * 
 *     last modified: 20/01 2020 17:55
 */
#ifndef __LIBHAL_INCLUDE_HAL_LOG_H_
#define __LIBHAL_INCLUDE_HAL_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_config.h"
#include <errno.h>
#include <libgen.h>

typedef enum {
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,

    LOG_LEVEL_MAX,
} LogLevel_t;

typedef enum {
    LOG_COLOR_OFF,
    LOG_COLOR_ON,

    LOG_COLOR_MAX,
} LogColor_t;

typedef struct {
    LogLevel_t level;
    LogColor_t color_flag;
    hal_uint32_t buf_len;
} LogConfig_t;

typedef void * LogHandle_t;

void HalLogInit(LogConfig_t *log_config);
void HalLogFinal(void);

void HalLogSetLevel(LogLevel_t level);
void HalLogSetColor(LogColor_t color_flag);
void HalLogSetDoubleLine(void);

void HalLogDebug(LogLevel_t level, hal_int32_t num, 
                 const hal_char_t *file, hal_uint32_t line, 
                 const hal_char_t *fmt, ...);

#define LOG_DEBUG(level, ...) \
    HalLogDebug(level, errno, basename(__FILE__), __LINE__, __VA_ARGS__)

#define HalLogV(...)    LOG_DEBUG(LOG_LEVEL_VERBOSE, __VA_ARGS__) 
#define HalLogT(...)    LOG_DEBUG(LOG_LEVEL_INFO,    __VA_ARGS__) 
#define HalLogD(...)    LOG_DEBUG(LOG_LEVEL_DEBUG,   __VA_ARGS__) 
#define HalLogW(...)    LOG_DEBUG(LOG_LEVEL_WARNING, __VA_ARGS__) 
#define HalLogE(...)    LOG_DEBUG(LOG_LEVEL_ERROR,   __VA_ARGS__) 

#ifdef __cplusplus
}
#endif

#endif //__LIBHAL_INCLUDE_HAL_LOG_H_

