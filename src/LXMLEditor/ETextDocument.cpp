#include "stdafx.h"
#include "LXMLEditor2.h"
#include "ETextDocument.h"

#include "TextView.h"

#include "LXMLEditorApp.h"
//#include "WebEditorFrame.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CETextDocument

int CETextDocument::FinalConstruct()
{
	HRESULT hr;

	hr = m_textData.CoCreateInstance(CLSID_TextData);
	if (FAILED(hr)) return hr;

	hr = CComObject<CWEUndoManager>::CreateInstance(&m_undoManager);
	if (FAILED(hr)) return hr;
	m_undoManager->AddRef();

	return S_OK;
}

void CETextDocument::FinalRelease()
{
	if (m_textData)
	{
		m_textData.Release();
	}

	if (m_undoManager)
	{
		m_undoManager->Release();
		m_undoManager = NULL;
	}
}

STDMETHODIMP CETextDocument::get_undoManager(/*[out, retval]*/ IOleUndoManager* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_undoManager;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CETextDocument::NewDocument()
{
	CEDocumentImpl<CETextDocument>::NewDocument();

	return S_OK;
}

// IPersist
STDMETHODIMP CETextDocument::GetClassID(CLSID __RPC_FAR *pClassID)
{
	if (pClassID == NULL) return E_POINTER;
	*pClassID = GetObjectCLSID();
	return S_OK;
}

// IPersistFile
STDMETHODIMP CETextDocument::IsDirty( void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CETextDocument::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
	HRESULT hr;

	hr = CEDocumentImpl<CETextDocument>::LoadDocument(_bstr_t(pszFileName));

	return hr;
}

STDMETHODIMP CETextDocument::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CETextDocument::SaveCompleted(LPCOLESTR pszFileName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CETextDocument::GetCurFile(LPOLESTR __RPC_FAR *ppszFileName)
{
	return E_NOTIMPL;
}

// IPersistMoniker
STDMETHODIMP CETextDocument::Load( 
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode)
{
	m_curMoniker = pimkName;

	LPOLESTR displayName;
	pimkName->GetDisplayName(pibc, NULL, &displayName);
	m_pathName = displayName;
	//m_fileTitle 
	CoTaskMemFree(displayName);

	CComQIPtr<IPersistMoniker> persistMoniker = m_textData;
	HRESULT hr = persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);

	return hr;
}

STDMETHODIMP CETextDocument::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CETextDocument::SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	return E_NOTIMPL;
}

STDMETHODIMP CETextDocument::GetCurMoniker(/*[out]*/ IMoniker **ppimkName)
{
	if (ppimkName == NULL) return E_POINTER;
	*ppimkName = m_curMoniker;
	if (*ppimkName) (*ppimkName)->AddRef();
	return S_OK;
}

///////////////

STDMETHODIMP CETextDocument::LoadDocumentByteArray(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success)
{
#if 0
	m_webDocument->LoadDocumentByteArray(dataArray, success);
	if (*success)
	{
		Prepare();

		m_lockSource++;

		VARIANT_BOOL bsuccess;
		m_xmlcnt->parse(&bsuccess);

		m_lockSource--;

		Fire_doneParsingDOM();

		if (bsuccess)
		{
		}
	}

	if (*success)
	{
		if (m_pTree && !m_pTree->m_childList.IsEmpty())
		{
			SetTargetElement((CElement*)m_pTree->m_childList.GetHead(), 0);
		}
	}
#endif

	return S_OK;
}

HRESULT CETextDocument::NewWindow(IEFrame* eframe)
{
#if 0
	CComQIPtr<ILXAddin> addin = m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<IUIManager> uiManager;
	addinSite->GetUIManager((IUnknown**)&uiManager);

//	CComQIPtr<IUIManager> uiManager = gApp->m_frame;

	CComQIPtr<IUIMDIFrame> mdiframe = eframe;

	CComObject<CTextView>* textView;
	CComObject<CTextView>::CreateInstance(&textView);
	if (textView)
	{
		ASSERT(0);
#if 0
		uiManager->FindMenu(_Module.GetResourceInstance(), IDR_TEXTVIEW, &textView->m_menu);

		textView->m_document = this;

		CComPtr<IUIMDIChild> childFrame;
		mdiframe->CreateChildFrame(textView, &childFrame);
#endif
	}

	return S_OK;

#if 0
	{
		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		{
		// Text
				textView->m_document = GetUnknown();
				child->AddPage(textView, NULL);
			}
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}
#endif
#endif
	return 0;
}

STDMETHODIMP CETextDocument::ShowViews(IEFrame* pFrame)
{
	NewWindow(pFrame);
	return S_OK;
}

STDMETHODIMP CETextDocument::Activate()
{
	// TODO: Add your implementation code here

	return S_OK;
}

/*
STDMETHODIMP CETextDocument::GetDocumentsClass(IDocumentsClass **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
*/

BEGIN_CMD_MAP(CETextDocument)
// File
	CMD_HANDLER(ID_FILE_SAVE, OnFileSave)
	CMD_HANDLER(ID_FILE_SAVE_AS, OnFileSaveAs)

// Edit
	CMD_HANDLER(ID_EDIT_UNDO, OnEditUndo)
	CMD_UPDATE(ID_EDIT_UNDO, OnEditUndoUpdate)
	CMD_HANDLER(ID_EDIT_REDO, OnEditRedo)
	CMD_UPDATE(ID_EDIT_REDO, OnEditRedoUpdate)

END_CMD_MAP()

LRESULT CETextDocument::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pathName.length())
	{
		HRESULT hr = SaveDocument(m_pathName);
		if (FAILED(hr))
		{
			MessageBox(NULL/*TODO: GetMainHwnd()*/, "Couldn't Save file", "LXMLEditor", MB_OK);
		}
	}
	else
	{
		OnFileSaveAs(wNotifyCode, wID, hWndCtl, bHandled);
	}

	return 0;
}

#include "FileSaveTextOptionsDlg.h"

LRESULT CETextDocument::OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	CComQIPtr<ILXAddin> addin = m_app;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> frame;
	addinSite->GetFrame(&frame);

	CComQIPtr<IUIWnd> wnd = frame;
	HWND hWnd;
	wnd->get_hwnd(&hWnd);

//	BSTR pathName;
//	m_webDocument->get_filePath(&pathName);

	TCHAR username[1024];
	TCHAR password[1024];
	TCHAR server[1024];
	TCHAR urlpath[1024];

	URL_COMPONENTS url_components = {0};
	url_components.dwStructSize = sizeof(url_components);
	//url_components.nScheme = INTERNET_SCHEME_FTP;
	//url_components.nPort = m_nPort;
	url_components.lpszUserName = username;
	url_components.dwUserNameLength = _countof(username);
	url_components.lpszPassword = password;
	url_components.dwPasswordLength = _countof(password);
	url_components.lpszHostName = server;
	url_components.dwHostNameLength = _countof(server);
	url_components.lpszUrlPath = urlpath;
	url_components.dwUrlPathLength = _countof(urlpath);

	InternetCrackUrl(m_pathName, m_pathName.length(), ICU_DECODE | ICU_ESCAPE, &url_components);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, urlpath);	// Initial filename

	CFileSaveTextOptionsDlg dlg(FALSE, NULL, sbuffer, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, hWnd);

	if (dlg.DoModal())
	{
		HRESULT hr = SaveDocument(A2W(sbuffer));
		if (SUCCEEDED(hr))
		{
#if 0
			for (int i = 0; i < m_viewGroups.GetSize(); i++)
			{
				m_viewGroups[i]->UpdateFrameTitle();
			}
#endif
		}
		else
		{
			MessageBox(hWnd, "Couldn't Save file", "LXMLEditor", MB_OK);
		}
	}
#endif

	return 0;
}

LRESULT CETextDocument::OnEditUndo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->UndoTo(NULL);
	return 0;
}

LRESULT CETextDocument::OnEditRedo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->RedoTo(NULL);
	return 0;
}

void CETextDocument::OnEditUndoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	HRESULT hr = m_undoManager->GetLastUndoDescription(&bdescription);
	if (hr == S_OK)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Undo");
	}

	pCmdUI->Enable(bEnable);
}

void CETextDocument::OnEditRedoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	HRESULT hr = m_undoManager->GetLastRedoDescription(&bdescription);
	if (hr == S_OK)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Redo");
	}

	pCmdUI->Enable(bEnable);
}

#endif