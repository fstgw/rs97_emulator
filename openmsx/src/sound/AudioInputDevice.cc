// $Id: AudioInputDevice.cc 12629 2012-06-14 20:16:30Z m9710797 $

#include "AudioInputDevice.hh"

using std::string;

namespace openmsx {

string_ref AudioInputDevice::getClass() const
{
	return "Audio Input Port";
}

} // namespace openmsx
