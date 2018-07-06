// $Id: DebugCondition.hh 12808 2012-08-13 19:27:30Z m9710797 $

#ifndef DEBUGCONDITION_HH
#define DEBUGCONDITION_HH

#include "BreakPointBase.hh"

namespace openmsx {

/** General debugger condition
 *  Like breakpoints, but not tied to a specifc address.
 */
class DebugCondition : public BreakPointBase
{
public:
	DebugCondition(GlobalCliComm& CliComm,
	               TclObject command, TclObject condition);
	unsigned getId() const { return id; }

private:
	const unsigned id;

	static unsigned lastId;
};

} // namespace openmsx

#endif
