/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_time.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 20:31
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 20:31
 */
#include <stdio.h>

#include "hy_time.h"
#include "inside_time.h"

#include "bt.h"
#include "lptim.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

#define TIME_0_CNT      (500)       // 定时1ms
#define TIME_0_MS       (1)

// #define LP_TIME_0_CNT   (0)         // 定时2s
// #define LP_TIME_0_MS    (2000)
#define LP_TIME_0_CNT   (32768)     // 定时1s
#define LP_TIME_0_MS    (1000)

typedef struct {
    HyTimeConfigSave_t config_save;

    HyTimeNum_t         num;
} _time_context_t;

static _time_context_t *context_arr[HY_TIME_NUM_MAX] = {0};

static void _delay_com(size_t cnt, size_t base)
{
    uint32_t u32end;
    size_t start = SystemCoreClock / base;

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    while (cnt-- > 0) {
        SysTick->VAL  = 0;
        u32end = 0x1000000 - start;

        while (SysTick->VAL > u32end) {
            ;
        }
    }

    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

void HyTimeDelayMs(size_t ms)
{
    _delay_com(ms, 1000);
}

void HyTimeDelayUs(size_t us)
{
    _delay_com(us, 1000000);
}

#define _TIME_CB(num, ms)                                               \
    do {                                                                \
        _time_context_t *context = context_arr[num];                    \
        if (context) {                                                  \
            HyTimeConfigSave_t *config_save = &context->config_save;    \
            if (config_save->time_cb) {                                 \
                config_save->time_cb(ms, config_save->args);            \
            }                                                           \
        }                                                               \
    } while (0)

void Tim0_IRQHandler(void)
{
    if (TRUE == Bt_GetIntFlag(TIM0, BtUevIrq)) {
        Bt_ClearIntFlag(TIM0,BtUevIrq);

        _TIME_CB(HY_TIME_NUM_0, TIME_0_MS);
    }
}

void LpTim_IRQHandler(void)
{
    if (TRUE == Lptim_GetItStatus(M0P_LPTIMER)) {
        Lptim_ClrItStatus(M0P_LPTIMER);

        _TIME_CB(HY_TIME_NUM_LP_0, LP_TIME_0_MS);
    }
}

static void _time0_init(HyTimeConfig_t *time_config)
{
    hy_u16_t cnt = 0x10000 - time_config->us;

    stc_bt_mode0_cfg_t stcBtBaseCfg;
    memset(&stcBtBaseCfg, '\0', sizeof(stcBtBaseCfg));

    Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, TRUE); //Base Timer外设时钟使能

    stcBtBaseCfg.enWorkMode = BtWorkMode0;          //定时器模式
    stcBtBaseCfg.enCT       = BtTimer;              //定时器功能，计数时钟为内部PCLK
    stcBtBaseCfg.enPRS      = BtPCLKDiv8;           //PCLK/64
    stcBtBaseCfg.enCntMode  = Bt16bitArrMode;       //自动重载16位计数器/定时器
    stcBtBaseCfg.bEnTog     = FALSE;
    stcBtBaseCfg.bEnGate    = FALSE;
    stcBtBaseCfg.enGateP    = BtGatePositive;
    Bt_Mode0_Init(TIM0, &stcBtBaseCfg);             //TIM0 的模式0功能初始化

    Bt_M0_ARRSet(TIM0, cnt);                //设置重载值(ARR = 0x10000 - 周期)
    Bt_M0_Cnt16Set(TIM0, cnt);              //设置计数初值

    Bt_ClearIntFlag(TIM0,BtUevIrq);                 //清中断标志   
    Bt_Mode0_EnableIrq(TIM0);                       //使能TIM0中断(模式0时只有一个中断)
    EnableNvic(TIM0_IRQn, IrqLevel3, TRUE);         //TIM0中断使能

    if (time_config->flag == HY_TIME_FLAG_ENABLE) {
        Bt_M0_Run(TIM0);                            //TIM0 运行。
    }
}

static void _lp_time0_init(HyTimeConfig_t *time_config)
{
    stc_lptim_cfg_t stcLptCfg;
    memset(&stcLptCfg, '\0', sizeof(stcLptCfg));

    ///< 使能LPTIM0 外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim, TRUE);

    stcLptCfg.enGate   = LptimGateLow;
    stcLptCfg.enGatep  = LptimGatePLow;
    stcLptCfg.enTcksel = LptimRcl;
    stcLptCfg.enTogen  = LptimTogEnLow;
    stcLptCfg.enCt     = LptimTimerFun;
    stcLptCfg.enMd     = LptimMode2;                //工作模式为模式1：无自动重装载16位计数器/定时器
    stcLptCfg.u16Arr   = (hy_u16_t)time_config->us; //预装载寄存器值
    Lptim_Init(M0P_LPTIMER, &stcLptCfg);

    Lptim_ClrItStatus(M0P_LPTIMER);                 //清除中断标志位
    Lptim_ConfIt(M0P_LPTIMER, TRUE);                //允许LPTIMER中断
    EnableNvic(LPTIM_IRQn, IrqLevel3, TRUE);

    if (time_config->flag) {
        Lptim_Cmd(M0P_LPTIMER, TRUE);               //LPT 运行
    }
}

static void _time_enable_disable(HyTimeNum_t num, HytimeFlag_t flag)
{
    switch (num) {
        case HY_TIME_NUM_0:
            if (flag == HY_TIME_FLAG_ENABLE) {
                Bt_M0_Run(TIM0);                    //TIM0 运行。
            } else {
                Bt_M0_Stop(TIM0);
            }
            break;
        case HY_TIME_NUM_LP_0:
            if (flag == HY_TIME_FLAG_ENABLE) {
                Lptim_Cmd(M0P_LPTIMER, TRUE);       //LPT 运行
            } else {
                Lptim_Cmd(M0P_LPTIMER, FALSE);      //LPT 运行
            }
            break;
        default:
            break;
    }
}

void HyTimeEnable(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _time_context_t *context = handle;

    _time_enable_disable(context->num, HY_TIME_FLAG_ENABLE);
}

void HyTimeDisable(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _time_context_t *context = handle;

    _time_enable_disable(context->num, HY_TIME_FLAG_DISABLE);
}

void HyTimeDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    HY_FREE(handle);
}

void *HyTimeCreate(HyTimeConfig_t *time_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!time_config, NULL);

    _time_context_t *context = NULL;

    do {
        context = (_time_context_t *)HY_MALLOC_BREAK(sizeof(*context));
        context_arr[time_config->num] = context;

        HY_MEMCPY(&context->config_save, &time_config->config_save);
        context->num = time_config->num;

        switch (time_config->num) {
            case HY_TIME_NUM_0:
                time_config->us = TIME_0_CNT;
                _time0_init(time_config);
                break;
            case HY_TIME_NUM_LP_0:
                time_config->us = LP_TIME_0_CNT;
                _lp_time0_init(time_config);
                break;
            default:
                break;
        }

        LOGI("time %s create successful \n", HY_TIME_NUM_2_STR(time_config->num));
        return context;
    } while (0);

    HyTimeDestroy((void **)&context);
    return NULL;
}

