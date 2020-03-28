/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_dl_lib.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    28/03 2020 16:20
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        28/03 2020      create the file
 * 
 *     last modified: 28/03 2020 16:20
 */
#include <dlfcn.h>
#include <gnu/lib-names.h>

#include "hal_config.h"

typedef struct {
    hal_char_t  *libname;
    DLLibHandle_t   handle;
} dll_context_t;
#define DLL_CONTEXT_LEN sizeof(dll_context_t)

static dll_context_t *_context_init(const hal_char_t *libname)
{
    dll_context_t *context = Hal_calloc(1, sizeof(DLL_CONTEXT_LEN));
    if (NULL == context) {
        Hal_LogE("the Hal_calloc faild \n");
        return NULL;
    }

    hal_uint32_t len = ALIGN4(Hal_strlen(libname));
    context->libname = Hal_calloc(1, len);
    if (NULL == context->libname) {
        Hal_LogE("the Hal_calloc faild \n");
        return NULL;
    }

    Hal_strncpy(context->libname, libname, len);

    return context;
}

static void _context_final(dll_context_t **context)
{
    dll_context_t *context_tmp = *context;

    if (NULL != context_tmp->libname) {
        Hal_free(context_tmp->libname);
        context_tmp->libname = NULL;
    }

    if (NULL != context_tmp) {
        Hal_free(context_tmp);
        context_tmp = NULL;
    }
}

DLLibHandle_t HalDllibOpen(const hal_char_t *libname)
{
    if (NULL == libname) {
        Hal_LogE("the libname is NULL \n");
        return NULL;
    }

    dll_context_t *context = _context_init(libname);
    if (NULL == context) {
        Hal_LogE("the libname is NULL \n");
        return NULL;
    }

    context->handle = dlopen(context->libname, RTLD_LAZY);
    if (NULL == context->handle) {
        Hal_LogE("dlopen failed, [%s] \n", dlerror());
    }

    Hal_LogT("open %s successful \n", context->libname);
    return (DLLibHandle_t)context;
}

void HalDllibExit(DLLibHandle_t handle)
{
    if (NULL == handle) {
        Hal_LogE("the handle is NULL \n");
        return;
    }

    dll_context_t *context = handle;
    dlclose(context->handle);

    Hal_LogT("close %s successful \n", context->libname);
    _context_final(&context);
}

void* HalDllLoadSymbol(DLLibHandle_t handle, const hal_char_t *symbol)
{
    if (NULL == handle || NULL == symbol) {
        Hal_LogE("the param is NULL \n");
        return NULL;
    }

    dll_context_t *context = handle;
    void *sym = dlsym(context->handle, symbol);
    if (NULL == sym) {
        Hal_LogE("load symbol[%s] failed, [%s] \n", symbol, dlerror());
    }

    Hal_LogT("load symbol[%s] from %s successful \n", symbol, context->libname);
    return sym;
}

