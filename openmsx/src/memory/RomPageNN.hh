// $Id: RomPageNN.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef ROMPAGENN_HH
#define ROMPAGENN_HH

#include "RomBlocks.hh"

namespace openmsx {

class RomPageNN : public Rom8kBBlocks
{
public:
	RomPageNN(const DeviceConfig& config, std::auto_ptr<Rom> rom, byte pages);
};

} // namespace openmsx

#endif
