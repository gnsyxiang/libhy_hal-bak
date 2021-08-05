/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_file.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    05/08 2021 15:39
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        05/08 2021      create the file
 * 
 *     last modified: 05/08 2021 15:39
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>

#include "hy_file.h"

#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

long open_file_get_len(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (NULL == fp) {
        LOGE("fopen %s faild", path);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    if (len <= 0) {
        printf("threre is no data in the %s file \n", path);
        return -1;
    }

    fclose(fp);

    return len;
}

static hy_s32_t _set_fcntl(hy_s32_t fd, long arg)
{
    hy_s32_t flags;

    if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
        flags = 0;

    return fcntl(fd, F_SETFL, flags | arg);
}

hy_s32_t file_set_nonblocking(hy_s32_t fd)
{
    return _set_fcntl(fd, O_NONBLOCK);
}

/*
 * 作用: 当fork子进程后，仍然可以使用fd。
 *       但执行exec后系统就会自动关闭进程中的fd
 */
hy_s32_t file_close_on_exec(hy_s32_t fd)
{
    return _set_fcntl(fd, FD_CLOEXEC);
}

ssize_t HyFileWrite(hy_s32_t fd, const void *buf, size_t cnt)
{
    return write(fd, buf, cnt);
}

ssize_t HyFileWriteCnt(hy_s32_t fd, const void *buf, size_t cnt)
{
    hy_s32_t ret;
    size_t nleft;
    const char *ptr;

    ptr = buf;
    nleft = cnt;

    while (nleft > 0) {
        if ((ret = write(fd, ptr, nleft)) <= 0) {
            if (ret < 0 && errno == EINTR)
                ret = 0;
            else
                return -1;
        }

        nleft -= ret;
        ptr   += ret;
    }

    return cnt;
}

ssize_t HyFileRead(hy_s32_t fd, void *buf, size_t cnt)
{
    return read(fd, buf, cnt);
}

ssize_t HyFileReadCnt(hy_s32_t fd, void *buf, size_t cnt)
{
    hy_s32_t ret;
    size_t nleft;
    size_t offset = 0;

    nleft = cnt;

    while (nleft > 0) {
        if ((ret = read(fd, buf + offset, nleft)) < 0) {
            if (errno == EINTR)
                ret = 0;
            else
                return -1;
        } else if (ret == 0)
            break;

        nleft  -= ret;
        offset += ret;
    }

    return offset;
}

ssize_t HyfileReadCntTimeout(hy_s32_t fd, void *buf, size_t cnt, hy_u32_t timeout_ms)
{
    hy_s32_t len = 0;
    fd_set rfds;
    struct timeval time;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

	time.tv_sec = timeout_ms / 1000;
	time.tv_usec = (timeout_ms % 1000) * 1000;

    size_t ret = select(fd+1, &rfds, NULL, NULL, &time);
    switch (ret) {
        case -1:
            LOGE("select error");
            cnt = -1;
            break;
        case 0:
            LOGE("select timeout");
            cnt = -1;
            break;
        default:
            if ((len = HyFileReadCnt(fd, buf, cnt)) == -1) {
                LOGE("read error");
                cnt = -1;
            }
            break;
    }

    return cnt;
}

