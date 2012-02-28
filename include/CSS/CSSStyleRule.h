#ifndef __CSSSTYLERULE_H__
#define __CSSSTYLERULE_H__

//#include "resource.h"       // main symbols

//#include "CSSStyleDeclaration.h"
//class CSSStyleDeclaration;

namespace System
{
namespace Web
{

class CSSEXT CSSStyleRule : 
	public CSSRule,
	public ICSSStyleDeclarationListener
{
public:
	CTOR CSSStyleRule();
	~CSSStyleRule();

	CSSStyleDeclaration* get_style();
	String get_selectorText();
	void set_selectorText(StringIn newVal);

	// Extensions
	CSSSelectorList* get_selectors()
	{
		return m_selectorList;
	}

// CSSRule
	CSSType get_type() const
	{
		return STYLE_RULE;
	}
	String get_cssText();
	void set_cssText(StringIn newVal);

	//void GetNSName(CSSStream* stream, System::StringW*& ns, System::StringW*& name);

	CSSSelectorList* m_selectorList;
	CSSStyleDeclaration* m_declaration;

protected:

	bool m_bCSSTextUpdated;

	void UpdateCSSText();
	void ParseCSSText();

	virtual void OnStyleDeclChanged(CSSStyleDeclaration* pStyleDecl)
	{
		m_bCSSTextUpdated = false;
		if (m_pListener)
		{
			m_pListener->OnRuleChanged(this);
		}
	}
};

}	// Web
}

#endif // __CSSSTYLERULE_H__
