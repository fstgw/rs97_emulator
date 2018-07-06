// $Id: RomFactory.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef ROMFACTORY_HH
#define ROMFACTORY_HH

#include <memory>

namespace openmsx {

class MSXDevice;
class DeviceConfig;

namespace RomFactory
{
	std::auto_ptr<MSXDevice> create(const DeviceConfig& config);
}

} // namespace openmsx

#endif
