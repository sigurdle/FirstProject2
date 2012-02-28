#ifndef __CSSCHARSETRULE_H_
#define __CSSCHARSETRULE_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class XMLEXT CSSCharsetRule : 
	public CSSRule
{
public:
	CTOR CSSCharsetRule();
	~CSSCharsetRule();

	String get_encoding();
	void set_encoding(StringIn newVal);

	CSSType get_type() const;
//	STDMETHOD(get_cssText)(BSTR *pVal);
//	STDMETHOD(set_cssText)(BSTR pVal);
};

}	// Web
}	// System

#endif // __CSSCHARSETRULE_H_
