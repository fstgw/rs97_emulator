// $Id: PluggableFactory.hh 4531 2005-06-26 19:17:47Z m9710797 $

#ifndef PLUGGABLEFACTORY_HH
#define PLUGGABLEFACTORY_HH

namespace openmsx {

class PluggingController;
class MSXMotherBoard;

class PluggableFactory
{
public:
	static void createAll(PluggingController& controller,
	                      MSXMotherBoard& motherBoard);
};

} // namespace openmsx

#endif
