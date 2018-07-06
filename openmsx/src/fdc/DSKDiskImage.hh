// $Id: DSKDiskImage.hh 12587 2012-06-06 20:31:32Z m9710797 $

#ifndef DSKDISKIMAGE_HH
#define DSKDISKIMAGE_HH

#include "SectorBasedDisk.hh"
#include "shared_ptr.hh"

namespace openmsx {

class File;

class DSKDiskImage : public SectorBasedDisk
{
public:
	explicit DSKDiskImage(const Filename& filename);
	DSKDiskImage(const Filename& filename, const shared_ptr<File>& file);
	virtual ~DSKDiskImage();

private:
	virtual void readSectorImpl(unsigned sector, byte* buf);
	virtual void writeSectorImpl(unsigned sector, const byte* buf);
	virtual bool isWriteProtectedImpl() const;
	virtual Sha1Sum getSha1Sum();

	const shared_ptr<File> file;
};

} // namespace openmsx

#endif
