AC_INIT(bigint, 1.0, growlot)
AM_INIT_AUTOMAKE

### Generate config.h file
AC_CONFIG_HEADER([config.h])

AC_PROG_CXX
AC_PROG_MAKE_SET

### Our specific checks
# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor gettimeofday pow sqrt])

### Generates files that are required for building our package
AC_OUTPUT(Makefile src/Makefile)

