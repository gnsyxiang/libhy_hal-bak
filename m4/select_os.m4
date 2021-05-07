dnl ===============================================================
dnl 
dnl Release under GPLv-3.0.
dnl 
dnl @file    select_os.m4
dnl @brief   
dnl @author  gnsyxiang <gnsyxiang@163.com>
dnl @date    07/05 2021 16:56
dnl @version v0.0.1
dnl 
dnl @since    note
dnl @note     note
dnl 
dnl     change log:
dnl     NO.     Author              Date            Modified
dnl     00      zhenquan.qiu        07/05 2021      create the file
dnl 
dnl     last modified: 07/05 2021 16:56
dnl ===============================================================

# SELECT_OS()
# --------------------------------------------------------------
# select system os

AC_DEFUN([SELECT_OS],
    [
        AC_ARG_WITH([system_os],
            [AS_HELP_STRING([--with-system_os=@<:@linux|mac|window|rtt@:>@], [select system os about @<:@linux|mac|window|rtt@:>@ @<:@default=linux@:>@])],
            [],
            [with_system_os=linux])

        case "$with_system_os" in
            linux)  AC_DEFINE(HAVE_SELECT_SYSTEM_OS_LINUX, 1, [select linux system]) ;;
            mac)    AC_DEFINE(HAVE_SELECT_SYSTEM_OS_MAC, 1, [select mac system]) ;;
            window) AC_DEFINE(HAVE_SELECT_SYSTEM_OS_WINDOW, 1, [select window system]) ;;
            rtt)    AC_DEFINE(HAVE_SELECT_SYSTEM_OS_RTT, 1, [select rtt system]) ;;
            *)      AC_MSG_ERROR([bad value ${with_system_os} for --with-system_os=@<:@linux|mac|window|rtt@:>@]) ;;
        esac

        AM_CONDITIONAL([COMPILE_SELECT_SYSTEM_OS_LINUX], [test "x$with_system_os" = "xlinux"])
        AM_CONDITIONAL([COMPILE_SELECT_SYSTEM_OS_MAC], [test "x$with_system_os" = "xmac"])
        AM_CONDITIONAL([COMPILE_SELECT_SYSTEM_OS_WINDOW], [test "x$with_system_os" = "xwindow"])
        AM_CONDITIONAL([COMPILE_SELECT_SYSTEM_OS_RTT], [test "x$with_system_os" = "xrtt"])
    ])

