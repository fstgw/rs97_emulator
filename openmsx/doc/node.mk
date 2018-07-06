# $Id: node.mk 11482 2010-06-05 09:02:06Z manuelbi $

include build/node-start.mk

SUBDIRS:=manual

# Not all of the docs are useful for end users, either because they are about
# the implementation, or because they are too rough/unfinished.
# Below is the list of docs that should be included in installation.
INSTALL_DOCS:= \
	authors.txt GPL.txt \
	release-notes.txt release-history.txt

DIST:=$(INSTALL_DOCS) \
	msxinfo-article.html schema1.png schema2.png \
	screenshot.png openmsx.sgml vram-addressing.txt \
	r800test.txt exsphl.txt dingux-readme.txt

include build/node-end.mk
