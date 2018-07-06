// $Id: Base64.hh 11579 2010-07-07 14:20:44Z m9710797 $

#ifndef BASE64_HH
#define BASE64_HH

#include <string>

namespace Base64 {
	std::string encode(const void* input, int len);
	std::string decode(const std::string& input);
}

#endif
