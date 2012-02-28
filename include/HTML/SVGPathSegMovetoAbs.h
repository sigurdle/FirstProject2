#ifndef Web_SVGPathSegMovetoAbs_h
#define Web_SVGPathSegMovetoAbs_h

//#include "SVGPathSeg.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegMovetoAbs : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegMovetoAbs();

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

	virtual SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_MOVETO_ABS;
	}

	virtual String get_pathSegTypeAsLetter() const
	{
		return &s_pathSegTypeAsLetter;
	}

	static ImmutableString<WCHAR> s_pathSegTypeAsLetter;

protected:

	double m_x;
	double m_y;
};

}	// Web
}

#endif // Web_SVGPathSegMovetoAbs_h
