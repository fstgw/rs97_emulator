// $Id: ReplayCLI.hh 12628 2012-06-14 20:15:37Z m9710797 $

#ifndef REPLAYCLI_HH
#define REPLAYCLI_HH

#include "CLIOption.hh"

namespace openmsx {

class CommandLineParser;
class GlobalCommandController;

class ReplayCLI : public CLIOption, public CLIFileType
{
public:
	explicit ReplayCLI(CommandLineParser& commandLineParser);
	virtual bool parseOption(const std::string& option,
	                         std::deque<std::string>& cmdLine);
	virtual string_ref optionHelp() const;
	virtual void parseFileType(const std::string& filename,
	                           std::deque<std::string>& cmdLine);
	virtual string_ref fileTypeHelp() const;

private:
	GlobalCommandController& commandController;
};

} // namespace openmsx

#endif
