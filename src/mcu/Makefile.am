# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    09/07 2021 15:30
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        09/07 2021      create the file
# 
#     last modified: 09/07 2021 15:30
# ===============================================================

noinst_LTLIBRARIES = libhy_os.la

# ------------------
# defining variables
# ------------------
_include_com    =
_sources_com    =
_cppflags_com   =
_cflags_com     =
_cxxflags_com   =
_ldflags_com    =
_ldadd_com      =

# ---------------------
# add necessary content
# ---------------------
_include_com    += \
                   -I$(top_srcdir)/include/wrapper \
                   -I$(top_srcdir)/include

_sources_com    += \
                   socket_wrapper.c \
                   time_wrapper.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

libhy_os_la_SOURCES   = $(_sources_com)
libhy_os_la_CPPFLAGS  = $(_cppflags_com)
libhy_os_la_CFLAGS    = $(_cflags_com)
libhy_os_la_CXXFLAGS  = $(_cxxflags_com)
libhy_os_la_LDFLAGS   = $(_ldflags_com)
libhy_os_la_LIBADD    = $(_ldadd_com)

