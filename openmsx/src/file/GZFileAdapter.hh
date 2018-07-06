// $Id: GZFileAdapter.hh 11571 2010-07-06 06:16:10Z m9710797 $

#ifndef GZFILEADAPTER_HH
#define GZFILEADAPTER_HH

#include "CompressedFileAdapter.hh"

namespace openmsx {

class GZFileAdapter : public CompressedFileAdapter
{
public:
	explicit GZFileAdapter(std::auto_ptr<FileBase> file);

private:
	virtual void decompress(FileBase& file, Decompressed& decompressed);
};

} // namespace openmsx

#endif
