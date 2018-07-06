// $Id: StdioMessages.cc 12625 2012-06-14 20:13:15Z m9710797 $

#include "StdioMessages.hh"
#include <iostream>

using std::string;

namespace openmsx {

void StdioMessages::log(CliComm::LogLevel level, string_ref message)
{
	const char* const* levelStr = CliComm::getLevelStrings();
	((level == CliComm::INFO) ? std::cout : std::cerr) <<
		levelStr[level] << ": " << message << std::endl;

}

void StdioMessages::update(CliComm::UpdateType /*type*/, string_ref /*machine*/,
                           string_ref /*name*/, string_ref /*value*/)
{
	// ignore
}

} // namespace openmsx
