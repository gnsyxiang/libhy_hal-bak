/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    uart.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/07 2021 17:32
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/07 2021      create the file
 * 
 *     last modified: 09/07 2021 17:32
 */
#include <stdio.h>

#include "hy_uart.h"
#include "hy_gpio.h"
#include "inside_uart.h"

#include "uart.h"
#include "gpio.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_error.h"
#include "hy_utils/hy_type.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

#define _DEFINE_UART()              \
    M0P_UART_TypeDef* uart[] = {    \
        M0P_UART0,                  \
        M0P_UART1,                  \
    }

typedef struct {
    HyUartConfigSave_t config_save;

    HyUartNum_t num;
} _uart_context_t;

static _uart_context_t *context_arr[HY_UART_NUM_MAX] = {0};

#ifdef DEBUG_UART
#ifdef __GNUC__
int _write(int fd, char *ptr, int len)
{
    /*
     * write "len" of char from "ptr" to file id "fd"
     * Return number of char written.
     *
     * Only work for STDOUT, STDIN, and STDERR
     */
    if (fd > 2) {
        return -1;
    }

    _DEFINE_UART();

    int i = 0;
    while (*ptr && (i < len)) {
        if (*ptr == '\n') {
            Uart_SendDataPoll(uart[DEBUG_UART_NUM], '\r');
        }
        Uart_SendDataPoll(uart[DEBUG_UART_NUM], *ptr);
        i++;
        ptr++;
    }
    return i;
}
#endif
#if __CC_ARM
int fputc(int ch, FILE *f)
{
    _DEFINE_UART();

    if ((hy_u8_t)ch == '\n') {
        Uart_SendDataPoll(uart[DEBUG_UART_NUM], '\r');
    }
    Uart_SendDataPoll(uart[DEBUG_UART_NUM], (hy_u8_t)ch);

    return 1;
}
#endif
#endif

static inline void _uart_irq_handler(HyUartNum_t num)
{
    _uart_context_t *context = context_arr[num];

    _DEFINE_UART();

    if (Uart_GetStatus(uart[num], UartRC)) {
        Uart_ClrStatus(uart[num], UartRC);

        HyUartConfigSave_t *config_save = &context->config_save;
        if (config_save && config_save->read_cb) {
            hy_u8_t ch = Uart_ReceiveData(uart[num]);
            config_save->read_cb((void *)&ch, 1, config_save->args);
        }
    }
}

void Uart0_IRQHandler(void)
{
    _uart_irq_handler(HY_UART_NUM_0);
}

void Uart1_IRQHandler(void)
{
    _uart_irq_handler(HY_UART_NUM_1);
}

static void _init_uart_gpio(HyUartNum_t num)
{
    HyGpio_t gpio[][2] = {
        {{HY_GPIO_GROUP_PA, HY_GPIO_PIN_9}, {HY_GPIO_GROUP_PA, HY_GPIO_PIN_10}},
        {{HY_GPIO_GROUP_PD, HY_GPIO_PIN_0}, {HY_GPIO_GROUP_PD, HY_GPIO_PIN_1}},
    };

    HyGpioSetOutput(&gpio[num][0], HY_GPIO_LEVEL_HIGH);
    HyGpioSetInput(&gpio[num][1]);
}

static void _init_uart_func(HyUartConfig_t *uart_config)
{
    _DEFINE_UART();

    en_sysctrl_peripheral_gate_t clock[HY_UART_NUM_MAX] = {
        SysctrlPeripheralUart0, SysctrlPeripheralUart1
    };

    en_uart_stop_t stop[HY_UART_STOP_MAX] = {
        0, UartMsk1bit, UartMsk1_5bit, UartMsk2bit
    };

    en_uart_mmdorck_t parity[] = {
        UartMskDataOrAddr, UartMskOdd, UartMskEven
    };

    hy_u32_t rate[HY_UART_RATE_MAX] = {
        1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200,
    };

    IRQn_Type irq[] = {UART0_IRQn, UART1_IRQn};

    Sysctrl_SetPeripheralGate(clock[uart_config->num], TRUE);

    stc_uart_cfg_t stcCfg;
    memset(&stcCfg, '\0', sizeof(stcCfg));

    stcCfg.enRunMode        = UartMskMode1;
    stcCfg.enStopBit        = stop[uart_config->stop];
    stcCfg.enMmdorCk        = parity[uart_config->parity];
    stcCfg.stcBaud.u32Baud  = rate[uart_config->rate];
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<通道采样分频配置
    stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<获得外设时钟（PCLK）频率值
    Uart_Init(uart[uart_config->num], &stcCfg);

    Uart_ClrStatus(uart[uart_config->num], UartRC);
    Uart_ClrStatus(uart[uart_config->num], UartTC);
    Uart_EnableIrq(uart[uart_config->num], UartRxIrq);
    //Uart_EnableIrq(uart[uart_config->num], UartTxIrq);

    EnableNvic(irq[uart_config->num], IrqLevel3, TRUE);
}

hy_s32_t HyUartProcess(void *handle)
{
    return 0;
}

hy_s32_t HyUartWrite(void *handle, void *buf, size_t len)
{
    HY_ASSERT_NULL_RET_VAL(!handle || !buf, HY_ERR_FAILD);

    _uart_context_t *context = handle;
    _DEFINE_UART();

    char *ch = buf;
    for (size_t i = 0; i < len; ++i) {
        Uart_SendDataPoll(uart[context->num], (hy_u8_t)ch[i]);
    }

    return len;
}

void HyUartDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    HY_FREE(handle);

    LOGI("uart destroy successful \n");
}

void *HyUartCreate(HyUartConfig_t *uart_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!uart_config, NULL);

    _uart_context_t *context = NULL;

    do {
        context = (_uart_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        HY_MEMCPY(&context->config_save, &uart_config->config_save);
        context->num = uart_config->num;

        _init_uart_gpio(context->num);
        _init_uart_func(uart_config);

        context_arr[context->num] = context;

        LOGI("uart %s create successful \n", HY_UART_NUM_2_STR(uart_config->num));
        return context;
    } while (0);

    HyUartDestroy((void **)&context);
    return NULL;
}

