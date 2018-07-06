# $Id: node.mk 11279 2010-02-18 19:51:35Z seanyoung $

include build/node-start.mk

SRC_HDR_$(COMPONENT_LASERDISC):= \
	OggReader LaserdiscPlayerCLI \
	LaserdiscPlayer PioneerLDControl yuv2rgb

HDR_ONLY:= 

include build/node-end.mk

