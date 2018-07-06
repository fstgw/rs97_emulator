// $Id: MSXVictorHC9xSystemControl.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef MSXVICTORHC9XSYSTEMCONTROL_HH
#define MSXVICTORHC9XSYSTEMCONTROL_HH

#include "MSXDevice.hh"

namespace openmsx {

class MSXVictorHC9xSystemControl : public MSXDevice
{
public:
	explicit MSXVictorHC9xSystemControl(const DeviceConfig& config);
	virtual ~MSXVictorHC9xSystemControl();

	virtual byte readMem(word address, EmuTime::param time);
	virtual byte peekMem(word address, EmuTime::param time) const;
	virtual void writeMem(word address, byte value, EmuTime::param time);

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	byte systemControlRegister;

};

} // namespace openmsx

#endif
