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

typedef enum {
    AUDIO_RECORDER_S8 = 1,
    AUDIO_RECORDER_S16_LE = 0,
    AUDIO_RECORDER_S16_BE = 2,
    AUDIO_RECORDER_S24_LE,
    AUDIO_RECORDER_S24_BE,
    AUDIO_RECORDER_S24_3LE,
    AUDIO_RECORDER_S24_3BE,
    AUDIO_RECORDER_S32_LE,
    AUDIO_RECORDER_S32_BE,

    AUDIO_RECORDER_MAX
} AudioRecorderBit_t;

typedef enum {
    AUDIO_RECORDER_CH_0,
    AUDIO_RECORDER_CH_1,
    AUDIO_RECORDER_CH_2,
    AUDIO_RECORDER_CH_3,
    AUDIO_RECORDER_CH_4,
    AUDIO_RECORDER_CH_5,
    AUDIO_RECORDER_CH_6,
    AUDIO_RECORDER_CH_7,
    AUDIO_RECORDER_CH_8,
} AudioRecorderChannel_t;

typedef enum {
    AUDIO_RECORDER_RATE_8K = 8 * 1000,
    AUDIO_RECORDER_RATE_16K = 16 * 1000,
    AUDIO_RECORDER_RATE_32K = 32 * 1000,
    AUDIO_RECORDER_RATE_48K = 48 * 1000,
} AudioRecorderRate_t;

typedef hal_int32_t (*HalAudioDataCB_t)(hal_char_t *buf, hal_uint32_t len);

typedef struct {
    AudioRecorderRate_t     rate;
    AudioRecorderChannel_t  channel;
    AudioRecorderBit_t      bit;

    hal_uint32_t            period_size;
    hal_uint32_t            period_count;

    HalAudioDataCB_t        data_cb;
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

