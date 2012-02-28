// LHTMLActiveDocument.cpp : Implementation of CLHTMLActiveDocument
#include "stdafx.h"
#include "LAXMLViewer.h"
#include "..\LXML\LXML2.h"
#include "LHTMLActiveDocument.h"

//#include "LHTMLDocumentView.h"
#include "LHTMLDialog.h"

#include "LHTMLWindow.h"

#include "LDOMDocumentImpl.h"

#include "LElementTimeImpl.h"

#include "ScriptSite.h"

#pragma comment(lib, "Dsound.lib")

#pragma comment(lib, "C:\\DevActiveScript\\ad1.lib")

static DWORD dwOffset;	// TODO, Remove or move into a class if it's used at all?

/////////////////////////////////////////////////////////////////////////////
// CLDOMErrorHandler

STDMETHODIMP CLDOMErrorHandler::handleError(ILDOMError* pError, VARIANT_BOOL* pVal)
{
	*pVal = VARIANT_TRUE;
	return S_OK;
}

#if 0
STDMETHODIMP CLDOMErrorHandler::warn( 
         /* [in] */ ILDOMLocator __RPC_FAR *where,
         /* [in] */ BSTR how,
         /* [in] */ BSTR why)
{
	USES_CONVERSION;

	ATLTRACE("%S\n", why);
//	MessageBox(NULL, W2A(why), "LXViewer", MB_OK);
	return S_OK;
}

STDMETHODIMP CLDOMErrorHandler::fatalError( 
         /* [in] */ ILDOMLocator __RPC_FAR *where,
         /* [in] */ BSTR how,
         /* [in] */ BSTR why)
{
	USES_CONVERSION;

	ATLTRACE("%S\n", why);
//	MessageBox(NULL, W2A(why), "LXViewer", MB_OK);
	return E_FAIL;
}

