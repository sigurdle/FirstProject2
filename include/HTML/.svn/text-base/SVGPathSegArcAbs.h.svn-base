#ifndef Web_SVGPathSegArcAbs_h
#define Web_SVGPathSegArcAbs_h

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegArcAbs : public SVGPathSeg
{
public:
	CTOR SVGPathSegArcAbs();

	double get_x() const;
	void set_x(double newVal);
	double get_y() const;
	void set_y(double newVal);
	double get_r1() const;
	void set_r1(double newVal);
	double get_r2() const;
	void set_r2(double newVal);
	double get_angle() const;
	void set_angle(double newVal);
	bool get_largeArcFlag() const;
	void set_largeArcFlag(bool newVal);
	bool get_sweepFlag() const;
	void set_sweepFlag(bool newVal);

	SVGPathSegType get_pathSegType() const
	{
		return PATHSEG_ARC_ABS;
	}

	String get_pathSegTypeAsLetter() const;

	static ImmutableString<WCHAR> pathSegTypeAsLetter;

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

#endif // Web_SVGPathSegArcAbs_h
