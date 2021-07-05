# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    21/12 2019 13:20
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        21/12 2019      create the file
# 
#     last modified: 21/12 2019 13:20
# ===============================================================

if COMPILE_SELECT_TARGET_OS_LINUX
SUBDIRS = linux
select_target_os = linux
endif

if COMPILE_SELECT_TARGET_OS_MAC
SUBDIRS = mac
select_target_os = mac
endif

if COMPILE_SELECT_TARGET_OS_WINDOW
SUBDIRS = window
select_target_os = window
endif

if COMPILE_SELECT_TARGET_OS_RTOS
SUBDIRS = rtos
select_target_os = rtos
endif

lib_LTLIBRARIES = lib@project_name@.la

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
                   hy_socket.c \
                   hy_time.c \
                   hy_mem.c \
                   hy_log.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += \
                   $(LIB_LDFLAGS_COM) \
                   -export-symbols-regex 'Hy*' \
                   -version-info @current@:@revision@:@age@ \
                   $(top_builddir)/src/$(select_target_os)/libhy_os.la

lib@project_name@_la_SOURCES    = $(_sources_com)
lib@project_name@_la_CPPFLAGS   = $(_cppflags_com)
lib@project_name@_la_CFLAGS     = $(_cflags_com)
lib@project_name@_la_CXXFLAGS   = $(_cxxflags_com)
lib@project_name@_la_LDFLAGS    = $(_ldflags_com)
lib@project_name@_la_LIBADD     = $(_ldadd_com)

