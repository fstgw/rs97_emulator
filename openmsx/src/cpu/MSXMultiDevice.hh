// $Id: MSXMultiDevice.hh 12528 2012-05-17 17:36:10Z m9710797 $

#ifndef MSXMULTIDEVICE_HH
#define MSXMULTIDEVICE_HH

#include "MSXDevice.hh"

namespace openmsx {

class MSXMultiDevice : public MSXDevice
{
public:
	explicit MSXMultiDevice(const HardwareConfig& hwConf);

	virtual void reset(EmuTime::param time);
	virtual void powerUp(EmuTime::param time);
	virtual void powerDown(EmuTime::param time);
};

} // namespace openmsx

#endif
