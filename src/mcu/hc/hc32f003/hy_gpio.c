/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_gpio.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    04/09 2021 20:09
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        04/09 2021      create the file
 * 
 *     last modified: 04/09 2021 20:09
 */
#include <stdio.h>

#include "hy_gpio.h"
#include "inside_gpio.h"

#include "gpio.h"

#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_type.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    en_gpio_dir_t dir;
    char pu;
    char pd;
    char odr;
    char driver;
} gpio_config_t;

HyGpioLevel_t HyGpioGetLevel(HyGpio_t *gpio)
{
    return HY_GPIO_LEVEL_LOW;
}

void HyGpioSetLevel(HyGpio_t *gpio, HyGpioLevel_t level)
{
    HY_ASSERT_NULL_RET(!gpio);
    // LOGI("pin<%s, %s>, level: %s \n", HY_GPIO_GROUP_2_STR(gpio->group), HY_GPIO_PIN_2_STR(gpio->pin), HY_GPIO_LEVEL_2_STR(level));

    if (level == HY_GPIO_LEVEL_HIGH) {
        Gpio_SetIO(gpio->group, gpio->pin, TRUE);
    } else {
        Gpio_SetIO(gpio->group, gpio->pin, FALSE);
    }
}

void HyGpioSetLevelToggle(HyGpio_t *gpio)
{
}

static void _init_P0_pin(HyGpio_t *gpio, gpio_config_t *stcGpioCfg)
{
}

static void _init_P1_pin(HyGpio_t *gpio, gpio_config_t *stcGpioCfg)
{
}

static void _init_P2_pin(HyGpio_t *gpio, gpio_config_t *stcGpioCfg)
{
    switch (gpio->pin) {
        case HY_GPIO_PIN_5:
        case HY_GPIO_PIN_6:
            stcGpioCfg->pu = TRUE;
            stcGpioCfg->pd = FALSE;
            stcGpioCfg->odr = TRUE;
            stcGpioCfg->driver = FALSE;
            break;
        default:
            break;
    }
    Gpio_InitIOExt(gpio->group, gpio->pin,
            stcGpioCfg->dir, stcGpioCfg->pu, stcGpioCfg->pd,
            stcGpioCfg->odr, stcGpioCfg->driver);
}

static void _init_P3_pin(HyGpio_t *gpio, gpio_config_t *stcGpioCfg)
{
}

static void _init_gpio_com(HyGpio_t *gpio, en_gpio_dir_t dir)
{
    void (*_init_pin[HY_GPIO_GROUP_MAX])(HyGpio_t *, gpio_config_t *) = {
        _init_P0_pin, _init_P1_pin, _init_P2_pin, _init_P3_pin,
    };

    gpio_config_t stcGpioCfg;
    memset(&stcGpioCfg, '\0', sizeof(stcGpioCfg));

    stcGpioCfg.dir = dir;

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

