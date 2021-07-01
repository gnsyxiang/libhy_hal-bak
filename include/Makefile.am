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

NO_INSTALL_HEADERS_COM  =
INSTALL_HEADERS_COM     =
install_includedir      = $(includedir)/@project_name@

# ----------------------------------------------------
NO_INSTALL_HEADERS_COM  +=

INSTALL_HEADERS_COM     += \
                           hy_time.h \
                           hy_mem.h \
                           hy_type.h \
                           hy_compile.h \
                           hy_log.h

noinst_HEADERS          = $(NO_INSTALL_HEADERS_COM)
install_include_HEADERS = $(INSTALL_HEADERS_COM)

