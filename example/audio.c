/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    audio.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/12 2019 20:41
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/12 2019      create the file
 * 
 *     last modified: 17/12 2019 20:41
 */
#include "hal_config.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static hal_int32_t fd = -1;

static hal_int32_t _audio_data_cb(hal_char_t *buf, hal_uint32_t len)
{
    int ret = write(fd, buf, len);
    HalLogV("len: %d, ret: %d \n", len, ret);

    return 0;
}

hal_int32_t main(hal_int32_t argc, const hal_char_t *argv[])
{
    LogConfig_t log_config;
    log_config.level        = LOG_LEVEL_VERBOSE;
    log_config.color_flag   = LOG_COLOR_ON;
    log_config.buf_len      = 1024;

    HalLogInit(&log_config);

    AudioRecorderConfig_t audio_recorder_config;
    audio_recorder_config.rate          = AUDIO_RECORDER_RATE_48K;
    audio_recorder_config.channel       = AUDIO_RECORDER_CH_2;
    audio_recorder_config.bit           = AUDIO_RECORDER_S16_LE;

    audio_recorder_config.period_size   = 1024;
    audio_recorder_config.period_count  = 4;

    audio_recorder_config.data_cb       = _audio_data_cb;

    AudioRecorderHandle_t handle = HalAudioRecorderCreate(&audio_recorder_config);

    fd = open("test.pcm", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        HalLogE("open failed \n");
        return -1;
    }

    HalAudioRecorderStart(handle);
    Hal_sleep(10);
    HalAudioRecorderStop(handle);

    HalAudioRecorderDestroy(handle);
    HalLogFinal();
    close(fd);

    return 0;
}
