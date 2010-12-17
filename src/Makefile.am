AM_CFLAGS = -Wall

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libwp.la libwppthread.la

libwp_la_SOURCES = wpbase.c wpsocket.c wpstdc.c wpunix.c wpunix_rio.c libwp.h wpbase.h wpsocket.h wpstdc.h wpunix.h
libwp_la_LDFLAGS = -version-info @LT_VERSION@
libwppthread_la_SOURCES = wppthread.c wppthread.h
libwppthread_la_LDFLAGS = -version-info @LT_VERSION@

include_HEADERS = libwp.h wpbase.h wppthread.h wpsocket.h wpstdc.h wpunix.h
