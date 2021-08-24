/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_gpio.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 19:37
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 19:37
 */
#include <stdio.h>

#include "hy_gpio.h"
#include "inside_gpio.h"

#include "gpio.h"

#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_type.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

#define _DEFINE_GROUP()                                 \
    en_gpio_port_t group[HY_GPIO_GROUP_MAX] = {         \
        GpioPortA, GpioPortB, GpioPortC, GpioPortD      \
    }

#define _DEFINE_PIN()                                   \
    en_gpio_pin_t pin[HY_GPIO_PIN_MAX] = {              \
        GpioPin0,   GpioPin1,   GpioPin2,   GpioPin3,   \
        GpioPin4,   GpioPin5,   GpioPin6,   GpioPin7,   \
        GpioPin8,   GpioPin9,   GpioPin10,  GpioPin11,  \
        GpioPin12,  GpioPin13,  GpioPin14,  GpioPin15,  \
    }

HyGpioLevel_t HyGpioGetLevel(HyGpio_t *gpio)
{
    HY_ASSERT_NULL_RET_VAL(!gpio, HY_GPIO_LEVEL_MAX);

    _DEFINE_GROUP();
    _DEFINE_PIN();

    return (HyGpioLevel_t)Gpio_GetInputIO(group[gpio->group], pin[gpio->pin]);
}

void HyGpioSetLevel(HyGpio_t *gpio, HyGpioLevel_t level)
{
    HY_ASSERT_NULL_RET(!gpio);
    LOGI("pin<%s, %s>, level: %s \n", HY_GPIO_GROUP_2_STR(gpio->group), HY_GPIO_PIN_2_STR(gpio->pin), HY_GPIO_LEVEL_2_STR(level));

    _DEFINE_GROUP();
    _DEFINE_PIN();

    Gpio_WriteOutputIO(group[gpio->group], pin[gpio->pin], level);
}

void HyGpioSetLevelToggle(HyGpio_t *gpio)
{
    HY_ASSERT_NULL_RET(!gpio);
    LOGI("pin<%s, %s> toggle \n", HY_GPIO_GROUP_2_STR(gpio->group), HY_GPIO_PIN_2_STR(gpio->pin));

    _DEFINE_GROUP();
    _DEFINE_PIN();

    volatile uint32_t *addr = ((uint32_t)&M0P_GPIO->PAOUT + group[gpio->group]);

    *addr ^= ((1UL)<<(pin[gpio->pin]));
}

static void _init_PA_pin(HyGpio_t *gpio, stc_gpio_cfg_t *stcGpioCfg)
{
    _DEFINE_GROUP();
    _DEFINE_PIN();

    switch (gpio->pin) {
        case HY_GPIO_PIN_11:
        case HY_GPIO_PIN_12:
            stcGpioCfg->enPu  = GpioPuEnable;
            break;
        default:
            break;
    }
    Gpio_Init(group[gpio->group], pin[gpio->pin], stcGpioCfg);

    switch (gpio->pin) {
        case HY_GPIO_PIN_9:
        case HY_GPIO_PIN_10:
            Gpio_SetAfMode(group[gpio->group], pin[gpio->pin], GpioAf1);
            break;
        default:
            break;
    }
}

static void _init_PB_pin(HyGpio_t *gpio, stc_gpio_cfg_t *stcGpioCfg)
{

}

static void _init_PC_pin(HyGpio_t *gpio, stc_gpio_cfg_t *stcGpioCfg)
{

}

static void _init_PD_pin(HyGpio_t *gpio, stc_gpio_cfg_t *stcGpioCfg)
{
    _DEFINE_GROUP();
    _DEFINE_PIN();

    switch (gpio->pin) {
        case HY_GPIO_PIN_0:
        case HY_GPIO_PIN_1:
            stcGpioCfg->enPu  = GpioPuEnable;
            break;
        default:
            break;
    }
    Gpio_Init(group[gpio->group], pin[gpio->pin], stcGpioCfg);

    switch (gpio->pin) {
        case HY_GPIO_PIN_0:
        case HY_GPIO_PIN_1:
            Gpio_SetAfMode(group[gpio->group], pin[gpio->pin], GpioAf3);
            break;
        default:
            break;
    }
}

static void _init_gpio_com(HyGpio_t *gpio, en_gpio_dir_t dir)
{
    void (*_init_pin[HY_GPIO_GROUP_MAX])(HyGpio_t *, stc_gpio_cfg_t *) = {
        _init_PA_pin, _init_PB_pin, _init_PC_pin, _init_PD_pin,
    };

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    stc_gpio_cfg_t stcGpioCfg;
    memset(&stcGpioCfg, '\0', sizeof(stcGpioCfg));

    stcGpioCfg.enDir = dir;

    if (_init_pin[gpio->group]) {
        _init_pin[gpio->group](gpio, &stcGpioCfg);
    }
}

void HyGpioSetInput(HyGpio_t *gpio)
{
    HY_ASSERT_NULL_RET(!gpio);
    LOGI("pin<%s, %s> \n", HY_GPIO_GROUP_2_STR(gpio->group), HY_GPIO_PIN_2_STR(gpio->pin));

    _init_gpio_com(gpio, GpioDirIn);
}

void HyGpioSetOutput(HyGpio_t *gpio, HyGpioLevel_t level)
{
    HY_ASSERT_NULL_RET(!gpio);

    _init_gpio_com(gpio, GpioDirOut);

    HyGpioSetLevel(gpio, level);
}

