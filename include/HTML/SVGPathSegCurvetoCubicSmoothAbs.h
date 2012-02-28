#ifndef Web_SVGPathSegCurvetoCubicSmoothAbs_h
#define Web_SVGPathSegCurvetoCubicSmoothabs_h

//#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegCurvetoCubicSmoothAbs : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegCurvetoCubicSmoothAbs();

	double get_y2();
	void set_y2(double newVal);
	double get_x2();
	void set_x2(double newVal);
	double get_y();
	void set_y(double newVal);
	double get_x();
	void set_x(double newVal);

	SVGPathSegType get_pathSegType() const;
	String get_pathSegTypeAsLetter() const;

public:

	double m_x;
	double m_y;
	double m_x2;
	double m_y2;
};

}	// Web
}

#endif // Web_SVGPathSegCurvetoCubicSmoothabs_h
