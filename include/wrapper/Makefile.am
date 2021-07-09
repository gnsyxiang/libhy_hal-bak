# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    30/06 2021 17:03
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        30/06 2021      create the file
# 
#     last modified: 30/06 2021 17:03
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
                               hy_socket_wrapper.h \
                               hy_time_wrapper.h

_install_headers_com        +=

# ------------------
# make install files
# ------------------
noinst_HEADERS              = $(_no_install_headers_com)
install_include_HEADERS     = $(_install_headers_com)

