// $Id: RomMajutsushi.cc 12527 2012-05-17 17:34:11Z m9710797 $

// Mapper for "Hai no Majutsushi" from Konami.
// It's a Konami mapper with a DAC.

#include "RomMajutsushi.hh"
#include "DACSound8U.hh"
#include "Rom.hh"
#include "serialize.hh"

namespace openmsx {

RomMajutsushi::RomMajutsushi(const DeviceConfig& config, std::auto_ptr<Rom> rom)
	: RomKonami(config, rom)
	, dac(new DACSound8U("Majutsushi-DAC", "Hai no Majutsushi's DAC", config))
{
}

RomMajutsushi::~RomMajutsushi()
{
}

void RomMajutsushi::reset(EmuTime::param time)
{
	RomKonami::reset(time);
	dac->reset(time);
}

void RomMajutsushi::writeMem(word address, byte value, EmuTime::param time)
{
	if (0x5000 <= address && address < 0x6000) {
		dac->writeDAC(value, time);
	} else {
		RomKonami::writeMem(address, value, time);
	}
}

byte* RomMajutsushi::getWriteCacheLine(word address) const
{
	return (0x5000 <= address && address < 0x6000)
		? NULL : RomKonami::getWriteCacheLine(address);
}

template<typename Archive>
void RomMajutsushi::serialize(Archive& ar, unsigned /*version*/)
{
        ar.template serializeBase<RomKonami>(*this);
	ar.serialize("DAC", *dac);
}
INSTANTIATE_SERIALIZE_METHODS(RomMajutsushi);
REGISTER_MSXDEVICE(RomMajutsushi, "RomMajutsushi");

} // namespace openmsx
