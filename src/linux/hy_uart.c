/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    uart.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    10/07 2021 10:39
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        10/07 2021      create the file
 * 
 *     last modified: 10/07 2021 10:39
 */
#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "hy_uart.h"
#include "hy_file.h"

#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_error.h"
#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HyUartConfigSave_t config_save;

    hy_s32_t fd;
} _uart_context_t;

hy_s32_t HyUartWrite(void *handle, void *buf, size_t len)
{
    HY_ASSERT_NULL_RET_VAL(!handle | !buf, -1);
    _uart_context_t *context = handle;

    return HyFileWrite(context->fd, buf, len);
}

hy_s32_t HyUartProcess(void *handle)
{
    HY_ASSERT_NULL_RET_VAL(!handle, -1);
    _uart_context_t *context = handle;

    char buf[BUF_LEN] = {0};
    hy_s32_t ret = HyFileRead(context->fd, buf, BUF_LEN);

    if (ret > 0 && context->config_save.read_cb) {
        context->config_save.read_cb(buf, ret, context->config_save.args);
    }

    return 0;
}

static void _uart_close(_uart_context_t *context)
{
    if (context->fd > 0) {
        close(context->fd);
    }
}

static hy_s32_t _uart_open(_uart_context_t *context, HyUartConfig_t *uart_config)
{
    do {
        if (!uart_config->dev_name) {
            LOGE("the param is NULL \n");
            break;
        }

        hy_s32_t flag = 0;
        if (uart_config->is_block == HY_UART_NONBLOCK) {
            flag = O_RDWR | O_NOCTTY | O_NONBLOCK;
        } else {
            flag = O_RDWR | O_NOCTTY;
        }

        context->fd = open(uart_config->dev_name, flag);
        if(context->fd < 0) {
            LOGE("open faild \n");
            break;
        }

        // 恢复串口为阻塞状态
        if (fcntl(context->fd, F_GETFL, 0) < 0) {
            LOGE("fcntl faild \n");
            break;
        }

        return HY_ERR_OK;
    } while (0);

    _uart_close(context);
    return HY_ERR_FAILD;
}

static void _uart_destroy(_uart_context_t *context)
{
    _uart_close(context);
}

