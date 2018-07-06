// $Id: RomSuperLodeRunner.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef ROMSUPERLODERUNNER_HH
#define ROMSUPERLODERUNNER_HH

#include "RomBlocks.hh"

namespace openmsx {

class RomSuperLodeRunner : public Rom16kBBlocks
{
public:
	RomSuperLodeRunner(const DeviceConfig& config, std::auto_ptr<Rom> rom);
	virtual ~RomSuperLodeRunner();

	virtual void reset(EmuTime::param time);
	virtual void globalWrite(word address, byte value, EmuTime::param time);
};

} // namespace openmsx

#endif
