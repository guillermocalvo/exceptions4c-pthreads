#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


# Autoconf requirements
AC_PREREQ([2.68])


# Initialize package
AC_INIT([exceptions4c-pthreads], [0.1.0], [exceptions4c-pthreads@guillermo.dev], [exceptions4c-pthreads], [https://github.com/guillermocalvo/exceptions4c-pthreads/])


# Information on the package
AC_COPYRIGHT([Copyright 2025 Guillermo Calvo])
AC_REVISION([$PACKAGE_VERSION])
AC_MSG_NOTICE([
                         _   _                 _  _
  _____  _____ ___ _ __ | |_(_) ___  _ __  ___| || |   ___
 / _ \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \/ __| || |_ / __|
|  __/>  < (_|  __/ |_) | |_| | (_) | | | \__ \__   _| (__
 \___/_/\_\___\___| .__/ \__|_|\___/|_| |_|___/  |_|  \___|
                  |_| Multithreading exception handling for C
])


# Check if the source folder is correct
AC_CONFIG_SRCDIR([src/exceptions4c-pthreads.h])


# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_RANLIB
AM_PROG_AR


# Checks for header files.
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([setjmp.h])
AC_CHECK_HEADERS([errno.h])


# Checks for types
AC_TYPE_SIZE_T
AC_CHECK_TYPES(jmp_buf)
AC_CHECK_TYPES(sigjmp_buf)


# Checks for compiler characteristics
AC_LANG([C])


# Checks for library functions.
AC_CHECK_FUNCS([abort])
AC_CHECK_FUNCS([calloc])
AC_CHECK_FUNCS([fflush])
AC_CHECK_FUNCS([fprintf])
AC_CHECK_FUNCS([free])


AC_CHECK_HEADERS([pthread.h], [
    AC_CHECK_LIB(pthread, pthread_create, [
    LIBS="$LIBS -pthread"
    AC_DEFINE(HAVE_LIBPTHREAD, 1, 
         [Define to 1 if you have the 'pthread' library (-pthread).])
    ], 
    AC_MSG_ERROR(Missing required pthread library))
], AC_MSG_ERROR(Missing required pthread header))


# The config file is generated but not used by the source code
#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    exceptions4c-pthreads.pc
    Makefile
])


# Automake initialisation
AM_INIT_AUTOMAKE([
    -Wall
    -Werror
    foreign
    subdir-objects
    no-define
])


AC_OUTPUT
