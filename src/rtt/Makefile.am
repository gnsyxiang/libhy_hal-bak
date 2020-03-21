# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    21/03 2020 23:41
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        21/03 2020      create the file
# 
#     last modified: 21/03 2020 23:41
# ===============================================================

noinst_LTLIBRARIES = libhal_rtt.la          

CFLAGS_COM 	 = $(AM_CFLAGS_COM)
CFLAGS_COM  += -I$(top_srcdir)/include
CFLAGS_COM  += -I$(top_srcdir)/include/rtt \
		       -I$(top_srcdir)/include/rtt/include
CFLAGS_COM  += -Wno-unused-parameter
CFLAGS_COM  += -Wno-error=type-limits

SOURCES_COM  = hal_rtt_thread.c

LDFLAGS_COM	 = -rdynamic
LDFLAGS_COM += -export-symbols-regex 'Hal*'

AM_CFLAGS 		   	   = $(CFLAGS_COM)
libhal_rtt_la_LDFLAGS  = $(LDFLAGS_COM)
libhal_rtt_la_SOURCES  = $(SOURCES_COM)

