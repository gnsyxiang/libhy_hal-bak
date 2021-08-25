/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_system.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 20:34
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 20:34
 */
#include <stdio.h>

#include "hy_system.h"

#include "sysctrl.h"
#include "trim.h"
#include "flash.h"
#include "lpm.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_type.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HySystemConfigSave_t config_save;
} _system_context_t;

static void _clock_init(void)
{
    stc_sysctrl_clk_cfg_t stcCfg;

    ///< 开启FLASH外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralFlash, TRUE);
#if 0
    ///< 因将要倍频的PLL作为系统时钟HCLK会达到48MHz：所以此处预先设置FLASH 读等待周期为1 cycle(默认值为0 cycle)
    Flash_WaitCycle(FlashWaitCycle2);

    ///< 时钟初始化前，优先设置要使用的时钟源：此处配置PLL
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);             //PLL使用RCH作为时钟源，因此需要先设置RCH

    stc_sysctrl_pll_cfg_t stcPLLCfg;
    stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;     //RCH 4MHz
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL 输出48MHz
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //输入时钟源选择RCH
    stcPLLCfg.enPllMul    = SysctrlPllMul12;            //4MHz x 12 = 48MHz
    Sysctrl_SetPLLFreq(&stcPLLCfg);

    stcCfg.enClkSrc  = SysctrlClkPLL;                   //< 选择PLL作为HCLK时钟源;
#endif

#if 1
    ///< 因要使用的时钟源HCLK小于24M：此处设置FLASH 读等待周期为0 cycle(默认值也为0 cycle)
    Flash_WaitCycle(FlashWaitCycle0);

    ///< 时钟初始化前，优先设置要使用的时钟源：此处设置RCH为4MHz（默认值为4MHz）
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);

    stcCfg.enClkSrc    = SysctrlClkRCH;                 ///< 选择内部RCH作为HCLK时钟源;
#endif

    stcCfg.enHClkDiv = SysctrlHclkDiv1;                 //< HCLK SYSCLK/1
    stcCfg.enPClkDiv = SysctrlPclkDiv1;                 //< PCLK 为HCLK/1
    Sysctrl_ClkInit(&stcCfg);                           //< 系统时钟初始化

    //使能RCL
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
}

#if 0
static volatile uint8_t u8TrimTestFlag   = 0;
/*******************************************************************************
 * TRIM 中断服务程序
 ******************************************************************************/   
void ClkTrim_IRQHandler(void)
{
    volatile uint32_t u32CalCnt;
    
    if(Trim_GetIntFlag(TrimStop))
    {
        u32CalCnt = Trim_CalCntGet();
        ///<参考计数值计数完成（1ms)时，查看待校准计数值是否也为（1ms）计数值,或是否在允许误差范围内，此处为32768/1000 = 33(±0.3%)
        ///<可根据实际修改该比较范围，提高TRIM校准精度。
        if ((u32CalCnt <= (33u + 1u)) &&
            (u32CalCnt >= (33u - 1u)))
        {
            Trim_Stop();
            ///< 校准结束,此时的TRIM值即为最佳频率值
            u8TrimTestFlag = 0xFFu;
        }
        else
        {
            Trim_Stop();
            ///< 为达到目标精度，TRIM值增加1，继续校准
            M0P_SYSCTRL->RCL_CR_f.TRIM += 1;       
            Trim_Run();           
        }
        
    }
    
    if(Trim_GetIntFlag(TrimCalCntOf))  //参考校准时间设置过长，导致待校准计数器溢出，此时需要重新配置参考校准时间及校准精度
    {
        u8TrimTestFlag = 0;
    }
}

static void _trim_init(void)
{
    //设置初始TRIM值,本样例采用从小到大的方式来TRIM，故此处设置为'1',后续不断更新该值后进行TRIM，直到符合条件（校准）为止
    M0P_SYSCTRL->RCL_CR_f.TRIM = 1;
    ///< 使能待校准时钟，本样例对RCL 32768Hz进行校准
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);

    stc_trim_cfg_t stcCfg;

    //打开TRIM外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralTrim, TRUE);
     
    //TRIM校准流程
    stcCfg.enMON     = TrimMonDisable;
    stcCfg.enREFCLK  = TrimRefMskXTL;
    stcCfg.enCALCLK  = TrimCalMskRCL;
    stcCfg.u32RefCon = 33u;             //1ms校准时间（增加该时间可提高TRIM精度）
    stcCfg.u32CalCon = 0xFFFFFFFFu;     //配置为默认值
    Trim_Init(&stcCfg);
    
    ///< 打开TRIM中断使能
    Trim_EnableIrq();
    ///< 使能并配置TRIM 系统中断
    EnableNvic(CLKTRIM_IRQn, IrqLevel3, TRUE);
}
#endif

void HySystemDeepSleep(void)
{
    Lpm_GotoDeepSleep(FALSE);
}

void HySystemDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    HY_FREE(handle);
}

void *HySystemCreate(HySystemConfig_t *system_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!system_config, NULL);

    _system_context_t *context = NULL;

    do {
        context = (_system_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        HY_MEMCPY(&context->config_save, &system_config->config_save);

        _clock_init();
#if 0
        _trim_init();
#endif

        return context;
    } while (0);

    HySystemDestroy((void **)&context);
    return NULL;
}

