// $Id: CommandException.cc 12614 2012-06-14 20:06:47Z m9710797 $

#include "CommandException.hh"

namespace openmsx {

CommandException::CommandException(string_ref message)
	: MSXException(message)
{
}

SyntaxError::SyntaxError()
	: CommandException("Syntax error")
{
}

} // namespace openmsx

