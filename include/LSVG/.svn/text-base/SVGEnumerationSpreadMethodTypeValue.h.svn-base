#ifndef Web_SVGEnumerationSpreadMethodTypeValue_h
#define Web_SVGEnumerationSpreadMethodTypeValue_h

namespace System
{
namespace Web
{

class SVGEnumerationSpreadMethodTypeValue : public Object
{
public:

	SVGEnumerationSpreadMethodTypeValue();

	operator SVGSpreadMethodType ();
	SVGEnumerationSpreadMethodTypeValue& operator = (SVGSpreadMethodType value);
	SVGEnumerationSpreadMethodTypeValue& operator += (SVGSpreadMethodType value);

	friend void SetAsInt(SVGEnumerationSpreadMethodTypeValue* p, int value);
	friend int GetAsInt(SVGEnumerationSpreadMethodTypeValue* p);

	friend void SetAsString(SVGEnumerationSpreadMethodTypeValue* p, StringIn value);
	friend String GetAsString(SVGEnumerationSpreadMethodTypeValue* p);

	void InterpolateValue(const SVGEnumerationSpreadMethodTypeValue& a, const SVGEnumerationSpreadMethodTypeValue& b, double t);

	SVGSpreadMethodType m_value;
};

}	// Web
}

#endif // Web_SVGEnumerationSpreadMethodTypeValue_h
