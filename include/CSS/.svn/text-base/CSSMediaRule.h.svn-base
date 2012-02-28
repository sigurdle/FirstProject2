#ifndef w3c_CSSMediaRule_h
#define w3c_CSSMediaRule_h

#include "CSSRule.h"

namespace System
{
namespace Web
{

class CSSRuleList;
class MediaList;
class CSSMediaRule;

class XMLEXT CSSMediaRule : public CSSRule
{
public:
	CTOR CSSMediaRule();
	~CSSMediaRule();

	MediaList* get_media();
	CSSRuleList* get_cssRules();
	uint insertRule(StringIn rule, long index);
	void deleteRule(uint index);

	CSSType get_type() const;
	String get_cssText();
	void set_cssText(StringIn newVal);

public:

	void UpdateCSSText();
	void ParseCSSText();

#if 0
	virtual void OnStyleDeclChanged(CLCSSStyleDeclaration* pStyleDecl)
	{
		m_bCSSTextUpdated = false;
	//	FireOnChanged(type, targetObject, dispID);	// TODO remove
	}
#endif

public:

	ICSSRuleListener* m_pListener;

	MediaList* m_media;
	CSSRuleList* m_cssRules;

	bool m_bCSSTextUpdated;
};

}	// w3c
}

#endif // w3c_CSSMediaRule_h
