// $Id: NullSoundDriver.hh 12242 2011-08-27 14:59:06Z m9710797 $

#ifndef NULLSOUNDDRIVER_HH
#define NULLSOUNDDRIVER_HH

#include "SoundDriver.hh"

namespace openmsx {

class NullSoundDriver : public SoundDriver
{
public:
	virtual void mute();
	virtual void unmute();

	virtual unsigned getFrequency() const;
	virtual unsigned getSamples() const;

	virtual void uploadBuffer(short* buffer, unsigned len);
};

} // namespace openmsx

#endif
