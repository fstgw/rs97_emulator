// $Id: SettingRangePolicy.hh 11587 2010-07-13 21:55:48Z mthuurne $

#ifndef SETTINGRANGEPOLICY_HH
#define SETTINGRANGEPOLICY_HH

#include "SettingPolicy.hh"
#include "TclObject.hh"
#include <algorithm>

namespace openmsx {

template <typename T> class SettingRangePolicy : public SettingPolicy<T>
{
protected:
	SettingRangePolicy(T minValue_, T maxValue_)
		: minValue(minValue_), maxValue(maxValue_)
	{
	}

	void checkSetValue(T& value)
	{
		value = std::min(std::max(value, minValue), maxValue);
	}

	T getMinValue() const { return minValue; }
	T getMaxValue() const { return maxValue; }

	void additionalInfo(TclObject& result) const
	{
		TclObject range(result.getInterpreter());
		range.addListElement(getMinValue());
		range.addListElement(getMaxValue());
		result.addListElement(range);
	}

private:
	const T minValue;
	const T maxValue;
};

} // namespace openmsx

#endif

