#ifndef __SVGPATHSEGARCREL_H_
#define __SVGPATHSEGARCREL_H_

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegArcRel : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegArcRel();

	double get_x();
	void set_x(/*[in]*/ double newVal);
	double get_y();
	void set_y(/*[in]*/ double newVal);
	double get_r1();
	void set_r1(/*[in]*/ double newVal);
	double get_r2();
	void set_r2(/*[in]*/ double newVal);
	double get_angle();
	void set_angle(/*[in]*/ double newVal);
	bool get_largeArcFlag();
	void set_largeArcFlag(/*[in]*/ bool newVal);
	bool get_sweepFlag();
	void set_sweepFlag(/*[in]*/ bool newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_ARC_REL;
	}
	String get_pathSegTypeAsLetter() const
	{
		return WSTR("a");
	}

protected:

	double m_x;
	double m_y;
	double m_r1;
	double m_r2;
	double m_angle;
	bool m_largeArcFlag;
	bool m_sweepFlag;
};

}	// Web
}

#endif //__SVGPATHSEGARCREL_H_
