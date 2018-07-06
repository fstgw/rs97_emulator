// $Id: DummyIDEDevice.hh 8352 2008-11-12 18:39:08Z m9710797 $

#ifndef DUMMYIDEDEVICE_HH
#define DUMMYIDEDEVICE_HH

#include "IDEDevice.hh"
#include "serialize_meta.hh"

namespace openmsx {

class DummyIDEDevice : public IDEDevice
{
public:
	virtual void reset(EmuTime::param time);
	virtual word readData(EmuTime::param time);
	virtual byte readReg(nibble reg, EmuTime::param time);
	virtual void writeData(word value, EmuTime::param time);
	virtual void writeReg(nibble reg, byte value, EmuTime::param time);

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);
};

} // namespace openmsx

#endif
