// $Id: VideoSystem.cc 11065 2009-12-30 08:36:53Z mthuurne $

#include "VideoSystem.hh"
#include "MSXException.hh"

namespace openmsx {

VideoSystem::~VideoSystem()
{
}

bool VideoSystem::checkSettings()
{
	return true;
}

void VideoSystem::takeScreenShot(
	const std::string& /*filename*/, bool /*withOsd*/)
{
	throw MSXException(
		"Taking screenshot not possible with current renderer.");
}

void VideoSystem::setWindowTitle(const std::string& /*title*/)
{
	// ignore
}

} // namespace openmsx
