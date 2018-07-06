SOURCE_DIR:=derived/3rdparty/src

# Information about packages.
# Generated from the data in "build/packages.py".

# libxml2
PACKAGE_XML:=libxml2-2.8.0
TARBALL_XML:=derived/3rdparty/download/libxml2-2.8.0.tar.gz
# Download:
derived/3rdparty/download/libxml2-2.8.0.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://xmlsoft.org/sources/libxml2-2.8.0.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/libxml2-2.8.0.tar.gz.verified: derived/3rdparty/download/libxml2-2.8.0.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/libxml2-2.8.0.tar.gz 4915203 sha256=f2e2d0e322685193d1affec83b21dc05d599e17a7306d7b90de95bb5b9ac622a
	touch derived/3rdparty/download/libxml2-2.8.0.tar.gz.verified
# Extract:
derived/3rdparty/src/libxml2-2.8.0: derived/3rdparty/download/libxml2-2.8.0.tar.gz.verified
	rm -rf derived/3rdparty/src/libxml2-2.8.0
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/libxml2-2.8.0.tar.gz derived/3rdparty/src libxml2-2.8.0
	test ! -e build/3rdparty/libxml2-2.8.0.diff || $(PYTHON) build/patch.py build/3rdparty/libxml2-2.8.0.diff derived/3rdparty/src
	touch derived/3rdparty/src

# Expat
PACKAGE_EXPAT:=expat-2.0.1
TARBALL_EXPAT:=derived/3rdparty/download/expat-2.0.1.tar.gz
# Download:
derived/3rdparty/download/expat-2.0.1.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.sourceforge.net/expat/expat-2.0.1.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/expat-2.0.1.tar.gz.verified: derived/3rdparty/download/expat-2.0.1.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/expat-2.0.1.tar.gz 446456 sha256=847660b4df86e707c9150e33cd8c25bc5cd828f708c7418e765e3e983a2e5e93
	touch derived/3rdparty/download/expat-2.0.1.tar.gz.verified
# Extract:
derived/3rdparty/src/expat-2.0.1: derived/3rdparty/download/expat-2.0.1.tar.gz.verified
	rm -rf derived/3rdparty/src/expat-2.0.1
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/expat-2.0.1.tar.gz derived/3rdparty/src expat-2.0.1
	test ! -e build/3rdparty/expat-2.0.1.diff || $(PYTHON) build/patch.py build/3rdparty/expat-2.0.1.diff derived/3rdparty/src
	touch derived/3rdparty/src

# SQLite
PACKAGE_SQLITE:=sqlite-3.6.16
TARBALL_SQLITE:=derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz
# Download:
derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://www.sqlite.org//sqlite-amalgamation-3.6.16.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz.verified: derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz 1353155 sha256=f576c1be29726c03c079ac466095776b2c5b1ac8f996af1422b251855a0619a9
	touch derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz.verified
# Extract:
derived/3rdparty/src/sqlite-3.6.16: derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz.verified
	rm -rf derived/3rdparty/src/sqlite-3.6.16
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz derived/3rdparty/src sqlite-3.6.16
	test ! -e build/3rdparty/sqlite-3.6.16.diff || $(PYTHON) build/patch.py build/3rdparty/sqlite-3.6.16.diff derived/3rdparty/src
	touch derived/3rdparty/src

# SDL_ttf
PACKAGE_SDL_TTF:=SDL_ttf-2.0.11
TARBALL_SDL_TTF:=derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz
# Download:
derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz.verified: derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz 4053686 sha256=724cd895ecf4da319a3ef164892b72078bd92632a5d812111261cde248ebcdb7
	touch derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz.verified
# Extract:
derived/3rdparty/src/SDL_ttf-2.0.11: derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz.verified
	rm -rf derived/3rdparty/src/SDL_ttf-2.0.11
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz derived/3rdparty/src SDL_ttf-2.0.11
	test ! -e build/3rdparty/SDL_ttf-2.0.11.diff || $(PYTHON) build/patch.py build/3rdparty/SDL_ttf-2.0.11.diff derived/3rdparty/src
	touch derived/3rdparty/src

# zlib
PACKAGE_ZLIB:=zlib-1.2.7
TARBALL_ZLIB:=derived/3rdparty/download/zlib-1.2.7.tar.gz
# Download:
derived/3rdparty/download/zlib-1.2.7.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.sourceforge.net/libpng/zlib-1.2.7.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/zlib-1.2.7.tar.gz.verified: derived/3rdparty/download/zlib-1.2.7.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/zlib-1.2.7.tar.gz 560351 sha256=fa9c9c8638efb8cb8ef5e4dd5453e455751e1c530b1595eed466e1be9b7e26c5
	touch derived/3rdparty/download/zlib-1.2.7.tar.gz.verified
