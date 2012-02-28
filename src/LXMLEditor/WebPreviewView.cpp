// WebPreviewView.cpp : Implementation of CWebPreviewView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "WebEditor2.h"
#include "WebPreviewView.h"

#include "WebXMLViewGroup.h"

#include "WebEditorApp.h"
#include "WebEditorFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CWebPreviewView

STDMETHODIMP CWebPreviewView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	if (bActivate)
	{
		uiManager->ActivateObject(NULL, m_document);
		uiManager->ActivateObject(m_document, m_viewGroup->GetUnknown());
		uiManager->ActivateObject(m_viewGroup->GetUnknown(), GetUnknown());

		long modified;
		m_document->GetModified(&modified);

		if (modified != m_modifiedSinceLast)
		{
			CComPtr<ITextData> textData;
#if 0
			m_document->get_textDocument(&textData);
#endif
			_bstr_t filepath = L"C:\\preview.html";

			textData->save(filepath);

			VARIANT_BOOL bsuccess;
		//	m_webControl->GotoLocation(filepath, &bsuccess);
		//	m_spWebBrowser->GotoLocation(filepath, &bsuccess);

			CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;
			if (htmlActiveDoc)
			{
				htmlActiveDoc->GotoLocation(filepath, &bsuccess);
			}

			m_modifiedSinceLast = modified;
		}
	}
	else
	{
		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(m_viewGroup->GetUnknown());
		uiManager->DeactivateObject(m_document);
	}
#endif
	return S_OK;
}

LRESULT CWebPreviewView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gApp->m_frame;

/*
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axwebControl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axwebControl.AttachControl(m_webControl, &p);
*/

#if 0
	// Create the WebBrowser control
	CComPtr<IOleObject> spOleObject;
	HRESULT hr = CoCreateInstance(CLSID_LHTMLActiveDocument, NULL, CLSCTX_INPROC, IID_IOleObject,
											(void**)&spOleObject);
	if (hr != S_OK)
	{
		MessageBox(_T("CoCreateInstance failed"));
		return E_FAIL;
	}

	if (spOleObject->SetClientSite(this) != S_OK)
	{
		MessageBox(_T("SetClientSite failed"));
		return E_FAIL;
	}

	CRect rcClient;
	// In-place activate the WebBrower control
	MSG msg;
	GetClientRect(&rcClient);

	hr = spOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, &msg, this, 0, m_hWnd, &rcClient);
	if (hr != S_OK)
	{
		MessageBox(_T("DoVerb failed"));
		return E_FAIL;
	}

	// Get the pointer to the WebBrowser control.  Note that setting a CComQIPtr
	// equal to a pointer of another type causes CComQIPtr to call QueryInterface.
	m_spWebBrowser = spOleObject;
	_ASSERT(m_spWebBrowser);

	if (!m_spWebBrowser)
		return E_FAIL;

	// Set up the connection to the WebBrowser control to receive events
//	hr = AtlAdvise(m_spWebBrowser, GetUnknown(), DIID_DWebBrowserEvents2, &m_dwCookie);
//	if (FAILED(hr))
//		ATLTRACE(_T("Failed to Advise\n"));

	// Get the size of the status bar
//	RECT rcWindow;
//	m_wndStatusBar.GetWindowRect(&rcWindow);

	// Resize the control to accomodate the status bar and toolbar
//	rcClient.bottom -= (rcWindow.bottom - rcWindow.top);

//	m_wndToolBar.GetWindowRect(&rcWindow);
//	rcClient.top += (rcWindow.bottom - rcWindow.top);

	// QI for the in-place object to set the size
	m_spInPlaceObject = m_spWebBrowser;
	_ASSERT(m_spInPlaceObject);

	if (m_spInPlaceObject)
		m_spInPlaceObject->SetObjectRects(&rcClient, &rcClient);

	// QI for the IOleCommandTarget interface that will be used later
	m_spOleCmdTarg = m_spWebBrowser;
	_ASSERT(m_spOleCmdTarg);
