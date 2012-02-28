// TODO, remove this file

// DTDDocument.cpp : Implementation of CDTDDocument
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "DTDDocument.h"

//#include "DTDGridView.h"
#include "SourceView.h"
#include "DTDView.h"
#include "ASElementsTreeView.h"

#if 0

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CDTDDocument

CEDTDDocument::CEDTDDocument()
{
	m_bSourceEditLast = true;	// Consider right after opening document as a source edit
	m_lockDOM = 0;
	m_lockSource = 0;
}

#if 0
int CEDTDDocument::FinalConstruct()
{
	HRESULT hr;

	hr = m_textData.CoCreateInstance(CLSID_TextData);
	if (FAILED(hr)) hr;

//	ASSERT(0);
//	hr = m_undoManager.CoCreateInstance(CLSID_WEUndoManager);
//	if (FAILED(hr)) return E_NOINTERFACE;

//
#if 0
	hr = m_dtdModel.CoCreateInstance(L"ASDTDMod.ASDTDModel"/*CLSID_ASDTDModel*/);
	if (FAILED(hr)) return hr;
#endif

	hr = m_dtdDocument.CoCreateInstance(CLSID_LDTDDocument);
	if (FAILED(hr)) return hr;

	m_dtdDocument->put_errorHandler(static_cast<ILDOMErrorHandler*>(this));

	m_dtdModel.CoCreateInstance(CLSID_ASDTDModel);

//	m_dtdModel->put_sourceTextDoc(m_textDocument);
//	m_dtdModel->put_errorHandler(static_cast<ILDOMErrorHandler*>(this));
///

	return S_OK;
}

void CEDTDDocument::FinalRelease()
{
	if (m_dtdDocument)
	{
		m_dtdDocument.Release();
	}

	if (m_textData)
	{
		IDispEventImpl<1, CEDTDDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>::DispEventUnadvise(m_textData);
		m_textData.Release();
	}
}
#endif