# Extract:
derived/3rdparty/src/zlib-1.2.7: derived/3rdparty/download/zlib-1.2.7.tar.gz.verified
	rm -rf derived/3rdparty/src/zlib-1.2.7
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/zlib-1.2.7.tar.gz derived/3rdparty/src zlib-1.2.7
	test ! -e build/3rdparty/zlib-1.2.7.diff || $(PYTHON) build/patch.py build/3rdparty/zlib-1.2.7.diff derived/3rdparty/src
	touch derived/3rdparty/src

# FreeType
PACKAGE_FREETYPE:=freetype-2.4.10
TARBALL_FREETYPE:=derived/3rdparty/download/freetype-2.4.10.tar.gz
# Download:
derived/3rdparty/download/freetype-2.4.10.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.sourceforge.net/freetype/freetype-2.4.10.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/freetype-2.4.10.tar.gz.verified: derived/3rdparty/download/freetype-2.4.10.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/freetype-2.4.10.tar.gz 2006563 sha256=8a3f73cf0cd95ba91a7e6fbab6f7d2787424b387e8f09dfc915db12465a6d648
	touch derived/3rdparty/download/freetype-2.4.10.tar.gz.verified
# Extract:
derived/3rdparty/src/freetype-2.4.10: derived/3rdparty/download/freetype-2.4.10.tar.gz.verified
	rm -rf derived/3rdparty/src/freetype-2.4.10
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/freetype-2.4.10.tar.gz derived/3rdparty/src freetype-2.4.10
	test ! -e build/3rdparty/freetype-2.4.10.diff || $(PYTHON) build/patch.py build/3rdparty/freetype-2.4.10.diff derived/3rdparty/src
	touch derived/3rdparty/src

# libao
PACKAGE_AO:=libao-1.1.0
TARBALL_AO:=derived/3rdparty/download/libao-1.1.0.tar.gz
# Download:
derived/3rdparty/download/libao-1.1.0.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.xiph.org/releases/ao/libao-1.1.0.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/libao-1.1.0.tar.gz.verified: derived/3rdparty/download/libao-1.1.0.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/libao-1.1.0.tar.gz 397102 sha256=29de5bb9b1726ba890455ef7e562d877df87811febb0d99ee69164b88c171bd4
	touch derived/3rdparty/download/libao-1.1.0.tar.gz.verified
# Extract:
derived/3rdparty/src/libao-1.1.0: derived/3rdparty/download/libao-1.1.0.tar.gz.verified
	rm -rf derived/3rdparty/src/libao-1.1.0
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/libao-1.1.0.tar.gz derived/3rdparty/src libao-1.1.0
	test ! -e build/3rdparty/libao-1.1.0.diff || $(PYTHON) build/patch.py build/3rdparty/libao-1.1.0.diff derived/3rdparty/src
	touch derived/3rdparty/src

# libvorbis
PACKAGE_VORBIS:=libvorbis-1.3.3
TARBALL_VORBIS:=derived/3rdparty/download/libvorbis-1.3.3.tar.gz
# Download:
derived/3rdparty/download/libvorbis-1.3.3.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.3.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/libvorbis-1.3.3.tar.gz.verified: derived/3rdparty/download/libvorbis-1.3.3.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/libvorbis-1.3.3.tar.gz 1592663 sha256=6d747efe7ac4ad249bf711527882cef79fb61d9194c45b5ca5498aa60f290762
	touch derived/3rdparty/download/libvorbis-1.3.3.tar.gz.verified
# Extract:
derived/3rdparty/src/libvorbis-1.3.3: derived/3rdparty/download/libvorbis-1.3.3.tar.gz.verified
	rm -rf derived/3rdparty/src/libvorbis-1.3.3
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/libvorbis-1.3.3.tar.gz derived/3rdparty/src libvorbis-1.3.3
	test ! -e build/3rdparty/libvorbis-1.3.3.diff || $(PYTHON) build/patch.py build/3rdparty/libvorbis-1.3.3.diff derived/3rdparty/src
	touch derived/3rdparty/src

# Tcl
PACKAGE_TCL:=tcl8.5.11
TARBALL_TCL:=derived/3rdparty/download/tcl8.5.11-src.tar.gz
# Download:
derived/3rdparty/download/tcl8.5.11-src.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.sourceforge.net/tcl/tcl8.5.11-src.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/tcl8.5.11-src.tar.gz.verified: derived/3rdparty/download/tcl8.5.11-src.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/tcl8.5.11-src.tar.gz 4484001 sha256=8addc385fa6b5be4605e6d68fbdc4c0e674c5af1dc1c95ec5420390c4b08042a
	touch derived/3rdparty/download/tcl8.5.11-src.tar.gz.verified
