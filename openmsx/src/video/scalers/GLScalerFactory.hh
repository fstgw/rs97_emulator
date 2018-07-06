// $Id: GLScalerFactory.hh 11789 2010-12-04 17:05:22Z mthuurne $

#ifndef GLSCALERFACTORY_HH
#define GLSCALERFACTORY_HH

#include <memory>

namespace openmsx {

class GLScaler;
class RenderSettings;

namespace GLScalerFactory
{
	/** Instantiates a Scaler.
	  * @return A Scaler object, owned by the caller.
	  */
	std::auto_ptr<GLScaler> createScaler(RenderSettings& renderSettings);
}

} // namespace openmsx

#endif // GLSCALERFACTORY_HH
