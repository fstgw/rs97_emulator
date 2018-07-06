# $Id: node.mk 12705 2012-07-10 19:06:58Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	CommandException \
	GlobalCommandController \
	MSXCommandController \
	ProxyCommand \
	Completer \
	Command \
	InfoCommand \
	InfoTopic \
	Interpreter \
	TclObject \
	TclParser \
	TclCallback \

HDR_ONLY:= \
	InterpreterOutput \
	CommandController

include build/node-end.mk

