// $Id: KeyClick.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef KEYCLICK_HH
#define KEYCLICK_HH

#include "EmuTime.hh"
#include "noncopyable.hh"
#include <memory>

namespace openmsx {

class DeviceConfig;
class DACSound8U;

class KeyClick : private noncopyable
{
public:
	explicit KeyClick(const DeviceConfig& config);
	~KeyClick();

	void reset(EmuTime::param time);
	void setClick(bool status, EmuTime::param time);

private:
	const std::auto_ptr<DACSound8U> dac;
	bool status;
};

} // namespace openmsx

#endif
