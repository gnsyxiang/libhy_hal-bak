/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_audio_recorder.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/03 2020 15:10
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/03 2020      create the file
 * 
 *     last modified: 10/03 2020 15:10
 */
#include "config.h"
#include "hal_config.h"

typedef enum {
    AUDIO_RECORDER_STATE_IDLE,
    AUDIO_RECORDER_STATE_RUNNING,
    AUDIO_RECORDER_STATE_STOPPING,

    AUDIO_RECORDER_STATE_MAX,
} audio_recorder_state_t;

typedef struct {
    audio_recorder_state_t state;
    AudioRecorderConfig_t config;

    ThreadHandle_t thread_handle;
    hal_int32_t is_running;
    ThreadSemHandle_t sem_thread_exit_sync;

    ThreadSemHandle_t wait_stop;
    ThreadSemHandle_t wait_start;
} audio_recorder_context_t;
#define AUDIO_RECORDER_CONTEXT_LEN (sizeof(audio_recorder_context_t))

static hal_int32_t audio_recorder_is_init = 0;

static hal_char_t *_recorder_state_2_str(audio_recorder_state_t state)
{
    static hal_char_t *state_str[] = {
        [AUDIO_RECORDER_STATE_IDLE]     = "AUDIO_RECORDER_STATE_IDLE",
        [AUDIO_RECORDER_STATE_RUNNING]  = "AUDIO_RECORDER_STATE_RUNNING",
        [AUDIO_RECORDER_STATE_STOPPING] = "AUDIO_RECORDER_STATE_STOPPING",
    };
    if (state < AUDIO_RECORDER_STATE_IDLE || state > AUDIO_RECORDER_STATE_STOPPING) {
        return "N/A";
    }
    return state_str[state];
}

static void _set_audio_recorder_state(audio_recorder_context_t *context, \
                                      audio_recorder_state_t state)
{
    Hal_LogT("state changes from %s to %s \n", \
            _recorder_state_2_str(context->state), \
            _recorder_state_2_str(state));
    context->state = state;
}

static hal_int32_t _check_audio_recorder_state(audio_recorder_context_t *context, \
                                               audio_recorder_state_t state)
{
  return (context->state == state);
}

static void _recorder_thread_break(audio_recorder_context_t *context)
{
    context->is_running = 1;
    HalSemWait(context->sem_thread_exit_sync);
}

static void _recorder_thread_loop(void *args)
{
    audio_recorder_context_t *context = (audio_recorder_context_t *)args;

    HalSemWait(context->wait_start);

    while (0 == context->is_running) {
        if (_check_audio_recorder_state(context, AUDIO_RECORDER_STATE_STOPPING)) {
            _set_audio_recorder_state(context, AUDIO_RECORDER_STATE_IDLE);

            HalSemPost(context->wait_stop);
            Hal_LogT("audio record is force stopped \n");

            HalSemWait(context->wait_start);
            Hal_LogT("audio record is started \n");
        }

        Hal_LogT("haha test \n");

        Hal_sleep(1);
    }

    HalSemPost(context->sem_thread_exit_sync);
}

static void _create_recorder_thread(audio_recorder_context_t *context)
{
    HalThreadLoopConfig_t   loop_config;
    Hal_memset(&loop_config, '\0', HAL_THREAD_LOOP_CONFIG_LEN);
    loop_config.loop = _recorder_thread_loop;
    loop_config.args = context;

    HalThreadConfig_t       thread_config;
    Hal_memset(&thread_config, '\0', HAL_THREAD_CONFIG_LEN);
    thread_config.name        = "mic_recorder";
    thread_config.stack_size  = STACK_NORMAL_SIZE;
    thread_config.priority    = HAL_THREAD_PRIORITY_HIGH;
    thread_config.loop_config = &loop_config;

    context->thread_handle = HalThreadCreate(&thread_config);
}

static void _destroy_recorder_thread(audio_recorder_context_t *context)
{
    HalThreadDestroy(context->thread_handle);
}

