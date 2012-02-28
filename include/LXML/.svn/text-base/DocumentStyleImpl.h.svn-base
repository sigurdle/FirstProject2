#error don't

#if 0

#ifndef __DOCUMENTSTYLEIMPL_H
#define __DOCUMENTSTYLEIMPL_H

#include "StyleSheetList.h"

namespace System
{
namespace w3c
{

class WEBEXT DocumentStyleImpl
{
public:
	CTOR DocumentStyleImpl()
	{
		m_styleSheets = new StyleSheetList;
	}

	virtual ~DocumentStyleImpl()
	{
		delete m_styleSheets;
	}

	void loadDefaultStylesheet();

	/*
	int FinalConstruct()
	{
		HRESULT hr;

		//if (FAILED(hr)) return hr;
		//m_styleSheets->AddRef();

		{
			DWORD cookie;
			//m_styleSheets->Advise(static_cast<T*>(this), &cookie);
		}

		return 0;
	}

	void FinalRelease()
	{
		if (m_styleSheets)
		{
			//CComQIPtr<INotifySend> cp = m_styleSheets;
			//if (cp)
			{
//				m_styleSheets->Unadvise(static_cast<T*>(this));
			}

		//	m_styleSheets->Release();
			m_styleSheets = NULL;
		}
	}
*/

	StyleSheetList* get_styleSheets()
	{
		return m_styleSheets;
	}

	void removeStyleSheet(/*[in]*/ StyleSheet* styleSheet)
	{
		ASSERT(0);
#if 0
		for (int i = 0; i < m_styleSheets->m_items.GetSize(); i++)
		{
			if (m_styleSheets->m_items[i] == styleSheet)
			{
				ASSERT(0);
#if 0
				CComQIPtr<INotifySend, &IID_INotifySend> cp = m_styleSheets->m_items[i];
				cp->Unadvise(m_styleSheets);

				m_styleSheets->m_items[i]->Release();
				m_styleSheets->m_items.RemoveAt(i);
#endif
				return S_OK;
			}
		}

		ASSERT(0);
#endif
	}

private:

	StyleSheetList* m_styleSheets;
};

}	// Web
}

#endif

#endif
