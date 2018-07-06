#!/bin/sh
# $Id: openmsx-start.sh 12279 2011-09-19 15:41:57Z mthuurne $
# Startup script for openMSX.
# Run this to start openMSX; running the executable directly does not work.
export OPENMSX_SYSTEM_DATA=/usr/local/share/openmsx
exec /usr/local/bin/openmsx.dge
#exec /usr/local/bin/openmsx.dge &> /tmp/openmsx-log.txt
