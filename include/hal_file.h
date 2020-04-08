/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_file.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    06/04 2020 18:24
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        06/04 2020      create the file
 * 
 *     last modified: 06/04 2020 18:24
 */
#ifndef __LIBHAL_INCLUDE_HAL_FILE_H_
#define __LIBHAL_INCLUDE_HAL_FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <fcntl.h>
#include "hal_type.h"

hal_int32_t Hal_open(const hal_char_t *pathname, hal_int32_t flags, mode_t mode);
hal_int32_t Hal_close(hal_int32_t fd);

ssize_t Hal_read(hal_int32_t fd, void *buf, size_t count);
ssize_t Hal_write(hal_int32_t fd, const void *buf, size_t count);

hal_int32_t Hal_access(const hal_char_t *pathname, hal_int32_t mode);
off_t Hal_lseek(hal_int32_t fd, off_t offset, hal_int32_t whence);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_FILE_H_

