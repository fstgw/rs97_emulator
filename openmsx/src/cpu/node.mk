# $Id: node.mk 9390 2009-03-18 18:12:42Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	CPU CPUCore CPUClock Dasm \
	BreakPointBase BreakPoint WatchPoint DebugCondition \
	MSXCPUInterface MSXCPU \
	MSXMultiDevice MSXMultiIODevice MSXMultiMemDevice \
	MSXWatchIODevice \
	VDPIODelay \
	IRQHelper

HDR_ONLY:= \
	Z80 R800 \
	CacheLine

include build/node-end.mk

