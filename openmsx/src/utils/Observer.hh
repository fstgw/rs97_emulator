// $Id: Observer.hh 8183 2008-08-28 18:09:05Z m9710797 $

#ifndef OBSERVER_HH
#define OBSERVER_HH

namespace openmsx {

/**
 * Generic Gang-of-Four Observer class, templatized edition.
 */
template <typename T> class Observer
{
public:
	virtual void update(const T& subject) = 0;
	virtual void subjectDeleted(const T& /*subject*/) { /*nothing*/ }

protected:
	virtual ~Observer() {}
};

} // namespace openmsx

#endif
