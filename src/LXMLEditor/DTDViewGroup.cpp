// DTDViewGroup.cpp : Implementation of CDTDViewGroup
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "DTDViewGroup.h"

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

#include "SourceView.h"	// TODO remove

//extern CWebEditorApp* gApp;

#include "DTDDocument.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CDTDViewGroup

int CDTDViewGroup::FinalConstruct()
{
//	HRESULT hr;

	return 0;
}

void CDTDViewGroup::FinalRelease()
{
	for (int i = 0; i < m_views.GetSize(); i++)
	{
		int dwRef = m_views[i]->Release();
	}
	m_views.RemoveAll();
}

#if 0
LRESULT CDTDViewGroup::OnMDIActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwndChildDeact = (HWND) wParam;        // child being deactivated 
	HWND hwndChildAct = (HWND) lParam;          // child being activated 

	HWND hwnd;
	get_hwnd(&hwnd);

	BOOL bActivate = (hwnd == hwndChildAct);

	CComQIPtr<IUIManager> uiManager = gIFrame;

	if (bActivate)
	{
		//CComPtr<IDocumentsClass> documentsClass;
		//m_pDocument->GetDocumentsClass(&documentsClass);

		uiManager->ActivateObject(NULL/*documentsClass*/, m_pDocument->GetUnknown());
		uiManager->ActivateObject(m_pDocument->GetUnknown(), GetUnknown());
//		uiManager->ActivateObject(m_viewGroup->GetUnknown(), GetUnknown());
	}

	CUIMDIChildImpl<CDTDViewGroup>::OnMDIActivate(uMsg, wParam, lParam, bHandled);

	if (!bActivate)
	{
//		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(m_pDocument->GetUnknown());
	}

	return 0;
}

//virtual
void CDTDViewGroup::OnFinalMessage(HWND /*hWnd*/)
{
	for (int i = m_pDocument->m_viewGroups.GetSize()-1; i >= 0; i--)
	{
		if (m_pDocument->m_viewGroups[i] == this)
		{
			m_pDocument->m_viewGroups.RemoveAt(i);

			CDTDDocument* pDocument = m_pDocument;

			int refcount = Release();
			//ASSERT(refcount == 0);

			if (pDocument->m_viewGroups.GetSize() == 0)
			{
				pDocument->CloseDocument();
			}

			break;
		}
	}
}

LRESULT CDTDViewGroup::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pDocument->m_viewGroups.GetSize() == 1)
	{
		CUString msg;
		_bstr_t pathName;

		if (m_pDocument->m_pathName.length())
			pathName = m_pDocument->m_pathName;
		else
			pathName = m_pDocument->m_fileTitle;

		msg.Format("Save changes to %S?", (BSTR)pathName);

		int id = ::MessageBox(NULL/*TODO*/, msg, "WebEditor", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (id == IDCANCEL) return 0;

		if (id == IDYES)
		{
			// TODO save
		}
	}

	LRESULT lResult;
	bHandled = baseClass::ProcessWindowMessage(m_hWnd, uMsg, wParam, lParam, lResult);
	return lResult;
}
#endif

///////

STDMETHODIMP CDTDViewGroup::get_eDocument(/*[out,retval]*/ IEDocument* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pDocument;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

BEGIN_CMD_MAP(CDTDViewGroup)
END_CMD_MAP()

#if 0
// ICommandTarget
STDMETHODIMP CDTDViewGroup::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try document
	CComQIPtr<ICommandTarget> target = m_pDocument;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	return S_OK;
}
#endif

#endif
