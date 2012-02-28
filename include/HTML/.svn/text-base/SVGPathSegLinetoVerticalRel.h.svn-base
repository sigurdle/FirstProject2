#ifndef __SVGPATHSEGLINETOVERTICALREL_H_
#define __SVGPATHSEGLINETOVERTICALREL_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegLinetoVerticalRel : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegLinetoVerticalRel()
	{
		m_y = 0;
	}

	double get_y() const
	{
		return m_y;
	}
	void set_y(double y);

	virtual SVGPathSegType get_pathSegType() const override
	{
		return PATHSEG_LINETO_VERTICAL_REL;
	}
	virtual String get_pathSegTypeAsLetter() const override
	{
		return WSTR("v");
	}

protected:

	double m_y;
};

}	// Web
}

#endif //__SVGPATHSEGLINETOVERTICALREL_H_