#endif

	// Load Test Page
//	m_spWebBrowser->GotoLocation(L"res://edhost.exe/test.html", NULL, NULL, NULL, NULL);

	{
			CLSID rclsid = CLSID_LHTMLActiveDocument;
		//	 IPersistStorage*    pipstg  = NULL;

		 // Don't load if an object has already been loaded...
			 //if ((!_pstgfile) || (_poleobj)) return FALSE;

		 // Create an inproc handler and load the data from IStorage...
			HRESULT hr = CoCreateInstance(rclsid, NULL, CLSCTX_ALL, IID_IUnknown, (void**)&m_spUnknown);
			 //if (FAILED(hr) || (NULL == punk)) return FALSE;

		 // Load the data using IPersistStorage...
			/*
			 hr = m_spUnknown->QueryInterface(IID_IPersistStorage, (void**)&pipstg);
			if (SUCCEEDED(hr))
			 {
			  // If we opened a file and have moniker, load from existing data...
				  if (_pmkfile)
					  hr = pipstg->Load(_pstgfile);
				  else
					  hr = pipstg->InitNew(_pstgfile);

				pipstg->Release();
			 }
			 else
			 */
			/*
			 {
				  IPersistFile* pipf = NULL;
				  LPOLESTR  pwszDisplayName = NULL;

				  hr = _pmkfile->GetDisplayName(m_pbctx, NULL, &pwszDisplayName);
				  if (SUCCEEDED(hr))
				  {
						hr = m_spUnknown->QueryInterface(IID_IPersistFile, (void**)&pipf);
						if (SUCCEEDED(hr))
						{
							 pipf->Load(pwszDisplayName, STGM_READ);
							 pipf->Release();
						}
						CoTaskMemFree(pwszDisplayName);
				  }
			 }
			 */

			// Had loading here


		 // Check if the object could not be initialized...
			 //if (FAILED(hr)) {punk->Release(); return FALSE;}

		 // We need IOleObject so ask. If object doesn't support it we should fail...
				m_spOleObject = m_spUnknown;
				if (m_spOleObject == NULL)
				{
					ATLASSERT(0);
				}

		//	 hr = punk->QueryInterface(IID_IOleObject, (void **)&_poleobj);
		//	 punk->Release(); // Release punk here just in case...
		//	 if (FAILED(hr)) return FALSE;

		 // Fudge factor -- if you make the following calls too quickly, PPT will hang...
			// Sleep(250);

		 // Run the object (object must support IRunnableObject)...
			OleRun(m_spOleObject);

		 // SetClientSite is critical for DocObjects. If this fails the
		 // object doesn't support inplace activation!!
			hr = m_spOleObject->SetClientSite(static_cast<IOleClientSite*>(this));
			/*
			 if (FAILED(hr))
			 {
				  _poleobj->Release();
				  _poleobj = NULL;
				  return FALSE;
			 }
			 */

		 // Lock the object in memory and make a few housekeeping calls...
			 OleLockRunning(m_spOleObject, TRUE, FALSE);

			// m_spOleObject->SetHostNames(L"Framer Ex", _bstrDocName);
			 m_spOleObject->Advise(static_cast<IAdviseSink*>(this), &m_dwAdvise);
			 
			 CRect rc;
			 GetClientRect(&rc);
			 m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, m_hWnd, &rc);

			// Didn't have loading here
			CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;
			if (htmlActiveDoc)
			{
#if 0
				CComPtr<IDOMDocumentContainer> documentcnt;
				m_document->get_documentContainer(&documentcnt);
				htmlActiveDoc->SetDocumentContainer(documentcnt);
#endif
			//	CComPtr<ILDOMDocument> xmldocument;
			//	m_document->get_DOMDocument(&xmldocument);

		//		htmlActiveDoc->SetDocument(xmldocument);
				//htmlActiveDoc->SetElement(m_viewGroup->m_outerElement);

				//HRESULT hr = IDispEventImpl<4, CSvgLayoutView, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib, 1, 0>::DispEventAdvise(htmlActiveDoc);
				//ATLASSERT(SUCCEEDED(hr));
			}
		}

	return 0;
}

