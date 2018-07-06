// $Id: cstdiop.hh 11052 2009-12-29 18:05:07Z vampier $

#ifndef CSTDIOP_HH
#define CSTDIOP_HH

#include <cstdio>

#ifdef _MSC_VER
#include <io.h>

#define STDIN_FILENO _fileno(stdin)
#define snprintf _snprintf
#endif

#endif
