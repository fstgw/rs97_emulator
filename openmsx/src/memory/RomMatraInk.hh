// $Id: RomMatraInk.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef ROMMATRAINK_HH
#define ROMMATRAINK_HH

#include "MSXRom.hh"
#include "serialize.hh"
#include <memory>

namespace openmsx {

class Rom;
class AmdFlash;

class RomMatraInk : public MSXRom
{
public:
	RomMatraInk(const DeviceConfig& config, std::auto_ptr<Rom> rom);
	virtual ~RomMatraInk();

	virtual void reset(EmuTime::param time);
	virtual byte peekMem(word address, EmuTime::param time) const;
	virtual byte readMem(word address, EmuTime::param time);
	virtual void writeMem(word address, byte value, EmuTime::param time);
	virtual const byte* getReadCacheLine(word address) const;
	virtual byte* getWriteCacheLine(word address) const;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	const std::auto_ptr<AmdFlash> flash;
};

} // namespace openmsx

#endif
