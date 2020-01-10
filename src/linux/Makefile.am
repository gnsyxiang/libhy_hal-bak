# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    10/01 2020 20:11
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        10/01 2020      create the file
# 
#     last modified: 10/01 2020 20:11
# ===============================================================

lib_LTLIBRARIES = libhal.la

LDFLAGS_COM  = -rdynamic -fPIC
LDFLAGS_COM += -version-info @current@:@revision@:@age@

AM_CFLAGS = $(AM_CFLAGS_COM)
AM_CFLAGS += -I$(top_srcdir)/include

libhal_la_LDFLAGS = $(LDFLAGS_COM)
libhal_la_SOURCES = hal_pthread.c

all: libhal.la