STDMETHODIMP CLDOMErrorHandler::error(
         /* [in] */ ILDOMLocator __RPC_FAR *where,
         /* [in] */ BSTR how,
         /* [in] */ BSTR why)
{
	USES_CONVERSION;

	ATLTRACE("%S\n", why);
	//MessageBox(NULL, W2A(why), "LXViewer", MB_OK);
	return S_OK;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CLHTMLActiveDocument

CLHTMLActiveDocument::CLHTMLActiveDocument() : m_cwnd("static", this, 1)
{
	m_view = NULL;
	m_pWindow = NULL;

	VariantInit(&m_dialogArg);

	m_dwRegHBC = 0;
	m_pHBC = NULL;

#if 0
	m_bWindowOnly = FALSE;
#endif

	m_frameRate = 30;

	m_nTimerID = 0;
	m_hEvent = NULL;
	m_hThread = NULL;
	m_threadID = 0;
}

CLHTMLActiveDocument::~CLHTMLActiveDocument()
{
	ATLASSERT(m_nTimerID == 0);
	ATLASSERT(m_pWindow == NULL);
}

STDMETHODIMP CLHTMLActiveDocument::Show(ILXUIElement* element)
{
	/*
	{
		//CComPtr<IOleContainer> pContainer = NULL;
//		pClientSite->GetContainer(&pContainer);

		CComQIPtr<IServiceProvider> sp(m_spAddinSite);

		CComPtr<IWebBrowser> webBrowser;
		sp->QueryService(IID_IWebBrowserApp, IID_IWebBrowser2, (void**)&webBrowser);
	}
	*/

	CComQIPtr<ILDOMDocumentView> documentView = /*m_pDocument->*/m_document;
	ATLASSERT(0);
#if 0
	documentView->createPresentation(&m_view);
#endif

	CComObject<CLHTMLWindow2>::CreateInstance(&m_pWindow);
	if (m_pWindow)
	{
		m_pWindow->AddRef();

		ATLASSERT(0);
#if 0
		m_pWindow->m_pAddin = this;

		m_pWindow->m_pCanvas->m_pSite = NULL;//this;

		m_pWindow->m_pCanvas->m_pView = static_cast<CHTMLDocumentView*>(m_view.p);
		m_pWindow->m_pCanvas->m_htmTree = m_pWindow->m_pCanvas->m_pView->m_pRootElement;
#endif
	}

	m_inplaceElement = element;

	CComQIPtr<ILDOMEventTarget>(m_inplaceElement)->addEventListener(L"mousedown", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
	CComQIPtr<ILDOMEventTarget>(m_inplaceElement)->addEventListener(L"mouseup", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
	CComQIPtr<ILDOMEventTarget>(m_inplaceElement)->addEventListener(L"mousemove", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
	CComQIPtr<ILDOMEventTarget>(m_inplaceElement)->addEventListener(L"contextmenu", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
	CComQIPtr<ILDOMEventTarget>(m_inplaceElement)->addEventListener(L"resize", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);

	ATLASSERT(0);
#if 0
	long cookie;
	element->addBehavior(NULL, &CComVariant(GetUnknown()), &cookie);
#endif

	OnPostVerbInPlaceActivate();

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::handleEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"mousedown"))
	{
		CComQIPtr<ILDOMMouseEvent> mouseEvt = evt;

		long screenX;
		long screenY;
		long clientX;
		long clientY;
		mouseEvt->get_screenX(&screenX);
		mouseEvt->get_screenY(&screenY);
		mouseEvt->get_clientX(&clientX);
		mouseEvt->get_clientY(&clientY);

		if (m_pWindow)
		{
			m_pWindow->m_pCanvas->OnButtonDown(
				0,//nFlags,
				CPoint(screenX, screenY),
				CPoint(clientX, clientY),
				0, FALSE, NULL);
		}
	}
	else if (!wcscmp(type, L"mouseup"))
	{
		CComQIPtr<ILDOMMouseEvent> mouseEvt = evt;

		long screenX;
		long screenY;
		long clientX;
		long clientY;
		mouseEvt->get_screenX(&screenX);
		mouseEvt->get_screenY(&screenY);
		mouseEvt->get_clientX(&clientX);
		mouseEvt->get_clientY(&clientY);

		if (m_pWindow)
		{
			m_pWindow->m_pCanvas->OnButtonUp(
				0,//nFlags,
				CPoint(screenX, screenY),
				CPoint(clientX, clientY),
				0);
		}
	}
	else if (!wcscmp(type, L"mousemove"))
	{
		CComQIPtr<ILDOMMouseEvent> mouseEvt = evt;

		long screenX;
		long screenY;
		long clientX;
		long clientY;
		mouseEvt->get_screenX(&screenX);
		mouseEvt->get_screenY(&screenY);
		mouseEvt->get_clientX(&clientX);
		mouseEvt->get_clientY(&clientY);

		if (m_pWindow)
		{
			m_pWindow->m_pCanvas->OnMouseMove(
				0,//nFlags,
				CPoint(screenX, screenY),
				CPoint(clientX, clientY));
		}
	}
	else if (!wcscmp(type, L"resize"))
	{
		if (m_pWindow)
		{
			CComQIPtr<ILXUIDocViewElement> docview(m_inplaceElement);

			long width;
			long height;
			docview->get_width(&width);
			docview->get_height(&height);

			m_pWindow->m_pCanvas->m_client.right = width;
			m_pWindow->m_pCanvas->m_client.bottom = height;

			m_pWindow->m_pCanvas->OnSize();
		//	m_pWindow->PositionFrames();
		}
	}

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::Draw(/*[in]*/ ILCanvas* canvas)
{
	if (m_pWindow)
	{
		Gdiplus::Graphics* pGraphics;

		canvas->GetGdip((long*)&pGraphics);

		CRect clip(0,0, 999999, 999999);
		m_pWindow->m_pCanvas->Draw(*pGraphics, clip);
	}

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::SetCursor(/*[in]*/ POINT pt)
{
	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnSetCursor(pt);
	}

	return S_OK;
}

ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;

int CLHTMLActiveDocument::FinalConstruct()
{
	if (gdiplusToken == NULL)
	{
		if (Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok)
		{
			return E_FAIL;
		}
	}

	InitializeCriticalSection(&m_paintCriticalSection);

// Create a standard error handler
	CComObject<CLDOMErrorHandler>* pErrorHandler;
	CComObject<CLDOMErrorHandler>::CreateInstance(&pErrorHandler);
	m_errorHandler = pErrorHandler;

	m_curMoniker = NULL;

	m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);
	ATLASSERT(m_cwnd.m_hWnd);
	if (m_cwnd.m_hWnd == NULL)
		return E_FAIL;

#if 0
	{
		HRESULT hr;

		hr = DirectSoundCreate8(NULL, &m_ds8, NULL);
		ATLASSERT(SUCCEEDED(hr));

		hr = m_ds8->SetCooperativeLevel(m_cwnd.m_hWnd, DSSCL_PRIORITY/*DSSCL_NORMAL*/);
		ATLASSERT(SUCCEEDED(hr));
	}

	DSBUFFERDESC dsbdesc; 
	HRESULT hr; 
	
	// Set up wave format structure. 
	//memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT)); 
	//pcmwf = *(PCMWAVEFORMAT*)&m_wavfmt;
	m_wf.wFormatTag = WAVE_FORMAT_PCM; 
	m_wf.nChannels = 2;
	m_wf.nSamplesPerSec = 22050;
	m_wf.nBlockAlign = 2; 
	m_wf.nAvgBytesPerSec = m_wf.nSamplesPerSec * m_wf.nBlockAlign; 
	m_wf.wBitsPerSample = 8; 
	m_wf.cbSize = 0;
	
	// Set up DSBUFFERDESC structure. 

	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
	dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
	dsbdesc.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY; 
	
	dsbdesc.dwBufferBytes = 4 * m_wf.nAvgBytesPerSec;
	dsbdesc.lpwfxFormat = &m_wf; 

	// Create buffer. 
	
	CComPtr<IDirectSoundBuffer> dsBuffer;
	hr = m_ds8->CreateSoundBuffer(&dsbdesc, &dsBuffer, NULL); 
	if (SUCCEEDED(hr))
	{
		m_dsBuffer8 = dsBuffer;
	} 
	else
	{ 
		ATLASSERT(0);
	}
#endif

	return 0;
}

void CLHTMLActiveDocument::FinalRelease()
{
	ATLTRACE("CLHTMLActiveDocument::FinalRelease()\n");

	StopPlay();	// TODO, do somewhere else

	if (m_cwnd.m_hWnd)
	{
		m_cwnd.DestroyWindow();
	}

	if (m_pWindow)
	{
#if 0
		m_pWindow->Free();
#endif
		m_pWindow->Release();
		m_pWindow = NULL;
	}

	DeleteCriticalSection(&m_paintCriticalSection);

	if (m_element)
	{
		m_element.Release();
	}

	if (m_document)
	{
		m_document.p->AddRef();
		int refcount = m_document.p->Release();

		m_document.Release();
	}

	if (m_errorHandler)
	{
		m_errorHandler.p->AddRef();
		int refcount = m_errorHandler.p->Release();

		m_errorHandler.Release();
	}

	m_curMoniker.Release();
}

void CLHTMLActiveDocument::AdvancePlay()
{
//	m_totalIntendedTime += 1.0 / m_frameRate;

	if (m_document)
	{
#if 0
		CComPtr<ILDOMDocument> document;
		m_frameElement->get_contentDocument(&document);

		CComQIPtr<ILHTMLDocument> htmlDocument = document;
		if (htmlDocument)
		{
			bool bAny = static_cast<CLHTMLDocument*>(htmlDocument.p)->Seek(m_totalIntendedTime);

			if (bAny)
			{
				Flow();

				CRect urect = m_imageRect;
				urect.OffsetRect(m_client.left, m_client.top);
				m_pUI->InvalidateRect(&urect, TRUE);
				m_pUI->UpdateWindow();
			}
		}
#endif

		CComPtr<ILDOMElement> documentElement;
		m_document->get_documentElement(&documentElement);

		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;

		if (svgsvgElement)
		{
		/*	double currentTime;
			svgsvgElement->getCurrentTime(&currentTime);

			currentTime += 1.0 / m_frameRate;
			*/

			EnterCriticalSection(&m_paintCriticalSection);

			svgsvgElement->setCurrentTime(m_currentVideoTime);

			LeaveCriticalSection(&m_paintCriticalSection);
		}

	}
}

void CLHTMLActiveDocument::UpdateAllViews()
{
// Invalidate all views of the document
	CComQIPtr<CLDOMDocumentImplImpl> pDocument(m_document);

	for (int n = 0; n < pDocument->m_pViews.GetSize(); n++)
	{
		ATLASSERT(0);
#if 0
		pDocument->m_pViews[n]->InvalidateRect(NULL);
#endif
	}
}

LRESULT CLHTMLActiveDocument::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//AdvancePlay();
	UpdateAllViews();

	return 0;
}

#if 0
HRESULT CLHTMLActiveDocument::OnDraw(ATL_DRAWINFO& di)
{
//	TextOut(di.hdcDraw, di.prcBounds->left, di.prcBounds->top, "Test2", 5);

	HDC hDC = di.hdcDraw;

	int state = SaveDC(hDC);

	CPoint oldOrg;
	OffsetViewportOrgEx(hDC, di.prcBounds->left, di.prcBounds->top, &oldOrg);

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnPaint(hDC);
	}

	RestoreDC(hDC, state);

	return 0;
}

LRESULT CLHTMLActiveDocument::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	m_spInPlaceSite->SetFocus(TRUE);

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	CPoint screenpt = point;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnButtonDown(nFlags, screenpt, point, 0, FALSE, NULL);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	CPoint screenpt = point;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnButtonDown(nFlags, screenpt, point, 1, FALSE, NULL);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	CPoint screenpt = point;

#if 0
	{
		HDC hDC = NULL;
		HRESULT hr = m_spInPlaceSite->GetDC(&m_rcPos, OLEDC_NODRAW/*OLEDC_OFFSCREEN*/, &hDC);
		ATLASSERT(SUCCEEDED(hr));

		m_spInPlaceSite->ReleaseDC(hDC);
	}
#endif

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnButtonUp(nFlags, screenpt, point, 0);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	CPoint screenpt = point;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnMouseMove(nFlags, screenpt, point);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

//	ScreenToClient(&point);

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnContextMenu(hwnd, point);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nKey = wParam;
	int lKeyData = lParam;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnKeyDown(nKey, lKeyData);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nKey = wParam;
	int lKeyData = lParam;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnKeyUp(nKey, lKeyData);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnSysKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nVirtKey = (int)wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->m_bAlt = lKeyData & (1<<29);
		m_pWindow->m_pCanvas->OnKeyDown(nVirtKey, lKeyData);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnSysKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nVirtKey = (int) wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->m_bAlt = lKeyData & (1<<29);
		m_pWindow->m_pCanvas->OnKeyUp(nVirtKey, lKeyData);
	}

	return 0;
}