# Extract:
derived/3rdparty/src/tcl8.5.11: derived/3rdparty/download/tcl8.5.11-src.tar.gz.verified
	rm -rf derived/3rdparty/src/tcl8.5.11
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/tcl8.5.11-src.tar.gz derived/3rdparty/src tcl8.5.11
	test ! -e build/3rdparty/tcl8.5.11.diff || $(PYTHON) build/patch.py build/3rdparty/tcl8.5.11.diff derived/3rdparty/src
	touch derived/3rdparty/src

# DirectX
PACKAGE_DIRECTX:=dx70
TARBALL_DIRECTX:=derived/3rdparty/download/dx70_mgw.tar.gz
# Download:
derived/3rdparty/download/dx70_mgw.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://alleg.sourceforge.net/files/dx70_mgw.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/dx70_mgw.tar.gz.verified: derived/3rdparty/download/dx70_mgw.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/dx70_mgw.tar.gz 236675 sha256=59f489a7d9f51c70fe37fbb5a6225d4716a97ab774c58138f1dc4661a80356f0
	touch derived/3rdparty/download/dx70_mgw.tar.gz.verified
# Extract:
derived/3rdparty/src/dx70: derived/3rdparty/download/dx70_mgw.tar.gz.verified
	rm -rf derived/3rdparty/src/dx70
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/dx70_mgw.tar.gz derived/3rdparty/src dx70
	test ! -e build/3rdparty/dx70.diff || $(PYTHON) build/patch.py build/3rdparty/dx70.diff derived/3rdparty/src
	touch derived/3rdparty/src

# SDL
PACKAGE_SDL:=SDL-1.2.15
TARBALL_SDL:=derived/3rdparty/download/SDL-1.2.15.tar.gz
# Download:
derived/3rdparty/download/SDL-1.2.15.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://www.libsdl.org/release/SDL-1.2.15.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/SDL-1.2.15.tar.gz.verified: derived/3rdparty/download/SDL-1.2.15.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/SDL-1.2.15.tar.gz 3920622 sha256=d6d316a793e5e348155f0dd93b979798933fb98aa1edebcc108829d6474aad00
	touch derived/3rdparty/download/SDL-1.2.15.tar.gz.verified
# Extract:
derived/3rdparty/src/SDL-1.2.15: derived/3rdparty/download/SDL-1.2.15.tar.gz.verified
	rm -rf derived/3rdparty/src/SDL-1.2.15
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/SDL-1.2.15.tar.gz derived/3rdparty/src SDL-1.2.15
	test ! -e build/3rdparty/SDL-1.2.15.diff || $(PYTHON) build/patch.py build/3rdparty/SDL-1.2.15.diff derived/3rdparty/src
	touch derived/3rdparty/src

# GLEW
PACKAGE_GLEW:=glew-1.7.0
TARBALL_GLEW:=derived/3rdparty/download/glew-1.7.0.tgz
# Download:
derived/3rdparty/download/glew-1.7.0.tgz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.sourceforge.net/glew/glew-1.7.0.tgz derived/3rdparty/download
# Verify:
derived/3rdparty/download/glew-1.7.0.tgz.verified: derived/3rdparty/download/glew-1.7.0.tgz
	$(PYTHON) build/checksum.py derived/3rdparty/download/glew-1.7.0.tgz 512582 sha256=1653a63fb1e1a518c4b5ccbaf1a617f1a0b4c1c29d39ae4e2583844d98365c09
	touch derived/3rdparty/download/glew-1.7.0.tgz.verified
# Extract:
derived/3rdparty/src/glew-1.7.0: derived/3rdparty/download/glew-1.7.0.tgz.verified
	rm -rf derived/3rdparty/src/glew-1.7.0
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/glew-1.7.0.tgz derived/3rdparty/src glew-1.7.0
	test ! -e build/3rdparty/glew-1.7.0.diff || $(PYTHON) build/patch.py build/3rdparty/glew-1.7.0.diff derived/3rdparty/src
	touch derived/3rdparty/src

# libogg
PACKAGE_OGG:=libogg-1.3.0
TARBALL_OGG:=derived/3rdparty/download/libogg-1.3.0.tar.gz
# Download:
derived/3rdparty/download/libogg-1.3.0.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.xiph.org/releases/ogg/libogg-1.3.0.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/libogg-1.3.0.tar.gz.verified: derived/3rdparty/download/libogg-1.3.0.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/libogg-1.3.0.tar.gz 425144 sha256=a8de807631014615549d2356fd36641833b8288221cea214f8a72750efe93780
	touch derived/3rdparty/download/libogg-1.3.0.tar.gz.verified
