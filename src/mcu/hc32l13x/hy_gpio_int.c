/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_gpio_int.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 20:24
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 20:24
 */
#include <stdio.h>

#include "hy_gpio_int.h"
#include "inside_gpio.h"

#include "gpio.h"

#include "hy_utils/hy_type.h"
#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
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

typedef struct {
    HyIntConfigSave_t config_save;

    HyGpio_t gpio;
} _int_context_t;

static _int_context_t *context_arr[HY_GPIO_GROUP_MAX][HY_GPIO_PIN_MAX] = {0};

#define _PIN_INT_CB(_group, _pin)                                       \
    do {                                                                \
        _DEFINE_GROUP();                                                \
        _DEFINE_PIN();                                                  \
                                                                        \
        if (TRUE == Gpio_GetIrqStatus(group[_group], pin[_pin])) {      \
            Gpio_ClearIrq(group[_group], pin[_pin]);                    \
                                                                        \
            _int_context_t *context = context_arr[_group][_pin];        \
            HyIntConfigSave_t *config_save = &context->config_save;     \
            if (config_save->int_cb) {                                  \
                config_save->int_cb(config_save->args);                 \
            }                                                           \
        }                                                               \
    } while (0);

void PortA_IRQHandler(void)
{
    for (HyGpioPin_t i = HY_GPIO_PIN_0; i < HY_GPIO_PIN_MAX; ++i) {
        _PIN_INT_CB(HY_GPIO_GROUP_PA, i);
    }
}

void PortB_IRQHandler(void)
{
    for (HyGpioPin_t i = HY_GPIO_PIN_0; i < HY_GPIO_PIN_MAX; ++i) {
        _PIN_INT_CB(HY_GPIO_GROUP_PB, i);
    }
}

void PortC_IRQHandler(void)
{
    for (HyGpioPin_t i = HY_GPIO_PIN_0; i < HY_GPIO_PIN_MAX; ++i) {
        _PIN_INT_CB(HY_GPIO_GROUP_PC, i);
    }
}

void PortD_IRQHandler(void)
{
    for (HyGpioPin_t i = HY_GPIO_PIN_0; i < HY_GPIO_PIN_MAX; ++i) {
        _PIN_INT_CB(HY_GPIO_GROUP_PD, i);
    }
}

static void _int_irq(HyIntConfig_t *int_config)
{
    _DEFINE_GROUP();
    _DEFINE_PIN();

    IRQn_Type enIrq[] = {
        PORTA_IRQn, PORTB_IRQn, PORTC_IRQn, PORTD_IRQn,
    };

    en_gpio_irqtype_t enType[] = {
        GpioIrqLow, GpioIrqHigh, GpioIrqRising, GpioIrqFalling
    };

    HyGpio_t *gpio = &int_config->config_save.gpio;
    Gpio_EnableIrq(group[gpio->group], pin[gpio->pin], enType[int_config->trigger_mode]);
    EnableNvic(enIrq[gpio->group], IrqLevel3, TRUE);
}

void HyIntDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    HY_FREE(handle);
}

void *HyIntCreate(HyIntConfig_t *int_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!int_config, NULL);

    _int_context_t *context = NULL;

    do {
        context = (_int_context_t *)HY_MALLOC_BREAK(sizeof(*context));
        HyGpio_t *gpio = &context->config_save.gpio;

        HY_MEMCPY(&context->config_save, &int_config->config_save);
        context_arr[gpio->group][gpio->pin] = context;

        HyGpioSetInput(gpio);

        _int_irq(int_config);

        LOGI("interrupt pin<%s, %s> create successful \n", HY_GPIO_GROUP_2_STR(gpio->group), HY_GPIO_PIN_2_STR(gpio->pin));
        return context;
    } while (0);

    HyIntDestroy((void **)&context);
    return NULL;
}

