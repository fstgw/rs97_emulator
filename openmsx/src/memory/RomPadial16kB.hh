// $Id: RomPadial16kB.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef ROMPADIAL16KB_HH
#define ROMPADIAL16KB_HH

#include "RomAscii16kB.hh"

namespace openmsx {

class RomPadial16kB : public RomAscii16kB
{
public:
	RomPadial16kB(const DeviceConfig& config, std::auto_ptr<Rom> rom);

	virtual void reset(EmuTime::param time);
};

} // namespace openmsx

#endif
