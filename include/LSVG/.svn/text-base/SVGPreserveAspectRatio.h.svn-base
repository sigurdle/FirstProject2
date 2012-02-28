#ifndef Web_SVGPreserveAspectRatio_h
#define Web_SVGPreserveAspectRatio_h

namespace System
{
namespace Web
{

class SVGEXT SVGPreserveAspectRatio :
	public Object,
	public ISVGPreserveAspectRatio
{
public:
	CTOR SVGPreserveAspectRatio();

	SVGPreserveAspectRatioAlignType get_align();
	void set_align(SVGPreserveAspectRatioAlignType newVal);

	SVGMeetOrSliceType get_meetOrSlice();
	void set_meetOrSlice(SVGMeetOrSliceType newVal);

	SVGPreserveAspectRatio& operator = (const SVGPreserveAspectRatio& value)
	{
		m_align = value.m_align;
		m_meetOrSlice = value.m_meetOrSlice;
		return *this;
	}

	/*
	SVGPreserveAspectRatio& operator += (const SVGPreserveAspectRatio& value)
	{
		m_align = value.m_align;
		m_meetOrSlice = value.m_meetOrSlice;
		return *this;
	}
	*/

	String GetAsString();
	void SetAsString(StringIn str);

	friend SVGEXT String GetAsString(SVGPreserveAspectRatio* p);
	friend SVGEXT void SetAsString(SVGPreserveAspectRatio* p, StringIn str);

	void InterpolateValue(const SVGPreserveAspectRatio& a, const SVGPreserveAspectRatio& b, double t);

protected:

	friend class SVGPreserveAspectRatioValueHandler;

	SVGPreserveAspectRatioAlignType m_align;
	SVGMeetOrSliceType m_meetOrSlice;
};

}	// Web
}

#endif // Web_SVGPreserveAspectRatio_h
