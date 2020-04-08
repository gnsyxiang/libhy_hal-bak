/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_file.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "hal_file.h"

hal_int32_t Hal_open(const char *pathname, int flags, mode_t mode)
{
    return open(pathname, flags, mode);
}

hal_int32_t Hal_close(hal_int32_t fd)
{
    return close(fd);
}

ssize_t Hal_read(hal_int32_t fd, void *buf, size_t count)
{
    return read(fd, buf, count);
}

ssize_t Hal_write(hal_int32_t fd, const void *buf, size_t count)
{
    return write(fd, buf, count);
}

hal_int32_t Hal_access(const hal_char_t *pathname, hal_int32_t mode)
{
    return access(pathname, mode);
}

off_t Hal_lseek(hal_int32_t fd, off_t offset, hal_int32_t whence)
{
    return lseek(fd, offset, whence);
}




