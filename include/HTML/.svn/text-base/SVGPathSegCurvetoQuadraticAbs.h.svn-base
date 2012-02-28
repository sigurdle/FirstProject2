#ifndef __SVGPATHSEGCURVETOQUADRATICABS_H_
#define __SVGPATHSEGCURVETOQUADRATICABS_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegCurvetoQuadraticAbs : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegCurvetoQuadraticAbs()
	{
		m_x = m_y = m_x1 = m_y1 = 0;
	}

	double get_y1() const
	{
		return m_y1;
	}
	void set_y1(double newVal);
	double get_x1() const
	{
		return m_x1;
	}
	void set_x1(double newVal);
	double get_y() const
	{
		return m_y;
	}
	void set_y(double newVal);
	double get_x() const
	{
		return m_x;
	}
	void set_x(double newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_CURVETO_QUADRATIC_ABS;
	}

	String get_pathSegTypeAsLetter() const
	{
		return WSTR("Q");
	}

protected:

	double m_x;
	double m_y;
	double m_x1;
	double m_y1;
};

}	// Web
}

#endif //__SVGPATHSEGCURVETOQUADRATICABS_H_
