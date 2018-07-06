// $Id: MSXMultiDevice.cc 12528 2012-05-17 17:36:10Z m9710797 $

#include "MSXMultiDevice.hh"
#include "DeviceConfig.hh"
#include "XMLElement.hh"
#include "unreachable.hh"

namespace openmsx {

static DeviceConfig getMultiConfig(const HardwareConfig& hwConf)
{
	static XMLElement xml("Multi");
	return DeviceConfig(hwConf, xml);
}

MSXMultiDevice::MSXMultiDevice(const HardwareConfig& hwConf)
	: MSXDevice(getMultiConfig(hwConf), "Multi")
{
}

void MSXMultiDevice::reset(EmuTime::param /*time*/)
{
	UNREACHABLE;
}

void MSXMultiDevice::powerUp(EmuTime::param /*time*/)
{
	UNREACHABLE;
}

void MSXMultiDevice::powerDown(EmuTime::param /*time*/)
{
	UNREACHABLE;
}

} // namespace openmsx
