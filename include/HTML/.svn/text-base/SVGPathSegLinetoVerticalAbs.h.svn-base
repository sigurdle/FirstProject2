#ifndef __SVGPATHSEGLINETOVERTICALABS_H__
#define __SVGPATHSEGLINETOVERTICALABS_H__

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegLinetoVerticalAbs : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegLinetoVerticalAbs()
	{
		m_y = 0;
	}

	double get_y() const
	{
		return m_y;
	}
	void set_y(double newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_LINETO_VERTICAL_ABS;
	}
	String get_pathSegTypeAsLetter() const
	{
		return WSTR("V");
	}

protected:

	double m_y;
};

}	// Web
}

#endif //__SVGPATHSEGLINETOVERTICALABS_H_
