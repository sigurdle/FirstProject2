// LHTMLDocumentView.cpp : Implementation of CLHTMLDocumentView
#include "stdafx.h"

#if 0

#include "LAXMLViewer.h"
#include "LHTML2.h"
#include "LHTMLDocumentView.h"

#include "LHTMLActiveDocument.h"

//#include "HTMControlFrameBase.h"
#if 0
#include "HTMFrameSet.h"
#include "HTMFrame.h"
#endif
//#include "HTMLDialog.h"

#include "LHTMLWindow.h"

/////////////////////////////////////////////////////////////////////////////
// CLHTMLDocumentView

CLHTMLDocumentView::CLHTMLDocumentView()
{
	m_rect.SetRectEmpty();

//	m_dragging = 0;
//	m_pSizeFrame = NULL;

//	m_oleFrame = NULL;

	m_pDocument = NULL;
	m_view = NULL;
	m_pWindow = NULL;

	m_framesDesign = VARIANT_FALSE;
}

CLHTMLDocumentView::~CLHTMLDocumentView()
{
	ATLASSERT(m_pWindow == NULL);

	ATLASSERT("~CLHTMLDocumentView()\n");
}

void CLHTMLDocumentView::FinalRelease()
{
	if (m_pWindow)
	{
#if 0
		m_pWindow->Free();
#endif
		m_pWindow->Release();
		m_pWindow = NULL;
	}
}

LRESULT CLHTMLDocumentView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	/*
	int success = SetICMMode(dc.m_hDC, ICM_ON);
	ATLASSERT(success);
	*/

//#if 0
	CRect client;
	GetClientRect(&client);

	CRect clip;
	dc.GetClipBox(&clip);
/*
	dc.FillSolidRect(&clip, RGB(255, 0, 0));
	Sleep(25);
*/
	LPBITMAPINFO m_lpbmi = (LPBITMAPINFO)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));
	if (m_lpbmi)
	{
	// Allocate a bitmap just the size of the invalid clip rect
		m_lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_lpbmi->bmiHeader.biWidth = clip.Width();
		m_lpbmi->bmiHeader.biHeight = clip.Height();
		m_lpbmi->bmiHeader.biBitCount = 24;
		m_lpbmi->bmiHeader.biPlanes = 1;

		HBITMAP hTBitmap;
		LPBYTE TBits = NULL;

		//if (hTBitmap = CreateDIBSection(NULL, m_lpbmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
		{
			HDC hTDC = CreateCompatibleDC(dc.m_hDC);

			hTBitmap = CreateCompatibleBitmap(dc.m_hDC, clip.Width(), clip.Height());

			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

		//	FillSolidRect(hTDC, 0, 0, clip.Width(), clip.Height(), RGB(190, 190, 190));
		//	FillSolidRect(hTDC, 0, 0, clip.Width(), clip.Height(), RGB(255, 255, 255));

			POINT oldOrg;
			SetViewportOrgEx(hTDC, -clip.left, -clip.top, &oldOrg);

// TODO, maybe don't have this
#if 0
			FillSolidRect(hTDC, &client, GetSysColor(COLOR_BTNFACE));
#endif

		//	OffsetViewportOrgEx(hTDC, m_client.left, m_client.top, NULL);

			if (m_pWindow)
			{
				m_pWindow->m_pCanvas->OnPaint(hTDC);
			}

			SetViewportOrgEx(hTDC, oldOrg.x, oldOrg.y, NULL);

			dc.BitBlt(clip.left, clip.top, clip.Width(), clip.Height(), hTDC, 0, 0, SRCCOPY);

			SelectObject(hTDC, hOldBitmap);
			DeleteObject(hTBitmap);
			DeleteDC(hTDC);
		}
		GlobalFree(m_lpbmi);
	}

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->DrawCaret(dc.m_hDC);
	}
//#endif
/*
	if (m_pSizeFrame)
	{
		m_pSizeFrame->DrawCaret(dc.m_hDC);
	}
*/
	return 0;
}

//////////

