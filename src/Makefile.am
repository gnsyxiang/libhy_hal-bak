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

lib_LTLIBRARIES = libhal.la

LDFLAGS_COM  = -rdynamic -fPIC
LDFLAGS_COM += -version-info @current@:@revision@:@age@

AM_CFLAGS = $(AM_CFLAGS_COM)

libhal_la_LDFLAGS = $(LDFLAGS_COM)
libhal_la_SOURCES = demo.c

all: libhal.la

