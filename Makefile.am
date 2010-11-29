ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

EXTRA_DIST = libwp.spec.in build-aux/config.rpath

rpm: dist
	mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
	cp @PACKAGE@-@VERSION@.tar.gz ~/rpmbuild/SOURCES/
	rpmbuild -ba libwp.spec
	rm -rf ~/rpmbuild/SOURCES/@PACKAGE@-@VERSION@.tar.gz
	rm -rf ~/rpmbuild/BUILD/@PACKAGE@-@VERSION@
	mv `find ~/rpmbuild/ -name "@PACKAGE@-*@VERSION@-@RELEASE@.*.rpm"` .

clean-local:
	rm -rf *.rpm
