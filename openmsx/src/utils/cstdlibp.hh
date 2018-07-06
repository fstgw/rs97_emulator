// $Id: cstdlibp.hh 12600 2012-06-07 15:41:01Z Vampier $

#ifndef CSTDLIBP_HH
#define CSTDLIBP_HH

#include <cstdlib>

#ifdef _MSC_VER
#define strtoll  _strtoi64
#define strtoull _strtoui64
#endif

#endif
