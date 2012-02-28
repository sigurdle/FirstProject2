#ifndef Web_CSSRect_h
#define Web_CSSRect_h

namespace System
{
namespace Web
{

class WEBEXT CSSRect : public Object, public ICSSPrimitiveValueListener
{
public:
	CTOR CSSRect();
	~CSSRect();

	virtual void OnCSSValueChanged(CSSPrimitiveValue* pValue)
	{
		if (m_pListener)
		{
			m_pListener->OnChangedRect(this);
		}
	}

	CSSPrimitiveValue* get_top();
	CSSPrimitiveValue* get_right();
	CSSPrimitiveValue* get_bottom();
	CSSPrimitiveValue* get_left();

public:

	ICSSRectListener* m_pListener;

	CSSPrimitiveValue* m_top;
	CSSPrimitiveValue* m_right;
	CSSPrimitiveValue* m_bottom;
	CSSPrimitiveValue* m_left;
};

}	// Web
}

#endif // Web_CSSRect_h
