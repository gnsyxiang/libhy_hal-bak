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

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS_COM  = $(ACLOCAL_AMFLAGS)
AM_CFLAGS_COM += -pipe -W -Wall -Werror
AM_CFLAGS_COM += -I$(top_srcdir)/../include
export AM_CFLAGS_COM

SUBDIRS = include src example

