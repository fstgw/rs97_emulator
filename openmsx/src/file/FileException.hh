// $Id: FileException.hh 12614 2012-06-14 20:06:47Z m9710797 $

#ifndef FILEEXCEPTION_HH
#define FILEEXCEPTION_HH

#include "MSXException.hh"

namespace openmsx {

class FileException : public MSXException
{
public:
	explicit FileException(string_ref message)
		: MSXException(message) {}
};

} // namespace openmsx

#endif
