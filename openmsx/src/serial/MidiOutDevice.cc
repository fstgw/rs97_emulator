// $Id: MidiOutDevice.cc 12629 2012-06-14 20:16:30Z m9710797 $

#include "MidiOutDevice.hh"

namespace openmsx {

string_ref MidiOutDevice::getClass() const
{
	return "midi out";
}

void MidiOutDevice::setDataBits(DataBits /*bits*/)
{
	// ignore
}

void MidiOutDevice::setStopBits(StopBits /*bits*/)
{
	// ignore
}

void MidiOutDevice::setParityBit(bool /*enable*/, ParityBit /*parity*/)
{
	// ignore
}

} // namespace openmsx
