#include "stdafx.h"
#include "HTML2.h"
#include "HTMLObjectElement.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// COleObjectSite

HRESULT COleObjectSite::Connect(bool bInited, IStream* pStream)
{
	ASSERT(m_spUnknown != NULL);

	HRESULT hr = S_OK;
	m_spUnknown->QueryInterface(IID_IOleObject, (void**)&m_spOleObject);
	if (m_spOleObject)
	{
		m_spOleObject->GetMiscStatus(DVASPECT_CONTENT, &m_dwMiscStatus);
		if (m_dwMiscStatus & OLEMISC_SETCLIENTSITEFIRST)
		{
			//CComQIPtr<IOleClientSite> spClientSite(GetControllingUnknown());
			m_spOleObject->SetClientSite(static_cast<IOleClientSite*>(this)/*spClientSite*/);
		}

#if 0
		CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> spPSI(m_spOleObject);
		if (!bInited && spPSI)
		{
			if (pStream)
				hr = spPSI->Load(pStream);
			else
				hr = spPSI->InitNew();
		}
#endif

		ASSERT(hr == 0);

		if (!(m_dwMiscStatus & OLEMISC_SETCLIENTSITEFIRST))
		{
			//CComQIPtr<IOleClientSite> spClientSite(GetControllingUnknown());
			m_spOleObject->SetClientSite(static_cast<IOleClientSite*>(this)/*spClientSite*/);
		}

		m_dwViewObjectType = 0;
		//HRESULT hr;
		hr = m_spOleObject->QueryInterface(IID_IViewObjectEx, (void**) &m_spViewObject);
		if (FAILED(hr))
		{
			hr = m_spOleObject->QueryInterface(IID_IViewObject2, (void**) &m_spViewObject);
			m_dwViewObjectType = 3;
		}
		else
			m_dwViewObjectType = 7;

		if (FAILED(hr))
		{
			hr = m_spOleObject->QueryInterface(IID_IViewObject, (void**) &m_spViewObject);
			m_dwViewObjectType = 1;
		}

		//CComQIPtr<IAdviseSink> spAdviseSink(this/*GetControllingUnknown()*/);
		m_spOleObject->Advise(static_cast<IAdviseSink*>(this)/*spAdviseSink*/, &m_dwOleObject);

		if (m_dwViewObjectType)
			m_spViewObject->SetAdvise(DVASPECT_CONTENT, 0, static_cast<IAdviseSink*>(this)/*spAdviseSink*/);
		m_spOleObject->SetHostNames(OLESTR("LXViewer"), NULL);
	}

	CComPtr<IObjectWithSite> spSite;
	m_spUnknown->QueryInterface(IID_IObjectWithSite, (void**)&spSite);
	if (spSite != NULL)
		spSite->SetSite(static_cast<IOleClientSite*>(this)/*GetControllingUnknown()*/);

	return hr;
}

