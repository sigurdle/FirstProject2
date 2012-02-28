#ifndef Web_SVGEnumerationBlendModeTypeValue_h
#define Web_SVGEnumerationBlendModeTypeValue_h

namespace System
{
namespace Web
{

class SVGEnumerationBlendModeTypeValue : public Object
{
public:

	CTOR SVGEnumerationBlendModeTypeValue();

	operator SVGBlendModeType ();
	SVGEnumerationBlendModeTypeValue& operator = (SVGBlendModeType value);
	SVGEnumerationBlendModeTypeValue& operator += (SVGBlendModeType value);

	void InterpolateValue(SVGEnumerationBlendModeTypeValue& a, SVGEnumerationBlendModeTypeValue& b, double t);

	friend void SetAsString(SVGEnumerationBlendModeTypeValue* p, StringIn str);
	friend String GetAsString(SVGEnumerationBlendModeTypeValue* p);

	friend int GetAsInt(SVGEnumerationBlendModeTypeValue* p)
	{
		return (int)p->m_value;
	}

	SVGBlendModeType m_value;
};

}	// Web
}

#endif // Web_SVGEnumerationBlendModeTypeValue_h
