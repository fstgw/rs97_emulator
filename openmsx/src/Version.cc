// $Id: Version.cc 8522 2009-01-27 23:32:51Z mthuurne $

#include "Version.hh"

namespace openmsx {

#include "Version.ii"

const std::string Version::FULL_VERSION
	= "openMSX " + Version::VERSION
	+ (Version::RELEASE ? "" : "-dev" + Version::REVISION);

} // namespace openmsx
