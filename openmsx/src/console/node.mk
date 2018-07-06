# $Id: node.mk 8490 2009-01-21 18:13:53Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	CommandConsole \
	OSDConsoleRenderer \
	OSDGUILayer OSDGUI \
	OSDWidget OSDImageBasedWidget \
	OSDTopWidget OSDRectangle OSDText \
	TTFFont

include build/node-end.mk

