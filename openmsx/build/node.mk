# $Id: node.mk 11475 2010-06-03 21:02:23Z manuelbi $

include build/node-start.mk

SUBDIRS:= \
	3rdparty package-darwin package-slackware msvc package-arch \
	package-dingux package-windows

DIST:= \
	main.mk node-end.mk node-start.mk entry.mk entry-seq.mk \
	custom.mk 3rdparty.mk \
	flavour-*.mk platform-*.mk \
	*.py python-search.sh

include build/node-end.mk
