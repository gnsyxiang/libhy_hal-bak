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
if COMPILE_WITH_CODE_COVERAGE_HAL
AM_CFLAGS_COM += -fprofile-arcs -ftest-coverage
endif
export AM_CFLAGS_COM

# FIXME 下面的问题还没有解决
# script_SCRIPTS: 指定"make install"时安装的脚本
# dist_script_DATA: 指定"make dist"时安装的脚本
# scriptdir = ${prefix}
# script_SCRIPTS = build.sh
# dist_script_DATA = build.sh
# tinyalsalibdir = ${prefix}/3rd_lib/tinyalsa
# tinyalsalib_DATA = 3rd_lib/tinyalsa/*
# EXTRA_DIST=conf           #在make dist打包的时候也要将扩展文件夹打包进去

dist_doc_DATA = README.md

dist_build_SCRIPTS = build.sh

SUBDIRS = include src example

