AM_CFLAGS = -Wall

ACLOCAL_AMFLAGS = -I m4

libwpdir = ${libdir}
libwp_LTLIBRARIES = libwp.la \
				  libwppthread.la

libwp_la_SOURCES = wpbase.c \
				   wpsocket.c \
				   wpsocket_interface.c \
				   wpstdc.c \
				   libwp.h \
				   wpbase.h \
				   wpsocket.h \
				   wpstdc.h \
				   wpunix.c \
				   wpunix.h \
				   wpunix_rio.c \
				   _wpbintree.c \
				   wpbintree.c \
				   _wpbintree.h \
				   wpbintree.h \
				   wplist.c \
				   wplist.h \
				   wplistnode.c \
				   wplistnode.h \
				   wpqueue.c \
				   wpqueue.h \
				   wprbtree.c \
				   wprbtree.h \
				   wpstack.c \
				   wpstack.h \
				   wptreenode.c \
				   wptreenode.h \
				   wphash.c \
				   wphash.h \
				   wpmacros.h \
				   wptypes.h
libwp_la_LDFLAGS = -version-info `echo $(VERSION) | tr . :`
libwppthread_la_SOURCES = wppthread.c wppthread.h
libwppthread_la_LDFLAGS = -version-info `echo $(VERSION) | tr . :`

libwp_includedir=$(includedir)/@PACKAGE@
libwp_include_HEADERS = libwp.h \
				  wpbase.h \
				  wppthread.h \
				  wpsocket.h \
				  wpstdc.h \
				  wpunix.h \
				  wpds.h \
				  _wpbintree.h \
				  wpbintree.h \
				  wplist.h \
				  wplistnode.h \
				  wpqueue.h \
				  wprbtree.h \
				  wpstack.h \
				  wptreenode.h \
				  wphash.h \
				  wpmacros.h \
				  wptypes.h
