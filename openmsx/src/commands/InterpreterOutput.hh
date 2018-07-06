// $Id: InterpreterOutput.hh 12626 2012-06-14 20:14:17Z m9710797 $

#ifndef INTERPRETEROUTPUT_HH
#define INTERPRETEROUTPUT_HH

#include "string_ref.hh"

namespace openmsx {

class InterpreterOutput
{
public:
	virtual ~InterpreterOutput() {}
	virtual void output(string_ref text) = 0;
	virtual unsigned getOutputColumns() const = 0;
};

} // namespace openmsx

#endif
