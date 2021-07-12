/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    utils.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/07 2021 15:08
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/07 2021      create the file
 * 
 *     last modified: 09/07 2021 15:08
 */
#ifndef __LIBHY_HAL_INCLUDE_HY_UTILS_H_
#define __LIBHY_HAL_INCLUDE_HY_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define JUDGE_NULL_RET(param, ret)      \
    if (param) {                        \
        LOGE("the param is NULL \n");   \
        return ret;                     \
    }

#define JUDGE_NULL(param)               \
    if (param) {                        \
        LOGE("the param is NULL \n");   \
        return ;                        \
    }

#define FREE(mem)       \
    do {                \
        free(*mem);     \
        *mem = NULL;    \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif

