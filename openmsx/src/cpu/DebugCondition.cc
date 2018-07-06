// $Id: DebugCondition.cc 12808 2012-08-13 19:27:30Z m9710797 $

#include "DebugCondition.hh"

namespace openmsx {

unsigned DebugCondition::lastId = 0;

DebugCondition::DebugCondition(GlobalCliComm& cliComm,
                               TclObject command, TclObject condition)
	: BreakPointBase(cliComm, command, condition)
	, id(++lastId)
{
}

} // namespace openmsx

