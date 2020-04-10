/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_assert.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    29/02 2020 20:50
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        29/02 2020      create the file
 * 
 *     last modified: 29/02 2020 20:50
 */
#ifndef __LIBHAL_INCLUDE_HAL_ASSERT_H_
#define __LIBHAL_INCLUDE_HAL_ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_type.h"

void Hal_assert(hal_int32_t expression);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_ASSERT_H_

