// $Id: StdioMessages.hh 12625 2012-06-14 20:13:15Z m9710797 $

#ifndef STDIOMESSAGES_HH
#define STDIOMESSAGES_HH

#include "CliListener.hh"

namespace openmsx {

class StdioMessages : public CliListener
{
public:
	virtual void log(CliComm::LogLevel level, string_ref message);

	virtual void update(CliComm::UpdateType type, string_ref machine,
	                    string_ref name, string_ref value);
};

} // namespace openmsx

#endif
