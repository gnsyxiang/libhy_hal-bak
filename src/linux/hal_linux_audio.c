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
#include "hal_linux_audio.h"
#include "hal_audio_recorder_internal.h"
#include "hal_type.h"
#include "hal_mem.h"
#include "hal_log.h"
#include "hal_assert.h"

#include "tinyalsa/pcm.h"
#include "tinyalsa/mixer.h"

typedef struct hal_audio_para {
    struct pcm      *pcm;
    struct mixer    *mixer;
    hal_uint32_t    bytes_per_frame;
    hal_uint32_t    frames_per_sec;
    hal_uint32_t    buffer_size;

    hal_uint32_t    card;
    hal_uint32_t    device;
    hal_uint32_t    pcm_flags;
} linux_audio_context_t;
#define LINUX_AUDIO_CONTEXT_LEN (sizeof(linux_audio_context_t))

static inline linux_audio_context_t *_context_init(void *config_tmp)
{
    linux_audio_context_t *context = Hal_calloc(1, LINUX_AUDIO_CONTEXT_LEN);
    if (NULL == context) {
        HalLogE("hal calloc failed \n");
        return NULL;
    }


    return context;
}

static inline void _context_final(linux_audio_context_t **context_tmp)
{
    linux_audio_context_t *context = *context_tmp;
    if (NULL != context) {
        Hal_free(context);
        *context_tmp = NULL;
    }
}

static inline void _dump_audio_recorder_config(struct pcm_config *config, AudioRecorderBit_t bit)
{
    hal_char_t *format_str[] = {
        "PCM_FORMAT_S16_LE",
        "PCM_FORMAT_S8",
        "PCM_FORMAT_S16_BE",
        "PCM_FORMAT_S24_LE",
        "PCM_FORMAT_S24_BE",
        "PCM_FORMAT_S24_3LE",
        "PCM_FORMAT_S24_3BE",
        "PCM_FORMAT_S32_LE",
        "PCM_FORMAT_S32_BE",
        "PCM_FORMAT_MAX",
    };

    HalLogT("capture \n");
    HalLogT("channel:\t\t%d \n",          config->channels);
    HalLogT("rate:\t\t\t%d \n",           config->rate);
    HalLogT("bit:\t\t\t%s \n",            format_str[bit]);

    HalLogT("period_size:\t\t%d \n",      config->period_size);
    HalLogT("period_count:\t\t%d \n",     config->period_count);
}

static hal_int32_t _tinyalsa_open(linux_audio_context_t *context, AudioRecorderConfig_t *audio_config)
{
    hal_uint32_t format[] = {
        PCM_FORMAT_S16_LE,
        PCM_FORMAT_S8,
        PCM_FORMAT_S16_BE,
        PCM_FORMAT_S24_LE,
        PCM_FORMAT_S24_BE,
        PCM_FORMAT_S24_3LE,
        PCM_FORMAT_S24_3BE,
        PCM_FORMAT_S32_LE,
        PCM_FORMAT_S32_BE,
        PCM_FORMAT_MAX
    };

    struct pcm_config pcm_config = {0};

    pcm_config.channels     = audio_config->channel;
    pcm_config.rate         = audio_config->rate;
    pcm_config.format       = format[audio_config->bit];

    pcm_config.period_size  = audio_config->period_size;
    pcm_config.period_count = audio_config->period_count;

    _dump_audio_recorder_config(&pcm_config, audio_config->bit);

    context->card            = 0;
    context->device          = 0;
    context->pcm_flags       = PCM_IN;

    context->pcm = pcm_open(context->card, context->device, context->pcm_flags, &pcm_config);
    if(NULL == context->pcm) {
        HalLogE("failed to allocate memory for PCM \n");
        goto L_TINYALSA_OPEN_1;
    } else if (!pcm_is_ready(context->pcm)){
        HalLogE("failed to open PCM, %s\n", pcm_get_error(context->pcm));
        goto L_TINYALSA_OPEN_2;
    }

    context->mixer = mixer_open(context->card);
    if(NULL == context->mixer){
        HalLogE("mixer_open failed (%s)\n", pcm_get_error(context->pcm));
        goto L_TINYALSA_OPEN_2;
    }

    context->bytes_per_frame = pcm_frames_to_bytes(context->pcm, 1);
    context->frames_per_sec = pcm_get_rate(context->pcm);
    context->buffer_size = pcm_frames_to_bytes(context->pcm, pcm_get_buffer_size(context->pcm));

    return HAL_NO_ERR;
L_TINYALSA_OPEN_2:
    pcm_close(context->pcm);
L_TINYALSA_OPEN_1:
    return HAL_INVALID_HANDLE_ERR;
}

static void _tinyalsa_close(linux_audio_context_t *context)
{
    if (context->mixer) {
        mixer_close(context->mixer);
    }

    if (context->pcm) {
        pcm_close(context->pcm);
    }
}

static hal_int32_t _linux_audio_open(void **handle, void *config_tmp)
{
    Hal_assert(NULL != handle);
    Hal_assert(NULL != config_tmp);
    hal_int32_t ret = HAL_NO_ERR;

    linux_audio_context_t *context = _context_init(config_tmp);
    if (NULL == context) {
        HalLogE("context init faild \n");
        ret = HAL_ALLOC_MEM_ERR;
        goto L_AUDIO_OPEN_1;
    }

    if (HAL_NO_ERR != _tinyalsa_open(context, config_tmp)) {
        HalLogE("context init faild \n");
        ret = HAL_ALLOC_MEM_ERR;
        goto L_AUDIO_OPEN_2;
    }

    *handle = context;
    return HAL_NO_ERR;
L_AUDIO_OPEN_2:
    _context_final(&context);
L_AUDIO_OPEN_1:
    return ret;
}

static hal_int32_t _linux_audio_close(void *handle)
{
    Hal_assert(NULL != handle);

    linux_audio_context_t *context = handle;
    _tinyalsa_close(context);
    _context_final(&context);

    return HAL_NO_ERR;
}

static hal_int32_t _linux_audio_read(void *handle, const hal_char_t *buf, hal_uint32_t len)
{
    Hal_assert(NULL != handle);
    Hal_assert(NULL != buf);

    linux_audio_context_t *context = handle;
    hal_uint32_t bytes_per_frame = context->bytes_per_frame;

    if(len % bytes_per_frame){
        HalLogE("the len is error \n");
        return HAL_INVALID_PARAM_ERR;
    }

    int read_count = pcm_readi(context->pcm, (void *)buf, len / bytes_per_frame);
    // HalLogD("read_count: %d, len: %d \n", read_count, len);
    if (read_count < 0) {
        HalLogE("pcm_readi read count failed \n");
        return HAL_INVALID_STATE_ERR;
    }

    return pcm_frames_to_bytes(context->pcm, read_count);
}

void AudioSystemInit(hal_system_init_cb_t *system_cb)
{
    Hal_assert(NULL != system_cb);

    system_cb->create   = _linux_audio_open;
    system_cb->destroy  = _linux_audio_close;

    system_cb->read     = _linux_audio_read;
}

