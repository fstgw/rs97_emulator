// $Id: Version.hh 8522 2009-01-27 23:32:51Z mthuurne $

#ifndef VERSION_HH
#define VERSION_HH

#include <string>

namespace openmsx {

class Version {
public:
	// Defined by build system:
	static const bool RELEASE;
	static const std::string VERSION;
	static const std::string REVISION;
	static const std::string BUILD_FLAVOUR;

	// Computed using constants above:
	static const std::string FULL_VERSION;
};

} // namespace openmsx

#endif