LRESULT CLHTMLActiveDocument::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	HWND hwnd = (HWND)wParam;       // handle to window with cursor 
	int nHittest = LOWORD(lParam);  // hit-test code 
	int wMouseMsg = HIWORD(lParam); // mouse-message identifier 

	if (m_pWindow)
	{
		CPoint point;
		::GetCursorPos(&point);

		HWND hwnd;
		m_spInPlaceSite->GetWindow(&hwnd);

		::ScreenToClient(hwnd, &point);

		point.x -= m_rcPos.left;
		point.y -= m_rcPos.top;

		BOOL bRet = m_pWindow->m_pCanvas->OnSetCursor(/*nHittest, wMouseMsg,*/ point);
		if (bRet)
			return bRet;
	}

	bHandled = false;
	return 0;
}
#endif

#if 0
HRESULT CLHTMLActiveDocument::IOleInPlaceObject_SetObjectRects(LPCRECT prcPos,LPCRECT prcClip)
{
	CComControl<CLHTMLActiveDocument>::IOleInPlaceObject_SetObjectRects(prcPos, prcClip);
	//IOleInPlaceObjectWindowlessImpl<CLHTMLActiveDocument>::

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->m_client = m_rcPos;
		m_pWindow->m_pCanvas->OnSize();
	//	m_pWindow->PositionFrames();
	}

	//m_pFrame->

	return S_OK;
}
#endif

STDMETHODIMP CLHTMLActiveDocument::GotoLocation(BSTR burl, VARIANT_BOOL *success)
{
	ATLASSERT(0);
#if 0
	if (success)
		*success = VARIANT_FALSE;

	_bstr_t url = burl;

	if (url.length() == 0)
	{
		::MessageBox(NULL, "GotoLocation: Empty url", "", MB_OK);
		return E_FAIL;
	}

#if 0
	if (m_pFrame)
	{
		m_pFrame->FreeImage();
		m_pFrame->Release();
		m_pFrame = NULL;
	}
#endif

	CComPtr<ILDOMImplementation> impl;
	impl.CoCreateInstance(CLSID_LDOMImplementation);
	if (impl)
	{
		CComPtr<ILDOMBuilder> builder;
		impl->createDOMBuilder(0, NULL, &builder);

		builder->parseURI(burl, &m_document);

	/// ??
		if (m_view)
		{
			if (m_view->m_pWindow)
			{
				m_view->m_pWindow->FreeImage();
				m_view->m_pWindow->Release();
				m_view->m_pWindow = NULL;
			}

			ATLASSERT(m_view->m_pWindow == NULL);	// ??
			m_view->CreateFrame();
			m_view->OnSize();
		}
///
	}

#if 0
	CComObject<CHTMFrame>::CreateInstance(&m_pFrame);
	if (m_pFrame)
	{
		m_pFrame->AddRef();

		m_pFrame->m_pHTMLDialogImpl->m_dialogArguments = m_dialogArg;
		m_pFrame->m_pUI = m_view;
		m_pFrame->GotoLocation(url);

		if (m_view) m_view->OnSize();

		if (success)
			*success = VARIANT_TRUE;
	}
#endif
#endif
	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::get_src(/*[out, retval]*/ BSTR *pVal)
{
	return m_src.CopyTo(pVal);
}

/*
getSVGDocument

Exceptions 
DOMException  NOT_SUPPORTED_ERR: No SVGDocument object is available.  
*/
STDMETHODIMP CLHTMLActiveDocument::getSVGDocument(/*[out,retval]*/ ILSVGDocument* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComQIPtr<ILSVGDocument> svgDocument = m_document;
	*pVal = svgDocument;
	if (*pVal)
	{
		(*pVal)->AddRef();
		return S_OK;
	}
	else
	{
		*pVal = NULL;
		return E_FAIL;
	}
}

#if 0
#include "LSVGVideoElement.h"	// TODO remove
#endif

// TODO remove?
void CLHTMLActiveDocument::RenderAllAudio(ILDOMElement* element, double tsf, double tlen, ULONG nSamples)
{
	ATLASSERT(0);
#if 0
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILRenderAudio> renderAudio = node;
		if (renderAudio)
		{
			WAVEFORMATEX srcfmt;
			renderAudio->GetWaveFormat(&srcfmt);

			ULONG srcSamples = srcfmt.nSamplesPerSec*tlen;

			nSamples = tlen * m_wf.nSamplesPerSec;

			LPBYTE srcbuffer = (LPBYTE)GlobalAlloc(0, srcSamples * srcfmt.nBlockAlign);

			renderAudio->RenderAudio(tsf, tlen, (LPBYTE)srcbuffer, nSamples);

			for (int n = 0; n < nSamples; n++)
			{
				ULONG nsrcSample = n * srcfmt.nSamplesPerSec / m_wf.nSamplesPerSec;

				m_wavbuffer[n*2+0] = srcbuffer[nsrcSample*2+0];
				m_wavbuffer[n*2+1] = srcbuffer[nsrcSample*2+1];
			}

			GlobalFree(srcbuffer);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}

DWORD WINAPI StartProc(LPVOID lpParam)
{
	CLHTMLActiveDocument* pDocument = (CLHTMLActiveDocument*)lpParam;

	MSG msg;
	do
	{
		BOOL bAdvance = FALSE;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) && (msg.message == WM_USER+100))
		{
			bAdvance = TRUE;
			ATLASSERT(msg.hwnd == NULL);
		}

		if (bAdvance)
		{
			pDocument->AdvancePlay();
			pDocument->m_cwnd.PostMessage(WM_USER+100, 0, 0);
		}
	}
	while (msg.message != WM_QUIT);

#if 0

	while (1)
	{
		DWORD dw = WaitForSingleObject(pDocument->m_hEvent, INFINITE);

	//	DWORD dwPlayPos;
	//	pDocument->m_dsBuffer8->GetCurrentPosition(&dwPlayPos, NULL);

		dwOffset += 2*pDocument->m_wf.nAvgBytesPerSec;

		while (dwOffset >= 4*pDocument->m_wf.nAvgBytesPerSec)
			dwOffset -= 4*pDocument->m_wf.nAvgBytesPerSec;

		currentAudioTime += 2;// / (double)pDocument->m_wf.nAvgBytesPerSec;

		/*
		CComPtr<ILDOMElement> documentElement;
		pDocument->m_document->get_documentElement(&documentElement);

		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;

		double currentTime;
		svgsvgElement->getCurrentTime(&currentTime);
		*/

	//	DWORD dwWritePos;
	//	pDocument->m_dsBuffer8->GetCurrentPosition(NULL, &dwWritePos);

		//DWORD nSamples = pDocument->m_wf.nSamplesPerSec*4;

		DWORD dwbuffer1;
		LPBYTE buffer1;

		DWORD dwbuffer2;
		LPBYTE buffer2;

		if (SUCCEEDED(pDocument->m_dsBuffer8->Lock(dwOffset, pDocument->m_wf.nAvgBytesPerSec*2, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0)))
		{
			CComPtr<ILDOMElement> documentElement;
			pDocument->m_document->get_documentElement(&documentElement);

			pDocument->m_wavbuffer = (LPSTR)buffer1;
			pDocument->RenderAllAudio(documentElement, currentAudioTime, (double)dwbuffer1 / pDocument->m_wf.nAvgBytesPerSec, 0);

			if (buffer2)
			{
				pDocument->m_wavbuffer = (LPSTR)buffer2;
				pDocument->RenderAllAudio(documentElement, currentAudioTime + (double)dwbuffer2 / pDocument->m_wf.nAvgBytesPerSec, (double)dwbuffer2 / pDocument->m_wf.nAvgBytesPerSec, 0);
			}

			pDocument->m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
		}
		else
			MessageBeep(-1);
	}
#endif

	return 0;
}

