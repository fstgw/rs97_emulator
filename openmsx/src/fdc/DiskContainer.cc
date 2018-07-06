// $Id: DiskContainer.cc 9286 2009-02-28 18:15:49Z mfeingol $

#include "DiskContainer.hh"
#include "NowindRomDisk.hh"

namespace openmsx {

DiskContainer::~DiskContainer()
{
}

bool DiskContainer::isRomdisk() const
{
	return dynamic_cast<const NowindRomDisk*>(this) != NULL;
}

} // namespace openmsx
