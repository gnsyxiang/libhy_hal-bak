/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_assert.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    29/02 2020 20:51
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        29/02 2020      create the file
 * 
 *     last modified: 29/02 2020 20:51
 */
#include "config.h"
#include "hal_config.h"

#ifdef HAVE_LINUX_HAL
#include <assert.h>

void HalAssert(int expression)
{
    assert(expression);
}
#endif

