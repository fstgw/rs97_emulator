// $Id: FilenameSetting.cc 12624 2012-06-14 20:12:38Z m9710797 $

#include "FilenameSetting.hh"
#include "Completer.hh"
#include "FileContext.hh"

namespace openmsx {

FilenameSettingPolicy::FilenameSettingPolicy()
{
}

void FilenameSettingPolicy::tabCompletion(std::vector<std::string>& tokens) const
{
	SystemFileContext context;
	Completer::completeFileName(tokens, context);
}

string_ref FilenameSettingPolicy::getTypeString() const
{
	return "filename";
}


FilenameSetting::FilenameSetting(
		CommandController& commandController,
		string_ref name, string_ref description,
		string_ref initialValue)
	: SettingImpl<FilenameSettingPolicy>(
		commandController, name, description, initialValue.str(),
		Setting::SAVE)
{
}

} // namespace openmsx
