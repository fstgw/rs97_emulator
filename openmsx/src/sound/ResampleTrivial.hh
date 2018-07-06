// $Id: ResampleTrivial.hh 12241 2011-08-27 14:58:39Z m9710797 $

#ifndef RESAMPLETRIVIAL_HH
#define RESAMPLETRIVIAL_HH

#include "ResampleAlgo.hh"

namespace openmsx {

class ResampledSoundDevice;

class ResampleTrivial : public ResampleAlgo
{
public:
	ResampleTrivial(ResampledSoundDevice& input);
	virtual bool generateOutput(int* dataOut, unsigned num,
	                            EmuTime::param time);

private:
	ResampledSoundDevice& input;
};

} // namespace openmsx

#endif
