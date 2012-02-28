#ifndef __SVGPATHSEGMOVETOREL_H_
#define __SVGPATHSEGMOVETOREL_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegMovetoRel : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegMovetoRel();

	double get_y() const;
	void set_y(double newVal);
	double get_x() const;
	void set_x(double newVal);
// SVGPathSeg
	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_MOVETO_REL;
	}
	String get_pathSegTypeAsLetter() const
	{
		return WSTR("m");
	}

protected:

	double m_x;
	double m_y;
};

}	// Web
}

#endif //__SVGPATHSEGMOVETOREL_H_
