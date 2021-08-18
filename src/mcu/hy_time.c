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

#include "timer3.h"
#include "bt.h"
#include "lptim.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HyTimeConfigSave_t config_save;

    HyTimeNum_t         num;
} _time_context_t;

static _time_context_t *context_arr[HY_TIME_NUM_MAX] = {0};

void Tim0_IRQHandler(void)
{
    if(TRUE == Bt_GetIntFlag(TIM0, BtUevIrq)) {
        Bt_ClearIntFlag(TIM0,BtUevIrq); //中断标志清零

        _time_context_t *context = context_arr[HY_TIME_NUM_0];
        context->config_save.time_cb(context->config_save.args);
    }
}

void Tim3_IRQHandler(void)
{
    if (TRUE == Tim3_GetIntFlag(Tim3UevIrq)) {
        Tim3_ClearIntFlag(Tim3UevIrq);

        _time_context_t *context = context_arr[HY_TIME_NUM_3];
        context->config_save.time_cb(context->config_save.args);
    }
}

void LpTim_IRQHandler(void)
{
    if (TRUE == Lptim_GetItStatus(M0P_LPTIMER)) {
        Lptim_ClrItStatus(M0P_LPTIMER);             //清除LPTimer的中断标志位

        _time_context_t *context = context_arr[HY_TIME_NUM_LP_0];
        context->config_save.time_cb(context->config_save.args);
    }
}

void App_Timer0Cfg(uint16_t u16Period)
{
    uint16_t                  u16ArrValue;
    uint16_t                  u16CntValue;
    stc_bt_mode0_cfg_t     stcBtBaseCfg;

    DDL_ZERO_STRUCT(stcBtBaseCfg);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, TRUE); //Base Timer外设时钟使能

    stcBtBaseCfg.enWorkMode = BtWorkMode0;          //定时器模式
    stcBtBaseCfg.enCT       = BtTimer;              //定时器功能，计数时钟为内部PCLK
    stcBtBaseCfg.enPRS      = BtPCLKDiv8;           //PCLK/64
    stcBtBaseCfg.enCntMode  = Bt16bitArrMode;       //自动重载16位计数器/定时器
    stcBtBaseCfg.bEnTog     = FALSE;
    stcBtBaseCfg.bEnGate    = FALSE;
    stcBtBaseCfg.enGateP    = BtGatePositive;
    Bt_Mode0_Init(TIM0, &stcBtBaseCfg);             //TIM0 的模式0功能初始化

    u16ArrValue = 0x10000 - u16Period;
    Bt_M0_ARRSet(TIM0, u16ArrValue);                //设置重载值(ARR = 0x10000 - 周期)

    u16CntValue = 0x10000 - u16Period;
    Bt_M0_Cnt16Set(TIM0, u16CntValue);              //设置计数初值

    Bt_ClearIntFlag(TIM0,BtUevIrq);                 //清中断标志   
    Bt_Mode0_EnableIrq(TIM0);                       //使能TIM0中断(模式0时只有一个中断)
    EnableNvic(TIM0_IRQn, IrqLevel3, TRUE);         //TIM0中断使能

    Bt_M0_Run(TIM0);                                //TIM0 运行。
}

static void App_Timer3Cfg(uint16_t u16Period)
{
    uint16_t                    u16ArrValue;
    uint16_t                    u16CntValue;
    stc_tim3_mode0_cfg_t     stcTim3BaseCfg;

    DDL_ZERO_STRUCT(stcTim3BaseCfg);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, TRUE); //Base Timer外设时钟使能

    stcTim3BaseCfg.enWorkMode = Tim3WorkMode0;              //定时器模式
    stcTim3BaseCfg.enCT       = Tim3Timer;                  //定时器功能，计数时钟为内部PCLK
    stcTim3BaseCfg.enPRS      = Tim3PCLKDiv16;              //PCLK/16
    stcTim3BaseCfg.enCntMode  = Tim316bitArrMode;           //自动重载16位计数器/定时器
    stcTim3BaseCfg.bEnTog     = FALSE;
    stcTim3BaseCfg.bEnGate    = FALSE;
    stcTim3BaseCfg.enGateP    = Tim3GatePositive;

    Tim3_Mode0_Init(&stcTim3BaseCfg);                       //TIM3 的模式0功能初始化

    u16ArrValue = 0x10000 - u16Period ;

    Tim3_M0_ARRSet(u16ArrValue);                            //设置重载值(ARR = 0x10000 - 周期)

    u16CntValue = 0x10000 - u16Period;

    Tim3_M0_Cnt16Set(u16CntValue);                          //设置计数初值

    Tim3_ClearIntFlag(Tim3UevIrq);                          //清中断标志
    Tim3_Mode0_EnableIrq();                                 //使能TIM3中断(模式0时只有一个中断)
    EnableNvic(TIM3_IRQn, IrqLevel3, TRUE);                 //TIM3 开中断 

    Tim3_M0_Run();   //TIM3 运行。
}

static void App_LPTimerInit(HyTimeConfig_t *time_config)
{
    stc_lptim_cfg_t    stcLptCfg;
    DDL_ZERO_STRUCT(stcLptCfg);

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
        Lptim_Cmd(M0P_LPTIMER, TRUE);    //LPT 运行
    }
}

static void _time_enable_disable(HyTimeNum_t num, HytimeFlag_t flag)
{
    switch (num) {
        case HY_TIME_NUM_0:
            if (flag == HY_TIME_FLAG_ENABLE) {
                Bt_M0_Run(TIM0);                                //TIM0 运行。
            } else {
                Bt_M0_Stop(TIM0);
            }
            break;
        case HY_TIME_NUM_LP_0:
            if (flag == HY_TIME_FLAG_ENABLE) {
                Lptim_Cmd(M0P_LPTIMER, TRUE);    //LPT 运行
            } else {
                Lptim_Cmd(M0P_LPTIMER, FALSE);    //LPT 运行
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

// @note: 该定时器指定40ms计时
void *HyTimeCreate(HyTimeConfig_t *time_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!time_config, NULL);

    _time_context_t *context = NULL;

    do {
        context = (_time_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        HY_MEMCPY(&context->config_save, &time_config->config_save);
        context->num = time_config->num;

        switch (time_config->num) {
            case HY_TIME_NUM_0:
                // App_Timer0Cfg(30000);
                App_Timer0Cfg(500);
                break;
            case HY_TIME_NUM_LP_0:
                time_config->us = 0;   // 内部设定2s定时，跟外界设置无关
                App_LPTimerInit(time_config);
                break;
            default:
                break;
        }

        context_arr[time_config->num] = context;

        LOGI("time %d create successful \n", time_config->num);
        return context;
    } while (0);

    HyTimeDestroy((void **)&context);
    return NULL;
}

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

