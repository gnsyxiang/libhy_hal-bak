dnl ===============================================================
dnl 
dnl Release under GPLv-3.0.
dnl 
dnl @file    check_libhy_utils.m4
dnl @brief   
dnl @author  gnsyxiang <gnsyxiang@163.com>
dnl @date    08/05 2021 10:29
dnl @version v0.0.1
dnl 
dnl @since    note
dnl @note     note
dnl 
dnl     change log:
dnl     NO.     Author              Date            Modified
dnl     00      zhenquan.qiu        08/05 2021      create the file
dnl 
dnl     last modified: 08/05 2021 10:29
dnl ===============================================================

# CHECK_LIBHY_UTILS()
# --------------------------------------------------------------
# check libhy_utils

AC_DEFUN([CHECK_LIBHY_UTILS],
    [
        AC_ARG_WITH([libhy_utils],
                    [AS_HELP_STRING([--with-libhy_utils=@<:@yes|no@:>@], [use libhy_utils library @<:@default=yes@:>@])],
                    [],
                    [with_libhy_utils=yes])

        if test x"$with_libhy_utils" = xyes ; then
            have_libhy_utils=no

            if test x"$LIBHY_UTILS_CFLAGS" != x -a x"$LIBHY_UTILS_LIBS" != x; then
                CPPFLAGS="$LIBHY_UTILS_CFLAGS $CPPFLAGS"
                LDFLAGS="$LIBHY_UTILS_LIBS $LDFLAGS"
                LIBS="$LIBS -lhy_utils"

                # Can I compile and link it?
                AC_TRY_LINK([#include "hy_utils/hy_log.h"],
                            [HyLogDestroy();],
                            [libhy_utils_linked=yes],
                            [libhy_utils_linked=no])
                if test $libhy_utils_linked = no; then
                    AC_MSG_ERROR([assign LIBHY_UTILS_CFLAGS or LIBHY_UTILS_LIBS for libhy_utils])
                fi

                have_libhy_utils="yes (inc lib)"
            else
                PKG_CHECK_MODULES([LIBHY_UTILS],
                                  [libhy_utils > 0.1.0],
                                  [have_libhy_utils="yes (pkg-config)"],
                                  [:])

                if test "$have_libhy_utils" != no; then
                    CPPFLAGS="$LIBHY_UTILS_CFLAGS $CPPFLAGS"
                    LDFLAGS="$LIBHY_UTILS_LIBS $LDFLAGS"
                else
                    # fall back to standard autoconf test
                    AC_CHECK_LIB([hy_utils],
                                 [HyLogDestroy],
                                 [
                                    AC_CHECK_HEADER([hy_utils/hy_log.h],
                                                    [have_libhy_utils="yes (autoconf test)"])
                                 ])
                fi

                if test "$have_libhy_utils" = no; then
                    AC_MSG_ERROR([external libhy_utils support requested but library not found])
                fi
            fi

            AC_DEFINE(HAVE_LIBHY_UTILS, 1, [Have libhy_utils library])
            AM_CONDITIONAL([COMPILE_LIBHY_UTILS], [test "$have_libhy_utils" != no])
        fi
    ])

