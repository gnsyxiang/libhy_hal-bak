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
bin_PROGRAMS    =
BUILT_SOURCES   =
CLEANFILES      =

# ---------------------
# add necessary content
# ---------------------
_no_error_com       += -Wno-error=address

_include_com    += -I$(top_srcdir)/include

_sources_com    +=

_cppflags_com   += $(CPPFLAGS_COM) \
                   $(_no_error_com) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(BIN_LDFLAGS_COM)

if COMPILE_LIBHY_UTILS
_ldadd_com      += $(HY_UTILS_LIBS)
endif

_ldadd_com      += $(top_builddir)/src/lib@project_name@.la

if COMPILE_SELECT_TARGET_OS_LINUX
bin_PROGRAMS                += hy_time_demo
hy_time_demo_SOURCES        = $(_sources_com) hy_time_demo.c
hy_time_demo_CPPFLAGS       = $(_cppflags_com)
hy_time_demo_CFLAGS         = $(_cflags_com)
hy_time_demo_CXXFLAGS       = $(_cxxflags_com)
hy_time_demo_LDFLAGS        = $(_ldflags_com)
hy_time_demo_LDADD          = $(_ldadd_com)

bin_PROGRAMS                += hy_socket_demo
hy_socket_demo_SOURCES      = $(_sources_com) hy_socket_demo.c
hy_socket_demo_CPPFLAGS     = $(_cppflags_com)
hy_socket_demo_CFLAGS       = $(_cflags_com)
hy_socket_demo_CXXFLAGS     = $(_cxxflags_com)
hy_socket_demo_LDFLAGS      = $(_ldflags_com)
hy_socket_demo_LDADD        = $(_ldadd_com)

bin_PROGRAMS                += hy_uart_demo
hy_uart_demo_SOURCES        = $(_sources_com) hy_uart_demo.c
hy_uart_demo_CPPFLAGS       = $(_cppflags_com)
hy_uart_demo_CFLAGS         = $(_cflags_com)
hy_uart_demo_CXXFLAGS       = $(_cxxflags_com)
hy_uart_demo_LDFLAGS        = $(_ldflags_com)
hy_uart_demo_LDADD          = $(_ldadd_com)
endif

if COMPILE_SELECT_TARGET_OS_MCU

if COMPILE_LIBHY_UTILS
_ldadd_com      += $(HY_MCU_LIBS)
endif

bin_PROGRAMS                += hy_mcu_time_demo
hy_mcu_time_demo_SOURCES    = $(_sources_com) hy_mcu_time_demo.c
hy_mcu_time_demo_CPPFLAGS   = $(_cppflags_com)
hy_mcu_time_demo_CFLAGS     = $(_cflags_com)
hy_mcu_time_demo_CXXFLAGS   = $(_cxxflags_com)
hy_mcu_time_demo_LDFLAGS    = $(_ldflags_com)
hy_mcu_time_demo_LDADD      = $(_ldadd_com)

if COMPILE_LIBPROTOBUF_C

if COMPILE_LIBPROTOBUF_C
_ldadd_com      += $(LIBPROTOBUF_C_LIBS)
endif

bin_PROGRAMS                += hy_protobuf-c_demo
hy_protobuf_c_demo_SOURCES  = $(_sources_com) hy_protobuf-c_demo.c address_book.pb-c.c
hy_protobuf_c_demo_CPPFLAGS = $(_cppflags_com)
hy_protobuf_c_demo_CFLAGS   = $(_cflags_com)
hy_protobuf_c_demo_CXXFLAGS = $(_cxxflags_com)
hy_protobuf_c_demo_LDFLAGS  = $(_ldflags_com)
hy_protobuf_c_demo_LDADD    = $(_ldadd_com)

address_book.pb.c address_book.pb.h: @PROTOC_C@ address_book.proto
	$(AM_V_GEN)@PROTOC_C@ --c_out=. address_book.proto

BUILT_SOURCES += \
                 address_book.pb.c \
                 address_book.pb.h

CLEANFILES += $(BUILT_SOURCES)

install-exec-hook:
	@gcc_prefix@objcopy -O binary main.elf main.bin
	@gcc_prefix@objcopy -O binary protobuf-c-demo.elf protobuf-c-demo.bin
	$(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) *.bin "$(DESTDIR)$(bindir)$$dir"
endif
endif