void CALLBACK VideoPlayTimeProc(
  UINT uID,     
  UINT uMsg,  
  DWORD dwUser,
  DWORD dw1,
  DWORD dw2
)
{
	CLHTMLActiveDocument* pDoc = (CLHTMLActiveDocument*)dwUser;

	/*
	if (!audioClock)
	{
		pDoc->m_currentTime += 1 / pDoc->m_frameRate;
	}
	*/

	pDoc->m_currentVideoTime += 1 / pDoc->m_frameRate;

	::PostThreadMessage(pDoc->m_threadID, WM_USER+100, 0, 0);
}

void Run(ILDOMElement* element)
{
	CComQIPtr<CLElementTimeImplImpl> elementTime = element;
	if (elementTime)
	{
		elementTime->Run();
	}

	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			Run(element);
		}


		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}

HRESULT CLHTMLActiveDocument::StartPlay()
{
// Timer
	//m_totalIntendedTime = 0;

	m_currentAudioTime = 0;
	m_currentVideoTime = 0;

	LONG uDelay = (LONG)(1000/m_frameRate);

#if 0
	if (FALSE)
	{
		CComQIPtr<IDirectSoundNotify8, &IID_IDirectSoundNotify> notify8;// = m_dsBuffer8;
		m_dsBuffer8->QueryInterface(IID_IDirectSoundNotify8, (void**)&notify8);

		m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hThread = CreateThread(NULL, 0, StartProc, (LPVOID)this, 0, &m_threadID);

		currentVideoTime = 0;
		currentAudioTime = 0;

		dwOffset = 0;
		DSBPOSITIONNOTIFY ps[2];
		ps[0].dwOffset = 0;
		ps[0].hEventNotify = m_hEvent;
		ps[1].dwOffset = 2*m_wf.nAvgBytesPerSec;
		ps[1].hEventNotify = m_hEvent;

		notify8->SetNotificationPositions(2, ps);

		//DWORD nSamples = m_wf.nSamplesPerSec*2;
		DWORD dwbuffer;
		if (SUCCEEDED(m_dsBuffer8->Lock(0, 2 * m_wf.nAvgBytesPerSec, (void**)&m_wavbuffer, &dwbuffer, NULL, NULL, 0)))
		{
			CComPtr<ILDOMElement> documentElement;
			m_document->get_documentElement(&documentElement);

			RenderAllAudio(documentElement, 0, 2, 0);

			m_dsBuffer8->Unlock(m_wavbuffer, dwbuffer, NULL, 0);
		}
	}
#endif

	ATLASSERT(m_nTimerID == 0);
//	m_timerID = m_cwnd.SetTimer(1, uDelay);

	CComPtr<ILDOMElement> documentElement;
	m_document->get_documentElement(&documentElement);
	if (documentElement)
	{
		Run(documentElement);
	}

	m_hThread = CreateThread(NULL, 0, StartProc, (LPVOID)this, 0, &m_threadID);

	m_nTimerID = timeSetEvent(uDelay, 0, VideoPlayTimeProc, (DWORD)this, TIME_PERIODIC);

#if 0
	if (FALSE)
	{
		m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
	}
#endif

	return S_OK;
}

