#ifndef __CSSRULELIST_H_
#define __CSSRULELIST_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class XMLEXT CSSRuleList : public Object, public ICSSRuleList
{
public:
	CTOR CSSRuleList();
	~CSSRuleList();

	unsigned int get_length() const;
	ICSSRule* item(unsigned int index) const;

protected:
	friend class CSSStyleSheet;
	friend class CSSMediaRule;

	vector<CSSRule*> m_rules;
};

}	// Web
}

#endif //__CSSRULELIST_H_
