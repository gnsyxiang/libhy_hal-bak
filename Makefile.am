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

SUBDIRS = \
          include \
          src \
          example \
          doc \
          res

# ------------------
# defining variables
# ------------------
_no_error_com       =
_remove_unuse_func  =
_install_files_com  =
_dist_files_com     =

CPPFLAGS_COM        =
CFLAGS_COM          =
CXXFLAGS_COM        =
LIB_LDFLAGS_COM     =
BIN_LDFLAGS_COM     =

ACLOCAL_AMFLAGS     = -I m4
pkgconfigdir        = $(libdir)/pkgconfig

# ---------------------
# add necessary content
# ---------------------
_no_error_com       += \
                       -W -Wall -Werror \
                       -Wno-error=unused-function \
                       -Wno-unused-parameter \
                       -Wno-error=unused-variable \
                       -Wno-error=unused-but-set-variable \
                       -Wno-error=unused-result

CPPFLAGS_COM        += \
                       -pipe \
                       $(_no_error_com) \
                       $(ACLOCAL_AMFLAGS)

if COMPILE_SELECT_TARGET_OS_LINUX
BIN_LDFLAGS_COM     += -rdynamic
endif

_remove_unuse_func  += \
                       -ffunction-sections \
                       -fdata-sections
CFLAGS_COM          += $(_remove_unuse_func)
CXXFLAGS_COM        += $(_remove_unuse_func)
BIN_LDFLAGS_COM     += -Wl,--gc-sections

if COMPILE_LIBHY_UTILS
CPPFLAGS_COM        += $(HY_UTILS_INCS)
endif

export CPPFLAGS_COM
export CFLAGS_COM
export CXXFLAGS_COM
export LIB_LDFLAGS_COM
export BIN_LDFLAGS_COM

# ------------------
# make install files
# ------------------
_install_files_com  += \
                       LICENSE \
                       README.md
dist_doc_DATA       = $(_install_files_com)
pkgconfig_DATA      = @project_name@.pc

# ---------------
# make dist files
# ---------------
_dist_files_com     += \
                       autogen.sh \
                       build.sh \
                       @project_name@.pc.in
EXTRA_DIST          = $(_dist_files_com)

if COMPILE_SELECT_TARGET_OS_MCU
install-exec-hook:
	sed -i 's/-lhy_hal/-lhy_hal -lhy_mcu/g' \
		$(top_builddir)/@project_name@.pc
endif
