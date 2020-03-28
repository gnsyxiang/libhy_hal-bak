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

static hal_int32_t _audio_data_cb(hal_char_t *buf, hal_uint32_t len)
{
    HalLogT("buf: %s, len: %d \n", buf, len);

    return 0;
}

hal_int32_t main(hal_int32_t argc, const hal_char_t *argv[])
{
    LogConfig_t log_config;
    log_config.level        = LOG_LEVEL_VERBOSE;
    log_config.color_flag   = LOG_COLOR_ON;

    HalLogInit(&log_config);

    AudioRecorderConfig_t audio_recorder_config;
    audio_recorder_config.rate    = 16 * 1000;
    audio_recorder_config.channel = 2;
    audio_recorder_config.bit     = 16;
    audio_recorder_config.data_cb = _audio_data_cb;

    AudioRecorderHandle_t handle = HalAudioRecorderCreate(&audio_recorder_config);

    while (1) {
        HalAudioRecorderStart(handle);
        Hal_sleep(5);
        HalAudioRecorderStop(handle);
    }

    HalAudioRecorderDestroy(handle);
    HalLogFinal();

    return 0;
}
