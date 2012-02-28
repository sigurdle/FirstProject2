#ifndef SVGEnumerationColorMatrixTypeValue_h
#define SVGEnumerationColorMatrixTypeValue_h

namespace System
{
namespace Web
{

class SVGEXT SVGEnumerationColorMatrixTypeValue : public Object
{
public:

	CTOR SVGEnumerationColorMatrixTypeValue();

	operator SVGColorMatrixType () const;
	SVGEnumerationColorMatrixTypeValue& operator = (SVGColorMatrixType value);
	SVGEnumerationColorMatrixTypeValue& operator += (SVGColorMatrixType value);

	friend String GetAsString(SVGEnumerationColorMatrixTypeValue* p);
	friend void SetAsString(SVGEnumerationColorMatrixTypeValue* p, StringIn value);

	friend int GetAsInt(SVGEnumerationColorMatrixTypeValue* p);
	friend void SetAsInt(SVGEnumerationColorMatrixTypeValue* p, int value);

	void InterpolateValue(const SVGEnumerationColorMatrixTypeValue& a, const SVGEnumerationColorMatrixTypeValue& b, double t);

	SVGColorMatrixType m_value;
};

}	// Web
}

#endif // SVGEnumerationColorMatrixTypeValue_h
