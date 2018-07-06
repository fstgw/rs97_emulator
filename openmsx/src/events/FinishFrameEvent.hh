// $Id: FinishFrameEvent.hh 8199 2008-09-04 17:04:38Z m9710797 $

#ifndef FINISHFRAMEEVENT_HH
#define FINISHFRAMEEVENT_HH

#include "Event.hh"
#include "VideoSource.hh"

namespace openmsx {

class FinishFrameEvent : public Event
{
public:
	FinishFrameEvent(VideoSource source_, bool skipped_)
		: Event(OPENMSX_FINISH_FRAME_EVENT)
		, source(source_), skipped(skipped_)
	{
	}

	VideoSource getSource() const { return source; }
	bool isSkipped() const { return skipped; }

private:
	const VideoSource source;
	const bool skipped;
};

} // namespace openmsx

#endif
