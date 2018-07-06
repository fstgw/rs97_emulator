// $Id: LDDummyRenderer.cc 10248 2009-07-22 21:02:14Z m9710797 $

#include "LDDummyRenderer.hh"

namespace openmsx {

void LDDummyRenderer::frameStart(EmuTime::param /*time*/)
{
}

void LDDummyRenderer::frameEnd()
{
}

void LDDummyRenderer::drawBlank(int /*r*/, int /*g*/, int /*b*/)
{
}

RawFrame* LDDummyRenderer::getRawFrame()
{
	return NULL;
}

} // namespace openmsx
