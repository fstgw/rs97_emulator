// $Id: MidiInDevice.hh 12629 2012-06-14 20:16:30Z m9710797 $

#ifndef MIDIINDEVICE_HH
#define MIDIINDEVICE_HH

#include "Pluggable.hh"

namespace openmsx {

class MidiInDevice : public Pluggable
{
public:
	// Pluggable (part)
	virtual string_ref getClass() const;

	virtual void signal(EmuTime::param time) = 0;
};

} // namespace openmsx

#endif
