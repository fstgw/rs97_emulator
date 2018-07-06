// $Id: LDDummyRenderer.hh 10248 2009-07-22 21:02:14Z m9710797 $

#ifndef LDDUMMYRENDERER_HH
#define LDDUMMYRENDERER_HH

#include "LDRenderer.hh"

namespace openmsx {

class LDDummyRenderer : public LDRenderer
{
public:
	virtual void frameStart(EmuTime::param time);
	virtual void frameEnd();
	virtual void drawBlank(int r, int g, int b);
	virtual RawFrame* getRawFrame();
};

} // namespace openmsx

#endif
