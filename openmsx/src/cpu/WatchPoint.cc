// $Id: WatchPoint.cc 12808 2012-08-13 19:27:30Z m9710797 $

#include "WatchPoint.hh"
#include <cassert>

namespace openmsx {

unsigned WatchPoint::lastId = 0;

WatchPoint::WatchPoint(GlobalCliComm& cliComm,
                       TclObject command, TclObject condition,
                       Type type_, unsigned beginAddr_, unsigned endAddr_,
                       unsigned newId /*= -1*/)
	: BreakPointBase(cliComm, command, condition)
	, id((newId == unsigned(-1)) ? ++lastId : newId)
	, beginAddr(beginAddr_), endAddr(endAddr_), type(type_)
{
	assert(beginAddr <= endAddr);
}

WatchPoint::~WatchPoint()
{
}

} // namespace openmsx

