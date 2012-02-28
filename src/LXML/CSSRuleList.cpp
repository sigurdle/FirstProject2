#include "stdafx.h"
#include "LXML.h"
#include "CSSRuleList.h"
#include "CSSRule.h"

namespace System
{
namespace Web
{

CSSRuleList::CSSRuleList()
{
}

CSSRuleList::~CSSRuleList()
{
}

#if 0
int CSSRuleList::FinalConstruct()
{
	return 0;
}

void CSSRuleList::FinalRelease()
{
	for (int i = 0; i < m_rules.GetSize(); i++)
	{
	//	CComQIPtr<CSSRuleImplImpl, &IID_CSSRuleImplImpl>((IUnknown*)m_rules[i])->m_pListener = NULL;
	//	m_rules[i]->Release();
	}
	m_rules.RemoveAll();
}
#endif

unsigned int CSSRuleList::get_length() const
{
	return m_rules.size();
}

CSSRule* CSSRuleList::item(unsigned int index) const
{
	if (index < m_rules.GetSize())
	{
		return m_rules[index];
	}
	else
		return NULL;
}

}	// Web
}
