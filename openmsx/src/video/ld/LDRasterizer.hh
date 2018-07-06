// $Id: LDRasterizer.hh 10248 2009-07-22 21:02:14Z m9710797 $

#ifndef LDRASTERIZER_HH
#define LDRASTERIZER_HH

#include "EmuTime.hh"
#include "openmsx.hh"

namespace openmsx {

class RawFrame;

class LDRasterizer
{
public:
	virtual ~LDRasterizer() {}
	virtual void frameStart(EmuTime::param time) = 0;
	virtual void drawBlank(int r, int g, int b) = 0;
	virtual RawFrame* getRawFrame() = 0;
};

} // namespace openmsx

#endif
