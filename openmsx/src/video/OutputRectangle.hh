// $Id: OutputRectangle.hh 12018 2011-03-13 10:05:58Z mthuurne $

#ifndef OUTPUTRECTANGLE_HH
#define OUTPUTRECTANGLE_HH

namespace openmsx {

class OutputRectangle
{
public:
	virtual unsigned getOutputWidth()  const = 0;
	virtual unsigned getOutputHeight() const = 0;
protected:
	virtual ~OutputRectangle() {}
};


class DummyOutputRectangle : public OutputRectangle
{
public:
	DummyOutputRectangle(unsigned width_, unsigned height_)
		: width(width_), height(height_)
	{
	}
	virtual unsigned getOutputWidth()  const { return width;  }
	virtual unsigned getOutputHeight() const { return height; }
private:
	const unsigned width;
	const unsigned height;
};

} // namespace openmsx

#endif
