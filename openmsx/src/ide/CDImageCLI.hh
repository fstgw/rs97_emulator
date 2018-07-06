// $Id: CDImageCLI.hh 12628 2012-06-14 20:15:37Z m9710797 $

#ifndef CDIMAGECLI_HH
#define CDIMAGECLI_HH

#include "CLIOption.hh"

namespace openmsx {

class CommandLineParser;
class GlobalCommandController;

class CDImageCLI : public CLIOption
{
public:
	explicit CDImageCLI(CommandLineParser& cmdLineParser);
	virtual bool parseOption(const std::string& option,
	                         std::deque<std::string>& cmdLine);
	virtual string_ref optionHelp() const;

private:
	GlobalCommandController& commandController;
};

} // namespace openmsx

#endif