static hy_s32_t _uart_create(_uart_context_t *context, HyUartConfig_t *uart_config)
{
    do {
        if (HY_ERR_OK != _uart_open(context, uart_config)) {
            LOGE("_uart_open faild \n");
            break;
        }

        struct termios options;

        /*获取终端属性*/
        if(tcgetattr(context->fd, &options) < 0) {
            LOGE("tcgetattr faild \n");
            break;
        }

        /*设置输入输出波特率，两者保持一致*/
        switch(uart_config->rate) {
            case HY_RATE_1200:
                cfsetispeed(&options, B1200);
                cfsetospeed(&options, B1200);
                break;
            case HY_RATE_2400:
                cfsetispeed(&options, B2400);
                cfsetospeed(&options, B2400);
                break;
            case HY_RATE_4800:
                cfsetispeed(&options, B4800);
                cfsetospeed(&options, B4800);
                break;
            case HY_RATE_9600:
                cfsetispeed(&options, B9600);
                cfsetospeed(&options, B9600);
                break;
            case HY_RATE_19200:
                cfsetispeed(&options, B19200);
                cfsetospeed(&options, B19200);
                break;
            case HY_RATE_38400:
                cfsetispeed(&options, B38400);
                cfsetospeed(&options, B38400);
                break;
            case HY_RATE_57600:
                cfsetispeed(&options, B57600);
                cfsetospeed(&options, B57600);
                break;
            case HY_RATE_115200:
                cfsetispeed(&options, B115200);
                cfsetospeed(&options, B115200);
                break;
            default:
                LOGE("unknow rate\n");
                break;
        }

        /*设置控制模式*/
        options.c_cflag |= CLOCAL;      //保证程序不占用串口
        options.c_cflag |= CREAD;       //保证程序可以从串口中读取数据

        /*设置数据流控制*/
        switch(uart_config->flow_control) {
            case HY_UART_FLOW_CONTROL_DISABLE://不进行流控制
                options.c_cflag &= ~CRTSCTS;
                break;
            case HY_UART_FLOW_CONTROL_HARD_ENABLE://进行硬件流控制
                options.c_cflag |= CRTSCTS;
                break;
            case HY_UART_FLOW_CONTROL_SOFT_ENABLE://进行软件流控制
                options.c_cflag |= IXON|IXOFF|IXANY;
                break;
            default:
                LOGE("unknow flow control \n");
                break;
        }

        /*设置数据位*/
        switch(uart_config->bits) {
            case HY_UART_BITS_5:
                options.c_cflag &= ~CSIZE;//屏蔽其它标志位
                options.c_cflag |= CS5;
                break;
            case HY_UART_BITS_6:
                options.c_cflag &= ~CSIZE;//屏蔽其它标志位
                options.c_cflag |= CS6;
                break;
            case HY_UART_BITS_7:
                options.c_cflag &= ~CSIZE;//屏蔽其它标志位
                options.c_cflag |= CS7;
                break;
            case HY_UART_BITS_8:
                options.c_cflag &= ~CSIZE;//屏蔽其它标志位
                options.c_cflag |= CS8;
                break;
            default:
                LOGE("unknow bits \n");
                break;
        }

        /*设置校验位*/
        switch(uart_config->parity) {
            /*无奇偶校验位*/
            case HY_UART_PARITY_N:
                options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校验
                break;
                /*设为空格,即停止位为2位*/
            case HY_UART_PARITY_S:
                options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校验
                options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
                break;
                /*设置奇校验*/
            case HY_UART_PARITY_O:
                options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
                options.c_cflag |= PARODD;//PARODD：若设置则为奇校验,否则为偶校验
                options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
                options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
                break;
                /*设置偶校验*/
            case HY_UART_PARITY_E:
                options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
                options.c_cflag &= ~PARODD;//PARODD：若设置则为奇校验,否则为偶校验
                options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
                options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
                break;
            default:
                LOGE("unknow parity \n");
                break;
        }

        /*设置停止位*/
        switch(uart_config->stop) {
            case HY_UART_STOP_1:
                options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
                break;
            case HY_UART_STOP_2:
                options.c_cflag |= CSTOPB;//CSTOPB：使用两位停止位
                break;
            default:
                LOGE("unknow stop \n");
                break;
        }

        /*设置输出模式为原始输出*/
        options.c_oflag &= ~OPOST;      //OPOST：若设置则按定义的输出处理，否则所有c_oflag失效

        /*设置本地模式为原始模式*/
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        /*
         *ICANON：允许规范模式进行输入处理
         *ECHO：允许输入字符的本地回显
         *ECHOE：在接收EPASE时执行Backspace,Space,Backspace组合
         *ISIG：允许信号
         */

        /*设置等待时间和最小接受字符*/
        options.c_cc[VTIME] = 0;//可以在select中设置
        options.c_cc[VMIN] = 1;//最少读取一个字符

        /*如果发生数据溢出，只接受数据，但是不进行读操作*/
        tcflush(context->fd, TCIFLUSH);

        /*激活配置*/
        if(tcsetattr(context->fd, TCSANOW, &options) < 0) {
            LOGE("tcsetattr faild \n");
            break;
        }

        return HY_ERR_OK;
    } while (0);

    _uart_destroy(context);
    return HY_ERR_FAILD;
}

void HyUartDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    _uart_context_t *context = *handle;
    _uart_destroy(context);

    HY_FREE(handle);
}

void *HyUartCreate(HyUartConfig_t *uart_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!uart_config, NULL);

    _uart_context_t *context = NULL;

    do {
        context = (_uart_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        HY_MEMCPY(&context->config_save, &uart_config->config_save);

        if (HY_ERR_OK != _uart_create(context, uart_config)) {
            LOGE("_uart_create faild \n");
            break;
        }

        return context;
    } while (0);

    HyUartDestroy((void **)&context);
    return NULL;
}

