// $Id: InitException.hh 12614 2012-06-14 20:06:47Z m9710797 $

#ifndef INITEXCEPTION_HH
#define INITEXCEPTION_HH

#include "MSXException.hh"

namespace openmsx {

/** Thrown when a subsystem initialisation fails.
  * For example: opening video surface, opening audio output etc.
  */
class InitException: public MSXException
{
public:
	explicit InitException(string_ref message)
		: MSXException(message) {}
};

} // namespace openmsx

#endif
