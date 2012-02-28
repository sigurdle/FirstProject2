#ifndef __SVGPATHSEGLINETOHORIZONTALABS_H_
#define __SVGPATHSEGLINETOHORIZONTALABS_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT CLSVGPathSegLinetoHorizontalAbs : 
	public SVGPathSeg
{
public:
	CTOR CLSVGPathSegLinetoHorizontalAbs()
	{
		m_x = 0;
	}

	double get_x()
	{
		return m_x;
	}

	void set_x(double newVal);

	virtual SVGPathSegType get_pathSegType() const override
	{
		return PATHSEG_LINETO_HORIZONTAL_ABS;
	}
	virtual String get_pathSegTypeAsLetter() const override
	{
		return WSTR("H");
	}

protected:

	double m_x;
};

}	// Web
}

#endif //__SVGPATHSEGLINETOHORIZONTALABS_H_
