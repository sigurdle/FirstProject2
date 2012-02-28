// HTMLFramesDesignView.cpp : Implementation of CHTMLFramesDesignView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "HTMLFramesDesignView.h"

#if 0

//#include "HTMDocumentFrames.h"

/////////////////////////////////////////////////////////////////////////////
// CHTMLFramesDesignView

#if 0
void CHTMLFramesDesignView::BuildFrames()
{
	delete m_pFrameSet;
	m_pFrameSet = NULL;

	CComQIPtr<IWebXMLDocument> document;
	get_document(&document);

	CComPtr<ILDOMDocument> doc;
	document->get_DOMDocument(&doc);

	CComQIPtr<ILHTMLDocument> htmldoc = doc;
	if (htmldoc)
	{
		CComQIPtr<ILHTMLElement> documentElement;
		htmldoc->get_documentElement((ILDOMElement**)&documentElement);

		if (documentElement)
		{
			ILDOMElement* pFrameSetElement = FindByTagName(documentElement, L"frameset");

			if (pFrameSetElement)
			{
				m_pFrameSet = new CHTMDesignFrameSet;
			//	m_pFrameSet->m_pDocument = GetDoc();
				m_pFrameSet->CreateFrames(pFrameSetElement);
			}
		}
	}
}
#endif

STDMETHODIMP CHTMLFramesDesignView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	if (bActivate)
	{
	//	CComPtr<IDocumentsClass> documentsClass;
	//	m_document->GetDocumentsClass(&documentsClass);

	//	uiManager->ActivateObject(documentsClass, m_document);
	//	uiManager->ActivateObject(m_document, m_viewGroup);
		uiManager->ActivateObject(m_viewGroup, GetUnknown());

//		m_objectSelection->FromTargets(m_targetObjects.GetData(), m_targetObjects.GetSize());
//		uiManager->ActivateObject(GetUnknown(), m_objectSelection->GetUnknown());
	}
	else
	{
		uiManager->DeactivateObject(GetUnknown());
	//	uiManager->DeactivateObject(m_viewGroup);
	//	uiManager->DeactivateObject(m_document);
	}
#endif

	return S_OK;
}

