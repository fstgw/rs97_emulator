// $Id: FileNotFoundException.hh 12614 2012-06-14 20:06:47Z m9710797 $

#ifndef FILENOTFOUNDEXCEPTION_HH
#define FILENOTFOUNDEXCEPTION_HH

#include "FileException.hh"

namespace openmsx {

class FileNotFoundException : public FileException
{
public:
	explicit FileNotFoundException(string_ref message)
		: FileException(message) {}
};

} // namespace openmsx

#endif
