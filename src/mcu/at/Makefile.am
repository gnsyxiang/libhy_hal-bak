# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    06/09 2021 10:33
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        06/09 2021      create the file
# 
#     last modified: 06/09 2021 10:33
# ===============================================================

if COMPILE_SELECT_MCU_AT32F4XX
_mcu_type = at32f4xx
endif

SUBDIRS = $(_mcu_type)

noinst_LTLIBRARIES = libmcu_os.la

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
_include_com    +=

_sources_com    +=

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      += $(top_builddir)/src/mcu/at/$(_mcu_type)/libat_mcu_os.la

libmcu_os_la_SOURCES  = $(_sources_com)
libmcu_os_la_CPPFLAGS = $(_cppflags_com)
libmcu_os_la_CFLAGS   = $(_cflags_com)
libmcu_os_la_CXXFLAGS = $(_cxxflags_com)
libmcu_os_la_LDFLAGS  = $(_ldflags_com)
libmcu_os_la_LIBADD   = $(_ldadd_com)
