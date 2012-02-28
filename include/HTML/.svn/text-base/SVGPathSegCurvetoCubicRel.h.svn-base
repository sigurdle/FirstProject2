#ifndef Web_SVGPathsegCurvetoCubicRel_h
#define Web_SVGPathsegCurvetoCubicRel_h

//#include "resource.h"       // main symbols

#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegCurvetoCubicRel : public SVGPathSeg
{
public:
	CTOR SVGPathSegCurvetoCubicRel()
	{
		m_x = 0;
		m_y = 0;
		m_x1 = 0;
		m_y1 = 0;
		m_x2 = 0;
		m_y2 = 0;
	}

	double get_y2() const;
	void set_y2(double newVal);
	double get_x2() const;
	void set_x2(double newVal);
	double get_y1() const;
	void set_y1(double newVal);
	double get_x1() const;
	void set_x1(double newVal);
	double get_y() const;
	void set_y(double newVal);
	double get_x() const;
	void set_x(double newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_CURVETO_CUBIC_REL;
	}

	String get_pathSegTypeAsLetter() const
	{
		return WSTR("c");
	}

protected:

	double m_x;
	double m_y;
	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;
};

}	// Web
}

#endif // Web_SVGPathsegCurvetoCubicRel_h
