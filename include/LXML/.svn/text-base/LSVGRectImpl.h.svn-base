#ifndef w3c_SVGRectImpl_h
#define w3c_SVGRectImpl_h

namespace System
{
namespace Web
{

class WEBEXT SVGRectImpl : public Object, public ISVGRect
{
public:
	CTOR SVGRectImpl()
	{
		m_x = 0;
		m_y = 0;
		m_width = 0;
		m_height = 0;
	}

	SVGRectImpl& operator = (const SVGRectImpl& value)
	{
		m_x = value.m_x;
		m_y = value.m_y;
		m_width = value.m_width;
		m_height = value.m_height;

		return *this;
	}

	void InterpolateValue(SVGRectImpl* a, SVGRectImpl* b, double t)
	{
		m_x = a->m_x + (b->m_x - a->m_x)*t;
		m_y = a->m_y + (b->m_y - a->m_y)*t;
		m_width = a->m_width + (b->m_width - a->m_width)*t;
		m_height = a->m_height + (b->m_height - a->m_height)*t;
	}

	double get_x() const
	{
		return m_x;
	}

	void set_x(double newVal)
	{
		m_x = newVal;
	}

	double get_y() const
	{
		return m_y;
	}

	void set_y(double newVal)
	{
		m_y = newVal;
	}

	double get_width() const
	{
		return m_width;
	}

	void set_width(double newVal)
	{
		m_width = newVal;
	}

	double get_height() const
	{
		return m_height;
	}

	void set_height(double newVal)
	{
		m_height = newVal;
	}

public:

	double m_x;
	double m_y;
	double m_width;
	double m_height;
};

}	// w3c
}

#endif // w3c_SVGRectImpl_h
