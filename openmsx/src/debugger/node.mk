# $Id: node.mk 8182 2008-08-28 18:05:52Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	Debugger \
	DasmTables \
	SimpleDebuggable \
	Probe ProbeBreakPoint

HDR_ONLY:= \
	Debuggable

include build/node-end.mk

