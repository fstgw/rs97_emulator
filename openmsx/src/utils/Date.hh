// $Id: Date.hh 12590 2012-06-06 20:32:24Z m9710797 $

#ifndef DATE_HH
#define DATE_HH

#include <string>
#include <ctime>

namespace openmsx {

namespace Date {

	// 'line' must point to a buffer that is at least 24 characters long
	time_t fromString(const char* line);

	std::string toString(time_t time);

} // namespace Date

} // namespace openmsx

#endif
