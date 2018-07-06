# $Id: node.mk 11871 2011-01-04 20:23:54Z mthuurne $

include build/node-start.mk

SUBDIRS:= \
	src build doc Contrib

DIST:= \
	GNUmakefile configure \
	README \
	share

include build/node-end.mk
