#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "WEUndoMoveObjects.h"

#include "EXMLDocument.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CWEUndoMoveObjects

STDMETHODIMP CWEUndoSourceLast::GetDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
{
	return S_OK;
}

STDMETHODIMP CWEUndoSourceLast::GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID)
{
//	*pClsid = CLSID_WEUndoMoveObjects;
	*plID = 0;

	return S_OK;
}

STDMETHODIMP CWEUndoSourceLast::OnNextAdd(void)
{
	return S_OK;
}

STDMETHODIMP CWEUndoSourceLast::Do(/* [in] */ IUndoManager *pUndoManager)
{
#if 0
	CComPtr<ILDOMDocument> domdocument;
	m_pDocument->get_DOMDocument(&domdocument);

	CComQIPtr<ILDOMElement> documentElement;
	domdocument->get_documentElement(&documentElement);

	CComQIPtr<ITextData> textDocument = m_pDocument->m_textDocument;

	if (m_bRedo)
	{
		ATLASSERT(m_sourceText == NULL);

		if (m_bSourceEditLast)
		{
			BSTR p; textDocument->get_data(&p);
			m_sourceText = SysAllocString(p);	// Make a copy
		}
	}
	else	// Undo
	{
		m_pDocument->m_bSourceEditLast = m_bSourceEditLast;

		if (m_sourceText)
		{
			ATLASSERT(m_bSourceEditLast == TRUE);

			m_pDocument->m_lockDOM++;
			textDocument->put_data(m_sourceText);	// text document now owns the string
			m_pDocument->m_lockDOM--;

			m_sourceText = NULL;
		}
		else
		{
			ATLASSERT(m_bSourceEditLast == FALSE);
		}
	}
#endif
	return S_OK;
}

#endif