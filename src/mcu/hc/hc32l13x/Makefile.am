# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    09/07 2021 15:30
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        09/07 2021      create the file
# 
#     last modified: 09/07 2021 15:30
# ===============================================================

noinst_LTLIBRARIES = libhc_mcu_os.la

# ------------------
# defining variables
# ------------------
_no_error_com   =
_include_com    =
_sources_com    =
_cppflags_com   =
_cflags_com     =
_cxxflags_com   =
_ldflags_com    =
_ldadd_com      =

# ---------------------
# add necessary content
# ---------------------
_no_error_com   += -Wno-error=int-conversion

_include_com    += -I$(top_srcdir)/include

_include_com    += $(HY_MCU_INCS)

_sources_com    += \
                   hy_adc.c \
                   hy_gpio.c \
                   hy_gpio_int.c \
                   hy_system.c \
                   hy_time.c \
                   hy_uart.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_no_error_com) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      +=

libhc_mcu_os_la_SOURCES   = $(_sources_com)
libhc_mcu_os_la_CPPFLAGS  = $(_cppflags_com)
libhc_mcu_os_la_CFLAGS    = $(_cflags_com)
libhc_mcu_os_la_CXXFLAGS  = $(_cxxflags_com)
libhc_mcu_os_la_LDFLAGS   = $(_ldflags_com)
libhc_mcu_os_la_LIBADD    = $(_ldadd_com)

