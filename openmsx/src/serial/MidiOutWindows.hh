// $Id: MidiOutWindows.hh 12633 2012-06-14 20:41:30Z m9710797 $

#ifndef MIDIOUTWINDOWS_HH
#define MIDIOUTWINDOWS_HH

#if defined(_WIN32)
#include "MidiOutDevice.hh"
#include "serialize_meta.hh"

namespace openmsx {

class PluggingController;

class MidiOutWindows : public MidiOutDevice
{
public:
	static void registerAll(PluggingController& controller);

	explicit MidiOutWindows(unsigned num);
	virtual ~MidiOutWindows();

	// Pluggable
	virtual void plugHelper(Connector& connector, EmuTime::param time);
	virtual void unplugHelper(EmuTime::param time);
	virtual const std::string& getName() const;
	virtual string_ref getDescription() const;

	// SerialDataInterface (part)
	virtual void recvByte(byte value, EmuTime::param time);

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	unsigned devidx;
	std::string name;
	std::string desc;
};

} // namespace openmsx

#endif // defined(_WIN32)
#endif // MIDIOUTWINDOWS_HH
