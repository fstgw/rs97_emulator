# $Id: node.mk 12528 2012-05-17 17:36:10Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	XMLLoader XMLElement \
	HardwareConfig \
	SettingsConfig \
	DeviceConfig \

HDR_ONLY:= \
	ConfigException \
	XMLException \

include build/node-end.mk

