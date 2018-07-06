// $Id: Timer.hh 4852 2005-11-12 17:48:41Z m9710797 $

#ifndef TIMER_HH
#define TIMER_HH

namespace openmsx {

namespace Timer {

	/** Get current (real) time in us. Absolute value has no meaning.
	  */
	unsigned long long getTime();

	/** Sleep for the specified amount of time (in us). It is possible
	  * that this method sleeps longer or shorter than the requested time.
	  */
	void sleep(unsigned long long us);

} // namespace Timer

} // namespace openmsx

#endif