LRESULT CWebPreviewView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;
	if (htmlActiveDoc)
	{
	//	hr = IDispEventImpl<4, CSvgLayoutView, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib, 1, 0>::DispEventUnadvise(htmlActiveDoc);
	//	ATLASSERT(SUCCEEDED(hr));
	}

	m_pIOleDocView->SetInPlaceSite(NULL);
	//m_spOleObject->Unadvise(m_dwAdvise);
	m_spOleObject->SetClientSite(NULL);

	return 0;
}

LRESULT CWebPreviewView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect	client;
	GetClientRect(&client);
	
	if (m_pIOleDocView != NULL)
	{
		CRect rc = client;
	     m_pIOleDocView->SetRect(&rc);
	}
	
	return 0;
}

long CWebPreviewView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

/*
 * CImpIOleDocumentsite::ActivateMe
 *
 * Purpose:
 *  Instructs the container to activate the object in this site as
 *  a document object.
 *
 * Parameters:
 *  pView           IOleDocumentView * of the object to activate.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, error code otherwise.
 */
HRESULT STDMETHODCALLTYPE CWebPreviewView::ActivateMe(/* [in] */ IOleDocumentView __RPC_FAR *pView)
{
	RECT                rc;
	IOleDocument*       pDoc;
	
	/*
	* If we're passed a NULL view pointer, then try to get one from
	* the document object (the object within us).
	*/
	if (pView == NULL)
	{
		if (FAILED(m_spUnknown->QueryInterface(IID_IOleDocument, (void **)&pDoc)))
			return E_FAIL;
		
		if (FAILED(pDoc->CreateView(this/*m_pSite->m_pImpIOleIPSite*/, NULL/*m_pIStream*/, 0, &pView)))
			return E_OUTOFMEMORY;
		
		// Release doc pointer since CreateView is a good com method that addrefs
		pDoc->Release();
	}        
	else
	{
		//Make sure that the view has our client site
		pView->SetInPlaceSite(this/*m_pSite->m_pImpIOleIPSite*/);

		////We're holding onto the pointer, so AddRef it.
		//pView->AddRef();
	}
	
	
	/*
	* Activation steps, now that we have a view:
	*
	*  1.  Call IOleDocumentView::SetInPlaceSite (assume done since
	*      either the view already knows, or IOleDocument::CreateView
	*      has done it already.
	*
	*  2.  Call IOleDocumentView::SetRect to give a bunch of space to
	*      the view.  In our case this is the whole client area of
	*      the CPages window.  (Patron doesn't use SetRectComplex)
	*
	*  3.  Call IOleDocumentView::Show to make the thing visible.
	*
	*  4.  Call IOleDocumentView::UIActivate to finish the job.
	*
	*/
	
	m_pIOleDocView = pView;	// Hold on to view

#if 0
	m_pSite->m_fDocObj=TRUE;
	m_pSite->m_pIOleDocView=pView;
	
#endif

	//This sets up toolbars and menus first    
	pView->UIActivate(TRUE);

	//Set the window size sensitive to new toolbars
	GetClientRect(&rc);
	pView->SetRect(&rc);

	//Makes it all active
	pView->Show(TRUE);    
	return NOERROR;
}

/*
 * CImpIOleInPlaceSite::OnInPlaceActivate
 *
 * Purpose:
 *  Informs the container that an object is being activated in-place
 *  such that the container can prepare appropriately.  The
 *  container does not, however, make any user interface changes at
 *  this point.  See OnUIActivate.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */
