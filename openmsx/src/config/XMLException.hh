// $Id: XMLException.hh 12614 2012-06-14 20:06:47Z m9710797 $

#ifndef XMLEXCEPTION_HH
#define XMLEXCEPTION_HH

#include "MSXException.hh"

namespace openmsx {

class XMLException : public MSXException
{
public:
	explicit XMLException(string_ref message)
		: MSXException(message) {}
};

} // namespace openmsx

#endif