# Extract:
derived/3rdparty/src/libogg-1.3.0: derived/3rdparty/download/libogg-1.3.0.tar.gz.verified
	rm -rf derived/3rdparty/src/libogg-1.3.0
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/libogg-1.3.0.tar.gz derived/3rdparty/src libogg-1.3.0
	test ! -e build/3rdparty/libogg-1.3.0.diff || $(PYTHON) build/patch.py build/3rdparty/libogg-1.3.0.diff derived/3rdparty/src
	touch derived/3rdparty/src

# libtheora
PACKAGE_THEORA:=libtheora-1.1.1
TARBALL_THEORA:=derived/3rdparty/download/libtheora-1.1.1.tar.gz
# Download:
derived/3rdparty/download/libtheora-1.1.1.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.xiph.org/releases/theora/libtheora-1.1.1.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/libtheora-1.1.1.tar.gz.verified: derived/3rdparty/download/libtheora-1.1.1.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/libtheora-1.1.1.tar.gz 2111877 sha256=40952956c47811928d1e7922cda3bc1f427eb75680c3c37249c91e949054916b
	touch derived/3rdparty/download/libtheora-1.1.1.tar.gz.verified
# Extract:
derived/3rdparty/src/libtheora-1.1.1: derived/3rdparty/download/libtheora-1.1.1.tar.gz.verified
	rm -rf derived/3rdparty/src/libtheora-1.1.1
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/libtheora-1.1.1.tar.gz derived/3rdparty/src libtheora-1.1.1
	test ! -e build/3rdparty/libtheora-1.1.1.diff || $(PYTHON) build/patch.py build/3rdparty/libtheora-1.1.1.diff derived/3rdparty/src
	touch derived/3rdparty/src

# libpng
PACKAGE_PNG:=libpng-1.2.50
TARBALL_PNG:=derived/3rdparty/download/libpng-1.2.50.tar.gz
# Download:
derived/3rdparty/download/libpng-1.2.50.tar.gz:
	mkdir -p derived/3rdparty/download
	$(PYTHON) build/download.py http://downloads.sourceforge.net/libpng/libpng-1.2.50.tar.gz derived/3rdparty/download
# Verify:
derived/3rdparty/download/libpng-1.2.50.tar.gz.verified: derived/3rdparty/download/libpng-1.2.50.tar.gz
	$(PYTHON) build/checksum.py derived/3rdparty/download/libpng-1.2.50.tar.gz 826893 sha256=19f17cd49782fcec8df0f7d1b348448cc3f69ed7e2a59de24bc0907b907f1abc
	touch derived/3rdparty/download/libpng-1.2.50.tar.gz.verified
# Extract:
derived/3rdparty/src/libpng-1.2.50: derived/3rdparty/download/libpng-1.2.50.tar.gz.verified
	rm -rf derived/3rdparty/src/libpng-1.2.50
	mkdir -p derived/3rdparty/src
	$(PYTHON) build/extract.py derived/3rdparty/download/libpng-1.2.50.tar.gz derived/3rdparty/src libpng-1.2.50
	test ! -e build/3rdparty/libpng-1.2.50.diff || $(PYTHON) build/patch.py build/3rdparty/libpng-1.2.50.diff derived/3rdparty/src
	touch derived/3rdparty/src

# Convenience target to download all source packages.
.PHONY: download
download: derived/3rdparty/download/libxml2-2.8.0.tar.gz derived/3rdparty/download/expat-2.0.1.tar.gz derived/3rdparty/download/sqlite-amalgamation-3.6.16.tar.gz derived/3rdparty/download/SDL_ttf-2.0.11.tar.gz derived/3rdparty/download/zlib-1.2.7.tar.gz derived/3rdparty/download/freetype-2.4.10.tar.gz derived/3rdparty/download/libao-1.1.0.tar.gz derived/3rdparty/download/libvorbis-1.3.3.tar.gz derived/3rdparty/download/tcl8.5.11-src.tar.gz derived/3rdparty/download/dx70_mgw.tar.gz derived/3rdparty/download/SDL-1.2.15.tar.gz derived/3rdparty/download/glew-1.7.0.tgz derived/3rdparty/download/libogg-1.3.0.tar.gz derived/3rdparty/download/libtheora-1.1.1.tar.gz derived/3rdparty/download/libpng-1.2.50.tar.gz
