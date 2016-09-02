# canonicalize.m4 serial 2 (gettext-0.13)
dnl Copyright (C) 2003 Free Software Foundation, Inc.
dnl This file is free software, distributed under the terms of the GNU
dnl General Public License.  As a special exception to the GNU General
dnl Public License, this file may be distributed as part of a program
dnl that contains a configuration script generated by Autoconf, under
dnl the same distribution terms as the rest of that program.

AC_DEFUN([gl_CANONICALIZE],
[
  dnl Do this replacement check manually because the file name is shorter
  dnl than the function name.
  AC_CHECK_FUNCS(canonicalize_file_name)
  if test $ac_cv_func_canonicalize_file_name = no; then
    AC_LIBOBJ(canonicalize)
    AC_DEFINE([realpath], [rpl_realpath],
      [Define to a replacement function name for realpath().])
    gl_PREREQ_CANONICALIZE
  fi
])

# Prerequisites of lib/canonicalize.c.
AC_DEFUN([gl_PREREQ_CANONICALIZE],
[
  AC_CHECK_HEADERS_ONCE(sys/param.h unistd.h)
  AC_CHECK_FUNCS(getcwd readlink)
])
