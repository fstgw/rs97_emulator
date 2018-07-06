// $Id: DummyAudioInputDevice.cc 12631 2012-06-14 20:18:24Z m9710797 $

#include "DummyAudioInputDevice.hh"

namespace openmsx {

string_ref DummyAudioInputDevice::getDescription() const
{
	return "";
}

void DummyAudioInputDevice::plugHelper(Connector& /*connector*/,
                                       EmuTime::param /*time*/)
{
}

void DummyAudioInputDevice::unplugHelper(EmuTime::param /*time*/)
{
}

short DummyAudioInputDevice::readSample(EmuTime::param /*time*/)
{
	return 0; // silence
}

} // namespace openmsx
