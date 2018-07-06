// $Id: FilenameSetting.hh 12624 2012-06-14 20:12:38Z m9710797 $

#ifndef FILENAMESETTING_HH
#define FILENAMESETTING_HH

#include "StringSetting.hh"

namespace openmsx {

class FileContext;

class FilenameSettingPolicy : public StringSettingPolicy
{
protected:
	explicit FilenameSettingPolicy();
	void tabCompletion(std::vector<std::string>& tokens) const;
	string_ref getTypeString() const;
};

class FilenameSetting : public SettingImpl<FilenameSettingPolicy>
{
public:
	FilenameSetting(CommandController& commandController,
	                string_ref name, string_ref description,
	                string_ref initialValue);
};

} // namespace openmsx

#endif