long CHTMLFramesDesignView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	if (TRUE)
	{
#if 0
		IMoniker* _pmkfile;
		HRESULT hr = CreateFileMoniker(filePath, &_pmkfile);

		hr = CreateBindCtx(0, &m_pbctx);

		if (StgIsStorageFile(filePath) == S_OK)
		{
			/*
			FORMATETC fetc;
			fetc.cfFormat = 0;
			fetc.ptd = NULL;
			fetc.dwAspect = DVASPECT_CONTENT;
			fetc.lindex = -1;
			fetc.tymed = TYMED_ISTORAGE;
			*/

			HRESULT hr;

    /*
     * 7.  Create a temp file for all embedded files.  Note that in this
     *     sample we don't save any changes to DocObjects because we 
	 *     don't manage any storage directly.
	 */	  
			 if (FAILED(StgCreateDocfile(NULL, STGM_TRANSACTED | STGM_READWRITE
				  | STGM_SHARE_EXCLUSIVE | STGM_CREATE| STGM_DELETEONRELEASE
				  , 0, &m_pIStorage)))
				  return FALSE;

			 /*
			CComPtr<IStorage> stg;
			hr = StgOpenStorage(
				L"C:\\test.doc",
				NULL,
				STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
				NULL,
				0,
				&stg);
				*/

			{
			 DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
								  | STGM_SHARE_EXCLUSIVE;
			 TCHAR       szName[32];

//			 IStorage* pIStorage = m_pIStorage;
//			 if (NULL==pIStorage)
//				  return FALSE;

			 /*
			  * Attempt to open the storage under this ID.  If there is
			  * none, then create it.  In either case we end up with an
			  * IStorage that we either save in pPage or release.
			  */
			 wsprintf(szName, TEXT("Site %lu"), 1);

			#ifdef UNICODE
			 hr=m_pIStorage->CreateStorage(szName, dwMode, 0, 0, &m_pIStorage2);
			#else
			 OLECHAR  szwName[32];
			MultiByteToWideChar(CP_ACP, 0, szName, -1, szwName, 32);    
			 hr=m_pIStorage->CreateStorage(szwName, dwMode, 0, 0, &m_pIStorage2);
			#endif

			 if (FAILED(hr))
				  return FALSE;

			//Create stream for the object; name is irrelevant
			dwMode=STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
			#ifdef UNICODE
			 hr=m_pIStorage2->CreateStream(TEXT("\003DocObjInfo"), dwMode, 0, 0
				  , &m_pIStream);
			#else    
			MultiByteToWideChar(CP_ACP, 0, "\003DocObjInfo", -1, szwName, 32);    
			 hr=m_pIStorage2->CreateStream(szwName, dwMode, 0, 0, &m_pIStream);
			#endif
   
			 //If we failed to create a stream in the file, do it in memory
			if (FAILED(hr))
				{
				if (FAILED(CreateStreamOnHGlobal(NULL, TRUE, &m_pIStream)))
					 return FALSE;
				}
			}

			char* pszFile = "C:\\test.doc";

			 //Now create an object from the file
			#ifdef UNICODE    
			 hr=OleCreateFromFile(CLSID_NULL, pszFile, IID_IUnknown
				  , OLERENDER_NONE, NULL, NULL, m_pIStorage2, (void **)&pObj);
			#else
			 OLECHAR     szFile[512];    //Assumption on string length

			 MultiByteToWideChar(CP_ACP, 0, pszFile, -1, szFile, 512);    
			hr=OleCreateFromFile(CLSID_NULL, szFile, IID_IUnknown
				  , OLERENDER_NONE, NULL, NULL, m_pIStorage2, (void **)&m_spUnknown);
			#endif

		//	hr = OleCreateFromFile(CLSID_NULL, L"C:\\test.doc", IID_IOleObject,
		//		OLERENDER_NONE, &fetc, NULL, stg, (void**)&spOleObject);

			m_dwAdvise = 0;

			if (SUCCEEDED(hr))
			{
				m_spOleObject = m_spUnknown;
				m_spOleDocument = m_spUnknown;

				m_spOleObject->SetClientSite(this);
				m_spOleObject->Advise(this, &m_dwAdvise);

				OleRun(m_spUnknown);

				CRect rc;
				GetClientRect(&rc);
				m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, hwnd, &rc);
			}
			else
			{
				ATLTRACE("OleCreateFromFile()=%ld\n", hr);
				::MessageBox(NULL, "Failed to create document", "", MB_OK);
			}
		}
		else
#endif
		{
//			CLSID rclsid = CLSID_HTMLDOCUMENT;
			CLSID rclsid = CLSID_LHTMLActiveDocument;
			 IPersistStorage*    pipstg  = NULL;

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
			CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;
			if (htmlActiveDoc)
			{
				CComPtr<ILDOMDocument> xmldocument;
				m_document->get_DOMDocument(&xmldocument);

				htmlActiveDoc->SetDocument(xmldocument);
			//	htmlActiveDoc->SetElement(m_viewGroup->m_outerElement);

#if 0
				HRESULT hr = IDispEventImpl<4, CSvgLayoutView, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib, 1, 0>::DispEventAdvise(htmlActiveDoc);
				ASSERT(SUCCEEDED(hr));
#endif
			}


		 // Check if the object could not be initialized...
			 //if (FAILED(hr)) {punk->Release(); return FALSE;}

		 // We need IOleObject so ask. If object doesn't support it we should fail...
				m_spOleObject = m_spUnknown;
				if (m_spOleObject == NULL)
				{
					ASSERT(0);
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
		}
	}

	::RegisterDragDrop(m_hWnd, this);

