/**
 *
 * Release under GPL-3.0.
 * 
 * @file    hy_type.h
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
#ifndef __LIBHY_HAL_INCLUDE_HY_TYPE_H_
#define __LIBHY_HAL_INCLUDE_HY_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef char                hy_int8_t;
typedef short               hy_int16_t;
typedef int                 hy_int32_t;
typedef long long           hy_int64_t;

typedef unsigned char       hy_uint8_t;
typedef unsigned short      hy_uint16_t;
typedef unsigned int        hy_uint32_t;
typedef unsigned long long  hy_uint64_t;

typedef char            hy_char_t;
typedef double          hy_double_t;

typedef enum {
    HY_NO_ERR = 0,

    HY_THREAD_ERR,

    HY_SYSTEM_ERR,

    HY_INVALID_STATE_ERR,
    HY_INVALID_HANDLE_ERR,
    HY_INVALID_FILE_ERR,
    HY_INVALID_SIZE_ERR,
    HY_INVALID_FORMAT_ERR,
    HY_INVALID_PARAM_ERR,
    HY_ALLOC_MEM_ERR,
    HY_UNSUPPORT_ERR,
    HY_ERR_NUM_END
} HyErr_t;

/* 
 * BYTE_ALIGN:  字节对齐
 * ALIGN4:      4字节对齐
 * ALIGN2:      2字节对齐
 * ALIGN4_UP:   绝对字节对齐(原来已经事4字节对齐，使用后再增加4个字节)
 */
#define BYTE_ALIGN(len, align)  (((len) + (align) - 1) & ~((align) - 1))
#define ALIGN4(len)             BYTE_ALIGN(len, 4)
#define ALIGN2(len)             BYTE_ALIGN(len, 2)
#define ALIGN4_UP(len)          (BYTE_ALIGN(len, 4) + ALIGN4(1))

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

#ifdef __cplusplus
}
#endif

#endif

