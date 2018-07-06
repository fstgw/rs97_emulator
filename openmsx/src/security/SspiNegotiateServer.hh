// $Id: SspiNegotiateServer.hh 10116 2009-06-30 21:11:15Z m9710797 $

#ifndef SSPI_NEGOTIATE_SERVER_HH
#define SSPI_NEGOTIATE_SERVER_HH

#ifdef _WIN32

#include "SspiUtils.hh"

namespace openmsx {

class SspiNegotiateServer : public sspiutils::SspiPackageBase
{
public:
	explicit SspiNegotiateServer(sspiutils::StreamWrapper& serverStream);
	~SspiNegotiateServer();

	bool Authenticate();
	bool Authorize();

private:
	PSECURITY_DESCRIPTOR psd;
};

} // namespace openmsx

#endif // _WIN32

#endif // SSPI_NEGOTIATE_SERVER_HH
