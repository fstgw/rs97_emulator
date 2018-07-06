// $Id: PasswordCart.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef PASSWORDCART_HH
#define PASSWORDCART_HH

#include "MSXDevice.hh"

namespace openmsx {

class PasswordCart : public MSXDevice
{
public:
	explicit PasswordCart(const DeviceConfig& config);

	virtual void reset(EmuTime::param time);
	virtual void writeIO(word port, byte value, EmuTime::param time);
	virtual byte readIO(word port, EmuTime::param time);
	virtual byte peekIO(word port, EmuTime::param time) const;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	const word password;
	byte pointer;
};

} // namespace

#endif
