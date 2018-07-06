// $Id: MSXException.hh 12614 2012-06-14 20:06:47Z m9710797 $

#ifndef MSXEXCEPTION_HH
#define MSXEXCEPTION_HH

#include "string_ref.hh"

namespace openmsx {

class MSXException
{
public:
	explicit MSXException(string_ref message);
	~MSXException();

	const std::string& getMessage() const {
		return message;
	}

private:
	const std::string message;
};

class FatalError
{
public:
	explicit FatalError(string_ref message);
	~FatalError();

	const std::string& getMessage() const {
		return message;
	}

private:
	const std::string message;
};

} // namespace openmsx

#endif
