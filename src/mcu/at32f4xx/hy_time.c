/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_time.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    19/08 2021 19:48
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        19/08 2021      create the file
 * 
 *     last modified: 19/08 2021 19:48
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hy_time.h"
#include "inside_time.h"

#include "at32f4xx_rcc.h"
#include "at32f4xx_tim.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_log.h"
#include "hy_utils/hy_assert.h"

#define ALONE_DEBUG 1

#define _DEFINE_TIME()              \
    TMR_Type *time[] = {            \
        NULL,                       \
        TMR1, TMR2, TMR3, TMR4,     \
        TMR5, TMR6, TMR7, TMR8,     \
        TMR9, TMR10, TMR11, TMR12,  \
        TMR13, TMR14,               \
    }

typedef struct {
    HyTimeNum_t num;

    HyTimeConfigSave_t config_save;
} _time_context_t;

static _time_context_t *context_array[HY_TIME_NUM_MAX] = {NULL};

static void _time_irq_handler(HyTimeNum_t num)
{
    if (context_array[num]) {
        _DEFINE_TIME();

        if (TMR_GetINTStatus(time[num], TMR_INT_Overflow) == SET)  {
            TMR_ClearITPendingBit(time[num], TMR_INT_Overflow);

            HyTimeConfigSave_t *time_config = &context_array[num]->config_save;
            if (time_config->time_cb) {
                time_config->time_cb(time_config->args);
            }
        }
    }
}

void TMR1_OV_TMR10_IRQHandler(void)
{
    _time_irq_handler(HY_TIME_NUM_1);
}

void TMR2_GLOBAL_IRQHandler(void)
{
    _time_irq_handler(HY_TIME_NUM_2);
}

void HyTimeEnable(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _DEFINE_TIME();
    _time_context_t *context = handle;

    TMR_Cmd(time[context->num], ENABLE);
}

void HyTimeDisable(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _DEFINE_TIME();
    _time_context_t *context = handle;

    TMR_Cmd(time[context->num], DISABLE);
}

static void _init_time_func(HyTimeConfig_t *time_config)
{
    _DEFINE_TIME();

    hy_u32_t rcc[][2] = {
        {0, 0},
        {2, RCC_APB2PERIPH_TMR1},   {1, RCC_APB1PERIPH_TMR2},   {1, RCC_APB1PERIPH_TMR3},   {1, RCC_APB1PERIPH_TMR4},
        {1, RCC_APB1PERIPH_TMR5},   {1, RCC_APB1PERIPH_TMR6},   {1, RCC_APB1PERIPH_TMR7},   {2, RCC_APB2PERIPH_TMR8},
        {2, RCC_APB2PERIPH_TMR9},   {2, RCC_APB2PERIPH_TMR10},  {2, RCC_APB2PERIPH_TMR11},  {1, RCC_APB1PERIPH_TMR12},
        {1, RCC_APB1PERIPH_TMR13},  {1, RCC_APB1PERIPH_TMR14},
    };

    if (rcc[time_config->num][0] == 1) {
        RCC_APB1PeriphClockCmd(rcc[time_config->num][1], ENABLE);
    } else {
        RCC_APB2PeriphClockCmd(rcc[time_config->num][1], ENABLE);
    }

    NVIC_InitType NVIC_InitStructure;
    TMR_TimerBaseInitType  TMR_TMReBaseStructure;
    TMR_TimeBaseStructInit(&TMR_TMReBaseStructure);
    hy_u16_t clk_div;

    switch (time_config->num) {
        case HY_TIME_NUM_1:
            #define _TIME1_CNT (40)
            clk_div = (uint16_t) (SystemCoreClock / (_TIME1_CNT * 1000)) - 1;

            TMR_TMReBaseStructure.TMR_DIV = clk_div; // 预分频器, 使用40KHz频率计数
            TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;
            TMR_TMReBaseStructure.TMR_Period = _TIME1_CNT - 1; // 计数周期1ms，因为从0开始计数，所以减1
            TMR_TMReBaseStructure.TMR_ClockDivision = TMR_CKD_DIV1;

            NVIC_InitStructure.NVIC_IRQChannel = TMR1_OV_TMR10_IRQn;
            break;
        case HY_TIME_NUM_8:
            NVIC_InitStructure.NVIC_IRQChannel = TMR8_OV_TMR13_IRQn;
            break;

        case HY_TIME_NUM_2:
            #define _TIME1_CNT (40)
            clk_div = (uint16_t) (SystemCoreClock / (_TIME1_CNT * 1000)) - 1;

            TMR_TMReBaseStructure.TMR_DIV = clk_div;
            TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;
            TMR_TMReBaseStructure.TMR_Period = _TIME1_CNT - 1;
            TMR_TMReBaseStructure.TMR_ClockDivision = TMR_CKD_DIV1;

            NVIC_InitStructure.NVIC_IRQChannel = TMR2_GLOBAL_IRQn;
            break;
        case HY_TIME_NUM_3:
            NVIC_InitStructure.NVIC_IRQChannel = TMR3_GLOBAL_IRQn;
            break;
        case HY_TIME_NUM_4:
            NVIC_InitStructure.NVIC_IRQChannel = TMR4_GLOBAL_IRQn;
            break;
        case HY_TIME_NUM_5:
            NVIC_InitStructure.NVIC_IRQChannel = TMR5_GLOBAL_IRQn;
            break;
        case HY_TIME_NUM_6:
            NVIC_InitStructure.NVIC_IRQChannel = TMR6_GLOBAL_IRQn;
            break;
        case HY_TIME_NUM_7:
            NVIC_InitStructure.NVIC_IRQChannel = TMR7_GLOBAL_IRQn;
            break;
        default:
            break;
    }

    TMR_TimeBaseInit(time[time_config->num], &TMR_TMReBaseStructure);

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    if (time_config->flag == HY_TIME_FLAG_ENABLE) {
        TMR_INTConfig(time[time_config->num], TMR_INT_Overflow, ENABLE);
        TMR_Cmd(time[time_config->num], ENABLE);
    }
}

void HyTimeDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    _time_context_t *context = *handle;

    context_array[context->num] = NULL;

    HY_FREE(handle);
}

void *HyTimeCreate(HyTimeConfig_t *time_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!time_config, NULL);

    _time_context_t *context = NULL;

    do {
        context = (_time_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        HY_MEMCPY(&context->config_save, &time_config->config_save);
        context->num                    = time_config->num;
        context_array[time_config->num] = context;

        _init_time_func(time_config);

        LOGI("time %s create successful \n", HY_TIME_NUM_2_STR(time_config->num));
        return context;
    } while (0);

    HyTimeDestroy((void **)&context);
    return NULL;
}

