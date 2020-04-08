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

HEADERS_COM = hal_type.h \
			  hal_log.h \
			  hal_mem.h \
			  hal_time.h \
			  hal_string.h \
			  hal_assert.h \
			  hal_thread.h \
			  hal_sem.h \
			  hal_file.h

HEADERS_FUNC_MODULE =

noinst_HEADERS  = hal_module_cb.h \
				  hal_thread_internal.h

if COMPILE_WITH_LINUX_HAL
HEADERS_COM 	+= hal_dl_lib.h

noinst_HEADERS 	+= linux/hal_linux_thread.h
				   
if COMPILE_WITH_AUDIO_HAL
HEADERS_FUNC_MODULE += hal_audio_recorder.h
noinst_HEADERS 		+= linux/hal_linux_audio.h \
					   hal_audio_recorder_internal.h
endif
endif

if COMPILE_WITH_RTT_HAL
noinst_HEADERS += rtt/hal_rtt_thread.h
endif

halincludedir = $(includedir)/hal

halinclude_HEADERS = $(HEADERS_COM) $(HEADERS_FUNC_MODULE)

