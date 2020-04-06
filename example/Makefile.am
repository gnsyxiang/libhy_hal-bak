# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    21/12 2019 13:22
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        21/12 2019      create the file
# 
#     last modified: 21/12 2019 13:22
# ===============================================================

CFLAGS_COM  	= -I$(top_srcdir)/include
# CFLAGS_COM += -Wno-error=unused-parameter
CFLAGS_COM 		+= -Wno-unused-parameter
CFLAGS_COM 		+= -DCONFIG_DIR=\"$(sysconfdir)\"

if COMPILE_WITH_RTT_HAL
CFLAGS_COM 	   	+= -I$(top_srcdir)/include/rtt \
				   -I$(top_srcdir)/include/rtt/include
CFLAGS_COM		+= --specs=rdimon.specs
endif

hal_ld_com  	= -L$(top_builddir)/src/.libs
hal_ld_com 	   	+= -lhal
if COMPILE_WITH_CODE_COVERAGE_HAL
hal_ld_com 	   	+= -lgcov
endif

exampledir 	  	 = $(prefix)/example
example_DATA  	 = demo.c log.c makefile
dist_example_DATA = makefile
if COMPILE_WITH_LINUX_HAL
example_DATA 	+= dl_lib.c thread.c
if COMPILE_WITH_AUDIO_HAL
example_DATA 	+= audio.c
endif
endif

bin_PROGRAMS 	= demo
demo_SOURCES 	= demo.c
demo_LDADD   	= $(hal_ld_com)
demo_CFLAGS  	= $(AM_CFLAGS_COM) $(CFLAGS_COM)

bin_PROGRAMS	+= log
log_SOURCES 	= log.c
log_LDADD   	= $(hal_ld_com)
log_CFLAGS  	= $(AM_CFLAGS_COM) $(CFLAGS_COM)

bin_PROGRAMS	+= file
file_SOURCES 	= file.c
file_LDADD   	= $(hal_ld_com)
file_CFLAGS  	= $(AM_CFLAGS_COM) $(CFLAGS_COM)

if COMPILE_WITH_LINUX_HAL
bin_PROGRAMS   	+= dl_lib
dl_lib_SOURCES 	= dl_lib.c
dl_lib_LDADD   	= $(hal_ld_com)
dl_lib_CFLAGS  	= $(AM_CFLAGS_COM) $(CFLAGS_COM)

if COMPILE_WITH_AUDIO_HAL
bin_PROGRAMS   	+= audio
audio_SOURCES 	= audio.c
audio_LDADD   	= $(hal_ld_com) -ltinyalsa
audio_CFLAGS  	= $(AM_CFLAGS_COM) $(CFLAGS_COM)
endif

bin_PROGRAMS   	+= thread
thread_SOURCES 	= thread.c
thread_LDADD   	= $(hal_ld_com) -lpthread
thread_CFLAGS  	= $(AM_CFLAGS_COM) $(CFLAGS_COM)
endif

