#ifndef __SVGPATHSEGCURVETOQUADRATICSMOOTHABS_H_
#define __SVGPATHSEGCURVETOQUADRATICSMOOTHABS_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegCurvetoQuadraticSmoothAbs : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegCurvetoQuadraticSmoothAbs();

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
		return PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS;
	}
	System::String get_pathSegTypeAsLetter() const
	{
		return WSTR("T");
	}

protected:

	double m_x;
	double m_y;
};

}	// Web
}

#endif //__SVGPATHSEGCURVETOQUADRATICSMOOTHABS_H_
