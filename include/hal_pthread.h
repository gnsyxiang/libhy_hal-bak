/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_pthread.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/01 2020 21:01
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/01 2020      create the file
 * 
 *     last modified: 10/01 2020 21:01
 */
#ifndef __LIBHAL_INCLUDE_HAL_PTHREAD_H_
#define __LIBHAL_INCLUDE_HAL_PTHREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBHAL_INCLUDE_HAL_PTHREAD_GB
#define LIBHAL_INCLUDE_HAL_PTHREAD_EX extern
#else
#define LIBHAL_INCLUDE_HAL_PTHREAD_EX
#endif

LIBHAL_INCLUDE_HAL_PTHREAD_EX void hello_world(void);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_PTHREAD_H_

