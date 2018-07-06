// $Id: XMLLoader.hh 8198 2008-09-03 16:19:47Z m9710797 $

#ifndef XMLLOADER_HH
#define XMLLOADER_HH

#include <string>
#include <memory>

namespace openmsx {

class XMLElement;

namespace XMLLoader
{
	std::auto_ptr<XMLElement> load(const std::string& filename,
	                               const std::string& systemID);
};

} // namespace openmsx

#endif
