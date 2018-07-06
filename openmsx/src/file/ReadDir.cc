// $Id: ReadDir.cc 9286 2009-02-28 18:15:49Z mfeingol $

#include "ReadDir.hh"

namespace openmsx {

ReadDir::ReadDir(const std::string& directory)
{
	dir = opendir(directory.empty() ? "." : directory.c_str());
}

ReadDir::~ReadDir()
{
	if (dir) {
		closedir(dir);
	}
}

struct dirent* ReadDir::getEntry()
{
	if (!dir) {
		return NULL;
	}
	return readdir(dir);
}

bool ReadDir::isValid() const
{
	return dir != NULL;
}

} // namespace openmsx
