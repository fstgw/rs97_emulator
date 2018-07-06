# $Id: node.mk 6573 2007-06-01 22:09:47Z manuelbi $

include build/node-start.mk

SRC_HDR:= \
	HD HDCommand \
	SunriseIDE \
	DummyIDEDevice \
	IDEDeviceFactory \
	AbstractIDEDevice IDEHD IDECDROM \
	HDImageCLI CDImageCLI \
	DummySCSIDevice SCSIHD SCSILS120 \
	WD33C93 GoudaSCSI \
	MB89352 MegaSCSI

HDR_ONLY:= \
	IDEDevice \
	SCSI SCSIDevice

include build/node-end.mk

