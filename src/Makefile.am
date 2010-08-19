AM_CFLAGS = -Wall

ACLOCAL_AMFLAGS = -I m4

WP_LIBS = libwpbase.la libwpstdc.la libwpunix.la libwpsocket.la libwppthread.la

lib_LTLIBRARIES = $(WP_LIBS)

libwpbase_la_SOURCES = libwpbase.c libwpbase.h
libwpstdc_la_SOURCES = libwpstdc.c libwpstdc.h
libwpunix_la_SOURCES = libwpunix.c libwpunix.h
libwpsocket_la_SOURCES = libwpsocket.c libwpsocket.h
libwppthread_la_SOURCES = libwppthread.c libwppthread.h

include_HEADERS = libwp.h libwpbase.h libwppthread.h libwpsocket.h libwpstdc.h libwpunix.h
