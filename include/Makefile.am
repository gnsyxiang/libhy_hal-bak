# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    21/12 2019 13:21
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        21/12 2019      create the file
# 
#     last modified: 21/12 2019 13:21
# ===============================================================

HEADERS_COM = hal_config.h \
			  hal_type.h \
			  hal_log.h \
			  hal_mem.h \
			  hal_time.h \
			  hal_string.h \
			  hal_assert.h \
			  hal_thread.h \
			  hal_sem.h

HEADERS_FUNC_MODULE = hal_audio_recorder.h

noinst_HEADERS  = hal_thread_internal.h

if COMPILE_WITH_LINUX_HAL
noinst_HEADERS += linux/hal_linux_thread.h
endif

if COMPILE_WITH_RTT_HAL
noinst_HEADERS += rtt/hal_rtt_thread.h
endif

include_HEADERS = $(HEADERS_COM) $(HEADERS_FUNC_MODULE)

# FIXME 下面的问题还没有解决
# inheaderdir = ${prefix}
# inheader_DATA = hal_thread_internal.h \
			  # linux/hal_linux_thread.h \
			  # rtt/hal_rtt_thread.h
#
# EXTRA_DIST = $(inheader_DATA)