HRESULT STDMETHODCALLTYPE CWebPreviewView::OnInPlaceActivate( void)
{
   m_pIOleIPObject = m_spUnknown;
	ATLASSERT(m_pIOleIPObject != NULL);
		//pSite->m_pObj->QueryInterface(IID_IOleInPlaceObject
  //      , (void **)&m_pSite->m_pIOleIPObject);

    return NOERROR;
}

/*
 * CImpIOleInPlaceSite::GetWindowContext
 *
 * Purpose:
 *  Provides an in-place object with pointers to the frame and
 *  document level in-place interfaces (IOleInPlaceFrame and
 *  IOleInPlaceUIWindow) such that the object can do border
 *  negotiation and so forth.  Also requests the position and
 *  clipping rectangles of the object in the container and a
 *  pointer to an OLEINPLACEFRAME info structure which contains
 *  accelerator information.
 *
 *  Note that the two interfaces this call returns are not
 *  available through QueryInterface on IOleInPlaceSite since they
 *  live with the frame and document, but not the site.
 *
 * Parameters:
 *  ppIIPFrame      LPOLEINPLACEFRAME * in which to return the
 *                  AddRef'd pointer to the container's
 *                  IOleInPlaceFrame.
 *  ppIIPUIWindow   LPOLEINPLACEUIWINDOW * in which to return
 *                  the AddRef'd pointer to the container document's
 *                  IOleInPlaceUIWindow.
 *  prcPos          LPRECT in which to store the object's position.
 *  prcClip         LPRECT in which to store the object's visible
 *                  region.
 *  pFI             LPOLEINPLACEFRAMEINFO to fill with accelerator
 *                  stuff.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

HRESULT STDMETHODCALLTYPE CWebPreviewView::GetWindowContext( 
																	/* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame,
																	/* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc,
																	/* [out] */ LPRECT prcPos,
																	/* [out] */ LPRECT prcClip,
																	/* [out][in] */ LPOLEINPLACEFRAMEINFO pFI)
{
//	CComQIPtr<IWebEditorFrame> frame;
//	gApp->m_frame;get_frame(&frame);

	*ppFrame = gApp->m_frame;
//	frame->QueryInterface(IID_IOleInPlaceFrame, (void**)ppFrame);
//	ATLASSERT(*ppFrame != NULL);
	(*ppFrame)->AddRef();

	//*ppDoc = NULL;
	*ppDoc = this;
	(*ppDoc)->AddRef();
//	QueryInterface(IID_IOleInPlaceUIWindow, (void**)ppDoc);
//	ATLASSERT(*ppDoc != NULL);

	if (prcPos != NULL) GetClientRect(prcPos);
	*prcClip=*prcPos;
	
	pFI->cb=sizeof(OLEINPLACEFRAMEINFO);
	pFI->fMDIApp=TRUE;
// ??
	pFI->hwndFrame = gApp->m_frame->m_hWnd;//frame->get_hwnd(&pFI->hwndFrame);//=m_pSite->m_pFR->Window();

	pFI->haccel=NULL;//m_pSite->m_pFR->Accelerators();
	pFI->cAccelEntries=0;//CACCELERATORS;

	return NOERROR;
}

STDMETHODIMP CWebPreviewView::GetInMemoryDocument(BSTR uri, ILDOMDocument* *pVal)
{
	ATLASSERT(pVal);
	if (pVal == NULL) return E_POINTER;
#if 0
	CComQIPtr<IEDocument> document;

	for (int i = 0; i < gApp->m_documents.GetSize(); i++)
	{
		BSTR pathName2;
		gApp->m_documents[i]->get_filePath(&pathName2);
		if (!wcsicmp(uri, pathName2))
		{
			document = gApp->m_documents[i];
			break;
		}
	}

	CComQIPtr<IEXMLDocument> xmldocument = document;
	if (xmldocument)
	{
		return xmldocument->get_DOMDocument(pVal);
	}
	else
		*pVal = NULL;
#endif
	return S_OK;
}
