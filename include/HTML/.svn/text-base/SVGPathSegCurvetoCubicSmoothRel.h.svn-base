#ifndef __SVGPATHSEGCURVETOCUBICSMOOTHREL_H_
#define __SVGPATHSEGCURVETOCUBICSMOOTHREL_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegCurvetoCubicSmoothRel : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegCurvetoCubicSmoothRel()
	{
		m_x = 0;
		m_y = 0;
		m_x2 = 0;
		m_y2 = 0;
	}

	double get_y2();
	void set_y2(double newVal);
	double get_x2();
	void set_x2(double newVal);
	double get_y();
	void set_y(double newVal);
	double get_x();
	void set_x(double newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_CURVETO_CUBIC_SMOOTH_REL;
	}
	String get_pathSegTypeAsLetter() const
	{
		return WSTR("s");
	}

protected:

	double m_x;
	double m_y;
	double m_x2;
	double m_y2;
};

}	// w3c
}

#endif //__SVGPATHSEGCURVETOCUBICSMOOTHREL_H_
