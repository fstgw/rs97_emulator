# $Id: node.mk 7698 2008-03-20 20:43:12Z m9710797 $

include build/node-start.mk

SRC_HDR:= \
	SettingsManager \
	Setting \
	SettingImpl \
	ProxySetting \
	IntegerSetting \
	FloatSetting \
	StringSetting \
	BooleanSetting \
	EnumSetting \
	FilenameSetting \
	KeyCodeSetting \
	UserSettings

HDR_ONLY:= \
	SettingPolicy \
	SettingRangePolicy \
	ReadOnlySetting

include build/node-end.mk

