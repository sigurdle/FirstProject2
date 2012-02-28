#ifndef w3c_SVGColorProfileRule_h
#define w3c_SVGColorProfileRule_h

//#include "resource.h"       // main symbols

//#include "CSSRule.h"

namespace System
{
namespace Web
{

class WEBEXT CCSSDescriptors : public System::Object
{
public:

	class CDescriptor : public Object
	{
	public:
		String descriptor;
		CSSValue* m_value;
	};

	vector<CDescriptor*> m_items;
};

class WEBEXT SVGColorProfileRule : public CSSRule
{
public:
	CTOR SVGColorProfileRule()
	{
		m_bCSSTextUpdated = true;
	}

	~SVGColorProfileRule()
	{
	}

//	int FinalConstruct();
//	void FinalRelease();

	String get_src();
	void set_src(StringIn newVal);
	String get_name();
	void set_name(StringIn newVal);
	SVGRenderingIntent get_renderingIntent();
	void set_renderingIntent(SVGRenderingIntent newVal);

	CSSType get_type() const
	{
		return COLOR_PROFILE_RULE;
	}

	void set_cssText(StringIn newVal);

protected:

	void UpdateCSSText();
	void ParseCSSText();

	bool m_bCSSTextUpdated;

public:

	/*
	CComBSTR m_src;
	CComBSTR m_name;
	LSVGRenderingIntent m_renderingIntent;
	*/

	CCSSDescriptors* m_descriptors;
//	CArray<CSSSelector*,CSSSelector*> m_selectorList;	// The parsed selectorText list
};

}	// w3c
}

#endif // w3c_SVGColorProfileRule_h
