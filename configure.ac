#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([libwp-0_0],[0.1.0],[4179e1@gmail.com])
AC_CONFIG_SRCDIR([src/wpbase.c])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_USE_SYSTEM_EXTENSIONS
AM_INIT_AUTOMAKE([gnu -Wall -Werror])
LT_INIT

PKG_VERSION="0.0"
AC_SUBST(PKG_VERSION)

RELEASE="1.1"
AC_SUBST(RELEASE)

# Checks for programs.
AC_LANG([C])
AC_C_INLINE
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h limits.h netdb.h shadow.h stdlib.h string.h sys/ioctl.h sys/socket.h sys/time.h syslog.h unistd.h utime.h attr/xattr.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_UID_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_FORK
AC_FUNC_FSEEKO
AC_FUNC_GETGROUPS
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([atexit dup2 fchdir fdatasync ftruncate getcwd gethostname getspnam gettimeofday lchown mkdir mkfifo munmap pathconf putenv rmdir setenv socket strchr strerror uname utime gethostbyaddr gethostbyname memset select])

AC_CONFIG_FILES([$PACKAGE.spec libwp-$PKG_VERSION.pc wppthread-$PKG_VERSION.pc Makefile src/Makefile])
AC_OUTPUT