HRESULT CLHTMLActiveDocument::StopPlay()
{
#if 0
	if (m_dsBuffer8)
	{
		m_dsBuffer8->Stop();
		//m_dsBuffer8.Release();
	}

	if (m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}
#endif

	if (m_nTimerID)
	{
		timeKillEvent(m_nTimerID);
		m_nTimerID = 0;
	}

	if (m_hThread)
	{
		::PostThreadMessage(m_threadID, WM_QUIT, 0, 0);
		::WaitForSingleObject(m_hThread, INFINITE);
		m_hThread = NULL;
		m_threadID = 0;
	}

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::put_src(/*[in]*/ BSTR newVal)
{
	ATLASSERT(0);
#if 0
	StopPlay();

	if (m_textData)
	{
		m_textData.Release();
	}

	if (m_pWindow)
	{
#if 0
		m_pWindow->Free();
#endif
		m_pWindow->Release();
		m_pWindow = NULL;

		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}

	m_src = newVal;

	CComQIPtr<IServiceProvider> sp = m_spClientSite;
	if (sp)
	{
		CComPtr<IMoniker> imkName;

		CComPtr<IBindHost> bindHost;
		if (SUCCEEDED(sp->QueryService(SID_SBindHost, &bindHost)))
		{
			bindHost->CreateMoniker(m_src, NULL, &imkName, 0);
		}
		else
		{
			CreateURLMoniker(NULL, m_src, &imkName);
		}

		if (imkName)
		{
			// Note I'm creating the window before loading the document
			CComObject<CLHTMLWindow2>::CreateInstance(&m_pWindow);
			if (m_pWindow)
			{
				m_pWindow->AddRef();
			//	m_hWnd = m_hWnd;
#if 0	// I Had this
				m_pWindow->m_pActiveDocument = this;
#endif

			// TODO, init scripting if not already done?

				CComPtr<IBindCtx> bctx;
				if (SUCCEEDED(CreateBindCtx(0/*reserved*/, &bctx)))
				{
					Load(FALSE, imkName, bctx, 0);

					if (m_document)
					{
						CComQIPtr<ILDOMDocumentView> documentView = m_document;
						documentView->createPresentation(&m_view);
					//	SetDocument(document);

						if (FALSE)
						{
							StartPlay();
						}

						m_pWindow->m_pCanvas->m_pView = static_cast<CHTMLDocumentView*>(m_view.p);
						m_pWindow->m_pCanvas->m_htmTree = m_pWindow->m_pCanvas->m_pView->m_pRootElement;

					//	CComQIPtr<ILDOMDocumentView> documentView = m_document;
					//	documentView->createPresentation(&m_view);
					//	ATLASSERT(0);
#if 0
						m_pView->SetDocument(m_document);
#endif
					}
				}
			}
		}
	}

#endif
	return S_OK;
}

HRESULT CLHTMLActiveDocument::OnPostVerbInPlaceActivate()
{
	if (m_pWindow)	// Scripting
	{
		// TODO, make a function

		HRESULT hr;

		CComQIPtr<CLDOMDocumentImplImpl> documentImpl(m_document);

		documentImpl->m_pScriptSite->m_pGlobalObject = m_pWindow->GetUnknown();
		documentImpl->m_pScriptSite->m_hWnd = NULL;	// TODO

	// Add global 'window' object to the script
		hr = documentImpl->m_pScriptSite->m_activeScript->AddNamedItem(L"globalobject", SCRIPTITEM_GLOBALMEMBERS | SCRIPTITEM_ISVISIBLE/* | SCRIPTITEM_ISSOURCE | SCRIPTITEM_ISPERSISTENT*/);
		ATLASSERT(SUCCEEDED(hr));

		//	hr = m_pScriptSite->m_activeScript->SetScriptState(SCRIPTSTATE_STARTED);
		//	ATLASSERT(SUCCEEDED(hr));

		//
		//DebugOutputTypeInfo(m_pScriptDisp);

		// Start running scripts
		hr = documentImpl->m_pScriptSite->m_activeScript->SetScriptState(SCRIPTSTATE_STARTED);
		ATLASSERT(SUCCEEDED(hr));

	// force the engine to connect any outbound interfaces to the 
	// host's objects
		hr = documentImpl->m_pScriptSite->m_activeScript->SetScriptState(SCRIPTSTATE_CONNECTED);
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<ILDOMElement> documentElement;
		m_document->get_documentElement(&documentElement);
		if (documentElement)
		{
			OnSVGLoad(documentElement);
		}
	}

	if (FALSE)
	{
		StartPlay();
	}

#if 0	// ??
	// Done in m_pWindow->SetDocument()?
	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}
#endif

	return S_OK;
}

#if 0
HRESULT CLHTMLActiveDocument::DoVerbInPlaceActivate(LPCRECT prcPosRect, HWND hwndParent)
{
	HRESULT hr = IOleObjectImpl<CLHTMLActiveDocument>::DoVerbInPlaceActivate(prcPosRect, hwndParent);
	if (SUCCEEDED(hr))
	{
	}

	return hr;
}
#endif

