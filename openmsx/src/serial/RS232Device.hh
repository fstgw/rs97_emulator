// $Id: RS232Device.hh 12629 2012-06-14 20:16:30Z m9710797 $

#ifndef RS232DEVICE_HH
#define RS232DEVICE_HH

#include "Pluggable.hh"
#include "SerialDataInterface.hh"

namespace openmsx {

class RS232Device : public Pluggable, public SerialDataInterface
{
public:
	// Pluggable (part)
	virtual string_ref getClass() const;

	// input
	virtual void signal(EmuTime::param time) = 0;

	// SerialDataInterface (part) (output)
	virtual void setDataBits(DataBits bits);
	virtual void setStopBits(StopBits bits);
	virtual void setParityBit(bool enable, ParityBit parity);

	// control
	virtual bool getCTS(EmuTime::param time) const;
	virtual bool getDSR(EmuTime::param time) const;
	virtual void setDTR(bool status, EmuTime::param time);
	virtual void setRTS(bool status, EmuTime::param time);
};

} // namespace openmsx

#endif
