#ifndef __SVGPATHSEGLINETOHORIZONTALREL_H_
#define __SVGPATHSEGLINETOHORIZONTALREL_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegLinetoHorizontalRel : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegLinetoHorizontalRel();

	double get_x();
	void set_x(double newVal);

	virtual SVGPathSegType get_pathSegType() const override;
	virtual String get_pathSegTypeAsLetter() const override;

public:

	double m_x;
};

}	// Web
}

#endif //__SVGPATHSEGLINETOHORIZONTALREL_H_
