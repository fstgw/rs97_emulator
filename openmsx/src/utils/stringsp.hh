// $Id: stringsp.hh 11152 2010-01-14 09:20:28Z m9710797 $

#ifndef STRINGSP_HH
#define STRINGSP_HH

#ifndef _MSC_VER
#include <strings.h>
#else

#include <string.h>
#define strcasecmp  _stricmp
#define strncasecmp _strnicmp

#endif

#endif
