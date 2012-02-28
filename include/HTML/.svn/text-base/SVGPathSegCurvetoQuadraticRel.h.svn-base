#ifndef Web_SVGPathSegCurvetoQuadraticRel_h
#define Web_SVGPathSegCurvetoQuadraticRel_h

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegCurvetoQuadraticRel : public SVGPathSeg
{
public:
	CTOR SVGPathSegCurvetoQuadraticRel();
	CTOR SVGPathSegCurvetoQuadraticRel(double x, double y, double x1, double y1);

	double get_y1() const
	{
		return m_y1;
	}
	void set_y1(double newVal);

	double get_x1() const
	{
		return m_x1;
	}
	void set_x1(double newVal);
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

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_CURVETO_QUADRATIC_REL;
	}
	String get_pathSegTypeAsLetter() const;

protected:

	double m_x;
	double m_y;
	double m_x1;
	double m_y1;
};

}	// Web
}

#endif // Web_SVGPathSegCurvetoQuadraticRel_h
