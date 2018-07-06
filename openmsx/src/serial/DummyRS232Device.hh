// $Id: DummyRS232Device.hh 12631 2012-06-14 20:18:24Z m9710797 $

#ifndef DUMMYRS232DEVICE_HH
#define DUMMYRS232DEVICE_HH

#include "RS232Device.hh"

namespace openmsx {

class DummyRS232Device : public RS232Device
{
public:
	virtual void signal(EmuTime::param time);
	virtual string_ref getDescription() const;
	virtual void plugHelper(Connector& connector, EmuTime::param time);
	virtual void unplugHelper(EmuTime::param time);

	// SerialDataInterface (part)
	virtual void recvByte(byte value, EmuTime::param time);
};

} // namespace openmsx

#endif
