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
_no_install_headers_com     +=

_install_headers_com        += \
                               hy_socket.h \
                               hy_time.h \
                               hy_uart.h

if COMPILE_SELECT_TARGET_OS_LINUX
_install_headers_com        += hy_file.h
endif

# ------------------
# make install files
# ------------------
noinst_HEADERS              = $(_no_install_headers_com)
install_include_HEADERS     = $(_install_headers_com)

