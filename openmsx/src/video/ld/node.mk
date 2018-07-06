# $Id: node.mk 11474 2010-06-02 22:25:53Z manuelbi $

include build/node-start.mk

SRC_HDR_$(COMPONENT_LASERDISC)+= \
	LDSDLRasterizer \
	LDPixelRenderer LDRenderer LDDummyRenderer

HDR_ONLY:= LDRasterizer

include build/node-end.mk
