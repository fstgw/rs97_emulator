// $Id: win32-arggen.hh 12018 2011-03-13 10:05:58Z mthuurne $

#ifndef WIN32_ARG_GEN_HH
#define WIN32_ARG_GEN_HH

#ifdef _WIN32

#include "MemBuffer.hh"

namespace openmsx {

class ArgumentGenerator
{
public:
	~ArgumentGenerator();
	char** GetArguments(int& argc);

private:
	MemBuffer<char*> argv;
};

#endif

} // namespace openmsx

#endif // WIN32_ARG_GEN_HH