HRESULT COleObjectSite::ActivateAx(HWND hWndParent/*bool bInited, IStream* pStream*/)
{
	m_hWndParent = hWndParent;

	ASSERT(m_spUnknown != NULL);

	HRESULT hr = S_OK;
//	m_spUnknown->QueryInterface(IID_IOleObject, (void**)&m_spOleObject);
	if (m_spOleObject)
	{
#if 0
		m_spOleObject->GetMiscStatus(DVASPECT_CONTENT, &m_dwMiscStatus);
		if(m_dwMiscStatus & OLEMISC_SETCLIENTSITEFIRST)
		{
			//CComQIPtr<IOleClientSite> spClientSite(GetControllingUnknown());
			m_spOleObject->SetClientSite(this/*spClientSite*/);
		}

		CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> spPSI(m_spOleObject);
		if (!bInited && spPSI)
		{
			if (pStream)
				spPSI->Load(pStream);
			else
				spPSI->InitNew();
		}

		if((m_dwMiscStatus & OLEMISC_SETCLIENTSITEFIRST) == 0)
		{
			//CComQIPtr<IOleClientSite> spClientSite(GetControllingUnknown());
			m_spOleObject->SetClientSite(this/*spClientSite*/);
		}

		m_dwViewObjectType = 0;
		HRESULT hr;
		hr = m_spOleObject->QueryInterface(IID_IViewObjectEx, (void**) &m_spViewObject);
		if (FAILED(hr))
		{
			hr = m_spOleObject->QueryInterface(IID_IViewObject2, (void**) &m_spViewObject);
			m_dwViewObjectType = 3;
		}
		else
			m_dwViewObjectType = 7;

		if (FAILED(hr))
		{
			hr = m_spOleObject->QueryInterface(IID_IViewObject, (void**) &m_spViewObject);
			m_dwViewObjectType = 1;
		}

		CComQIPtr<IAdviseSink> spAdviseSink(this/*GetControllingUnknown()*/);
		m_spOleObject->Advise(spAdviseSink, &m_dwOleObject);

		if (m_dwViewObjectType)
			m_spViewObject->SetAdvise(DVASPECT_CONTENT, 0, spAdviseSink);
		m_spOleObject->SetHostNames(OLESTR("MMStudio"), NULL);
#endif

		if (TRUE)
		{
			m_rcPos.left = 0;
			m_rcPos.top = 0;
			m_spOleObject->GetExtent(DVASPECT_CONTENT, &m_hmSize);
		}
		else
		{
#if 0
			GetClientRect(&m_rcPos);
			m_rcPos.left = 0;
			m_rcPos.top = 0;
			m_rcPos.right= 120;
			m_rcPos.bottom = 120;

			m_pxSize.cx = m_rcPos.right - m_rcPos.left;
			m_pxSize.cy = m_rcPos.bottom - m_rcPos.top;
			AtlPixelToHiMetric(&m_pxSize, &m_hmSize);
			m_spOleObject->SetExtent(DVASPECT_CONTENT, &m_hmSize);
			m_spOleObject->GetExtent(DVASPECT_CONTENT, &m_hmSize);
#endif
		}

		AtlHiMetricToPixel(&m_hmSize, &m_pxSize);
		m_rcPos.right = m_rcPos.left + m_pxSize.cx;
		m_rcPos.bottom = m_rcPos.top + m_pxSize.cy;

		CComQIPtr<IOleClientSite> spClientSite(this/*GetControllingUnknown()*/);
		hr = m_spOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, spClientSite, 0, m_hWndParent, &m_rcPos);
#if 0 //Have this
		HWND hwnd; m_PHTMElement->m_pFrame->m_pUI->get_hwnd(&hwnd);
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_INTERNALPAINT | RDW_FRAME);
#endif
	}

/*
	CComPtr<IObjectWithSite> spSite;
	m_spUnknown->QueryInterface(IID_IObjectWithSite, (void**)&spSite);
	if (spSite != NULL)
		spSite->SetSite((IOleClientSite*)this);
*/
	return hr;
}

void COleObjectSite::ReleaseAll()
{
	if (m_bReleaseAll)
		return;
	m_bReleaseAll = TRUE;

	if (m_spViewObject != NULL)
		m_spViewObject->SetAdvise(DVASPECT_CONTENT, 0, NULL);

	if(m_dwAdviseSink != 0xCDCDCDCD)
	{
		AtlUnadvise(m_spUnknown, m_iidSink, m_dwAdviseSink);
		m_dwAdviseSink = 0xCDCDCDCD;
	}

	if (m_spOleObject)
	{
		m_spOleObject->Unadvise(m_dwOleObject);
		m_spOleObject->Close(OLECLOSE_NOSAVE);
		m_spOleObject->SetClientSite(NULL);
	}

	if (m_spUnknown != NULL)
	{
		CComPtr<IObjectWithSite> spSite;
		m_spUnknown->QueryInterface(IID_IObjectWithSite, (void**)&spSite);
		if (spSite != NULL)
			spSite->SetSite(NULL);
	}

	m_spViewObject.Release();
	m_dwViewObjectType = 0;

	m_spInPlaceObjectWindowless.Release();
	m_spOleObject.Release();
	m_spUnknown.Release();

#if 0
	m_spInPlaceUIWindow.Release();
	m_spInPlaceFrame.Release();
#endif

	m_bInPlaceActive = FALSE;
	m_bWindowless = FALSE;
	m_bInPlaceActive = FALSE;
	m_bUIActive = FALSE;
	m_bCapture = FALSE;
	m_bReleaseAll = FALSE;
}

// IOleWindow
STDMETHODIMP COleObjectSite::GetWindow(/* [out] */ HWND __RPC_FAR *phwnd)
{
	*phwnd = m_hWndParent;
	return S_OK;
}

