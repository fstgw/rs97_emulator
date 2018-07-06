// $Id: DummyAudioInputDevice.hh 12631 2012-06-14 20:18:24Z m9710797 $

#ifndef DUMMYAUDIOINPUTDEVICE_HH
#define DUMMYAUDIOINPUTDEVICE_HH

#include "AudioInputDevice.hh"

namespace openmsx {

class DummyAudioInputDevice : public AudioInputDevice
{
public:
	virtual string_ref getDescription() const;
	virtual void plugHelper(Connector& connector, EmuTime::param time);
	virtual void unplugHelper(EmuTime::param time);
	virtual short readSample(EmuTime::param time);
};

} // namespace openmsx

#endif
