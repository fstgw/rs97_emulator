// $Id: RomPadial8kB.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef ROMPADIAL8KB_HH
#define ROMPADIAL8KB_HH

#include "RomAscii8kB.hh"

namespace openmsx {

class RomPadial8kB : public RomAscii8kB
{
public:
	RomPadial8kB(const DeviceConfig& config, std::auto_ptr<Rom> rom);

	virtual void reset(EmuTime::param time);
};

} // namespace openmsx

#endif
