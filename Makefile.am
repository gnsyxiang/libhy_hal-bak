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
export AM_CFLAGS_COM

# FIXME 下面的问题还没有解决
# script_SCRIPTS: 指定"make install"时安装的脚本
# dist_script_DATA: 指定"make dist"时安装的脚本
# scriptdir = ${prefix}
# script_SCRIPTS = build.sh
# dist_script_DATA = build.sh

SUBDIRS = include src example

