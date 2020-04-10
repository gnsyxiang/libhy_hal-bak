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
#include "hal_audio_recorder.h"
#include "hal_audio_recorder_internal.h"
#include "hal_log.h"
#include "hal_mem.h"

#include "hal_linux_audio.h"

static hal_int32_t audio_recorder_is_init = 0;
static hal_system_init_cb_t g_system_cb;

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
    HalLogT("state changes from %s to %s \n", \
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
    HalSemPost(context->wait_start);
    HalSemWait(context->sem_thread_exit_sync);
}

static void _recorder_thread_loop(void *args)
{
    audio_recorder_context_t *context = (audio_recorder_context_t *)args;

    HalSemWait(context->wait_start);

    int ret = 0;
    hal_uint32_t len = context->period_size * context->period_count;
    hal_char_t *buf = Hal_calloc(1, len);
    if (NULL == buf) {
        HalLogE("calloc failed \n");
        return;
    }

    while (0 == context->is_running) {
        if (_check_audio_recorder_state(context, AUDIO_RECORDER_STATE_STOPPING)) {
            _set_audio_recorder_state(context, AUDIO_RECORDER_STATE_IDLE);

            HalSemPost(context->wait_stop);
            HalLogT("audio record is force stopped \n");

            HalSemWait(context->wait_start);
            HalLogT("audio record is started \n");

            if (1 == context->is_running) {
                break;
            }
        }

        if (NULL != g_system_cb.read) {
            ret = g_system_cb.read(context->hal_audio_handle, buf, len);
        }

        if (NULL != context->data_cb) {
            context->data_cb(buf, ret);
        }
    }

    Hal_free(buf);
    buf = NULL;

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
        HalLogE("hal calloc faild \n");
        return NULL;
    }
    context->state                = AUDIO_RECORDER_STATE_IDLE;
    context->data_cb              = audio_recorder_config->data_cb;

    context->sem_thread_exit_sync = HalSemInit(0, 0);
    context->wait_stop            = HalSemInit(0, 0);
    context->wait_start           = HalSemInit(0, 0);

    context->period_size            = audio_recorder_config->period_size;
    context->period_count           = audio_recorder_config->period_count;

    return context;
}

static inline void _context_final(audio_recorder_context_t **context_tmp)
{
    audio_recorder_context_t *context = *context_tmp;
    if (NULL != context) {
        HalSemDestroy(context->sem_thread_exit_sync);
        HalSemDestroy(context->wait_stop);
        HalSemDestroy(context->wait_start);

        Hal_free(context);
        *context_tmp = NULL;
    }
}

void *HalAudioRecorderCreate(AudioRecorderConfig_t *audio_recorder_config)
{
    if (NULL == audio_recorder_config) {
        HalLogE("the param is NULL \n");
        goto L_ERROR_INIT_1;
    }

    if (1 == audio_recorder_is_init) {
        HalLogW("hal audio recorder is init\n");
        goto L_ERROR_INIT_1;
    }

    AudioSystemInit(&g_system_cb);

    audio_recorder_context_t *context = _context_init(audio_recorder_config);
    if (NULL == context) {
        HalLogE("context init faild \n");
        goto L_ERROR_INIT_1;
    }

    if (NULL == g_system_cb.create \
            || 0 != g_system_cb.create(&context->hal_audio_handle, audio_recorder_config)) {
        HalLogE("call init faild \n");
        goto L_ERROR_INIT_2;
    }

    _create_recorder_thread(context);

    audio_recorder_is_init = 1;

    return context;
L_ERROR_INIT_2:
    _context_final(&context);
L_ERROR_INIT_1:
    return NULL;
}

void HalAudioRecorderDestroy(AudioRecorderHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the param is NULL \n");
        return;
    }

    audio_recorder_context_t *context = handle;

    _recorder_thread_break(context);
    _destroy_recorder_thread(context);

    if (NULL == g_system_cb.destroy || 0 != g_system_cb.destroy(context->hal_audio_handle)) {
        HalLogE("call final faild \n");
    }

    _context_final(&context);
}

hal_int32_t HalAudioRecorderStart(AudioRecorderHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the param is NULL \n");
        return HAL_INVALID_HANDLE_ERR;
    }

    audio_recorder_context_t *context = (audio_recorder_context_t *)handle;

    if (_check_audio_recorder_state(context, AUDIO_RECORDER_STATE_RUNNING)) {
        HalLogE("wrong state");
        return HAL_INVALID_STATE_ERR;
    }

    _set_audio_recorder_state(context, AUDIO_RECORDER_STATE_RUNNING);
    HalSemPost(context->wait_start);

    HalLogT("audio recorder start \n");
    return HAL_NO_ERR;
}

hal_int32_t HalAudioRecorderStop(AudioRecorderHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the param is NULL \n");
        return HAL_INVALID_HANDLE_ERR;
    }

    audio_recorder_context_t *context = (audio_recorder_context_t *)handle;

    if (_check_audio_recorder_state(context, AUDIO_RECORDER_STATE_STOPPING)) {
        HalLogE("wrong state");
        return HAL_INVALID_STATE_ERR;
    }

    _set_audio_recorder_state(context, AUDIO_RECORDER_STATE_STOPPING);
    HalSemWait(context->wait_stop);

    HalLogT("audio recorder stop \n");
    return HAL_NO_ERR;
}

hal_int32_t HalAudioRecorderIsActive(AudioRecorderHandle_t handle)
{
    if (NULL == handle) {
        HalLogE("the param is NULL \n");
        return HAL_INVALID_HANDLE_ERR;
    }

    audio_recorder_context_t *context = (audio_recorder_context_t *)handle;

    return _check_audio_recorder_state(context, AUDIO_RECORDER_STATE_RUNNING);
}

hal_int32_t HalAudioRecorderParamGet(AudioRecorderHandle_t handle, AudioRecorderParam_t type, void *args)
{
    if (NULL == handle) {
        HalLogE("the param is NULL \n");
        return HAL_INVALID_HANDLE_ERR;
    }

    return HAL_NO_ERR;
}

hal_int32_t HalAudioRecorderParamSet(AudioRecorderHandle_t handle, AudioRecorderParam_t type, void *args)
{
    if (NULL == handle) {
        HalLogE("the param is NULL \n");
        return HAL_INVALID_HANDLE_ERR;
    }

    return HAL_NO_ERR;
}

