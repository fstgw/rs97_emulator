// $Id: MC6850.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef MC6850_HH
#define MC6850_HH

#include "MSXDevice.hh"

namespace openmsx {

class MC6850 : public MSXDevice
{
public:
	explicit MC6850(const DeviceConfig& config);

	virtual void reset(EmuTime::param time);
	virtual byte readIO(word port, EmuTime::param time);
	virtual byte peekIO(word port, EmuTime::param time) const;
	virtual void writeIO(word port, byte value, EmuTime::param time);

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);
};

} // namespace openmsx

#endif
