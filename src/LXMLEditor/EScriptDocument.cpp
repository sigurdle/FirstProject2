#include "stdafx.h"
#include "LXMLEditor2.h"
#include "EScriptDocument.h"

#include "ScriptSourceView.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CEScriptDocument

int CEScriptDocument::FinalConstruct()
{
	HRESULT hr;

	hr = m_textData.CoCreateInstance(CLSID_TextData);
	if (FAILED(hr)) return hr;

//	ATLASSERT(0);
//	hr = m_undoManager.CoCreateInstance(CLSID_WEUndoManager);
//	if (FAILED(hr)) return E_NOINTERFACE;

	IDispEventImpl<1, CEScriptDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>::DispEventAdvise(m_textData);

	m_activeScript.CoCreateInstance(L"JScript");
	ATLASSERT(SUCCEEDED(hr));

	m_activeScript->SetScriptSite(this);

	CComQIPtr<IActiveScriptParse> scriptParse = m_activeScript;
	scriptParse->InitNew();

	return S_OK;
}

void CEScriptDocument::FinalRelease()
{
	if (m_textData)
	{
		IDispEventImpl<1, CEScriptDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>::DispEventUnadvise(m_textData);
		m_textData.Release();
	}

	if (m_undoManager)
	{
		m_undoManager.Release();
	}

	if (m_activeScript)
	{
		m_activeScript->Close();
		m_activeScript.Release();
	}
}

STDMETHODIMP CEScriptDocument::get_undoManager(/*[out, retval]*/ IUndoManager* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_undoManager;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CEScriptDocument::NewDocument()
{
	CEDocumentImpl<CEScriptDocument>::NewDocument();

	return S_OK;
}

// IPersist
STDMETHODIMP CEScriptDocument::GetClassID(CLSID __RPC_FAR *pClassID)
{
	return E_NOTIMPL;
}

// IPersistFile
STDMETHODIMP CEScriptDocument::IsDirty( void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEScriptDocument::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
	HRESULT hr;

	hr = CEDocumentImpl<CEScriptDocument>::LoadDocument(_bstr_t(pszFileName));

	return hr;
}

STDMETHODIMP CEScriptDocument::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEScriptDocument::SaveCompleted(LPCOLESTR pszFileName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEScriptDocument::GetCurFile(LPOLESTR __RPC_FAR *ppszFileName)
{
	return E_NOTIMPL;
}

// IPersistMoniker
STDMETHODIMP CEScriptDocument::Load( 
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

STDMETHODIMP CEScriptDocument::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEScriptDocument::SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEScriptDocument::GetCurMoniker(/*[out]*/ IMoniker **ppimkName)
{
	if (ppimkName == NULL) return E_POINTER;
	*ppimkName = m_curMoniker;
	if (*ppimkName) (*ppimkName)->AddRef();
	return S_OK;
}

////////////
STDMETHODIMP CEScriptDocument::LoadDocumentByteArray(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success)
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

void CEScriptDocument::NewWindow(IEFrame* eframe)
{
#if 0
	CComQIPtr<ILXAddin> addin = m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<IUIManager> uiManager;
	addinSite->GetUIManager((IUnknown**)&uiManager);

//	CComQIPtr<IUIManager> uiManager = gApp->m_frame;

	CComQIPtr<IUIMDIFrame> mdiframe = eframe;

	CComObject<CScriptSourceView>* textView;
	CComObject<CScriptSourceView>::CreateInstance(&textView);
	if (textView)
	{
		ATLASSERT(0);
#if 0
		uiManager->FindMenu(_Module.GetResourceInstance(), IDR_TEXTVIEW, &textView->m_menu);

		textView->m_document = this;

		CComPtr<IUIMDIChild> childFrame;
		mdiframe->CreateChildFrame(textView, &childFrame);
#endif
	}

#if 0
//	CComQIPtr<IUIManager> uiManager = gApp->m_uiManager;

	{
		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();

	//	CComQIPtr<IEDocument> webdoc;
	//	QueryInterface(IID_IEDocument, (void**)&webdoc);

		{
		// Source
			CComObject<CSourceView>* sourceView;
			CComObject<CSourceView>::CreateInstance(&sourceView);
			sourceView->m_document = this;
			child->AddPage(sourceView, NULL);
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}
#endif
#endif
}

STDMETHODIMP CEScriptDocument::ShowViews(IEFrame* pFrame)
{
	NewWindow(pFrame);
	return S_OK;
}

void CEScriptDocument::TextChanged()
{
	ClearErrors();

	CComQIPtr<IActiveScriptParse> scriptParse = m_activeScript;
	if (scriptParse)
	{
		HRESULT hr;

		hr = m_activeScript->SetScriptState(SCRIPTSTATE_INITIALIZED);
		if (SUCCEEDED(hr))
		{
			BSTR text;
			m_textData->get_data(&text);

			EXCEPINFO	excepinfo;

			hr = scriptParse->ParseScriptText(
				text,
				NULL,
				NULL,
				NULL,
				0,
				0,
				0,	// Flags
				NULL,
				&excepinfo);

			//m_activeScript->Close();
		}
		else
			ATLASSERT(0);
	}

	Fire_doneParsingDOM();
}

HRESULT __stdcall CEScriptDocument::OnTextDocumentContentChanged()
{
	TextChanged();
	return S_OK;
}

HRESULT __stdcall CEScriptDocument::OnTextDocumentInsertedText(long offset, long len)
{
	TextChanged();
	return S_OK;
}

HRESULT __stdcall CEScriptDocument::OnTextDocumentDeletedText(long offset, long len)
{
	TextChanged();
	return S_OK;
}

STDMETHODIMP CEScriptDocument::GetLCID(/* [out] */ LCID __RPC_FAR *plcid)
{
	return S_OK;
}

STDMETHODIMP CEScriptDocument::GetItemInfo(/* [in] */ LPCOLESTR pstrName, /* [in] */ DWORD dwReturnMask,/* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiunkItem,/* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppti)
{
	return S_OK;
}

STDMETHODIMP CEScriptDocument::GetDocVersionString(/* [out] */ BSTR __RPC_FAR *pbstrVersion)
{
	return S_OK;
}

STDMETHODIMP CEScriptDocument::OnScriptTerminate(/* [in] */ const VARIANT __RPC_FAR *pvarResult,/* [in] */ const EXCEPINFO __RPC_FAR *pexcepinfo)
{
	return S_OK;
}

STDMETHODIMP CEScriptDocument::OnStateChange(/* [in] */ SCRIPTSTATE ssScriptState)
{
	return S_OK;
}

STDMETHODIMP CEScriptDocument::OnScriptError(/* [in] */ IActiveScriptError __RPC_FAR *pscripterror)
{
	DWORD dwSourceContext;
	ULONG ulLineNumber;
	LONG ichCharPosition;

	pscripterror->GetSourcePosition(&dwSourceContext, &ulLineNumber, &ichCharPosition);

	EXCEPINFO	excepinfo = {0};
	pscripterror->GetExceptionInfo(&excepinfo);

	if (!excepinfo.bstrDescription)
	{
		if (excepinfo.pfnDeferredFillIn)
		{
			excepinfo.pfnDeferredFillIn(&excepinfo);
		}
	}

	CString str;
	str.Format("%S", excepinfo.bstrDescription);

	CError* pError = new CError;

	pError->m_severity = LSEVERITY_FATAL_ERROR;
	pError->m_message = str;
	pError->m_line = ulLineNumber;
	pError->m_column = ichCharPosition;
	pError->m_offset = 0;	// TODO, calculate
	//pError->m_uri = 

	m_errors.Add(pError);

	return S_OK;
}

STDMETHODIMP CEScriptDocument::OnEnterScript( void)
{
	return S_OK;
}

STDMETHODIMP CEScriptDocument::OnLeaveScript( void)
{
	return S_OK;
}

BEGIN_CMD_MAP(CEScriptDocument)
// File
//	CMD_HANDLER(ID_FILE_SAVE, OnFileSave)
//	CMD_HANDLER(ID_FILE_SAVE_AS, OnFileSaveAs)

// Edit
//	CMD_HANDLER(ID_EDIT_UNDO, OnEditUndo)
//	CMD_UPDATE(ID_EDIT_UNDO, OnEditUndoUpdate)
//	CMD_HANDLER(ID_EDIT_REDO, OnEditRedo)
//	CMD_UPDATE(ID_EDIT_REDO, OnEditRedoUpdate)

// Window
	CMD_HANDLER(ID_WINDOW_NEW, OnWindowNew)
END_CMD_MAP()

LRESULT CEScriptDocument::OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
//	NewWindow();
	return 0;
}

STDMETHODIMP CEScriptDocument::Activate()
{
	// TODO: Add your implementation code here

	return S_OK;
}

#endif