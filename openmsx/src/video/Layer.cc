// $Id: Layer.cc 9511 2009-04-09 18:34:13Z m9710797 $

#include "Layer.hh"
#include "LayerListener.hh"

namespace openmsx {

Layer::Layer(Coverage coverage_, ZIndex z_)
	: display(NULL), coverage(coverage_), z(z_)
{
}

Layer::~Layer()
{
}

void Layer::setCoverage(Coverage coverage_)
{
	coverage = coverage_;
}

void Layer::setZ(ZIndex z_)
{
	z = z_;
	if (display) display->updateZ(*this);
}

void Layer::setDisplay(LayerListener& display_)
{
	display = &display_;
}


// class ScopedLayerHider

ScopedLayerHider::ScopedLayerHider(Layer& layer_)
	: layer(layer_)
	, originalCoverage(layer.getCoverage())
{
	layer.setCoverage(Layer::COVER_NONE);
}

ScopedLayerHider::~ScopedLayerHider()
{
	layer.setCoverage(originalCoverage);
}

} // namespace openmsx
