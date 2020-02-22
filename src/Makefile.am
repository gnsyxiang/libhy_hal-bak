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
LIB_VERSION = -version-info @current@:@revision@:@age@

if COMPILE_WITH_RTT_HAL

else

LDFLAGS_COM  = -rdynamic -fPIC
LDFLAGS_COM += $(LIB_VERSION)

AM_CFLAGS  = $(AM_CFLAGS_COM)
AM_CFLAGS += -Wno-error=unused-parameter
AM_CFLAGS += -I$(top_srcdir)/include
AM_CFLAGS += -I$(top_srcdir)/include/linux

libhal_la_LDFLAGS  = $(LDFLAGS_COM)
libhal_la_SOURCES  = hal_thread.c
libhal_la_SOURCES += linux/hal_linux_thread.c
endif

all: libhal.la