static inline audio_recorder_context_t *_context_init(AudioRecorderConfig_t *audio_recorder_config)
{
    audio_recorder_context_t *context = Hal_calloc(1, AUDIO_RECORDER_CONTEXT_LEN);
    if (NULL == context) {
        Hal_LogE("hal calloc faild \n");
        return NULL;
    }
    context->config               = *audio_recorder_config;
    context->state                = AUDIO_RECORDER_STATE_IDLE;

    context->sem_thread_exit_sync = HalSemInit(0, 0);
    context->wait_stop            = HalSemInit(0, 0);
    context->wait_start           = HalSemInit(0, 0);

    return context;
}

static inline void _context_final(audio_recorder_context_t **context)
{
    audio_recorder_context_t *context_tmp = *context;
    if (NULL != context_tmp) {
        HalSemDestroy(context_tmp->sem_thread_exit_sync);
        HalSemDestroy(context_tmp->wait_stop);
        HalSemDestroy(context_tmp->wait_start);

        Hal_free(context_tmp);
        context_tmp = NULL;
    }
}

void *HalAudioRecorderCreate(AudioRecorderConfig_t *audio_recorder_config)
{
    Hal_assert(NULL != audio_recorder_config);
    if (1 == audio_recorder_is_init) {
        Hal_LogW("hal audio recorder is init\n");
        return NULL;
    }

    audio_recorder_context_t *context = _context_init(audio_recorder_config);
    if (NULL == context) {
        Hal_LogE("context init faild \n");
        return NULL;
    }

    _create_recorder_thread(context);

    audio_recorder_is_init = 1;

    return context;
}

void HalAudioRecorderDestroy(AudioRecorderHandle_t handle)
{
    Hal_assert(NULL != handle);
    audio_recorder_context_t *context = (audio_recorder_context_t *)handle;

    _recorder_thread_break(context);
    _destroy_recorder_thread(context);

    _context_final(&context);
}

hal_int32_t HalAudioRecorderStart(AudioRecorderHandle_t handle)
{
    Hal_assert(NULL != handle);
    audio_recorder_context_t *context = (audio_recorder_context_t *)handle;

    if (_check_audio_recorder_state(context, AUDIO_RECORDER_STATE_RUNNING)) {
        Hal_LogE("wrong state");
        return HAL_INVALID_STATE_ERR;
    }

    _set_audio_recorder_state(context, AUDIO_RECORDER_STATE_RUNNING);
    HalSemPost(context->wait_start);

    Hal_LogT("audio recorder start \n");
    return HAL_NO_ERR;
}

hal_int32_t HalAudioRecorderStop(AudioRecorderHandle_t handle)
{
    Hal_assert(NULL != handle);
    audio_recorder_context_t *context = (audio_recorder_context_t *)handle;

    if (_check_audio_recorder_state(context, AUDIO_RECORDER_STATE_STOPPING)) {
        Hal_LogE("wrong state");
        return HAL_INVALID_STATE_ERR;
    }

    _set_audio_recorder_state(context, AUDIO_RECORDER_STATE_STOPPING);
    HalSemWait(context->wait_stop);

    Hal_LogT("audio recorder stop \n");
    return HAL_NO_ERR;
}

hal_int32_t HalAudioRecorderIsActive(AudioRecorderHandle_t handle)
{
    Hal_assert(NULL != handle);
    audio_recorder_context_t *context = (audio_recorder_context_t *)handle;

    return _check_audio_recorder_state(context, AUDIO_RECORDER_STATE_RUNNING);
}

hal_int32_t HalAudioRecorderParamGet(AudioRecorderHandle_t handle, AudioRecorderParam_t type, void *args)
{
    return HAL_NO_ERR;
}

hal_int32_t HalAudioRecorderParamSet(AudioRecorderHandle_t handle, AudioRecorderParam_t type, void *args)
{
    return HAL_NO_ERR;
}

