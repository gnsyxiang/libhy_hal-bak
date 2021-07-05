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

SUBDIRS = wrapper

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
                               hy_mem.h \
                               hy_type.h \
                               hy_compile.h \
                               hy_error.h \
                               hy_log.h

# ------------------
# make install files
# ------------------
noinst_HEADERS              = $(_no_install_headers_com)
install_include_HEADERS     = $(_install_headers_com)

