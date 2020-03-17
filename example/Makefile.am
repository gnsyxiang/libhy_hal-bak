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

CFLAGS_COM  = -I$(top_srcdir)/include
# CFLAGS_COM += -Wno-error=unused-parameter
CFLAGS_COM += -Wno-unused-parameter

if COMPILE_WITH_RTT_HAL
CFLAGS_COM += -I$(top_srcdir)/include/rtt \
			  -I$(top_srcdir)/include/rtt/include
CFLAGS_COM += --specs=rdimon.specs
endif

demo_ld_com  = -L$(top_builddir)/src/.libs
demo_ld_com += -lhal

if COMPILE_WITH_LINUX_HAL
demo_ld_com += -lpthread
endif

SOURCES_COM = main.c

bin_PROGRAMS = demo
demo_SOURCES = $(SOURCES_COM)
demo_LDADD   = $(demo_ld_com)
demo_CFLAGS  = $(AM_CFLAGS_COM) \
			   $(CFLAGS_COM)

