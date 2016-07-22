ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = @PACKAGE@.pc @WPPTHREAD@.pc
EXTRA_DIST = @PACKAGE@.spec.in @PACKAGE@.pc.in @WPPTHREAD@.pc.in

rpm: dist-bzip2
	mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
	cp @PACKAGE@-@VERSION@.tar.bz2 ~/rpmbuild/SOURCES/
	rpmbuild -ba @PACKAGE@.spec
	rm -rf ~/rpmbuild/SOURCES/@PACKAGE@-@VERSION@.tar.bz2
	rm -rf ~/rpmbuild/BUILD/@PACKAGE@-@VERSION@
	mv `find ~/rpmbuild/ -name "@PACKAGE@-*@VERSION@-@RELEASE@.*.rpm"` .

clean-local:
	rm -rf *.rpm *.bz2 @PACKAGE@.spec @PACKAGE@.pc @WPPTHREAD@.pc 
