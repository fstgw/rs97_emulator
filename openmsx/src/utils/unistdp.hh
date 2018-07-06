// $Id: unistdp.hh 9871 2009-05-23 20:52:12Z mthuurne $

#ifndef UNISTDP_HH
#define UNISTDP_HH

#ifndef _MSC_VER

#include <unistd.h>

#else

#include <process.h>
#include <direct.h>

#define getpid _getpid

typedef int mode_t;

#endif

#endif // UNISTDP_HH
