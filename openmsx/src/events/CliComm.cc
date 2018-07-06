// $Id: CliComm.cc 12625 2012-06-14 20:13:15Z m9710797 $

#include "CliComm.hh"

namespace openmsx {

const char* const CliComm::levelStr[CliComm::NUM_LEVELS] = {
	"info", "warning", "error", "progress"
};

const char* const CliComm::updateStr[CliComm::NUM_UPDATES] = {
	"led", "setting", "setting-info", "hardware", "plug", "unplug",
	"media", "status", "extension", "sounddevice", "connector"
};


CliComm::CliComm()
{
}

CliComm::~CliComm()
{
}

void CliComm::printInfo(string_ref message)
{
	log(INFO, message);
}

void CliComm::printWarning(string_ref message)
{
	log(WARNING, message);
}

void CliComm::printError(string_ref message)
{
	log(LOGLEVEL_ERROR, message);
}

void CliComm::printProgress(string_ref message)
{
	log(PROGRESS, message);
}

} // namespace openmsx
