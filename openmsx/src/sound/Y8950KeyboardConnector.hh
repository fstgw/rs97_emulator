// $Id: Y8950KeyboardConnector.hh 12629 2012-06-14 20:16:30Z m9710797 $

#ifndef Y8950KEYBOARDCONNECTOR_HH
#define Y8950KEYBOARDCONNECTOR_HH

#include "Connector.hh"
#include "openmsx.hh"

namespace openmsx {

class Y8950KeyboardDevice;

class Y8950KeyboardConnector : public Connector
{
public:
	explicit Y8950KeyboardConnector(PluggingController& pluggingController);
	virtual ~Y8950KeyboardConnector();

	void write(byte data, EmuTime::param time);
	byte read(EmuTime::param time);
	Y8950KeyboardDevice& getPluggedKeyb() const;

	// Connector
	virtual const std::string getDescription() const;
	virtual string_ref getClass() const;
	virtual void plug(Pluggable& dev, EmuTime::param time);

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	byte data;
};

} // namespace openmsx

#endif
