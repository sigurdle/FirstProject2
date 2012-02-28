#ifndef __LSVGPATHSEGCURVETOQUADRATICSMOOTHREL_H_
#define __LSVGPATHSEGCURVETOQUADRATICSMOOTHREL_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegCurvetoQuadraticSmoothRel : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegCurvetoQuadraticSmoothRel();

	double get_y() const;
	void put_y(double newVal);
	double get_x() const;
	void put_x(double newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL;
	}
	String get_pathSegTypeAsLetter() const
	{
		return WSTR("t");
	}

	double m_x;
	double m_y;
};

}	// Web
}

#endif //__LSVGPATHSEGCURVETOQUADRATICSMOOTHREL_H_
