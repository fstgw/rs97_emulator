// $Id: DynamicClock.cc 10141 2009-07-02 19:01:40Z m9710797 $

#include "DynamicClock.hh"
#include "serialize.hh"

namespace openmsx {

template<typename Archive>
void DynamicClock::serialize(Archive& ar, unsigned /*version*/)
{
	ar.serialize("lastTick", lastTick);
	unsigned freq = getFreq();
	ar.serialize("freq", freq);
	if (ar.isLoader()) setFreq(freq);
}
INSTANTIATE_SERIALIZE_METHODS(DynamicClock);

} // namespace openmsx
