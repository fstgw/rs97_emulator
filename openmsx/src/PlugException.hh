// $Id: PlugException.hh 12614 2012-06-14 20:06:47Z m9710797 $

#ifndef PLUGEXCEPTION_HH
#define PLUGEXCEPTION_HH

#include "MSXException.hh"

namespace openmsx {

/** Thrown when a plug action fails.
  */
class PlugException : public MSXException
{
public:
	explicit PlugException(string_ref message)
		: MSXException(message) {}
};

} // namespace openmsx

#endif
