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
#include "hal_thread_internal.h"

hal_int32_t LinuxAudioCreate(void *args)
{
    return 0;
}

hal_int32_t LinuxAudioDestroy(void *args)
{
    return 0;
}

hal_int32_t LinuxAudioStart(void *args)
{
    return 0;
}

hal_int32_t LinuxAudioStop(void *args)
{
    return 0;
}

void AudioSystemInit(hal_system_init_cb_t *system_cb)
{
    Hal_assert(NULL != system_cb);

    system_cb->create   = LinuxAudioCreate;
    system_cb->destroy  = LinuxAudioDestroy;

    system_cb->start    = LinuxAudioStart;
    system_cb->stop     = LinuxAudioStop;
}