#if 0
	BuildFrames();
#endif
#endif

	return 0;
}

long CHTMLFramesDesignView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = m_hWnd;

	RevokeDragDrop(hwnd);

	HRESULT hr;

	CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;
	if (htmlActiveDoc)
	{
#if 0
		hr = IDispEventImpl<4, CSvgLayoutView, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib, 1, 0>::DispEventUnadvise(htmlActiveDoc);
		ASSERT(SUCCEEDED(hr));
#endif
	}

	m_pIOleDocView->SetInPlaceSite(NULL);
	//m_spOleObject->Unadvise(m_dwAdvise);
	hr = m_spOleObject->SetClientSite(NULL);

	return 0;
}

long CHTMLFramesDesignView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CHTMLFramesDesignView::OnSize()
{
	CRect client;
	GetClientRect(&client);

	CRect rc = client;
	/*
	//Tell the in-place object about the new frame size
	
	  if (pFrame->m_pIOleIPActiveObject != NULL)
	  pFrame->m_pIOleIPActiveObject->ResizeBorder(&rc, this, FALSE);
	*/
	
	/*
	* Resize the client, which is done in all cases since this window
	* is the parent of the DocObject, plus we need to tell the 
	* DocObject of the new size through IOleDocumentView::SetRect.
	*/
	if (m_pIOleDocView != NULL)
	{
		m_pIOleDocView->SetRect(&rc);
	}

#if 0
	if (m_pFrameSet)
	{
		m_pFrameSet->m_client = client;
		m_pFrameSet->PositionFrames();
	}
#endif
}

long CHTMLFramesDesignView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

#if 0
	CRect client;
	GetClientRect(&client);

	FillSolidRect(dc.m_hDC, &client, GetSysColor(COLOR_BTNFACE));

	if (m_pFrameSet)
	{
		m_pFrameSet->OnPaint(dc.m_hDC);
	}
#endif

	return 0;
}

STDMETHODIMP CHTMLFramesDesignView::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

STDMETHODIMP CHTMLFramesDesignView::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CHTMLFramesDesignView::DragLeave()
{
	return S_OK;
}

STDMETHODIMP CHTMLFramesDesignView::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	ScreenToClient(&point);

#if 0
	if (m_pFrameSet)
	{
		COleDataObjectWrapper dataObject;
		dataObject.Attach(pDataObject);

		HGLOBAL hData;

		if (hData = dataObject.GetGlobalData(CF_HDROP))
		{
			DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
			if (dp)
			{
				char* p = (char*)(dp+1);

				int i = 0;
				TCHAR filename[512];
				while (*p)
				{
					filename[i++] = *p++;
				}
				filename[i] = 0;
	
				CHTMDesignFrame* pFrame = NULL;
				m_pFrameSet->OnButtonDown(0, point, 0, FALSE, &pFrame);
				if (pFrame)
				{
					pFrame->m_pElement->setAttribute(L"src", _bstr_t(filename));
					//m_pDocument->CreateHTMLTree();
					//m_pDocument->UpdateAllViews(NULL);
				}
			}

			GlobalUnlock(hData);

			{
				BuildFrames();

				OnSize();
				InvalidateRect(NULL, TRUE);
			}

			*pdwEffect = DROPEFFECT_COPY;
		}
		else if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("MMStudio-HTML-FramePreset")))
		{
			ASSERT(0);
#if 0
			char* text = (char*)GlobalLock(hData);
			long len = GlobalSize(hData);

			CHTMDoc* pDoc = new CHTMDoc;
			pDoc->m_pText = new CHTMDocument;
			pDoc->m_pText->m_pHTMDoc = pDoc;
			pDoc->m_pText->m_textData = text;
			pDoc->m_pText->m_textLen = len;

			pDoc->parseText();

			CHTMElement* pFrameSetElement;
			if (!stricmp(pDoc->m_documentElement->m_tagName, "FRAMESET"))
				pFrameSetElement = pDoc->m_documentElement;
			else
				pFrameSetElement = pDoc->m_documentElement->selectSingleNode("FRAMESET");

			if (pFrameSetElement)
			{
				CHTMDesignFrame* pFrame = NULL;
				m_pDocument->m_pFrameSet->OnButtonDown(0, point, 0, FALSE, &pFrame);
				if (pFrame)
				{
					pFrame->m_pElement->SetOuterHTML(pFrameSetElement->GetOuterHTML());

					m_pDocument->CreateHTMLTree();
					m_pDocument->UpdateAllViews(NULL);
				}
			}

			pDoc->m_pText->m_textData = NULL;
			pDoc->m_pText->m_textLen = 0;

			delete pDoc->m_pText;
			delete pDoc;

			GlobalUnlock(hData);
			return TRUE;
#endif
		}
	}
