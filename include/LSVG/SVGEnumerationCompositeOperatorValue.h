#ifndef Web_SVGEnumerationCompositeOperatorValue_h
#define Web_SVGEnumerationCompositeOperatorValue_h

namespace System
{
namespace Web
{

class SVGEnumerationCompositeOperatorValue :
	public Object
{
public:
	CTOR SVGEnumerationCompositeOperatorValue();

	operator SVGCompositeOperatorType () const;
	SVGEnumerationCompositeOperatorValue& operator = (SVGCompositeOperatorType value);
	SVGEnumerationCompositeOperatorValue& operator += (SVGCompositeOperatorType value);

	friend void SetAsString(SVGEnumerationCompositeOperatorValue* p, StringIn str);
	String GetAsString(SVGEnumerationCompositeOperatorValue* p);

	void InterpolateValue(const SVGEnumerationCompositeOperatorValue& a, const SVGEnumerationCompositeOperatorValue& b, double t);

	SVGCompositeOperatorType m_value;
};

}	// Web
}

#endif // Web_SVGEnumerationCompositeOperatorValue_h

