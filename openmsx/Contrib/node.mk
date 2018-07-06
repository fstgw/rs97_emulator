# $Id: node.mk 8414 2008-12-22 19:07:57Z m9710797 $

include build/node-start.mk

DIST:= \
	README \
	README.cbios cbios \
	README.openmsx-control \
	openmsx-control-stdio.cc openmsx-control-socket.cc \
	basictorom.tcl

include build/node-end.mk

