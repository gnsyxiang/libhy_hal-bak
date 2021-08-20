/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_gpio.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/08 2021 11:35
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/08 2021      create the file
 * 
 *     last modified: 20/08 2021 11:35
 */
#include <stdio.h>

#include "hy_gpio.h"

#include "at32f4xx_gpio.h"
#include "at32f4xx_rcc.h"

#include "hy_utils/hy_type.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

void HyGpioSetInput(HyGpio_t *gpio)
{

}

void HyGpioSetOutput(HyGpio_t *gpio, HyGpioLevel_t level)
{
    hy_u32_t rcc[] = {
        RCC_APB2PERIPH_GPIOA,
        RCC_APB2PERIPH_GPIOB,
        RCC_APB2PERIPH_GPIOC,
        RCC_APB2PERIPH_GPIOD,
    };

    GPIO_Type *group[] = {
        GPIOA, GPIOB, GPIOC, GPIOD, GPIOE,
    };

    hy_u16_t pin[] = {
        GPIO_Pins_0, GPIO_Pins_1, GPIO_Pins_2, GPIO_Pins_3,
        GPIO_Pins_4, GPIO_Pins_5, GPIO_Pins_6, GPIO_Pins_7,
        GPIO_Pins_8, GPIO_Pins_9, GPIO_Pins_10, GPIO_Pins_11,
        GPIO_Pins_12, GPIO_Pins_13, GPIO_Pins_14, GPIO_Pins_15,
        GPIO_Pins_All,
    };

    GPIO_InitType GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(rcc[gpio->group], ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pins        = pin[gpio->pin];
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_OUT_PP;
    GPIO_InitStructure.GPIO_MaxSpeed    = GPIO_MaxSpeed_50MHz;	
    GPIO_Init(group[gpio->group], &GPIO_InitStructure);

    HyGpioSetLevel(gpio, level);
}

HyGpioLevel_t HyGpioGetLevel(HyGpio_t *gpio)
{

    return HY_GPIO_LEVEL_LOW;
}

void HyGpioSetLevel(HyGpio_t *gpio, HyGpioLevel_t level)
{
    GPIO_Type *group[] = {
        GPIOA, GPIOB, GPIOC, GPIOD, GPIOE,
    };

    hy_u16_t pin[] = {
        GPIO_Pins_0, GPIO_Pins_1, GPIO_Pins_2, GPIO_Pins_3,
        GPIO_Pins_4, GPIO_Pins_5, GPIO_Pins_6, GPIO_Pins_7,
        GPIO_Pins_8, GPIO_Pins_9, GPIO_Pins_10, GPIO_Pins_11,
        GPIO_Pins_12, GPIO_Pins_13, GPIO_Pins_14, GPIO_Pins_15,
        GPIO_Pins_All,
    };

    if (level == HY_GPIO_LEVEL_HIGH) {
        group[gpio->group]->BSRE = pin[gpio->pin];
    } else {
        group[gpio->group]->BRE = pin[gpio->pin];
    }
}

