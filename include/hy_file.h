/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_file.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    05/08 2021 15:43
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        05/08 2021      create the file
 * 
 *     last modified: 05/08 2021 15:43
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_FILE_H_
#define __LIBHY_HAL_INCLUDE_HY_FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "hy_utils/hy_type.h"

ssize_t HyFileRead(hy_s32_t fd, void *buf, size_t cnt);
ssize_t HyFileReadCnt(hy_s32_t fd, void *buf, size_t cnt);
ssize_t HyfileReadCntTimeout(hy_s32_t fd, void *buf, size_t cnt, hy_u32_t timeout_ms);

ssize_t HyFileWrite(hy_s32_t fd, const void *buf, size_t cnt);
ssize_t HyFileWriteCnt(hy_s32_t fd, const void *buf, size_t cnt);

#ifdef __cplusplus
}
#endif

#endif

