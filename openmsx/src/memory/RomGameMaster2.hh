// $Id: RomGameMaster2.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef ROMGAMEMASTER2_HH
#define ROMGAMEMASTER2_HH

#include "RomBlocks.hh"

namespace openmsx {

class RomGameMaster2 : public Rom4kBBlocks
{
public:
	RomGameMaster2(const DeviceConfig& config, std::auto_ptr<Rom> rom);
	virtual ~RomGameMaster2();

	virtual void reset(EmuTime::param time);
	virtual void writeMem(word address, byte value, EmuTime::param time);
	virtual byte* getWriteCacheLine(word address) const;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	word sramOffset;
	bool sramEnabled;
};

} // namespace openmsx

#endif
