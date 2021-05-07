# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    05/03 2021 10:32
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        05/03 2021      create the file
# 
#     last modified: 05/03 2021 10:32
# ===============================================================

include res/doxygen.am

SUBDIRS = include \
		  src \
		  example \
		  docs \
		  res

# -----
# flags
# -----
ACLOCAL_AMFLAGS 	= -I m4

_no_error_com 		= -W -Wall -Werror \
					  -Wno-error=unused-result \
					  -Wno-unused-parameter \
					  -Wno-error=unused-but-set-variable

# 下面两个参数一个显示警告，一个直接通过
_no_error_com 		+= -Wno-error=unused-parameter
# _no_error_com 		+= -Wno-unused-parameter

_remove_unuse_func 	= -ffunction-sections \
					  -fdata-sections

CPPFLAGS_COM 		= -pipe \
					  $(_no_error_com) \
					  $(ACLOCAL_AMFLAGS)

CFLAGS_COM 			= $(_remove_unuse_func)

CXXFLAGS_COM 		= $(_remove_unuse_func)

# 用来通知链接器将所有符号添加到动态符号表中
#（目的是能够通过使用 dlopen 来实现向后跟踪）
LIB_LDFLAGS_COM 	= -rdynamic

BIN_LDFLAGS_COM 	= -Wl,--gc-sections

export CPPFLAGS_COM
export CFLAGS_COM
export CXXFLAGS_COM
export LIB_LDFLAGS_COM
export BIN_LDFLAGS_COM

# ------------------
# make install files
# ------------------
_install_files_com 	= LICENSE \
					  README.md
dist_doc_DATA 		= $(_install_files_com)

pkgconfigdir 		= $(libdir)/pkgconfig
pkgconfig_DATA 		= @PACKAGE_NAME@.pc

# ---------------
# make dist files
# ---------------
_dist_files_com 	= autogen.sh \
					  @PACKAGE_NAME@.pc.in
EXTRA_DIST 			= $(_dist_files_com)
