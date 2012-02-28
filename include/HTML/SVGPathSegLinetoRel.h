#ifndef __SVGPATHSEGLINETOREL_H_
#define __SVGPATHSEGLINETOREL_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegLinetoRel : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegLinetoRel()
	{
		m_x = m_y = 0;
	}

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

	virtual SVGPathSegType get_pathSegType() const override
	{
		return PATHSEG_LINETO_REL;
	}
	virtual String get_pathSegTypeAsLetter() const override
	{
		return WSTR("l");
	}

protected:

	double m_x;
	double m_y;
};

}	// Web
}

#endif //__SVGPATHSEGLINETOREL_H_
