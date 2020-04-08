/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hal_type.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    20/01 2020 15:34
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        20/01 2020      create the file
 * 
 *     last modified: 20/01 2020 15:34
 */
#ifndef __LIBHAL_INCLUDE_HAL_TYPE_H_
#define __LIBHAL_INCLUDE_HAL_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined _WIN32 || defined __CYGWIN__
    #ifdef BUILDING_DLL
        #ifdef __GNUC__
            #define EXPORT_FUNC __attribute__((dllexport))
        #else
            #define EXPORT_FUNC __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define EXPORT_FUNC __attribute__((dllimport))
        #else
            #define EXPORT_FUNC __declspec(dllimport)
        #endif
    #endif
#else
    #ifdef __GNUC__
        #if __GNUC__ >= 4 || defined(__arm__)
            #define EXPORT_FUNC __attribute__((visibility("default")))
            // #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
        #else
            #error "gcc version too low"
        #endif
    #endif
#endif

#include <stdio.h>
#include <sys/types.h>


typedef char            hal_int8_t;
typedef short           hal_int16_t;
typedef int             hal_int32_t;

typedef unsigned char   hal_uint8_t;
typedef unsigned short  hal_uint16_t;
typedef unsigned int    hal_uint32_t;

typedef char            hal_char_t;
typedef double          hal_double_t;

typedef enum {
  HAL_NO_ERR = 0,

  HAL_THREAD_ERR,

  HAL_SYSTEM_ERR,

  HAL_INVALID_STATE_ERR,
  HAL_INVALID_HANDLE_ERR,
  HAL_INVALID_FILE_ERR,
  HAL_INVALID_SIZE_ERR,
  HAL_INVALID_FORMAT_ERR,
  HAL_INVALID_PARAM_ERR,
  HAL_ALLOC_MEM_ERR,
  HAL_UNSUPPORT_ERR,
  HAL_ERR_NUM_END
} HalErr_t;

#define BYTE_ALIGN(len, align) (((len) + (align) - 1) & ~((align) - 1))

#define ALIGN4(len)     BYTE_ALIGN(len, 4)
#define ALIGN2(len)     BYTE_ALIGN(len, 2)

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_HAL_TYPE_H_

