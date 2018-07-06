// $Id: DummyRS232Device.cc 12631 2012-06-14 20:18:24Z m9710797 $

#include "DummyRS232Device.hh"

namespace openmsx {

void DummyRS232Device::signal(EmuTime::param /*time*/)
{
	// ignore
}

string_ref DummyRS232Device::getDescription() const
{
	return "";
}

void DummyRS232Device::plugHelper(Connector& /*connector*/,
                                  EmuTime::param /*time*/)
{
}

void DummyRS232Device::unplugHelper(EmuTime::param /*time*/)
{
}

void DummyRS232Device::recvByte(byte /*value*/, EmuTime::param /*time*/)
{
	// ignore
}

} // namespace openmsx