STDMETHODIMP COleObjectSite::ContextSensitiveHelp(BOOL fEnterMode)
{
	MessageBox(NULL, "ContextSensitiveHelp", "", MB_OK);
	return E_NOTIMPL;
}

// IOleInPlaceSite
STDMETHODIMP COleObjectSite::CanInPlaceActivate()
{
// Same as in AX
	return S_OK;
}

STDMETHODIMP COleObjectSite::OnInPlaceActivate()
{
//	MessageBox(NULL, "OnInPlaceActivate()", "", MB_OK);
// Same as in AX
	m_bInPlaceActive = TRUE;
	OleLockRunning(m_spOleObject, TRUE, FALSE);
	m_bWindowless = FALSE;
	m_spOleObject->QueryInterface(IID_IOleInPlaceObject, (void**) &m_spInPlaceObjectWindowless);
	return S_OK;
}

STDMETHODIMP COleObjectSite::OnUIActivate()
{
// Same as AX
	m_bUIActive = TRUE;
	return S_OK;
}

STDMETHODIMP COleObjectSite::GetWindowContext( 
         /* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame,
         /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc,
         /* [out] */ LPRECT lprcPosRect,
         /* [out] */ LPRECT lprcClipRect,
         /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
//	MessageBox(NULL, "GetWindowContext", "", MB_OK);

	HRESULT hr = S_OK;
	if (ppFrame == NULL || ppDoc == NULL || lprcPosRect == NULL || lprcClipRect == NULL)
		hr = E_POINTER;
	ASSERT(SUCCEEDED(hr));

	if (SUCCEEDED(hr))
	{
	//	CActiveXFrame* frame = ((CHTMLControl*)m_PHTMElement->m_pFrame->m_pUI)->m_oleFrame;

		//m_spInPlaceFrame = (IOleInPlaceFrame*)frame;
	
#if 0// Have this
		m_PHTMElement->m_pFrame->m_pUI->QueryInterface(IID_IOleInPlaceFrame, (void**)ppFrame);
		if (*ppFrame) (*ppFrame)->AddRef();// ??

		m_PHTMElement->m_pFrame->QueryInterface(IID_IOleInPlaceUIWindow, (void**)ppDoc);
		if (*ppDoc) (*ppDoc)->AddRef();	// ???

		lprcPosRect->left = m_rcPos.left;
		lprcPosRect->top = m_rcPos.top;
		lprcPosRect->right = m_rcPos.right;
		lprcPosRect->bottom = m_rcPos.bottom;
		*lprcClipRect = *lprcPosRect;

		ACCEL ac = { 0,0,0 };
		HACCEL hac = CreateAcceleratorTable(&ac, 1);
		lpFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
		lpFrameInfo->fMDIApp = FALSE;//m_bMDIApp;
		lpFrameInfo->haccel = hac;
		lpFrameInfo->cAccelEntries = 1;
		m_PHTMElement->m_pFrame->m_pUI->get_hwnd(&lpFrameInfo->hwndFrame);
#endif

#if 0
		if (!m_spInPlaceFrame)
		{
			CComObject<CAxFrameWindow>* pFrameWindow;
			CComObject<CAxFrameWindow>::CreateInstance(&pFrameWindow);
			pFrameWindow->QueryInterface(IID_IOleInPlaceFrame, (void**) &m_spInPlaceFrame);
			ASSERT(m_spInPlaceFrame);
		}
		if (!m_spInPlaceUIWindow)
		{
			CComObject<CAxUIWindow>* pUIWindow;
			CComObject<CAxUIWindow>::CreateInstance(&pUIWindow);
			pUIWindow->QueryInterface(IID_IOleInPlaceUIWindow, (void**) &m_spInPlaceUIWindow);
			ASSERT(m_spInPlaceUIWindow);
		}
		m_spInPlaceFrame.CopyTo(ppFrame);
		m_spInPlaceUIWindow.CopyTo(ppDoc);
		GetClientRect(lprcPosRect);
		GetClientRect(lprcClipRect);
		
		ACCEL ac = { 0,0,0 };
		HACCEL hac = CreateAcceleratorTable(&ac, 1);
		pFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
		pFrameInfo->fMDIApp = m_bMDIApp;
		pFrameInfo->hwndFrame = GetParent();
		pFrameInfo->haccel = hac;
		pFrameInfo->cAccelEntries = 1;
#endif
	}

	return hr;
}

