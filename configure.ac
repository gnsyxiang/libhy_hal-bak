#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
m4_include([m4/version.m4])

AC_INIT([libhal], [VERSION_NUM], [gnsyxiang@163.com])
AC_CONFIG_SRCDIR([src/demo.c])
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

AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_SILENT_RULES([yes])

AC_ARG_ENABLE(myprint,
              AS_HELP_STRING([--enable-myprint], [enable my print]),
              AC_DEFINE(HAVE_MY_PRINT, 1, [enables my print])
              )
AM_CONDITIONAL([COMPILE_WITH_MY_PRINT], [test "x$enable_myprint" = "xyes"])

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S

AM_PROG_AR
LT_INIT

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 example/Makefile
                 include/Makefile
                 src/Makefile])
AC_OUTPUT
