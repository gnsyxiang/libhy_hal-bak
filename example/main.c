/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    main.c
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
#include "config.h"
#include "hal_config.h"

#ifdef HAVE_RTT_HAL
hal_int32_t main(hal_int32_t argc, const hal_int8_t *argv[])
{
    return 0;
}
#endif

#ifdef HAVE_LINUX_HAL
hal_int32_t main(hal_int32_t argc, const hal_int8_t *argv[])
{
    AudioRecorderConfig_t audio_recorder_config;
    audio_recorder_config.rate    = 16 * 1000;
    audio_recorder_config.channel = 2;
    audio_recorder_config.bit     = 16;

    AudioRecorderHandle_t handle = HalAudioRecorderCreate(&audio_recorder_config);

    while (1) {
        HalAudioRecorderStart(handle);
        Hal_sleep(5);
        HalAudioRecorderStop(handle);
    }

    HalAudioRecorderDestroy(handle);

    return 0;
}
#endif

