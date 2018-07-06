# $Id: flavour-ppcg4.mk 9258 2009-02-26 00:44:53Z mthuurne $
#
# Configuration for "ppc" flavour:
# Optimised for PPC-G4 and higher.

# Start with generic optimisation flags.
include build/flavour-opt.mk

# Add PPC specific flags.
CXXFLAGS+=-mcpu=G4 -mtune=G4 -mpowerpc-gfxopt -maltivec -mabi=altivec
