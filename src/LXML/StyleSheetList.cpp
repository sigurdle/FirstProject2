#include "stdafx.h"
#include "LXML.h"
#include "StyleSheetList.h"

namespace System
{
namespace Web
{

StyleSheetList::StyleSheetList()
{
}

StyleSheetList::~StyleSheetList()
{
	ASSERT(m_items.GetSize() == 0);	// ASSERTING here may be FinalRelease wasn't called
}

void StyleSheetList::append(Style::IStyleSheet* stylesheet)
{
	ASSERT(stylesheet);
#if 0
	CComQIPtr<INotifySend, &IID_INotifySend> cp = stylesheet;
	if (cp)
	{
		DWORD cookie;
//			cp->Advise(this, &cookie);
	}
#endif
	m_items.Add(stylesheet);
}

Style::IStyleSheet* StyleSheetList::item(size_t index)
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
		return NULL;
}

size_t StyleSheetList::get_length()
{
	return m_items.GetSize();
}

}	// Web
}	// System
