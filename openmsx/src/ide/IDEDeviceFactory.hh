// $Id: IDEDeviceFactory.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef IDEDEVICEFACTORY_HH
#define IDEDEVICEFACTORY_HH

#include <memory>

namespace openmsx {

class IDEDevice;
class DeviceConfig;

namespace IDEDeviceFactory
{
	std::auto_ptr<IDEDevice> create(const DeviceConfig& config);
}

} // namespace openmsx

#endif
