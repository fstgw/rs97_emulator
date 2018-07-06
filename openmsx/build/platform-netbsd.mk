# $Id: platform-netbsd.mk 9973 2009-06-01 22:36:12Z mthuurne $
#
# Configuration for NetBSD.

# Does platform support symlinks?
USE_SYMLINK:=true

# File name extension of executables.
EXEEXT:=

COMPILE_FLAGS+=-D_REENTRANT -D_THREAD_SAFE