// IViewObject
 /* [local] */ STDMETHODIMP CLHTMLDocumentView::Draw( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ LONG lindex,
         /* [unique][in] */ void *pvAspect,
         /* [unique][in] */ DVTARGETDEVICE *ptd,
         /* [in] */ HDC hdcTargetDev,
         /* [in] */ HDC hdcDraw,
         /* [in] */ LPCRECTL lprcBounds,
         /* [unique][in] */ LPCRECTL lprcWBounds,
         /* [in] */ BOOL ( STDMETHODCALLTYPE *pfnContinue )( 
             ULONG_PTR dwContinue),
         /* [in] */ ULONG_PTR dwContinue)
{
	CDCHandle hTDC(hdcDraw);
	CRect client = *(CRect*)lprcBounds;

	POINT oldOrg;
	SetViewportOrgEx(hTDC, client.left, client.top, &oldOrg);

// TODO, maybe don't have this
	hTDC.FillSolidRect(&client, GetSysColor(COLOR_BTNFACE));

//	OffsetViewportOrgEx(hTDC, m_client.left, m_client.top, NULL);

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnPaint(hTDC);
	}

	SetViewportOrgEx(hTDC, oldOrg.x, oldOrg.y, NULL);

	return S_OK;
}

//////////
LRESULT CLHTMLDocumentView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
// Don't erase anything, everything is drawn in OnPaint
	return TRUE;
}

LRESULT CLHTMLDocumentView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::RegisterDragDrop(m_hWnd, static_cast<IDropTarget*>(this));

	return 0;
}

LRESULT CLHTMLDocumentView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO Set m_pFrame m_pUI to NULL

	::RevokeDragDrop(m_hWnd);

	return 0;
}

LRESULT CLHTMLDocumentView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	OnSize();	// ??
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CLHTMLDocumentView::OnSize()
{
	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->m_client = CRect(0, 0, m_rect.Width(), m_rect.Height());//client;
		//m_pWindow->PositionFrames();
		m_pWindow->m_pCanvas->OnSize();
	}
}

/*
void CHTMLControl::SetDialogArguments(VARIANT* variant)
{
	m_dialogArguments = *variant;
}
*/

/*
long CLHTMLDocumentView::OnAdvancePlay(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CHTMFrame* pFrame = (CHTMFrame*)wParam;

	pFrame->AdvancePlay();

	return 0;
}
*/

LRESULT CLHTMLDocumentView::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CLHTMLDocumentView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;
	int iButton = 0;
	BOOL bDblClk = FALSE;

	CPoint screenpt = point;

//	HWND hwnd = m_hWnd;

	SetFocus();

//	if (!m_dragging)
	{
		if (m_pWindow)
		{
			//m_pSizeFrame = NULL;
			/*m_dragging =*/ m_pWindow->m_pCanvas->OnButtonDown(nFlags, screenpt, point, iButton, bDblClk, NULL/*m_pSizeFrame*/);

			/*
			if (m_dragging)
			{
				ATLASSERT(m_pSizeFrame);
#if 0
				SetCapture();
#endif
			}
			*/
		}
	}

	return 0;
}

LRESULT CLHTMLDocumentView::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;
	int iButton = 2;
	BOOL bDblClk = FALSE;

	CPoint screenpt = point;

	SetFocus();

	//if (!m_dragging)
	{
		if (m_pWindow)
		{
			//m_pSizeFrame = NULL;
			/*m_dragging =*/ m_pWindow->m_pCanvas->OnButtonDown(nFlags, screenpt, point, iButton, bDblClk, NULL/*&m_pSizeFrame*/);

			/*
			if (m_dragging)
			{
				ASSERT(m_pSizeFrame);
				m_dragging = 1;
#if 0
				SetCapture();
#endif
			}
			*/
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CLHTMLDocumentView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	CPoint screenpt = point;

	if (m_pWindow)
//	if (m_dragging)
	{
	//	ATLASSERT(m_pSizeFrame);
	//	m_pSizeFrame->OnButtonUp(nFlags, point, 0);
		m_pWindow->m_pCanvas->OnButtonUp(nFlags, screenpt, point, 0);

		//m_pSizeFrame = NULL;
		//m_dragging = 0;
#if 0
		ReleaseCapture();
#endif
	}

	return 0;
}

CComBSTR GetCommaSeperatedString(WCHAR* str, int index);
CComBSTR SetCommaSeperatedString(WCHAR* str, WCHAR* value, int index);

long CLHTMLDocumentView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	CPoint screenpt = point;

	if (m_pWindow)
	//if (m_dragging)
	{
	//	ATLASSERT(m_pSizeFrame);
	//	m_pSizeFrame->OnMouseMove(nFlags, point);
		m_pWindow->m_pCanvas->OnMouseMove(nFlags, screenpt, point);
	}

	return 0;
}

