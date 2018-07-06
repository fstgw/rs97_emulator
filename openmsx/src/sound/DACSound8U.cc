// $Id: DACSound8U.cc 12631 2012-06-14 20:18:24Z m9710797 $

#include "DACSound8U.hh"

namespace openmsx {

DACSound8U::DACSound8U(string_ref name, string_ref desc,
                       const DeviceConfig& config)
	: DACSound16S(name, desc, config)
{
}

void DACSound8U::writeDAC(byte value, EmuTime::param time)
{
	DACSound16S::writeDAC((short(value) - 0x80) << 8, time);
}

} // namespace openmsx
