/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_audio_recorder_internal.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    27/03 2020 22:41
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        27/03 2020      create the file
 * 
 *     last modified: 27/03 2020 22:41
 */
#ifndef __LIBHAL_INCLUDE_HAL_HAL_AUDIO_RECORDER_INTERNAL_H_
#define __LIBHAL_INCLUDE_HAL_HAL_AUDIO_RECORDER_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "hal_config.h"

typedef enum {
    AUDIO_RECORDER_STATE_IDLE,
    AUDIO_RECORDER_STATE_RUNNING,
    AUDIO_RECORDER_STATE_STOPPING,

    AUDIO_RECORDER_STATE_MAX,
} audio_recorder_state_t;

typedef struct {
    audio_recorder_state_t  state;

    ThreadHandle_t          thread_handle;
    hal_int32_t             is_running;
    ThreadSemHandle_t       sem_thread_exit_sync;

    ThreadSemHandle_t       wait_stop;
    ThreadSemHandle_t       wait_start;

    HalAudioDataCB_t        data_cb;

    void                    *hal_audio_handle;
    hal_uint32_t            period_size;
    hal_uint32_t            period_count;
} audio_recorder_context_t;
#define AUDIO_RECORDER_CONTEXT_LEN (sizeof(audio_recorder_context_t))


#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_HAL_AUDIO_RECORDER_INTERNAL_H_