// TODO Am I using this ??
STDMETHODIMP CLHTMLActiveDocument::SetDocument(ILDOMDocument *document)
{
	ATLASSERT(0);
#if 0
	m_document = document;

	CComQIPtr<ILDOMDocumentView> documentView = m_document;
	documentView->createPresentation(&m_view);
#endif

#if 0
	m_document = document;
	CComQIPtr<CLDOMDocumentImplImpl>(m_document)->m_acDocument = this;

	m_element.Release();
	m_document->get_documentElement(&m_element);

	if (m_view)
	{
		if (m_view->m_pWindow)
		{
			m_view->m_pWindow->FreeImage();
			m_view->m_pWindow->Release();
			m_view->m_pWindow = NULL;
		}

		ATLASSERT(m_view->m_pWindow == NULL);	// ??
		m_view->CreateFrame();
		m_view->OnSize();
	}
#endif

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::SetElement(ILDOMElement *element)
{
	ATLASSERT(0);
#if 0
	m_element = element;

//	m_view->m_pFrame->SetElement(element);

//	ATLASSERT(0);
#if 0
	/*
	if (m_pFrame)
	{
		m_pFrame->FreeImage();
		m_pFrame->Release();
		m_pFrame = NULL;
	}

	CComObject<CHTMFrame>::CreateInstance(&m_pFrame);
	if (m_pFrame)
	{
		m_pFrame->AddRef();

  */
	if (element == NULL)
	{
		if (m_pFrame)
		{
			m_pFrame->FreeImage();
			m_pFrame->Release();
			m_pFrame = NULL;
		}

		if (m_view)
		{
			if (m_view->m_hWnd)
				m_view->Invalidate();

			m_view->OnSize();
		}
	}
	else
	{
		if (m_pFrame == NULL)
		{
			CComObject<CHTMFrame>::CreateInstance(&m_pFrame);
			if (m_pFrame)
			{
				m_pFrame->AddRef();

				m_pFrame->m_pUI = m_view;
			}
		}

		if (m_pFrame)
		{
			//m_pFrame->m_pHTMLDialogImpl->m_dialogArguments = m_dialogArg;
			m_pFrame->SetElement(element);
		}

		if (m_view)
		{
			m_view->OnSize();
		}
	}
#endif
#endif

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::get_errorHandler(/*[out, retval]*/ ILDOMErrorHandler* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_errorHandler;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::put_errorHandler(/*[in]*/ ILDOMErrorHandler* newVal)
{
	m_errorHandler = newVal;
	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_ILHTMLActiveDocument,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#if 0
// IOleDocument
HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::CreateView( 
		/* [unique][in] */ IOleInPlaceSite __RPC_FAR *pIPSite,
		/* [unique][in] */ IStream __RPC_FAR *pstm,
		/* [in] */ DWORD dwReserved,
		/* [out] */ IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
{
#ifdef _DEBUG
//	MessageBox(NULL, "CLHTMLActiveDocument::CreateView()", "", MB_OK);
#endif

	if (ppView == NULL) return E_POINTER;

	CComObject<CLHTMLDocumentView>* pView;
	CComObject<CLHTMLDocumentView>::CreateInstance(&pView);
	if (pView)
	{
		pView->AddRef();

		pView->Init(this, pIPSite);
	}

#if 0
	if (m_pFrame)
	{
		m_pFrame->SetView(pView);
	}
#endif

#if 0
	m_view = pView;	// TODO remove (document can have multiple views)
#endif

	*ppView = pView;
	//(*ppView)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::GetDocMiscStatus( 
		/* [out] */ DWORD __RPC_FAR *pdwStatus)
{
	if (pdwStatus == NULL) return E_POINTER;

#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::GetDocMiscStatus()", "", MB_OK);
#endif

	// Possible values
	/*
	DOCMISC_CANCREATEMULTIPLEVIEWS    =  1, 
    DOCMISC_SUPPORTCOMPLEXRECTANGLES  =  2, 
    DOCMISC_CANTOPENEDIT,             =  4, 
    DOCMISC_NOFILESUPPORT             =  8  
	 */
	*pdwStatus = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::EnumViews( 
		/* [out] */ IEnumOleDocumentViews __RPC_FAR *__RPC_FAR *ppEnum,
		/* [out] */ IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::EnumViews()", "", MB_OK);
#endif

	return E_NOTIMPL;
}
#endif

#if 0
// IPersist
HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::GetClassID(/* [out] */ CLSID __RPC_FAR *pClassID)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::IPersist::GetClassID()", "", MB_OK);
#endif

	return S_OK;
}
#endif

// IPersistFile

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::IsDirty( void)
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::Load(
   /* [in] */ LPCOLESTR pszFileName,
   /* [in] */ DWORD dwMode)
{
#ifdef _DEBUG
//	::MessageBox(NULL, "CLHTMLActiveDocument::IPersistFile::Load()", "", MB_OK);
#endif

	HRESULT hr;

	// for some reason we don't get through when using CreateFileMoniker (why?)

	CComPtr<IMoniker> imkName;
	hr = CreateURLMoniker(NULL, pszFileName, &imkName);
	if (SUCCEEDED(hr))
	{
		CComPtr<IBindCtx> bctx;
		hr = CreateBindCtx(0/*reserved*/, &bctx);
		if (SUCCEEDED(hr))
		{
			hr = Load(TRUE, imkName, bctx, 0);
		}
	}

	return hr;
	/*
	VARIANT_BOOL success;
	GotoLocation(_bstr_t(pszFileName), &success);
	*/

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::Save( 
   /* [unique][in] */ LPCOLESTR pszFileName,
   /* [in] */ BOOL fRemember)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::IPersistFile::Save()", "", MB_OK);
#endif

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::SaveCompleted( 
   /* [unique][in] */ LPCOLESTR pszFileName)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::GetCurFile( 
   /* [out] */ LPOLESTR __RPC_FAR *ppszFileName)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::GetCurFile()", "", MB_OK);
#endif

	return S_OK;
}

// IPersistStreamInit
STDMETHODIMP CLHTMLActiveDocument::Load(LPSTREAM pStm)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::IPersistStream::Load()", "", MB_OK);
#endif

	//pStm->
	return E_FAIL;
}
#if 0
STDMETHODIMP CLHTMLActiveDocument::Save(IStream *pStm, BOOL fClearDirty)
{
	return E_FAIL;
}

STDMETHODIMP CLHTMLActiveDocument::GetSizeMax(ULARGE_INTEGER *pcbSize)
{
	ATLASSERT(0);
	//*pcbSize = 0;
	return E_FAIL;
}
#endif

#include "DOMParser.h"

// IPersistMoniker
STDMETHODIMP CLHTMLActiveDocument::Load( 
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode)
{
#ifdef _DEBUG
	//::MessageBox(NULL, "CLHTMLActiveDocument::IPersistMoniker::Load()", "", MB_OK);
#endif

	m_curMoniker = pimkName;

	LPOLESTR szDisplayName;
	m_curMoniker->GetDisplayName(pibc, NULL, &szDisplayName);
	m_friendlyName = szDisplayName;
	CoTaskMemFree(szDisplayName);

//	CComPtr<IStream> stm;
//	pimkName->BindToStorage(pibc, NULL, IID_IStream, (void**)&stm);

	HRESULT hr;

	//CComPtr<ITextData> textData;
	hr = m_textData.CoCreateInstance(CLSID_TextData);
	if (SUCCEEDED(hr))
	{
		CComQIPtr<IPersistMoniker> persistMoniker = m_textData;
		hr = persistMoniker->Load(fFullyAvailable, pimkName, pibc, grfMode);

		if (SUCCEEDED(hr))
		{
		//	CComQIPtr<IPersistStream> persistStream = textData;
		//	persistStream->Load(stm);

			//CComPtr<ILDOMImplementation> impl;
			//impl.CoCreateInstance(CLSID_LDOMImplementation);
			//if (impl)
			{
				//CComPtr<ILDOMBuilder> builder;
				//impl->createDOMBuilder(0, NULL, &builder);

				//builder->put_errorHandler(m_errorHandler);	// Not standard ?

				CDOMParser parser;

#if 0
				parser.m_activeDocument = this;
#endif
				parser.m_errorHandler = m_errorHandler;
				parser.m_textDoc = m_textData;
				m_textData->get_url(&parser.m_uri);
				parser.loadXML2();

				CComPtr<ILDOMDocument> document = parser.m_document;

				/*
				*pVal = parser.m_document;
				if (*pVal) (*pVal)->AddRef();


				*pVal = parser.m_document;

				builder->parseTextData(m_textData, &document);
				*/

				m_document = document;
			}
		}
	}

	return hr;
}

STDMETHODIMP CLHTMLActiveDocument::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::GetCurMoniker( 
      /* [out] */ IMoniker **ppimkName)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::GetCurMoniker()", "", MB_OK);
#endif

	if (ppimkName == NULL) return E_POINTER;
	*ppimkName = m_curMoniker;
	if (*ppimkName) (*ppimkName)->AddRef();
	return S_OK;
}

// IOleObject

HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::SetMoniker( 
      /* [in] */ DWORD dwWhichMoniker,
      /* [unique][in] */ IMoniker __RPC_FAR *pmk)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::SetMoniker()", "", MB_OK);
#endif

	return E_NOTIMPL;
}

#if 0
HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::GetMoniker( 
      /* [in] */ DWORD dwAssign,
      /* [in] */ DWORD dwWhichMoniker,
      /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
{
#ifdef _DEBUG
	MessageBox(NULL, "CLHTMLActiveDocument::GetMoniker()", "", MB_OK);
#endif

	return E_NOTIMPL;
}
  
HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::InitFromData( 
      /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
      /* [in] */ BOOL fCreation,
      /* [in] */ DWORD dwReserved)
{
#ifdef _DEBUG
	MessageBox(NULL, "CLHTMLActiveDocument::InitFromData()", "", MB_OK);
#endif

	return E_NOTIMPL;
}
  
HRESULT STDMETHODCALLTYPE CLHTMLActiveDocument::GetClipboardData( 
      /* [in] */ DWORD dwReserved,
      /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDataObject)
{
#ifdef _DEBUG
	MessageBox(NULL, "CLHTMLActiveDocument::GetClipboardData()", "", MB_OK);
#endif

	return E_NOTIMPL;
}
#endif


#if 0
// Override DoVerb
STDMETHODIMP CLHTMLActiveDocument::DoVerb(LONG iVerb, LPMSG pMsg, IOleClientSite* pActiveSite, LONG lindex,
								 HWND hwndParent, LPCRECT lprcPosRect)
{
	// Check if we should activate as a docobject or not
	// (client supports IOleDocumentSite)
	if (m_bDocObject)
	{
		switch (iVerb)
		{
		case OLEIVERB_SHOW:
		case OLEIVERB_OPEN:
		case OLEIVERB_UIACTIVATE:
			if (!m_bUIActive)
				return m_spDocSite->ActivateMe(NULL);
		break;
		}
	}
	return IOleObjectImpl<CLHTMLActiveDocument>::DoVerb(iVerb, pMsg, pActiveSite, lindex, hwndParent, lprcPosRect);
}
#endif

#if 0
HRESULT CLHTMLActiveDocument::GetHlinkFrame(IHlinkFrame* *pVal)
{
	CComPtr<IHlinkFrame> pHlinkFrame;

	CComQIPtr<IOleClientSite> pCS = m_spClientSite;//m_lpClientSite;
	CComQIPtr<IServiceProvider> pSP = pCS;
	if (pSP)
		pSP->QueryService(SID_SHlinkFrame, IID_IHlinkFrame, (void**)&pHlinkFrame);
	
#if 0
	if (pHlinkFrame == NULL) // Try complicated way
	{
		CComQIPtr<IOleInPlaceSite> pIPS = m_view->m_spInPlaceSite;//pCS;

		CComPtr<IOleInPlaceFrame> pIPF;
		CComPtr<IOleInPlaceUIWindow> pIPUI;
		RECT pos, clip;
		OLEINPLACEFRAMEINFO frameInfo;
		pIPS->GetWindowContext(&pIPF, &pIPUI, &pos, &clip, &frameInfo);
		pIPF->QueryInterface(IID_IHlinkFrame, (void**)&pHlinkFrame);
	}
#endif

	*pVal = pHlinkFrame.Detach();

	return S_OK;
}

HRESULT CLHTMLActiveDocument::HaveBrowseContext()
{
	if (m_pHBC == NULL)
	{
		CComPtr<IHlinkFrame> phlFrame;
		GetHlinkFrame(&phlFrame);

		if (phlFrame!=NULL)
		    phlFrame->GetBrowseContext(&m_pHBC);

		if(m_pHBC==NULL)
			HlinkCreateBrowseContext(NULL,IID_IHlinkBrowseContext,(void**)&m_pHBC);

		if (m_pHBC != NULL)
		{	
			// register with the browse context
			//IMonikerPtr pMoniker;
			//pMoniker.Attach(GetMoniker(OLEGETMONIKER_FORCEASSIGN));
			m_pHBC->Register(0,
											GetUnknown(),//GetInterface((void*)&IID_IUnknown), 
											m_curMoniker, 
											&m_dwRegHBC);

			// because we want the user to be able to come back to this
			// object via GoBack functionality add self to the 
			// navigation stack. This effectively tells the browse context
			// that the current hyperlink container referred to by pMoniker 
			// is a member (at the top) of the navigation stack
			//AddCurrentLocationToBrowseContext(GetViewForNavigate());

		//	m_pHBC->OnNavigateHlink(0, m_curMoniker, L"test", L"test", NULL);

		}
		else
		{
			ATLASSERT(0);
			return E_FAIL;
			//abort();
		}
	}

	return S_OK;
//	return m_pIHlinkBrowseContext;
}

// IHlinkTarget
STDMETHODIMP CLHTMLActiveDocument::SetBrowseContext(IHlinkBrowseContext* pihlbc)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::IHlinkTarget::SetBrowseContext()", "", MB_OK);
#endif

	if (m_pHBC)
	{
		// un-register with current browse context
		HRESULT hr = m_pHBC->Revoke(m_dwRegHBC);
		ATLASSERT(SUCCEEDED(hr));

		m_pHBC.Release();
	}
	
	m_pHBC = pihlbc;
	
	if (m_pHBC)
	{
	// register with browse context
		CComPtr<IMoniker> pmkThis = m_curMoniker;

		/*
		GetMoniker(
			pThis->GetMoniker((OLEGETMONIKER)OLEGETMONIKER_FORCEASSIGN);
			*/
		//LPUNKNOWN pUnk;
		//pThis->InternalQueryInterface(&IID_IUnknown, (void**)&pUnk);
		HRESULT hr = m_pHBC->Register(0, GetUnknown(), pmkThis, &m_dwRegHBC);
		ATLASSERT(SUCCEEDED(hr));
	}

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::GetBrowseContext(IHlinkBrowseContext** ppihlbc)
{
#ifdef _DEBUG
//	::MessageBox(NULL, "CLHTMLActiveDocument::IHlinkTarget::GetBrowseContext()", "", MB_OK);
#endif

	if (ppihlbc == NULL) return E_POINTER;
	*ppihlbc = m_pHBC;
	if (*ppihlbc) (*ppihlbc)->AddRef();
	return S_OK;
}

// IHlinkTarget::Navigate:
//		PARAMS:
//		grfHLNF - enumerated value indicating types of navigation (INTERNALJUMP, NAVIGATINGBACK, etc.)
//		pwzJumpLocation - LPCWSTR indicating sublocation in this hyperlink target (ala "#book1")
//		DESCRIPTION:
//		This function is called by the hyperlinking framework to indicate that this document
//		has been identified as the recipient of a hyperlink navigation. The document needs to
//		activate itself in its container or show itself as appropriate. Then it needs to inform
//		the hyperlinking framework that the navigation has succeeded. Next, the window positions
//		need to be resized to match those of the last hyperlink in the nav. This maintains the
//		illusion of a browser jump even if we're not in a hyperlink-frame. Finally, the doc needs to
//		jump to requested sub-location in the view
STDMETHODIMP CLHTMLActiveDocument::Navigate(DWORD grfHLNF, LPCWSTR pwzJumpLocation)
{
#ifdef _DEBUG
//	::MessageBox(NULL, "CLHTMLActiveDocument::IHlinkTarget::Navigate()", "", MB_OK);
#endif

	/*
	HaveBrowseContext();
*/

	CComPtr<IHlinkFrame> pHlinkFrame;
	GetHlinkFrame(&pHlinkFrame);

	ULONG uHLID;
	//HRESULT hr = m_pHBC->OnNavigateHlink(grfHLNF, m_curMoniker, pwzJumpLocation, pwzJumpLocation, &uHLID);

	HRESULT hr = ::HlinkOnNavigate(pHlinkFrame, m_pHBC, grfHLNF, m_curMoniker, pwzJumpLocation, L"test"/*pwzJumpLocation*//*m_friendlyName*/, &uHLID);
	ATLASSERT(SUCCEEDED(hr));

	{	// ??
		CComQIPtr<IOleDocumentSite> spOleDocSite = m_spClientSite;

		spOleDocSite->ActivateMe(NULL);
	}

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::GetMoniker(LPCWSTR pwzLocation, DWORD dwAssign, IMoniker** ppimkLocation)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::IHlinkTarget::GetMoniker()", "", MB_OK);
#endif

	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLActiveDocument::GetFriendlyName(LPCWSTR pwzLocation, LPWSTR* ppwzFriendlyName)
{
#ifdef _DEBUG
	::MessageBox(NULL, "CLHTMLActiveDocument::IHlinkTarget::GetFriendlyName()", "", MB_OK);
#endif

	return E_NOTIMPL;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// IHlinkSite

#if 0
STDMETHODIMP CLHTMLActiveDocument::QueryService(DWORD dwSiteData, REFGUID guidService,
	REFIID riid, IUnknown __RPC_FAR *__RPC_FAR *ppiunk)
{
#ifdef _DEBUG
//	::MessageBox(NULL, "CLHTMLActiveDocument::IHlinkSite::QueryService()", "", MB_OK);
#endif

	if (riid == IID_IHlinkTarget)
		*ppiunk = static_cast<IHlinkTarget*>(this);
	else
		return E_NOINTERFACE;

	(*ppiunk)->AddRef();

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::GetMoniker(DWORD dwSiteData, DWORD dwAssign,
	DWORD dwWhich, IMoniker __RPC_FAR *__RPC_FAR *ppimk)
{
#ifdef _DEBUG
//	::MessageBox(NULL, "CLHTMLActiveDocument::GetMoniker()", "", MB_OK);
#endif

	if (ppimk == NULL) return E_POINTER;
	*ppimk = NULL;

	if (dwWhich == OLEWHICHMK_CONTAINER)
	{
		*ppimk = m_curMoniker;
		if (*ppimk) (*ppimk)->AddRef();
	}
	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::ReadyToNavigate(DWORD dwSiteData, DWORD dwReserved)
{
#ifdef _DEBUG
//	::MessageBox(NULL, "CLHTMLActiveDocument::ReadyToNavigate()", "", MB_OK);
#endif

	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::OnNavigationComplete(DWORD dwSiteData, DWORD dwreserved,
	HRESULT hrError, LPCWSTR pwzError)
{
	USES_CONVERSION;

#ifdef _DEBUG
//	::MessageBox(NULL, "CLHTMLActiveDocument::OnNavigationComplete()", "", MB_OK);
#endif

	if (FAILED(hrError))
	{
		if (pwzError == NULL)
			pwzError = L"Failed to  open document";

		HWND hWnd;
		/*
		if (m_hWnd)
			hWnd = m_hWnd;
		else
		*/
			hWnd = NULL;

		::MessageBox(hWnd, W2A(pwzError), "", MB_OK);
	}

	return S_OK;
}
#endif

///////////////////////////////////////////////////////////////

STDMETHODIMP CLHTMLActiveDocument::GetTextData(ITextData **pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_textData;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLHTMLActiveDocument::GetDocument(ILDOMDocument **pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

void CLHTMLActiveDocument::OnSVGLoad(ILDOMElement* element)
{
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			OnSVGLoad(element);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	CComBSTR namespaceURI;
	element->get_namespaceURI(&namespaceURI);

	if (namespaceURI.Length() && !wcscmp(namespaceURI, L"http://www.w3.org/2000/svg"))
	{
		CComQIPtr<ILDOMDocumentEvent> documentEvent = m_document;
		ATLASSERT(documentEvent);

		CComPtr<ILDOMEvent> evt;
		documentEvent->createEvent(L""/*UIEvents"*/, &evt);

		evt->initEvent(L"SVGLoad",
			VARIANT_FALSE,	// bubbles
			VARIANT_FALSE	// cancelable
		);

		if (evt)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = element;//static_cast<IBase*>(this);
			ATLASSERT(eventTarget);

			VARIANT_BOOL doDefault;
			eventTarget->dispatchEvent(evt, &doDefault);
		}
	}
}
