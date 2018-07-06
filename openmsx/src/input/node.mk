# $Id: node.mk 12332 2011-12-29 17:02:37Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	Keyboard \
	KeyboardSettings \
	UnicodeKeymap \
	JoystickPort \
	JoystickDevice \
	DummyJoystick \
	Joystick JoyMega \
	KeyJoystick \
	SETetrisDongle \
	MagicKey \
	Mouse \
	Trackball \
	JoyTap \
	NinjaTap \
	ArkanoidPad \
	EventDelay \
	MSXEventDistributor \
	StateChangeDistributor \
	RecordedCommand

HDR_ONLY:= \
	MSXEventListener \
	StateChangeListener \
	StateChange

include build/node-end.mk