LRESULT CLHTMLDocumentView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND)wParam;       // handle to window with cursor 
	int nHittest = LOWORD(lParam);  // hit-test code 
	int wMouseMsg = HIWORD(lParam); // mouse-message identifier 

	if (m_pWindow)
	{
		POINT clientpt;
		GetCursorPos(&clientpt);
		ScreenToClient(&clientpt);

		BOOL bRet = m_pWindow->m_pCanvas->OnSetCursor(clientpt);
		if (bRet)
			return bRet;
	}

	return DefWindowProc(uMsg, wParam, lParam);//FALSE;
}

LRESULT CLHTMLDocumentView::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nKey = wParam;
	int lKeyData = lParam;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnKeyDown(nKey, lKeyData);
	}

	return 0;
}

LRESULT CLHTMLDocumentView::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nKey = wParam;
	int lKeyData = lParam;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnKeyUp(nKey, lKeyData);
	}

	return 0;
}

LRESULT CLHTMLDocumentView::OnSysKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nVirtKey = (int)wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->m_bAlt = lKeyData & (1<<29);
		m_pWindow->m_pCanvas->OnKeyDown(nVirtKey, lKeyData);
	}

	return 0;
	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CLHTMLDocumentView::OnSysKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nVirtKey = (int) wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->m_bAlt = lKeyData & (1<<29);
		m_pWindow->m_pCanvas->OnKeyUp(nVirtKey, lKeyData);
	}

	return 0;
	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CLHTMLDocumentView::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	TCHAR nKey = wParam;
	int lKeyData = lParam;

	if (m_pWindow)
	{
		m_pWindow->m_pCanvas->OnChar(nKey, lKeyData);
	}

	return 0;
}

// virtual
HRESULT CLHTMLDocumentView::OnLink(BSTR href, BSTR target)
{
	HRESULT hr;

	CComPtr<IHlink> hlink;
	hr = HlinkCreateFromString(
		href,//LPCWSTR pwzTarget,    //String helping to identify the hyperlink target
		NULL,//L"location",//LPCWSTR pwzLocation,        //Location within the hyperlink target of new hyperlink object
		L"test",//LPCWSTR pwzFriendlyName,    //Friendly name of the hyperlink
		static_cast<IHlinkSite*>(m_pDocument),// pihlsite,      //Site for the new hyperlink object
		0,//DWORD dwSiteData,     //Additional site data for the new hyperlink object
		NULL,//IUnknown * piunkOuter,      //Whether or not object is part of an aggregate
		IID_IHlink,//REFIID riid,     //Interface identifier on new browse context object
		(void**)&hlink//, Void * ppvObj    //Location of the requested interface's pointer
		);

	if (hlink)
	{
		CComPtr<IHlinkFrame> phlFrame;
		m_pDocument->GetHlinkFrame(&phlFrame);

		hr = ::HlinkNavigate(hlink, phlFrame, 0, NULL, NULL/*static_cast<IBindStatusCallback*>(this)*/, m_pDocument->m_pHBC);
	}

	return hr;
}

//////////////////////////
// IDropTarget

STDMETHODIMP CLHTMLDocumentView::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	if (m_pWindow)
	{
//		m_pFrame->OnDragEnter(nKey, lKeyData);
	}

	return S_OK;
}

STDMETHODIMP CLHTMLDocumentView::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	if (m_pWindow)
	{
		*pdwEffect = m_pWindow->m_pCanvas->OnDragOver(NULL, grfKeyState, pt);
	}

	return S_OK;
}

STDMETHODIMP CLHTMLDocumentView::DragLeave()
{
	return S_OK;
}

STDMETHODIMP CLHTMLDocumentView::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	if (m_pWindow)
	{
		*pdwEffect = m_pWindow->m_pCanvas->OnDrop(pDataObject, grfKeyState, pt);
	}

	return S_OK;
}

