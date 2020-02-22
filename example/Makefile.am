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

AM_CFLAGS  = $(AM_CFLAGS_COM)
AM_CFLAGS += -Wno-error=unused-parameter
AM_CFLAGS += -I$(top_srcdir)/include

bin_PROGRAMS = demo

demo_SOURCES = main.c
demo_LDADD   = $(top_builddir)/src/.libs/libhal.a
demo_LDADD  += -lpthread

