#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(rlp, 1.1, rcgoncalves.pt@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/rlpy.y])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CC
AC_PROG_LEX

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
