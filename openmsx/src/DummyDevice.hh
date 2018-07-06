// $Id: DummyDevice.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef DUMMYDEVICE_HH
#define DUMMYDEVICE_HH

#include "MSXDevice.hh"

namespace openmsx {

class DummyDevice : public MSXDevice
{
public:
	explicit DummyDevice(const DeviceConfig& config);
	virtual void reset(EmuTime::param time);
};

} // namespace openmsx

#endif
