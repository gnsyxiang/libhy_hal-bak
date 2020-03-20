#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
m4_include([m4/version.m4])

AC_INIT([libhal], [VERSION_NUM], [gnsyxiang@163.com])

AC_CONFIG_SRCDIR([src/hal_thread.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_REQUIRE_AUX_FILE([generate-version.sh])

age=VERSION_AGE_NUM
current=VERSION_CURRENT_NUM
revision=VERSION_REVISION_NUM
AC_SUBST(current)
AC_SUBST(revision)
AC_SUBST(age)

AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror])
AM_SILENT_RULES([yes])
AM_PROG_AR
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([hal], [HalThreadCreate])
AC_CHECK_LIB([pthread], [pthread_create])

# Checks for header files.
# AC_CHECK_HEADERS (header-file . . ., [action-if-found ], [action-if-not-found ], [includes ])
# AC_CHECK_HEADER  (header-file,       [action-if-found ], [action-if-not-found ], [includes ])
AC_CHECK_HEADERS([stddef.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strdup])

AC_CONFIG_FILES([Makefile
                 example/Makefile
                 include/Makefile
                 src/Makefile])

# AC_ARG_WITH(package, help-string, [action-if-given], [action-if-not-given])
# AC_CACHE_CHECK(message, cache-id, commands-to-set-it)
# AC_TRY_LINK(includes, function-body, [action-if-true], [action-if-false])

trylibtinyalsadir=""
AC_ARG_WITH(
    [libtinyalsa],
    [  --with-libtinyalsa=PATH     Specify path to libtinyalsa installation ],
    [
        if test "x$withval" != "xno" ; then
            trylibtinyalsadir=$withval
        fi
    ]
    )

dnl ------------------------------------------------------
dnl libtinyalsa detection.  swiped from Tor.  modified a bit.

LIBTINYALSA_URL=https://github.com/tinyalsa/tinyalsa/releases

AC_CACHE_CHECK(
    [for libtinyalsa directory],
    [ac_cv_libtinyalsa_dir],
    [saved_LIBS="$LIBS"
     saved_LDFLAGS="$LDFLAGS"
     saved_CPPFLAGS="$CPPFLAGS"
     le_found=no
     for ledir in $trylibtinyalsadir "" $prefix /usr/local ; do
         LDFLAGS="$saved_LDFLAGS"
         LIBS="$saved_LIBS -ltinyalsa"
         # Skip the directory if it isn't there.
         if test ! -z "$ledir" -a ! -d "$ledir" ; then
             continue;
         fi
         if test ! -z "$ledir" ; then
             if test -d "$ledir/lib" ; then
                 LDFLAGS="-L$ledir/lib $LDFLAGS"
             else
                 LDFLAGS="-L$ledir $LDFLAGS"
             fi
             if test -d "$ledir/include" ; then
                 CPPFLAGS="-I$ledir/include $CPPFLAGS"
             else
                 CPPFLAGS="-I$ledir $CPPFLAGS"
             fi
         fi
         # Can I compile and link it?
         AC_TRY_LINK(
            [#include <stdio.h> #include <pcm.h>],
            [pcm_close(NULL);],
            [libtinyalsa_linked=yes],
            [libtinyalsa_linked=no])
         if test $libtinyalsa_linked = yes; then
             if test ! -z "$ledir" ; then
                 ac_cv_libtinyalsa_dir=$ledir
             else
                 ac_cv_libtinyalsa_dir="(system)"
             fi
             le_found=yes
             break
         fi
     done
     LIBS="$saved_LIBS"
     LDFLAGS="$saved_LDFLAGS"
     CPPFLAGS="$saved_CPPFLAGS"
     if test $le_found = no ; then
        AC_MSG_ERROR([libtinyalsa is required. You can get it from $LIBTINYALSA_URL, 
                      If it's already installed, specify its path using --with-libtinyalsa=/dir/])
     fi
    ])

LIBS="$LIBS -ltinyalsa"
if test $ac_cv_libtinyalsa_dir != "(system)"; then
    if test -d "$ac_cv_libtinyalsa_dir/lib" ; then
        LDFLAGS="-L$ac_cv_libtinyalsa_dir/lib $LDFLAGS"
        le_libdir="$ac_cv_libtinyalsa_dir/lib"
    else
        LDFLAGS="-L$ac_cv_libtinyalsa_dir $LDFLAGS"
        le_libdir="$ac_cv_libtinyalsa_dir"
    fi
    if test -d "$ac_cv_libtinyalsa_dir/include" ; then
        CPPFLAGS="-I$ac_cv_libtinyalsa_dir/include $CPPFLAGS"
    else
        CPPFLAGS="-I$ac_cv_libtinyalsa_dir $CPPFLAGS"
    fi
fi

# AC_ARG_ENABLE (feature, help-string, [action-if-given], [action-if-not-given])
AC_ARG_ENABLE([rtt],
    [AS_HELP_STRING([--enable-rtt], [using the hardware abstraction layer for rt-thread] [[default=no]])],
    [AC_DEFINE(HAVE_RTT_HAL, 1, [using the hardware abstraction layer for rt-thread])]
    [])
AM_CONDITIONAL([COMPILE_WITH_RTT_HAL], [test "x$enable_rtt" = "xyes"])

AC_ARG_ENABLE([linux],
    [AS_HELP_STRING([--enable-linux], [using the hardware abstraction layer for linux] [[default=no]])],
    [AC_DEFINE(HAVE_LINUX_HAL, 1, [using the hardware abstraction layer for linux])]
    )
AM_CONDITIONAL([COMPILE_WITH_LINUX_HAL], [test "x$enable_linux" = "xyes"])

AC_OUTPUT

