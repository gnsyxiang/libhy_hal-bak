/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    hal_pthread.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/01 2020 20:59
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/01 2020      create the file
 * 
 *     last modified: 10/01 2020 20:59
 */
#include "hal_config.h"
#include "hal_thread_internal.h"

/*
 * pthread_t pthread_self(void)     <进程级别>是pthread 库给每个线程定义的进程内唯一标识，是 pthread 库维护的，是进程级而非系统级
 * syscall(SYS_gettid)              <系统级别>这个系统全局唯一的“ID”叫做线程PID（进程ID），或叫做TID（线程ID），也有叫做LWP（轻量级进程=线程）的。
 */
static inline pid_t _getpid(void)
{
	return syscall(SYS_gettid);
}

// 设置的名字可以在proc文件系统中查看: cat /proc/PID/task/tid/comm
static inline void _linux_thread_set_name(pthread_t id, hal_char_t *name)
{
    // hal_int32_t ret = pthread_setname_np(id, name);
    hal_int32_t ret = prctl(PR_SET_NAME, name);
    if (0 != ret) {
        HalLogE("set name faild \n");
    }
}

static inline void _linux_thread_get_name(pthread_t id, hal_char_t *name)
{
    // hal_int32_t ret = pthread_getname_np(id, name, HAL_THREAD_NAME_MAX_LEN);
    hal_int32_t ret = prctl(PR_GET_NAME, name);
    if (0 != ret) {
        HalLogE("set name faild \n");
    }
}

static void *_loop_wrapper(void *args)
{
    hal_thread_context_t *context = (hal_thread_context_t *)args;

    context->pid = _getpid();
    _linux_thread_set_name(context->id, context->name);

    if (NULL != context->loop_config.loop) {
        context->loop_config.loop(context->loop_config.args);
    }

    // typedef unsigned long int pthread_t;
    context->id = 0;

    return NULL;
}

hal_int32_t LinuxThreadCreate(void *args)
{
    hal_thread_context_t *context = args;
    hal_int32_t ret = 0;
    pthread_attr_t attr;

    ret = pthread_attr_init(&attr);
    if (0 != ret) {
        HalLogE("pthread_attr_init faild \n");
        goto L_ERROR_INIT_1;
    }

    // 如果当前线程没有被设定成DETACHED的话，
    // 线程结束后，需要使用pthread_join来触发该一小段内存回收。
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (context->config->stack_size > 0) {
        ret = pthread_attr_setstacksize(&attr, context->config->stack_size);
        if (0 != ret) {
            HalLogE("pthread_attr_setstacksize faild \n");
            goto L_ERROR_INIT_2;
        }
    }

    hal_int32_t sched_priority[][2] = {
        {HAL_THREAD_PRIORITY_NORMAL,    50},
        {HAL_THREAD_PRIORITY_LOW,       30},
        {HAL_THREAD_PRIORITY_HIGH,      70},
        {HAL_THREAD_PRIORITY_REALTIME,  99},
        {HAL_THREAD_PRIORITY_IDLE,      10},
    };

    struct sched_param param;
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    param.sched_priority = sched_priority[context->config->priority][1];
    pthread_attr_setschedparam(&attr, &param);

    ret = pthread_create(&context->id, &attr, _loop_wrapper, context);
    if (0 != ret) {
        HalLogE("pthread_attr_setstacksize faild \n");
        goto  L_ERROR_INIT_2;
    }

    pthread_attr_destroy(&attr);
    return 0;
L_ERROR_INIT_2:
    pthread_attr_destroy(&attr);
L_ERROR_INIT_1:
    return -1;
}

hal_int32_t LinuxThreadDestroy(void *args)
{
    hal_thread_context_t *context = args;
    if (0 != context->id) {
        return pthread_cancel(context->id);
    } else {
        return HAL_NO_ERR;
    }
}

//FIXME 初始化后一般不需要修改名字(去掉)
static hal_int32_t _hal_linux_thread_set_name(hal_thread_context_t *context, void *args)
{
    return 0;
}

static hal_int32_t _hal_linux_thread_get_name(hal_thread_context_t *context, void *args)
{
    return 0;
}

static hal_linux_thread_param_cb_t _g_linux_thread_param[] = {
    {_hal_linux_thread_set_name, _hal_linux_thread_get_name},
};

hal_int32_t LinuxThreadParamSet(void *context, hal_int32_t type, void *args)
{
    return hal_thread_param_common(_g_linux_thread_param,
                                   context,
                                   type,
                                   args,
                                   HAL_THREAD_INDEX_SET);
}

hal_int32_t LinuxThreadParamGet(void *context, hal_int32_t type,  void *args)
{
    return hal_thread_param_common(_g_linux_thread_param,
                                   context,
                                   type,
                                   args,
                                   HAL_THREAD_INDEX_GET);
}

void ThreadSystemInit(hal_system_init_cb_t *system_cb)
{
    Hal_assert(NULL != system_cb);

    system_cb->create  = LinuxThreadCreate;
    system_cb->destroy = LinuxThreadDestroy;
    system_cb->get     = LinuxThreadParamGet;
    system_cb->set     = LinuxThreadParamSet;
}

#if 0
出现如下提示，表示线程资源没有释放，可能的原因如下: 

1, 创建的是非分离线程，线程结束后，需要使用pthread_join来触发该一小段内存回收。
2, 创建的是分离线程，但是主线程优先执行完退出程序，导致被创建的线程没有执行完，导致资源的泄露

==40360== HEAP SUMMARY:
==40360==     in use at exit: 272 bytes in 1 blocks
==40360==   total heap usage: 3 allocs, 2 frees, 1,344 bytes allocated
==40360==
==40360== 272 bytes in 1 blocks are possibly lost in loss record 1 of 1
==40360==    at 0x4C31B25: calloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==40360==    by 0x40134A6: allocate_dtv (dl-tls.c:286)
==40360==    by 0x40134A6: _dl_allocate_tls (dl-tls.c:530)
==40360==    by 0x4E44227: allocate_stack (allocatestack.c:627)
==40360==    by 0x4E44227: pthread_create@@GLIBC_2.2.5 (pthread_create.c:644)
==40360==    by 0x108F1C: HalLinuxThreadInit (hal_linux_thread.c:111)
==40360==    by 0x108CC1: HalThreadInit (hal_thread.c:85)
==40360==    by 0x108AD4: main (main.c:50)
==40360==
==40360== LEAK SUMMARY:
==40360==    definitely lost: 0 bytes in 0 blocks
==40360==    indirectly lost: 0 bytes in 0 blocks
==40360==      possibly lost: 272 bytes in 1 blocks
==40360==    still reachable: 0 bytes in 0 blocks
==40360==         suppressed: 0 bytes in 0 blocks
#endif

