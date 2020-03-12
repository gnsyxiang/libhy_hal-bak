/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_audio_recorder.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/03 2020 15:09
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/03 2020      create the file
 * 
 *     last modified: 10/03 2020 15:09
 */
#ifndef __LIBHAL_INCLUDE_HAL_HAL_AUDIO_RECORDER_H_
#define __LIBHAL_INCLUDE_HAL_HAL_AUDIO_RECORDER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_config.h"

typedef enum {
    AUDIO_RECORDER_PARAM_RATE,
    AUDIO_RECORDER_PARAM_CHANNEL,
    AUDIO_RECORDER_PARAM_BIT,

    AUDIO_RECORDER_PARAM_MAX,
} AudioRecorderParam_t;

typedef struct {
    hal_int32_t rate;
    hal_int32_t channel;
    hal_int32_t bit;
} AudioRecorderConfig_t;

typedef void * AudioRecorderHandle_t;

void *HalAudioRecorderCreate(AudioRecorderConfig_t *audio_recorder_config);
void HalAudioRecorderDestroy(AudioRecorderHandle_t handle);

hal_int32_t HalAudioRecorderStart(AudioRecorderHandle_t handle);
hal_int32_t HalAudioRecorderStop(AudioRecorderHandle_t handle);
hal_int32_t HalAudioRecorderIsActive(AudioRecorderHandle_t handle);

hal_int32_t HalAudioRecorderParamGet(AudioRecorderHandle_t handle, AudioRecorderParam_t type, void *args);
hal_int32_t HalAudioRecorderParamSet(AudioRecorderHandle_t handle, AudioRecorderParam_t type, void *args);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_HAL_AUDIO_RECORDER_H_

