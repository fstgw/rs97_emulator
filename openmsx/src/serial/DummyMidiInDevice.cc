// $Id: DummyMidiInDevice.cc 12631 2012-06-14 20:18:24Z m9710797 $

#include "DummyMidiInDevice.hh"

namespace openmsx {

void DummyMidiInDevice::signal(EmuTime::param /*time*/)
{
	// ignore
}

string_ref DummyMidiInDevice::getDescription() const
{
	return "";
}

void DummyMidiInDevice::plugHelper(Connector& /*connector*/,
                                   EmuTime::param /*time*/)
{
}

void DummyMidiInDevice::unplugHelper(EmuTime::param /*time*/)
{
}

} // namespace openmsx
