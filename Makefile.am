ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libwp-@PKG_VERSION@.pc wppthread-@PKG_VERSION@.pc

EXTRA_DIST = libwp-@PKG_VERSION@.spec.in libwp-@PKG_VERSION@.pc.in wppthread-@PKG_VERSION@.pc.in

rpm: dist-bzip2
	mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
	cp @PACKAGE@-@VERSION@.tar.bz2 ~/rpmbuild/SOURCES/
	rpmbuild -ba libwp.spec
	rm -rf ~/rpmbuild/SOURCES/@PACKAGE@-@VERSION@.tar.bz2
	rm -rf ~/rpmbuild/BUILD/@PACKAGE@-@VERSION@
	mv `find ~/rpmbuild/ -name "@PACKAGE@-*@VERSION@-@RELEASE@.*.rpm"` .

clean-local:
	rm -rf *.rpm
