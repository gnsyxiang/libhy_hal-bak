/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_config.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/01 2020 16:43
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/01 2020      create the file
 * 
 *     last modified: 20/01 2020 16:43
 */
#ifndef __LIBHAL_INCLUDE_HAL_CONFIG_H_
#define __LIBHAL_INCLUDE_HAL_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_RTT_HAL
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <sys/prctl.h>
#endif

#include "hal_type.h"
#include "hal_log.h"
#include "hal_mem.h"
#include "hal_time.h"
#include "hal_string.h"
#include "hal_thread.h"

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_CONFIG_H_

