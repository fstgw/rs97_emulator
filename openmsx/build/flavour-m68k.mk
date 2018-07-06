# $Id: flavour-m68k.mk 5596 2006-09-02 06:57:35Z andete $
#
# ARM specific optimization flags

# Optimisation flags:

# overrule optimization level for m68k
# TODO: is this still strictly needed?
CXXFLAGS+=-O1 -DNDEBUG


# Strip executable?
OPENMSX_STRIP:=true
