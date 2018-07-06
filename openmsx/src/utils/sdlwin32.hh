// $Id: sdlwin32.hh 12018 2011-03-13 10:05:58Z mthuurne $

#ifndef SDLWIN32_HH
#define SDLWIN32_HH

#ifdef _WIN32

#include <windows.h>

namespace openmsx {

HWND getSDLWindowHandle();

} // namespace openmsx

#endif

#endif // SDLWIN32_HH
