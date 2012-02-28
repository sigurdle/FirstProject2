#ifndef Web_CSSImportRule_h
#define Web_CSSImportRule_h

//#include "resource.h"       // main symbols

#include "CSSRule.h"

namespace System
{
namespace Web
{

interface CSSImportRuleListener
{
	virtual void OnStyleRuleChanged(CSSImportRule* pRule) = 0;
};

class XMLEXT CSSImportRule : 
	public CSSRule
{
public:
	CTOR CSSImportRule();
	~CSSImportRule();

//	int FinalConstruct();
//	void FinalRelease();

	/*
	CSSImportRuleListener* m_pListener;

	CComObject<CLCSSStyleDeclaration>* m_declaration;
	CArray<CSSSelector*,CSSSelector*> m_selectorList;	// The parsed selectorText list

	bool m_bCSSTextUpdated;

	void UpdateCSSText();
	void ParseCSSText();
	*/

	void LoadHref(StringIn href);

#if 0
	virtual void OnStyleDeclChanged(CLCSSStyleDeclaration* pStyleDecl)
	{
		m_bCSSTextUpdated = false;
	//	FireOnChanged(type, targetObject, dispID);	// TODO remove
	}
#endif

	MediaList* get_media();
	String get_href() const;
	CSSStyleSheet* get_styleSheet();

	CSSType get_type() const;
	void set_cssText(StringIn newVal);

public:

	CSSStyleSheet* m_styleSheet;

	String m_href;
};

}	// Web
}

#endif // Web_CSSImportRule_h
