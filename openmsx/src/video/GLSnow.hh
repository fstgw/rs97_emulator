// $Id: GLSnow.hh 12658 2012-06-23 19:58:36Z m9710797 $

#ifndef GLSNOW_HH
#define GLSNOW_HH

#include "Layer.hh"
#include "GLUtil.hh"
#include "noncopyable.hh"

namespace openmsx {

class Display;

/** Snow effect for background layer.
  */
class GLSnow : public Layer, private noncopyable
{
public:
	GLSnow(Display& display, unsigned width, unsigned height);
	virtual ~GLSnow();

	// Layer interface:
	virtual void paint(OutputSurface& output);
	virtual string_ref getLayerName() const;

private:
	Display& display;
	const unsigned width;
	const unsigned height;
	GLuint noiseTextureId;
};

} // namespace openmsx

#endif
