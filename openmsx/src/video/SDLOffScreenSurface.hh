// $Id: SDLOffScreenSurface.hh 11972 2011-02-26 13:21:22Z m9710797 $

#ifndef SDLOFFSCREENSURFACE_HH
#define SDLOFFSCREENSURFACE_HH

#include "OutputSurface.hh"
#include "SDLSurfacePtr.hh"

namespace openmsx {

class SDLOffScreenSurface : public OutputSurface
{
public:
	explicit SDLOffScreenSurface(const SDL_Surface& prototype);
	~SDLOffScreenSurface();

private:
	// OutputSurface
	virtual void saveScreenshot(const std::string& filename);

	SDLSurfacePtr surface;
	void* buffer;
};

} // namespace openmsx

#endif
