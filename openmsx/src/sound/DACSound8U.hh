// $Id: DACSound8U.hh 12631 2012-06-14 20:18:24Z m9710797 $

// This class implements a 8 bit unsigned DAC

#ifndef DACSOUND8U_HH
#define DACSOUND8U_HH

#include "DACSound16S.hh"

namespace openmsx {

class DACSound8U : public DACSound16S
{
public:
	DACSound8U(string_ref name, string_ref desc,
	           const DeviceConfig& config);

	void writeDAC(byte value, EmuTime::param time);
};

} // namespace openmsx

#endif
