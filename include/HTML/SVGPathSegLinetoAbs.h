#ifndef w3c_SVGPathSegLinetoAbs_h
#define w3c_SVGPathSegLinetoAbs_h

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegLinetoAbs : 
	public SVGPathSeg
{
public:
	CTOR SVGPathSegLinetoAbs()
	{
		m_x = m_y = 0;
	}

	double get_y();
	void set_y(double newVal);
	double get_x();
	void set_x(double newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_LINETO_ABS;
	}
	String get_pathSegTypeAsLetter() const
	{
		return WSTR("L");
	}

protected:

	double m_x;
	double m_y;
};

}	// Web
}

#endif // w3c_SVGPathSegLinetoAbs_h
