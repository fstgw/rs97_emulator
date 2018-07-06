// $Id: CliExtension.hh 12628 2012-06-14 20:15:37Z m9710797 $

#ifndef CLIEXTENSION_HH
#define CLIEXTENSION_HH

#include "CLIOption.hh"

namespace openmsx {

class CommandLineParser;

class CliExtension : public CLIOption
{
public:
	explicit CliExtension(CommandLineParser& cmdLineParser);

	virtual bool parseOption(const std::string& option,
	                         std::deque<std::string>& cmdLine);
	virtual string_ref optionHelp() const;

private:
	CommandLineParser& cmdLineParser;
};

} // namespace openmsx

#endif