STDMETHODIMP CEDTDDocument::get_undoManager(/*[out, retval]*/ IUndoManager* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_undoManager;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

void CEDTDDocument::Prepare()
{
	HRESULT hr;

	ASSERT(0);
#if 0
	hr = IDispEventImpl<1, CEDTDDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>::DispEventAdvise(m_textData);
	ASSERT(SUCCEEDED(hr));

#if 0
	hr = IDispEventImpl<2, CDTDDocument, &DIID__IDTDModelEvents, &LIBID_ASDTDMODLib, 1, 0>::DispEventAdvise(m_dtdModel);
	ASSERT(SUCCEEDED(hr));
#endif
#endif
}

STDMETHODIMP CEDTDDocument::NewDocument()
{
	CEDocumentImpl<CEDTDDocument>::NewDocument();
	Prepare();

	return S_OK;
}

// IPersist
STDMETHODIMP CEDTDDocument::GetClassID(CLSID __RPC_FAR *pClassID)
{
	return E_NOTIMPL;
}

// IPersistFile
STDMETHODIMP CEDTDDocument::IsDirty( void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEDTDDocument::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
	HRESULT hr;

	hr = CEDocumentImpl<CEDTDDocument>::LoadDocument(_bstr_t(pszFileName));

	if (FAILED(hr))
		return hr;

	Prepare();

	m_lockSource++;

	VARIANT_BOOL bsuccess;
	/*
	m_dtdModel->parse(&bsuccess);	// ??????????
	*/

	ASSERT(0);
#if 0
	m_dtdDocument->parseTextData(m_textData, &bsuccess);

	m_dtdModel->load(_bstr_t(pszFileName), &bsuccess);	// TODO remove
#endif

	m_lockSource--;

#if 0
	Fire_doneParsingDOM();
#endif

	if (bsuccess)
	{
	}

	return S_OK;
}

STDMETHODIMP CEDTDDocument::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEDTDDocument::SaveCompleted(LPCOLESTR pszFileName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEDTDDocument::GetCurFile(LPOLESTR __RPC_FAR *ppszFileName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEDTDDocument::LoadDocumentByteArray(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success)
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

#include "DTDViewGroup.h"

void CEDTDDocument::NewWindow()
{
#if 0
//	CComQIPtr<IUIManager> uiManager = gApp->m_uiManager;

	{
		CComObject<CDTDViewGroup>* child;
		CComObject<CDTDViewGroup>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		child->m_pDocument = this;

		{
		// GridView
			CComObject<CDTDGridView>* xmlgridView;
			CComObject<CDTDGridView>::CreateInstance(&xmlgridView);
			if (xmlgridView)
			{
				gApp->m_frame->FindMenu(IDR_DTDGRIDVIEW, &xmlgridView->m_menu);
				xmlgridView->m_document = this;

				xmlgridView->m_viewGroup = child;
				child->m_views.Add(xmlgridView);

				child->AddPage(xmlgridView, NULL);
			}

		// DTD
			CComObject<CDTDView>* dtdView;
			CComObject<CDTDView>::CreateInstance(&dtdView);
			if (dtdView)
			{
				gApp->m_frame->FindMenu(IDR_SCHEMAVIEW, &dtdView->m_menu);
				dtdView->m_document = this;
				child->AddPage(dtdView, NULL);
			}

			/*
		// Source
			CComObject<CSourceView>* sourceView;
			CComObject<CSourceView>::CreateInstance(&sourceView);
			if (sourceView)
			{
				sourceView->m_document = this;
				child->AddPage(sourceView, NULL);
			}
			*/

		// TreeView
			/*
			CComObject<CASElementsTreeView>* treeView;
			CComObject<CASElementsTreeView>::CreateInstance(&treeView);
			if (treeView)
			{
				gApp->m_frame->FindMenu(IDR_ASTREEVIEW, &treeView->m_menu);
				treeView->m_document = (CComObject<CDTDDocument>*)this;
				child->AddPage(treeView, NULL);
			}
			*/
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}
#endif
}

STDMETHODIMP CEDTDDocument::ShowViews(IEFrame* pFrame)
{
	NewWindow();
	return S_OK;
}

HRESULT __stdcall CEDTDDocument::OnTextDocumentContentChanged()
{
	TextHasChangedReparse();
	return S_OK;
}

HRESULT __stdcall CEDTDDocument::OnTextDocumentInsertedText(long offset, long len)
{
	TextHasChangedReparse();
	return S_OK;
}

HRESULT __stdcall CEDTDDocument::OnTextDocumentDeletedText(long offset, long len)
{
	TextHasChangedReparse();
	return S_OK;
}

void CEDTDDocument::TextHasChangedReparse()
{
	if (m_lockDOM == 0)
//	if (m_bSourceEditLast == FALSE)
	{
		m_bSourceEditLast = TRUE;

		ClearErrors();

		m_lockSource++;
		VARIANT_BOOL bsuccess;
		ASSERT(0);
#if 0
		m_dtdModel->parse(&bsuccess);
#endif

		m_lockSource--;

		ASSERT(0);
#if 0
		Fire_doneParsingDOM();
#endif
	}
}

void __stdcall CEDTDDocument::OnModelChanged()
{
	UpdateSourceFromDOM();
}

void CEDTDDocument::UpdateSourceFromDOM()
{
// Update source text
	if (m_lockSource == 0)
	{
		m_lockDOM++;

		BSTR btext;
		ASSERT(0);
#if 0
		m_dtdModel->saveAsText(&btext);
#endif

		ASSERT(0);
#if 0
		m_textData->put_data(btext);
#endif
		m_lockDOM--;
	}
}

BEGIN_CMD_MAP(CEDTDDocument)
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

LRESULT CEDTDDocument::OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	NewWindow();
	return 0;
}

STDMETHODIMP CEDTDDocument::Activate()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CEDTDDocument::GetModified(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

/*
STDMETHODIMP CDTDDocument::GetDocumentsClass(IDocumentsClass **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
*/
#endif