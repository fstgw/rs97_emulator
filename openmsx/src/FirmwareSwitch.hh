// $Id: FirmwareSwitch.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef FRONTSWITCH_HH
#define FRONTSWITCH_HH

#include "DeviceConfig.hh"
#include "noncopyable.hh"
#include <memory>

namespace openmsx {

class BooleanSetting;

class FirmwareSwitch : private noncopyable
{
public:
	explicit FirmwareSwitch(const DeviceConfig& config);
	~FirmwareSwitch();

	bool getStatus() const;

private:
	const DeviceConfig config;
	const std::auto_ptr<BooleanSetting> setting;
};

} // namespace openmsx

#endif