#if 0
STDMETHODIMP CLHTMLDocumentView::AttachEditor(IHTMLEditorSite *site)
{
	site->AddRef();	// ??
	m_editors.Add(site);

	return S_OK;
}
#endif

// IOleDocumentView

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::SetInPlaceSite( 
   /* [unique][in] */ IOleInPlaceSite __RPC_FAR *pIPSite)
{
	if (m_spInPlaceSite)
	{
		UIActivate(FALSE);
		m_spInPlaceSite.Release();
	}

	m_spInPlaceSite = pIPSite;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::GetInPlaceSite( 
   /* [out] */ IOleInPlaceSite __RPC_FAR *__RPC_FAR *ppIPSite)
{
	if (ppIPSite == NULL) return E_POINTER;
	*ppIPSite = m_spInPlaceSite;
	if (*ppIPSite) (*ppIPSite)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::GetDocument( 
   /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk)
{
	if (ppunk == NULL) return E_POINTER;
	*ppunk = m_pDocument->GetUnknown();
	(*ppunk)->AddRef();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::SetRect(/* [in] */ LPRECT prcView)
{
	m_rect = *prcView;

	OnSize();

	if (m_hWnd)
	{
		MoveWindow(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), TRUE);
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::GetRect(/* [out] */ LPRECT prcView)
{
	if (prcView == NULL) return E_POINTER;
	*prcView = m_rect;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::SetRectComplex( 
   /* [unique][in] */ LPRECT prcView,
   /* [unique][in] */ LPRECT prcHScroll,
   /* [unique][in] */ LPRECT prcVScroll,
   /* [unique][in] */ LPRECT prcSizeBox)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::Show(/* [in] */ BOOL fShow)
{
	if (fShow)
	{
		if (m_hWnd == NULL)
		{
			HWND hWndParent;
			m_spInPlaceSite->GetWindow(&hWndParent);

			Create(hWndParent, m_rect, NULL, WS_CHILD, 0, 0);
		}

		if (m_hWnd)
			ShowWindow(SW_SHOW);

	// ??
#if 0
		if (m_pWindow->m_pFrameSet)
		{
			m_pWindow->m_pFrameSet->UIActivate();
		}
#endif
	}
	else
	{
		UIActivate(FALSE);
		if (m_hWnd)
			ShowWindow(SW_HIDE);
	}

	return S_OK;
}

HRESULT CLHTMLDocumentView::Init(CLHTMLActiveDocument* pDocument, IOleInPlaceSite* spInPlaceSite)
{
	m_pDocument = pDocument;
	m_spInPlaceSite = spInPlaceSite;

	CComQIPtr<ILDOMDocumentView> documentView = m_pDocument->m_document;
	documentView->createPresentation(&m_view);

	CComObject<CLHTMLWindow2>::CreateInstance(&m_pWindow);
	if (m_pWindow)
	{
		m_pWindow->AddRef();

		m_pWindow->m_pCanvas->m_pSite = this;

		m_pWindow->m_pCanvas->m_pView = static_cast<CHTMLDocumentView*>(m_view.p);
		m_pWindow->m_pCanvas->m_htmTree = m_pWindow->m_pCanvas->m_pView->m_pRootElement;
	}

#if 0
	ATLASSERT(m_pWindow == NULL);

	CComObject<CHTMLDocumentView>* pView;
	CComObject<CHTMLDocumentView>::CreateInstance(&pView);
	if (pView)
	{
		pView->AddRef();

		CComObject<CHTMLWindow>::CreateInstance(&m_pWindow);
		if (m_pWindow)
		{
			m_pWindow->AddRef();

			pView->m_pWindow = m_pWindow;
			m_pWindow->m_pView = pView;

			ATLASSERT(::IsWindow(m_hWnd));
			m_pWindow->m_hWnd = m_hWnd;
#if 0
			m_pWindow->m_pActiveDocument = m_document;
			m_pWindow->m_pUI = this;
#endif

			if (SUCCEEDED(pView->SetDocument(m_document->m_document)))
			{


				//m_pFrame->SetView(this);

			// hm...
				/*
				if (m_document->m_element)
					m_pFrame->SetElement(m_document->m_element);
				else
				*/
				//ATLASSERT(0);
		//#if 0
		//#endif
			}
		}
	}
#endif

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::UIActivate(/* [in] */ BOOL fUIActivate)
{
/*
if (fActivate)
    {
    UI activate the view (do menu merging, show frame level tools, process accelerators)
    Take focus, and bring the view window forward.
    }
else
    call IOleInPlaceObject::UIDeactivate on this view

*/

	if (fUIActivate)
	{
	}
	else
	{
		UIDeactivate();
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::Open(void)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::CloseView(DWORD dwReserved)
{
	Show(FALSE);
	SetInPlaceSite(NULL);

	if (m_pWindow)
	{
#if 0
		m_pWindow->Free();
#endif
		m_pWindow->Release();
		m_pWindow = NULL;
	}
	//PostMessage(WM_CLOSE);

	CHTMLDocumentView* pView = static_cast<CHTMLDocumentView*>(m_view.p);
	if (pView)
	{
		pView->Free();
		m_view.Release();
	}

	DestroyWindow();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::SaveViewState( 
   /* [in] */ LPSTREAM pstm)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::ApplyViewState( 
   /* [in] */ LPSTREAM pstm)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::Clone( 
   /* [in] */ IOleInPlaceSite __RPC_FAR *pIPSiteNew,
   /* [out] */ IOleDocumentView __RPC_FAR *__RPC_FAR *ppViewNew)
{
	return S_OK;
}

// IOleWindow
HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::GetWindow( 
            /* [out] */ HWND __RPC_FAR *phwnd)
{
	if (phwnd == NULL) return E_POINTER;
	*phwnd = m_hWnd;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::ContextSensitiveHelp( 
            /* [in] */ BOOL fEnterMode)
{
	return S_OK;
}

// IOleInPlaceObject
HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::InPlaceDeactivate( void)
{
	// TODO ??
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::UIDeactivate( void)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::SetObjectRects( 
            /* [in] */ LPCRECT lprcPosRect,
            /* [in] */ LPCRECT lprcClipRect)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::ReactivateAndUndo( void)
{
	return S_OK;
}

// IPrint

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::SetInitialPageNum( 
   /* [in] */ LONG nFirstPage)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::GetPageInfo( 
   /* [out] */ LONG __RPC_FAR *pnFirstPage,
   /* [out] */ LONG __RPC_FAR *pcPages)
{
	return S_OK;
}

/* [local] */ HRESULT __stdcall CLHTMLDocumentView::Print( 
   /* [in] */ DWORD grfFlags,
   /* [out][in] */ DVTARGETDEVICE __RPC_FAR *__RPC_FAR *pptd,
   /* [out][in] */ PAGESET __RPC_FAR *__RPC_FAR *ppPageSet,
   /* [unique][out][in] */ STGMEDIUM __RPC_FAR *pstgmOptions,
   /* [in] */ IContinueCallback __RPC_FAR *pcallback,
   /* [in] */ LONG nFirstPage,
   /* [out] */ LONG __RPC_FAR *pcPagesPrinted,
   /* [out] */ LONG __RPC_FAR *pnLastPage)
{
	return S_OK;
}

// IOleCommandTarget

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::QueryStatus( 
   /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
   /* [in] */ ULONG cCmds,
   /* [out][in][size_is] */ OLECMD __RPC_FAR prgCmds[  ],
   /* [unique][out][in] */ OLECMDTEXT __RPC_FAR *pCmdText)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLHTMLDocumentView::Exec(
   /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
   /* [in] */ DWORD nCmdID,
   /* [in] */ DWORD nCmdexecopt,
   /* [unique][in] */ VARIANT __RPC_FAR *pvaIn,
   /* [unique][out][in] */ VARIANT __RPC_FAR *pvaOut)
{
	return S_OK;
}

STDMETHODIMP CLHTMLDocumentView::get_framesDesign(VARIANT_BOOL *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_framesDesign;
	return S_OK;
}

STDMETHODIMP CLHTMLDocumentView::put_framesDesign(VARIANT_BOOL newVal)
{
	m_framesDesign = newVal;
	return S_OK;
}

STDMETHODIMP CLHTMLDocumentView::GetHTMLWindow(ILHTMLWindow **pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = m_pWindow;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif