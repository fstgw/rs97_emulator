// $Id: DummyMidiOutDevice.cc 12631 2012-06-14 20:18:24Z m9710797 $

#include "DummyMidiOutDevice.hh"

namespace openmsx {

void DummyMidiOutDevice::recvByte(byte /*value*/, EmuTime::param /*time*/)
{
	// ignore
}

string_ref DummyMidiOutDevice::getDescription() const
{
	return "";
}

void DummyMidiOutDevice::plugHelper(
		Connector& /*connector*/, EmuTime::param /*time*/)
{
}

void DummyMidiOutDevice::unplugHelper(EmuTime::param /*time*/)
{
}

} // namespace openmsx
