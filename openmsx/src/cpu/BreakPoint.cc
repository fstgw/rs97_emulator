// $Id: BreakPoint.cc 12808 2012-08-13 19:27:30Z m9710797 $

#include "BreakPoint.hh"
#include "TclObject.hh"

namespace openmsx {

unsigned BreakPoint::lastId = 0;

BreakPoint::BreakPoint(GlobalCliComm& cliComm, word address_,
                       TclObject command, TclObject condition)
	: BreakPointBase(cliComm, command, condition)
	, id(++lastId)
	, address(address_)
{
}

word BreakPoint::getAddress() const
{
	return address;
}

unsigned BreakPoint::getId() const
{
	return id;
}

} // namespace openmsx

