#ifndef Web_CSSValue_h
#define Web_CSSValue_h

namespace System
{
namespace Web
{

class CSSValue;

interface ICSSValueListener
{
	virtual void OnCSSValueChanged(CSSValue* pValue) = 0;
};

class WEBEXT CSSValue : public Object
{
public:
	CTOR CSSValue();

	virtual CSSValueType get_cssValueType() const
	{
		return m_cssValueType;
	}

	virtual String getStringValue();

	virtual String get_cssText();
	virtual void set_cssText(StringIn newVal);

	void setString(StringIn value)
	{
		set_cssText(value);
	}

protected:

	String m_cssText;
	CSSValueType m_cssValueType;
	bool m_bCSSTextUpdated;
};

class CSSValueUnknown : public CSSValue
{
public:
	CTOR CSSValueUnknown()
	{
		m_pListener = NULL;
	}

	ICSSValueListener* m_pListener;
};

}	// Web
}

#endif	// Web_CSSValue_h