#endif

	return S_OK;
}

STDMETHODIMP CHTMLFramesDesignView::get_document(IEXMLDocument **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

/*
STDMETHODIMP CHTMLFramesDesignView::put_document(IWebXMLDocument *newVal)
{
	m_document = newVal;
	return S_OK;
}
*/

///////////////////////////
///////////////////////////

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
HRESULT STDMETHODCALLTYPE CHTMLFramesDesignView::ActivateMe(/* [in] */ IOleDocumentView __RPC_FAR *pView)
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
		
		if (FAILED(pDoc->CreateView(this/*m_pSite->m_pImpIOleIPSite*/, m_pIStream, 0, &pView)))
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

// Put the view in Frames Design Mode
	CComQIPtr<ILHTMLActiveView> activeView = pView;
	activeView->put_framesDesign(VARIANT_TRUE);

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
HRESULT STDMETHODCALLTYPE CHTMLFramesDesignView::OnInPlaceActivate( void)
{
   m_pIOleIPObject = m_spUnknown;
	ASSERT(m_pIOleIPObject != NULL);
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

HRESULT STDMETHODCALLTYPE CHTMLFramesDesignView::GetWindowContext( 
																	/* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame,
																	/* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc,
																	/* [out] */ LPRECT prcPos,
																	/* [out] */ LPRECT prcClip,
																	/* [out][in] */ LPOLEINPLACEFRAMEINFO pFI)
{
#if 0
//	CComQIPtr<IWebEditorFrame> frame;
//	gApp->m_frame;get_frame(&frame);

	*ppFrame = gApp->m_frame;
//	frame->QueryInterface(IID_IOleInPlaceFrame, (void**)ppFrame);
//	ASSERT(*ppFrame != NULL);
	(*ppFrame)->AddRef();

	//*ppDoc = NULL;
	*ppDoc = this;
	(*ppDoc)->AddRef();
//	QueryInterface(IID_IOleInPlaceUIWindow, (void**)ppDoc);
//	ASSERT(*ppDoc != NULL);

	if (prcPos != NULL) GetClientRect(prcPos);
	*prcClip=*prcPos;
	
	pFI->cb=sizeof(OLEINPLACEFRAMEINFO);
	pFI->fMDIApp=TRUE;
// ??
	pFI->hwndFrame = gApp->m_frame->m_hWnd;//frame->get_hwnd(&pFI->hwndFrame);//=m_pSite->m_pFR->Window();

	pFI->haccel=NULL;//m_pSite->m_pFR->Accelerators();
	pFI->cAccelEntries=0;//CACCELERATORS;
#endif

	return NOERROR;
}

BEGIN_CMD_MAP(CHTMLFramesDesignView)
END_CMD_MAP()

#if 0
// ICommandTarget
STDMETHODIMP CHTMLFramesDesignView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	CComQIPtr<ICommandTarget> target;
	
// Try viewgroup first
	target = m_viewGroup;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Then try us
	return ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
}
#endif

#endif