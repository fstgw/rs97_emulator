// $Id: ConfigException.hh 12614 2012-06-14 20:06:47Z m9710797 $

#ifndef CONFIGEXCEPTION_HH
#define CONFIGEXCEPTION_HH

#include "MSXException.hh"

namespace openmsx {

class ConfigException : public MSXException
{
public:
	explicit ConfigException(string_ref message)
		: MSXException(message) {}
};

} // namespace openmsx

#endif
