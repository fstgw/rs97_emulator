// $Id: IDEDevice.hh 8352 2008-11-12 18:39:08Z m9710797 $

#ifndef IDEDEVICE_HH
#define IDEDEVICE_HH

#include "EmuTime.hh"
#include "openmsx.hh"

namespace openmsx {

class IDEDevice
{
public:
	virtual ~IDEDevice() {}
	virtual void reset(EmuTime::param time) = 0;

	virtual word readData(EmuTime::param time) = 0;
	virtual byte readReg(nibble reg, EmuTime::param time) = 0;

	virtual void writeData(word value, EmuTime::param time) = 0;
	virtual void writeReg(nibble reg, byte value, EmuTime::param time) = 0;
};

} // namespace openmsx

#endif
