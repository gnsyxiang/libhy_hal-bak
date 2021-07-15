# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    21/12 2019 13:22
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        21/12 2019      create the file
# 
#     last modified: 21/12 2019 13:22
# ===============================================================

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
bin_PROGRAMS    =

# ---------------------
# add necessary content
# ---------------------
_include_com    += -I$(top_srcdir)/include

_sources_com    +=

_cppflags_com   += $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(BIN_LDFLAGS_COM)

if COMPILE_LIBHY_UTILS
_ldadd_com      += $(HY_UTILS_LIBS)
endif

_ldadd_com      += $(top_builddir)/src/lib@project_name@.la

bin_PROGRAMS            += hy_time_test
hy_time_test_SOURCES    = $(_sources_com) hy_time_test.c
hy_time_test_CPPFLAGS   = $(_cppflags_com)
hy_time_test_CFLAGS     = $(_cflags_com)
hy_time_test_CXXFLAGS   = $(_cxxflags_com)
hy_time_test_LDFLAGS    = $(_ldflags_com)
hy_time_test_LDADD      = $(_ldadd_com)

bin_PROGRAMS                += hy_socket_test
hy_socket_test_SOURCES      = $(_sources_com) hy_socket_test.c
hy_socket_test_CPPFLAGS     = $(_cppflags_com)
hy_socket_test_CFLAGS       = $(_cflags_com)
hy_socket_test_CXXFLAGS     = $(_cxxflags_com)
hy_socket_test_LDFLAGS      = $(_ldflags_com)
hy_socket_test_LDADD        = $(_ldadd_com)

