// $Id: CliExtension.cc 12628 2012-06-14 20:15:37Z m9710797 $

#include "CliExtension.hh"
#include "CommandLineParser.hh"
#include "MSXMotherBoard.hh"
#include "MSXException.hh"
#include <cassert>

using std::string;

namespace openmsx {

CliExtension::CliExtension(CommandLineParser& cmdLineParser_)
	: cmdLineParser(cmdLineParser_)
{
	cmdLineParser.registerOption("-ext", *this, 7);
}

bool CliExtension::parseOption(const string& option, std::deque<string>& cmdLine)
{
	try {
		string extensionName = getArgument(option, cmdLine);
		MSXMotherBoard* motherboard = cmdLineParser.getMotherBoard();
		assert(motherboard);
		motherboard->loadExtension(extensionName);
	} catch (MSXException& e) {
		throw FatalError(e.getMessage());
	}
	return true;
}

string_ref CliExtension::optionHelp() const
{
	return "Insert the extension specified in argument";
}

} // namespace openmsx
