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

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AM_PROG_AR
LT_INIT

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_ARG_ENABLE(rtt,
              AS_HELP_STRING([--enable-rtt], [using the hardware abstraction layer for rt-thread] [[default=no]]),
              AC_DEFINE(HAVE_RTT_HAL, 1, [using the hardware abstraction layer for rt-thread])
              )
AM_CONDITIONAL([COMPILE_WITH_RTT_HAL], [test "x$enable_rtt" = "xyes"])

AC_ARG_ENABLE(linux,
              AS_HELP_STRING([--enable-linux], [using the hardware abstraction layer for linux] [[default=no]]),
              AC_DEFINE(HAVE_LINUX_HAL, 1, [using the hardware abstraction layer for linux])
              )
AM_CONDITIONAL([COMPILE_WITH_LINUX_HAL], [test "x$enable_linux" = "xyes"])

AC_CONFIG_FILES([Makefile
                 example/Makefile
                 include/Makefile
                 src/Makefile
                 ])
AC_OUTPUT
