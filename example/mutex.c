/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    mutex.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    09/04 2020 17:46
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        09/04 2020      create the file
 * 
 *     last modified: 09/04 2020 17:46
 */
#include "hal_mutex.h"

hal_int32_t main(hal_int32_t argc, const hal_char_t *argv[])
{

    ThreadMutexHandle_t handle = HalMutexInit();

    HalMutexDestroy(handle);

    return 0;
}
