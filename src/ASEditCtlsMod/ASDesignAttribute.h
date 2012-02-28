#pragma once

#include "ASDesignObject.h"

class CASAttribute :
	public CDTDDesignSchemaNode
{
public:
	IASAttributeDeclaration* m_asAttr;

	virtual void OnEditChange(HDC hDC)
	{
		m_bEditChanged = true;
	}

	virtual void EndEdit()
	{
		ATLASSERT(0);
#if 0
		if (m_bEditChanged)
		{
			ATLASSERT(m_hWndEdit);

			int len = ::GetWindowTextLength(m_hWndEdit);
			TCHAR* buf = new TCHAR[len+1];

			::GetWindowText(m_hWndEdit, buf, len+1);

			m_asAttr->put_nodeName(_bstr_t(buf));

			delete buf;

			m_bEditChanged = false;
		}

#if 0
		m_pCtl->m_wndEdit.DestroyWindow();
		m_hWndEdit = NULL;
#endif
#endif
	}

};
