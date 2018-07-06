// $Id: OSDGUILayer.hh 12658 2012-06-23 19:58:36Z m9710797 $

#ifndef OSDGUILAYER_HH
#define OSDGUILAYER_HH

#include "Layer.hh"

namespace openmsx {

class OSDGUI;

class OSDGUILayer : public Layer
{
public:
	OSDGUI& getGUI();

	// Layer
	virtual string_ref getLayerName() const;

protected:
	explicit OSDGUILayer(OSDGUI& gui);
	~OSDGUILayer();

private:
	OSDGUI& gui;
};

class SDLOSDGUILayer : public OSDGUILayer
{
public:
	explicit SDLOSDGUILayer(OSDGUI& gui);

	// Layer
	virtual void paint(OutputSurface& output);
};

class GLOSDGUILayer : public OSDGUILayer
{
public:
	explicit GLOSDGUILayer(OSDGUI& gui);

	// Layer
	virtual void paint(OutputSurface& output);
};

} // namespace openmsx

#endif
