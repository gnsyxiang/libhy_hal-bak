# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    21/12 2019 13:21
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        21/12 2019      create the file
# 
#     last modified: 21/12 2019 13:21
# ===============================================================

# ------------------
# defining variables
# ------------------
_no_install_headers_com     =
_install_headers_com        =
install_includedir          = $(includedir)/@project_name@

# ---------------------
# add necessary content
# ---------------------
_no_install_headers_com     += \
                               inside_uart.h \
                               inside_time.h \
                               inside_gpio.h

_install_headers_com        += \
                               hy_socket.h \
                               hy_uart.h \
                               hy_utils.h

if COMPILE_SELECT_TARGET_OS_LINUX
_install_headers_com        += \
                               hy_file.h \
                               hy_signal.h
endif

if COMPILE_SELECT_TARGET_OS_MCU
_install_headers_com        += \
                               hy_timer.h \
                               hy_key.h \
                               hy_adc.h \
                               hy_gpio.h \
                               hy_gpio_int.h \
                               hy_system.h \
                               hy_time.h
endif

# ------------------
# make install files
# ------------------
noinst_HEADERS              = $(_no_install_headers_com)
install_include_HEADERS     = $(_install_headers_com)

