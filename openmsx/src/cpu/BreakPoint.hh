// $Id: BreakPoint.hh 12808 2012-08-13 19:27:30Z m9710797 $

#ifndef BREAKPOINT_HH
#define BREAKPOINT_HH

#include "BreakPointBase.hh"
#include "openmsx.hh"

namespace openmsx {

/** Base class for CPU breakpoints.
 *  For performance reasons every bp is associated with exactly one
 *  (immutable) address.
 */
class BreakPoint : public BreakPointBase
{
public:
	BreakPoint(GlobalCliComm& CliComm, word address,
	           TclObject command, TclObject condition);

	word getAddress() const;
	unsigned getId() const;

private:
	const unsigned id;
	const word address;

	static unsigned lastId;
};

} // namespace openmsx

#endif
