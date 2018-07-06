// $Id: MSXException.cc 12614 2012-06-14 20:06:47Z m9710797 $

#include "MSXException.hh"

namespace openmsx {

// class MSXException

MSXException::MSXException(string_ref message_)
	: message(message_.data(), message_.size())
{
}

MSXException::~MSXException()
{
}


// class FatalError

FatalError::FatalError(string_ref message_)
	: message(message_.data(), message_.size())
{
}

FatalError::~FatalError()
{
}

} // namespace openmsx
