# $Id: node.mk 11476 2010-06-03 22:26:28Z mthuurne $

include build/node-start.mk

SUBDIRS:= \
	images

DIST:= \
	controlpanel.wxi openmsx.wxs openmsx1033.wxl *.py \
	package.cmd vc_menu.cmd

include build/node-end.mk
