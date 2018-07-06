// $Id: MSXS1990.hh 12527 2012-05-17 17:34:11Z m9710797 $

#ifndef MSXS1990_HH
#define MSXS1990_HH

#include "MSXDevice.hh"
#include <memory>

namespace openmsx {

class FirmwareSwitch;
class S1990Debuggable;

/**
 * This class implements the MSX-engine found in a MSX Turbo-R (S1990)
 *
 * TODO explanation
 */
class MSXS1990 : public MSXDevice
{
public:
	explicit MSXS1990(const DeviceConfig& config);
	virtual ~MSXS1990();

	virtual void reset(EmuTime::param time);
	virtual byte readIO(word port, EmuTime::param time);
	virtual byte peekIO(word port, EmuTime::param time) const;
	virtual void writeIO(word port, byte value, EmuTime::param time);

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	byte readRegister(byte reg) const;
	void writeRegister(byte reg, byte value);
	void setCPUStatus(byte value);

	const std::auto_ptr<FirmwareSwitch> firmwareSwitch;
	const std::auto_ptr<S1990Debuggable> debuggable;
	byte registerSelect;
	byte cpuStatus;

	friend class S1990Debuggable;
};

} // namespace openmsx

#endif
