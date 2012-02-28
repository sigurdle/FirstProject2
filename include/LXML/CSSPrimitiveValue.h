#ifndef Web_CSSPrimitivevalue_h
#define Web_CSSPrimitivevalue_h

#ifndef Web_CSSCounter_h
#error CSSCounter.h not included
#endif

namespace System
{
namespace Web
{

class WEBEXT CSSPrimitiveValue : 
	public CSSValue,

	protected IRGBColorListener,
	protected ICSSRectListener
{
public:
	CTOR CSSPrimitiveValue();
	~CSSPrimitiveValue();

	CSSUnitType get_primitiveType() const;
	String getStringValue();
	void setStringValue(CSSUnitType stringType, StringIn stringValue);
	double getFloatValue(CSSUnitType unitType) const;
	void setFloatValue(CSSUnitType unitType, double floatValue);
	RGBColor* getRGBColorValue() const;
	CSSRect* getRectValue() const;
	CSSCounter* getCounterValue() const;
// CSSValue
	String get_cssText();
	void set_cssText(StringIn newVal);

public:

	ICSSPrimitiveValueListener* m_pListener;

	int m_propertyIndex;

	CSSUnitType m_unitType;

	double m_floatValue;
	double m_floatValueUserUnit;
	String m_stringValue;

	// union ??
	RGBColor* m_colorValue;
	CSSRect* m_rectValue;
	CSSCounter* m_counterValue;

#if 0
	CComPtr<ILDOMDocument> m_urlDocument;
#endif

	void SetRGBColor(Graphics::Color clr);
	void SetPrimitiveType(CSSUnitType unitType, StringIn stringValue, Graphics::Color color);
	void SetPrimitiveType(CSSUnitType unitType, double floatValue);

	void operator = (const CSSPrimitiveValue& value);
	void operator += (const CSSPrimitiveValue& value);

	/*
	System::StringW* getStringValue()
	{
		return get_cssText();
	}
	*/

	void InterpolateValue(const CSSPrimitiveValue& a, const CSSPrimitiveValue& b, double t);

	ErrorCode ParseCSSText(StringIn bnewVal);
	void UpdateCSSText();

	virtual void OnChangedRGBColor(RGBColor* pRGBColor);
	virtual void OnChangedRect(CSSRect* pRect);
};

}	// Web
}

#endif // Web_CSSPrimitivevalue_h
