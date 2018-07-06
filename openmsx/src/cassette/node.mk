# $Id: node.mk 11231 2010-02-03 17:51:48Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	CassetteDevice \
	CassettePlayer \
	CassettePlayerCLI \
	CassettePort \
	DummyCassetteDevice \
	CassetteImage \
	CasImage \
	WavImage

include build/node-end.mk