STDMETHODIMP COleObjectSite::Scroll(/* [in] */ SIZE scrollExtant)
{
	MessageBox(NULL, "Scroll", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP COleObjectSite::OnUIDeactivate(/* [in] */ BOOL fUndoable)
{
// Same as AX
	m_bUIActive = FALSE;
	return S_OK;
}

STDMETHODIMP COleObjectSite::OnInPlaceDeactivate()
{
// Untested
//	MessageBox(NULL, "OnInPlaceDeactivate", "", MB_OK);

// Same as AX
	m_bInPlaceActive = FALSE;
	m_spInPlaceObjectWindowless.Release();
	return S_OK;
}

STDMETHODIMP COleObjectSite::DiscardUndoState()
{
	MessageBox(NULL, "DiscardUndoState", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP COleObjectSite::DeactivateAndUndo()
{
	MessageBox(NULL, "DeactivateAndUndo", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP COleObjectSite::OnPosRectChange(/* [in] */ LPCRECT lprcPosRect)
{
//	MessageBox(NULL, "OnPosRectChange", "", MB_OK);
	return E_NOTIMPL;
}

// IOleInPlaceSiteEx
STDMETHODIMP COleObjectSite::OnInPlaceActivateEx(BOOL* pfNoRedraw, DWORD dwFlags)
{
//	MessageBox(NULL, "OnInPlaceActivateEx", "", MB_OK);
// Same as in AX
	m_bInPlaceActive = TRUE;
	OleLockRunning(m_spOleObject, TRUE, FALSE);
	HRESULT hr = E_FAIL;
	if (dwFlags & ACTIVATE_WINDOWLESS)
	{
		m_bWindowless = TRUE;
		hr = m_spOleObject->QueryInterface(IID_IOleInPlaceObjectWindowless, (void**) &m_spInPlaceObjectWindowless);
	}
	if (FAILED(hr))
	{
		m_bWindowless = FALSE;
		hr = m_spOleObject->QueryInterface(IID_IOleInPlaceObject, (void**) &m_spInPlaceObjectWindowless);
	}
	if (m_spInPlaceObjectWindowless)
		m_spInPlaceObjectWindowless->SetObjectRects(&m_rcPos, &m_rcClip);
	return S_OK;
}

STDMETHODIMP COleObjectSite::OnInPlaceDeactivateEx(BOOL fNoRedraw)
{
	MessageBox(NULL, "OnInPlaceDeactivateEx", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP COleObjectSite::RequestUIActivate()
{
	MessageBox(NULL, "RequestUIActivate", "", MB_OK);
	return E_NOTIMPL;
}

//IOleInPlaceSiteWindowless

STDMETHODIMP COleObjectSite::CanWindowlessActivate()
{
	return m_bCanWindowlessActivate ? S_OK : S_FALSE;
}

/*****************************************************************
Called by an in-place active, windowless object to determine if it
still has the mouse capture or not. */
STDMETHODIMP COleObjectSite::GetCapture()
{
	ASSERT(0);
	return S_FALSE;
#if 0
	if (m_pWindow->m_pOCItemCapture == this)
		return S_OK;
	else
		return S_FALSE;
#endif
}

STDMETHODIMP COleObjectSite::SetCapture(BOOL fCapture)
{
	ASSERT(0);
#if 0
	if (fCapture)
	{
		m_pWindow->SetCapture();
		m_pWindow->m_pOCItemCapture = this;
	}
	else
	{
		m_pWindow->ReleaseCapture();
		m_pWindow->m_pOCItemCapture = NULL;
	}
#endif

	return S_OK;
}

STDMETHODIMP COleObjectSite::GetFocus()
{
	MessageBox(NULL, "GetFocus", "", MB_OK);
	return S_OK;
}

STDMETHODIMP COleObjectSite::SetFocus(BOOL /*fFocus*/)
{
	MessageBox(NULL, "SetFocus", "", MB_OK);
	return S_OK;
}

STDMETHODIMP COleObjectSite::GetDC(LPCRECT /*pRect*/, DWORD /*grfFlags*/, HDC* phDC)
{
	MessageBox(NULL, "GetDC", "", MB_OK);
/*	if (phDC)
		return E_POINTER;
	*phDC = CWindowImpl<CAxHostWindow>::GetDC();
*/
	return S_OK;
}

STDMETHODIMP COleObjectSite::ReleaseDC(HDC hDC)
{
	MessageBox(NULL, "ReleaseDC", "", MB_OK);
//	CWindowImpl<CAxHostWindow>::ReleaseDC(hDC);
	return S_OK;
}

STDMETHODIMP COleObjectSite::InvalidateRect(LPCRECT pRect, BOOL fErase)
{
	ASSERT(0);
#if 0	// Had this
	CRect rect;
	if (pRect == NULL)
	{
		rect = m_rcPos;
	}
	else
	{
		rect = *pRect;
	}
#endif

	//rect.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top

#if 0
	ASSERT(0);
#endif


#if 0	// Had this
	if (m_pWindow->m_pUI->m_hWnd)
	{
		m_pWindow->m_pUI->InvalidateRect(&rect, fErase);
		//m_pFrame->m_pUI->UpdateWindow();
	}
#endif

//	MessageBox(NULL, "", "", MB_OK);
//	CWindowImpl<CAxHostWindow>::InvalidateRect(pRect, fErase);
	return S_OK;
}

STDMETHODIMP COleObjectSite::InvalidateRgn(HRGN hRGN, BOOL fErase)
{
	MessageBox(NULL, "InvalidateRgn", "", MB_OK);
//	CWindowImpl<CAxHostWindow>::InvalidateRgn(hRGN, fErase);
	return S_OK;
}

STDMETHODIMP COleObjectSite::ScrollRect(INT /*dx*/, INT /*dy*/, LPCRECT /*pRectScroll*/, LPCRECT /*pRectClip*/)
{
	MessageBox(NULL, "ScrollRect", "", MB_OK);
	return S_OK;
}

STDMETHODIMP COleObjectSite::AdjustRect(LPRECT /*prc*/)
{
	MessageBox(NULL, "AdjustRect", "", MB_OK);
	return S_OK;
}

STDMETHODIMP COleObjectSite::OnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT* plResult)
{
	MessageBox(NULL, "OnDefWindowMessage", "", MB_OK);
//	*plResult = DefWindowProc(msg, wParam, lParam);
	return S_OK;
}

namespace LHTML
{

/////////////////////////////////////////////////////////////////////////////
// HTMLObjectElement

sysstring HTMLObjectElement::get_data()
{
	return getAttribute(OLESTR("data"));
}

void HTMLObjectElement::set_data(const sysstring& newVal)
{
	setAttribute(L"data", newVal);
}

sysstring HTMLObjectElement::get_type()
{
	return getAttribute(L"type");
}

void HTMLObjectElement::set_type(const sysstring& newVal)
{
	setAttribute(L"type", newVal);
}

STDMETHODIMP HTMLObjectElement::get_declare(/*[out, retval]*/ VARIANT_BOOL *pVal)
{
	ASSERT(0);
	return S_OK;
}

STDMETHODIMP HTMLObjectElement::put_declare(/*[in]*/ VARIANT_BOOL newVal)
{
	ASSERT(0);
	return S_OK;
}

STDMETHODIMP HTMLObjectElement::get_contentDocument(/*[out, retval]*/ Document* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_contentDocument;
	return S_OK;
}

STDMETHODIMP HTMLObjectElement::get__object(IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	if (m_pOleObjectSite == NULL)
	{
		Load();
	}

	if (m_pOleObjectSite)
	{
		*pVal = m_pOleObjectSite->m_spUnknown;
		if (*pVal) (*pVal)->AddRef();
	}
	return S_OK;
}

HRESULT HTMLObjectElement::LoadComObject(REFCLSID clsid)
{
	ASSERT(0);
	return 0;
#if 0
	HRESULT hr;

	CComPtr<IUnknown> unk;
	hr = unk.CoCreateInstance(clsid);

	if (FAILED(hr))
	{
		// TODO
		// Try to download
	}

	if (unk != NULL)
	{
		hr = CComObject<COleObjectSite>::CreateInstance(&m_pOleObjectSite);
		if (SUCCEEDED(hr))
		{
			m_pOleObjectSite->AddRef();

			m_pOleObjectSite->m_pDocument = m_ownerDocument;

			//m_pOleObjectSite->m_PHTMElement = this;
			m_pOleObjectSite->m_spUnknown = unk;
			m_pOleObjectSite->m_clsid = clsid;
			//m_pOleObjectSite->m_pWindow = m_pWindow;

			/*
			CComQIPtr<IRunnableObject> runnable = m_pControl->m_spUnknown;
			if (runnable)
			{
			//	MessageBox(NULL, "runnable", "", MB_OK);
				HRESULT hr = runnable->Run(NULL);

			}
			*/

			m_pOleObjectSite->Connect(FALSE, NULL);

		/////////////////////////////////////////
		// Load the object's properties
			{
				CComPtr<IPersistPropertyBag> ppbag;
				HRESULT hr = m_pOleObjectSite->m_spUnknown->QueryInterface(IID_IPersistPropertyBag, (void**)&ppbag);
				if (hr == S_OK)
				{
					ppbag->InitNew();	// ??

					hr = ppbag->Load(static_cast<IPropertyBag*>(this), static_cast<IErrorLog*>(this));
				}
			}

	#if 0
			GetObjectDataPaths();

			CComPtr<IUnknown> dataSource = m_pControl->GetDataSourceUnknown();
			if (dataSource)
			{
				MessageBox(NULL, "datasource", "", MB_OK);
			}
	#endif

		/////////////////////////////////////
	#if 0
			CComQIPtr<IConnectionPointContainer> connectionPtContainer = unk;
			if (FALSE && connectionPtContainer)
			{
				CArray<IConnectionPoint*,IConnectionPoint*> connectionPoints;

				CComQIPtr<IEnumConnectionPoints> enumcpts;
				connectionPtContainer->EnumConnectionPoints(&enumcpts);
				if (enumcpts)
				{
				// Retrieve all connection points of object
					while (1)
					{
						IConnectionPoint* connectionpt;
						ULONG retrieved;

						enumcpts->Next(1, &connectionpt, &retrieved);
						if (retrieved == 0) break;

						connectionPoints.Add(connectionpt);
					}
				}

				CComQIPtr<IProvideClassInfo2> classinfo = unk;

				if (classinfo)
				{
					//classinfo->GetGUID(GUIDKIND_DEFAULT_SOURCE_DISP_IID
					ITypeInfo* pTInfo;
					HRESULT hr = classinfo->GetClassInfo(&pTInfo);

				// Needed to retrieve custom properties
					ITypeInfo2* pTInfo2;
					pTInfo->QueryInterface(IID_ITypeInfo2, (void**)&pTInfo2);
					if (pTInfo2) pTInfo2->Release();

					TYPEATTR* pType;
					pTInfo->GetTypeAttr(&pType);

					for (int i = 0; i < pType->cImplTypes; i++)
					{
						HREFTYPE pRefType = NULL;
						if (SUCCEEDED(pTInfo->GetRefTypeOfImplType(i, &pRefType)))
						{
							ITypeInfo* pTIInfo;
							pTInfo->GetRefTypeInfo(pRefType, &pTIInfo);

							TYPEATTR* pType;
							pTIInfo->GetTypeAttr(&pType);

							IConnectionPoint* connpt;
							connectionPtContainer->FindConnectionPoint(pType->guid, &connpt);
							if (connpt)
							{
							//	IID iid;
							//	connectionPoints[i]->GetConnectionInterface(&iid);

								CActiveXDispEvent* dispevent = new CActiveXDispEvent;
								dispevent->m_iid = pType->guid;
								connectionPoints[i]->Advise(dispevent, &dispevent->m_dwCookie);
								m_pControl->m_dispEvents.Add(dispevent);

								for (int i = 0; i < pType->cFuncs; i++)
								{
									FUNCDESC* pFuncDesc = NULL;
									if (SUCCEEDED(pTIInfo->GetFuncDesc(i, &pFuncDesc)))
									{
										BSTR bname;
										UINT pcNames;
										pTIInfo->GetNames(pFuncDesc->memid, &bname, 1, &pcNames);

										CActiveXEvent* event = new CActiveXEvent;
										event->m_name = bname;
										event->m_memberid = pFuncDesc->memid;

										dispevent->m_events.Add(event);

										pTInfo->ReleaseFuncDesc(pFuncDesc);
									}
								}
							}

							pTIInfo->Release();
						}
					}

					pTInfo->Release();
				}

			/*
				for (int i = 0; i < connectionPoints.GetSize(); i++)
				{
					IID iid;
					connectionPoints[i]->GetConnectionInterface(&iid);

					CActiveXDispEvent* dispevent = new CActiveXDispEvent;
					dispevent->m_iid = iid;
					connectionPoints[i]->Advise(dispevent, &dispevent->m_dwCookie);

					m_pControl->m_dispEvents.Add(dispevent);
				}
			*/

			// Release connection points
				/*
				for (i = 0; i < connectionPoints.GetSize(); i++)
				{
					connectionPoints[i]->Release();
				}
				connectionPoints.RemoveAll();
				*/
			}
	#endif

	#if 0
			// ?? activate window here??
			if (m_pWindow->m_pUI)
			{
				ASSERT(m_pWindow->m_pUI->m_hWnd);
				m_pControl->m_hWnd = m_pWindow->m_pUI->m_hWnd;
				m_pControl->ActivateAx(/*FALSE, NULL*/);
			}
	#endif
		}
	}

	return hr;
#endif
}

HRESULT HTMLObjectElement::Load()
{
	sysstring clsidstr = getAttribute(OLESTR("classid"));
	ASSERT(0);
	return 0;
#if 0

	if (clsidstr.Length() && !wcsnicmp(clsidstr, L"clsid:", 6))
	{
	// TODO, allow white-space

		_bstr_t classid = _bstr_t(clsidstr + lstrlen("clsid:"));

		if (((BSTR)classid)[0] != L'{')	// }
		{
			classid = L"{" + classid + L"}";
		}

		CLSID	clsid;
		HRESULT hr = CLSIDFromString(classid, &clsid);
		if (SUCCEEDED(hr))
		{
			return LoadComObject(clsid);
		}
	}

	return S_FALSE;
#endif
}

/////////////////////////////////////////////////////////////////////////
// IPropertyBag

/* [local] */ HRESULT STDMETHODCALLTYPE HTMLObjectElement::Read( 
		/* [in] */ LPCOLESTR pszPropName,
		/* [out][in] */ VARIANT *pVar,
		/* [in] */ IErrorLog *pErrorLog)
{
	if (pszPropName == NULL) return E_POINTER;
	if (pVar == NULL) return E_POINTER;

	ASSERT(0);
#if 0

// Search our children for the appropriate param element

	CComQIPtr<ILDOMNode> node;
	get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILHTMLElement> element = node;
		if (element)
		{
			CComBSTR tagName;
			element->get_localName(&tagName);
			if (tagName.Length() == 0)
			{
				tagName.Empty();
				element->get_tagName(&tagName);
			}

			if (!wcscmp(tagName, L"param"))
			{
				CComBSTR name;
				element->getAttribute(L"name", &name);
				if (name.Length())
				{
					//ATLTRACE("%S - %S\n", name, pszPropName);
					if (!wcsicmp(name, pszPropName))
					{
						CComBSTR value;
						element->getAttribute(L"value", &value);

						HRESULT hr = E_FAIL;

						// if (value.Length())	???
						{
							if (pVar->vt == VT_EMPTY)
							{
								pVar->vt = VT_BSTR;
								pVar->bstrVal = value.Detach();	// gives the ownership of the sysstring to the object
								hr = S_OK;
							}
							else
							{
								VARIANT var;
								var.vt = VT_BSTR;
								var.bstrVal = value;
								hr = VariantChangeType(pVar, &var, 0, pVar->vt);
							}

						//	MessageBox(NULL, _bstr_t(name) + L"=" + _bstr_t(value), "", MB_OK);
							return hr;
						}
					}
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

// The property named with pszPropName does not exist in the property bag
#endif
	return E_INVALIDARG;
}

HRESULT STDMETHODCALLTYPE HTMLObjectElement::Write( 
		/* [in] */ LPCOLESTR pszPropName,
		/* [in] */ VARIANT *pVar)
{
	return E_NOTIMPL;
}

// IErrorLog
HRESULT STDMETHODCALLTYPE HTMLObjectElement::AddError( 
		/* [in] */ LPCOLESTR pszPropName,
		/* [in] */ EXCEPINFO *pExcepInfo)
{
	USES_CONVERSION;

// TODO, have this differently
	MessageBox(NULL, W2A(pszPropName), "ErrorLog error reading property", MB_OK);

	return S_OK;
}

}	// LHTML

#endif