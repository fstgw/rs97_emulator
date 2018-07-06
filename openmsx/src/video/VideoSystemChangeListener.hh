// $Id: VideoSystemChangeListener.hh 4792 2005-10-30 22:45:38Z m9710797 $

#ifndef VIDEOSYSTEMCHANGELISTENER_HH
#define VIDEOSYSTEMCHANGELISTENER_HH

namespace openmsx {

class VideoSystemChangeListener
{
public:
	virtual void preVideoSystemChange() = 0;
	virtual void postVideoSystemChange() = 0;

protected:
	virtual ~VideoSystemChangeListener() {}
};

} // namespace openmsx

#endif
