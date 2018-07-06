// $Id: KeyCodeSetting.hh 12624 2012-06-14 20:12:38Z m9710797 $

#ifndef KEYCODESETTING_HH
#define KEYCODESETTING_HH

#include "SettingPolicy.hh"
#include "SettingImpl.hh"
#include "Keys.hh"

namespace openmsx {

class KeyCodeSettingPolicy : public SettingPolicy<Keys::KeyCode>
{
protected:
	explicit KeyCodeSettingPolicy();
	std::string toString(Keys::KeyCode key) const;
	Keys::KeyCode fromString(const std::string& str) const;
	string_ref getTypeString() const;
};

class KeyCodeSetting : public SettingImpl<KeyCodeSettingPolicy>
{
public:
	KeyCodeSetting(CommandController& commandController,
	               string_ref name, string_ref description,
	               Keys::KeyCode initialValue);
};

} // namespace openmsx

#endif
