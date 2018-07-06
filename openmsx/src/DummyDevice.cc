// $Id: DummyDevice.cc 12527 2012-05-17 17:34:11Z m9710797 $

#include "DummyDevice.hh"
#include "unreachable.hh"

namespace openmsx {

DummyDevice::DummyDevice(const DeviceConfig& config)
	: MSXDevice(config)
{
}

void DummyDevice::reset(EmuTime::param /*time*/)
{
	UNREACHABLE;
}

} // namespace openmsx
