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
#include "flash.h"

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

        return context;
    } while (0);

    HySystemDestroy((void **)&context);
    return NULL;
}

