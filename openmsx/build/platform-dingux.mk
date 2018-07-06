# $Id: platform-dingux.mk 12274 2011-09-17 22:45:28Z mthuurne $
#
# Configuration for Dingux: Linux for Dingoo A320.

# Set CXX before including platform-linux.mk (see comments in platform-linux.mk)
ifeq ($(OPENMSX_TARGET_CPU),mipsel)
# Automatically select the cross compiler from its default location.
ifeq ($(origin CXX),default)
CXX:=/home/steward/Downloads/buildroot-2017.02.9/output/host/usr/bin/mipsel-linux-g++
endif
# Use MIPS32 instruction set.
TARGET_FLAGS+=-march=mips32
endif

# Dingux is a Linux/uClibc system.
include build/platform-linux.mk

# Allow GMenu to identify our binary as an executable.
# Since the file system is FAT this cannot be done with a permission flag.
EXEEXT:=.dge

# Build a minimal set of components.
LINK_MODE:=3RD_STA_MIN

