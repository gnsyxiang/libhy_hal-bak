# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    21/03 2020 22:57
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        21/03 2020      create the file
# 
#     last modified: 21/03 2020 22:57
# ===============================================================

noinst_LTLIBRARIES = libhal_linux.la          

CFLAGS_COM 	 = $(AM_CFLAGS_COM)
CFLAGS_COM 	+= -I$(top_srcdir)/include
CFLAGS_COM 	+= -I$(top_srcdir)/include/linux
CFLAGS_COM 	+= -Wno-unused-parameter

SOURCES_COM  = hal_linux_thread.c

if COMPILE_WITH_AUDIO_HAL
SOURCES_COM += hal_linux_audio.c
endif

LDFLAGS_COM  = -rdynamic
LDFLAGS_COM += -export-symbols-regex 'Hal*'

AM_CFLAGS 		   	   	 = $(CFLAGS_COM)
libhal_linux_la_LDFLAGS  = $(LDFLAGS_COM)
libhal_linux_la_SOURCES  = $(SOURCES_COM)

