// $Id: openmsx.cc 9464 2009-04-05 04:50:55Z mfeingol $

#include "openmsx.hh"

#ifdef _WIN32
#include <windows.h>
#endif

namespace openmsx {

#ifdef _WIN32

void DebugPrint(const char* output)
{
	OutputDebugStringA(output);
	OutputDebugStringA("\n");
}

#endif

} // namespace openmsx
