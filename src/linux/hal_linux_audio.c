/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_linux_audio.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    12/03 2020 16:36
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        12/03 2020      create the file
 * 
 *     last modified: 12/03 2020 16:36
 */
#include "hal_config.h"
#include "hal_linux_audio.h"

static hal_int32_t _linux_audio_open(void *args)
{
    return 0;
}

static hal_int32_t _linux_audio_close(void *args)
{
    return 0;
}

static hal_int32_t _linux_audio_read(void *context, const hal_char_t *buf, hal_uint32_t len)
{
    return 0;
}

void AudioSystemInit(hal_system_init_cb_t *system_cb)
{
    Hal_assert(NULL != system_cb);

    system_cb->create   = _linux_audio_open;
    system_cb->destroy  = _linux_audio_close;

    system_cb->read     = _linux_audio_read;
}

