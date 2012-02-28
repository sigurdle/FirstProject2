#ifndef Web_CSSValueList_h
#define Web_CSSValueList_h

//#include "resource.h"       // main symbols

//#include "cssproperty.h"
//#include "CSSValueImpl.h"

//#include "CSSPrimitiveValue.h"

namespace System
{
namespace Web
{

class WEBEXT CSSValueList : 
	public CSSValue,
//	public CNotifySendImpl<CSSValueList>
	public ICSSPrimitiveValueListener,
	public ICSSValueListListener
//	public CLRGBColorListener
{
public:
	CTOR CSSValueList();
	~CSSValueList();

	void InterpolateValue(const CSSValueList& a, const CSSValueList& b, double t)
	{
		ASSERT(0);
	}

//	virtual void OnChangedRGBColor(CLRGBColor* pRGBColor);

	virtual void OnCSSValueChanged(CSSPrimitiveValue* pValue);
	virtual void OnCSSValueChanged(CSSValueList* pValue);

	unsigned int insertValue(StringIn value, unsigned int index);
	void deleteValue(unsigned int index);
	unsigned int get_length() const;
	CSSValue* item(unsigned int index);

	String get_cssText();
	void set_cssText(StringIn newVal);

protected:

	ErrorCode ParseCSSText(StringIn newVal);
	void UpdateCSSText();

public:	// TODO

	vector<CSSValue*> m_items;

	ICSSValueListListener* m_pListener;

	//CSStyle* m_pProperty;
	int m_propertyIndex;
};

}	// Web
}

#endif // Web_CSSValueList_h
