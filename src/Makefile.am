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

if COMPILE_WITH_LINUX_HAL
SUBDIRS = linux
endif

if COMPILE_WITH_RTT_HAL
SUBDIRS = rtt
endif

lib_LTLIBRARIES = libhal.la

# libtool动态库的版本由三个字段组成current:revision:age: 
#
# 动态库的版本应该开始于0:0:0
# 1. 如果library的源码发生了变动， 则revision加1
# 2. 如果library的接口发生了任何改动（增加， 删除，参数或返回值变动）， 则current加1， revision置0
# 3. 如果library只是增加了接口， 则age加1
# 4. 如果library的接口被删除或参数返回值发生变动， 则将age置0
#
#简单地讲：
# current为当前接口改动的次数
# revision为上次接口改变后源码修改（不改动接口）的次数
# age为当前版本向前兼容的版本数
#
#如【3:12:1】
# 表示该library的接口改动了3次， 第3次接口改动后修改了12次源码，
# 该版本的library兼容依赖于current=2（3-1）版本library的程序。
# 将该库进行编译后，会发现库的名字为libraryname.so.2.1.12， 即编译产生的库名为libraryname.so.c-a.a.r。
# 表示该library对于依赖于current=c-a(libraryname.so.2)到current=c(libraryname.so.3)的程序都是可用的， 运行时不会出现任何异常。
LDFLAGS_COM = -version-info @current@:@revision@:@age@

# 选项'-rdynamic'用来通知链接器将所有符号添加到动态符号表中（目的是能够通过使用 dlopen 来实现向后跟踪）
LDFLAGS_COM += -rdynamic

# 导出函数列表方法：
# 1，直接添加__attribute__((visibility("hidden")))到函数上
# 2，在CFLAG中添加-fvisibility=hidden参数，全部不导出，然后配合EXPORT_FUNC导出需要导出的函数
# 3，通过文件指定需要导出的函数，
#    在gcc中添加参数(两种实现方式): "-Wl,-version-script -Wl,.libs/libhal.ver"
#                                   "-Wl,--version-script=.libs/libhal.ver"
#  cat libhal.ver
#  { global:
#  Hal_strlen;
#  Hal_strncpy;
#  local: *; };
# 4, 通过libtool导出函数列表，如下参数
LDFLAGS_COM += -export-symbols-regex 'Hal*'

CFLAGS_COM  = $(AM_CFLAGS_COM)
CFLAGS_COM += -I$(top_srcdir)/include

# 下面两个参数一个显示警告，一个直接通过
# CFLAGS_COM += -Wno-error=unused-parameter
CFLAGS_COM += -Wno-unused-parameter

SOURCES_COM = hal_log.c \
			  hal_mem.c \
			  hal_time.c \
			  hal_string.c \
			  hal_assert.c \
			  hal_thread.c \
			  hal_sem.c \
			  hal_file.c

FUNC_MODULE_SOURCES =

if COMPILE_WITH_LINUX_HAL
if COMPILE_WITH_AUDIO_HAL
FUNC_MODULE_SOURCES += hal_audio_recorder.c
endif

SOURCES_COM += hal_dl_lib.c
LDFLAGS_COM += -ldl
if COMPILE_WITH_CODE_COVERAGE_HAL
LDFLAGS_COM += -lgcov
endif

LDFLAGS_COM += linux/*.lo
CFLAGS_COM 	+= -I$(top_srcdir)/include/linux
endif

if COMPILE_WITH_RTT_HAL
LDFLAGS_COM += rtt/*.lo
CFLAGS_COM  += -I$(top_srcdir)/include/rtt \
			   -I$(top_srcdir)/include/rtt/include
endif
export CFLAGS_COM

# AM_CPPFLAGS和AM_CFLAGS的区分
AM_CFLAGS 		   = $(CFLAGS_COM)
libhal_la_LDFLAGS  = $(LDFLAGS_COM)
libhal_la_SOURCES  = $(SOURCES_COM) \
					 $(FUNC_MODULE_SOURCES)

