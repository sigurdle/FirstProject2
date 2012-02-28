// EXMLLayoutView.h : Declaration of the CEXMLLayoutView

#ifndef __EXMLLAYOUTVIEW_H_
#define __EXMLLAYOUTVIEW_H_

#include "resource.h"       // main symbols

//class CLSVGBehavior;

#include "MarkupBar.h"
#include "LXMLEditorApp.h"	// TODO remove

namespace System
{

class IDataObject;

namespace LXmlEdit
{
class CEXMLViewGroup;	// TODO remove

class CEXMLLayoutView : 
public UI::ProcessTargetCommands,	// ILXUIEventListener

public UI::CViewGroup,

#if 0
//	public IOleDocumentSite,
//	public IOleClientSite,
//	public IAdviseSink,
	public IOleInPlaceSite,	// IOleWindow
	public IOleInPlaceUIWindow, // IOleWindow

	public IOleContainer,	// Here ?

///////
	public IHlinkTarget,	// Not sure if that should be on this object
	public IHlinkSite,
///////

	public ILDocHostUIHandler,
#endif

#if 0
	public IXMLDocumentInMemoryProvider,
#endif
//	public IDropTarget

public UI::Control

#if 0
	public IDispEventImpl<2, CEXMLLayoutView, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>,
	public IDispEventImpl<3, CEXMLLayoutView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
	public IDispEventImpl<4, CEXMLLayoutView, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib, 1, 0>
#endif
{
public:

	CEXMLLayoutView();
	~CEXMLLayoutView();

//	int FinalConstruct();
//	void FinalRelease();

	UI::CView* m_view;

//	CScrollBar m_sizeGrip;

	CMarkupBar m_markupBar;

	Web::Document* m_viewDocument;

//	CLSVGBehavior* m_pBehavior;

	int m_dragging;
	LDraw::PointD m_oldpoint;

	LDraw::PointD m_rulerOffset;
	bool m_bShowRulers;
	bool m_bShowTransparencyGrid;

	Web::CSSUnitType m_horRulerUnits;
	Web::CSSUnitType m_verRulerUnits;

	UI::Control* m_rulerElement;

	LDraw::Bitmap* m_pSkinBitmap;

	double m_marginLeft;
	double m_marginRight;
	double m_textIndent;

	CEXMLViewGroup* m_viewGroup;

// Container
	/*
	CComPtr<IUnknown> m_spUnknown;
	CComQIPtr<IOleObject> m_spOleObject;
	CComQIPtr<IOleDocument> m_spOleDocument;
	*/
	//CComQIPtr<IOleInPlaceObject> m_pIOleIPObject;

#if 0
	CComQIPtr<IOleDocumentView> m_pIOleDocView;
#endif

//	CComPtr<IOleInPlaceActiveObject> m_pIOleIPActiveObject;

	/*
	CComPtr<IStorage> m_pIStorage;
	CComPtr<IStorage> m_pIStorage2;
	CComPtr<IStream> m_pIStream;
   IBindCtx*			m_pbctx;
	DWORD m_dwAdvise;
	*/

	long OnViewTransformPage(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

//	CComPtr<ILPresentation> m_presentation;

	//

	//CComPtr<IHlinkBrowseContext> m_pIHlinkBrowseContext;	// TODO remove ??

	void OnSize();

	void CopyTargetObjectsToClipboard(IDataObject* dataObject);

	void ClearSelection();
	void ClearTargetObjects();

	ErrorCode ShowViews(IEFrame* pFrame);

	// CViewGroup
	virtual int OnGroupActivate(bool bActive);
	virtual int OnGroupClose();

	/*
	void InvalidateRect(LPRECT lprect)
	{
	}

	void GetClientRect(LPRECT lprect)
	{
		lprect->left = 0;
		lprect->top = 0;
		lprect->right = 300;
		lprect->bottom = 300;
	}
	*/

	virtual void handleEvent(System::Event* evt);

// ILXUIControlSited
//	CComPtr<ILElementBehaviorSite> m_behaviorSite;
#if 0
	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
	{
		m_behaviorSite = pBehaviorSite;
		OnCreate();
		return S_OK;
	}
	STDMETHODIMP Detach()
	{
		OnDestroy();
		m_behaviorSite.Release();
		return S_OK;
	}
#endif

#if 0
BEGIN_SINK_MAP(CEXMLLayoutView)
   SINK_ENTRY_EX(2, DIID__ILHTMLWindowEvents, /*dispid*/1, OnScroll)
   SINK_ENTRY_EX(2, DIID__ILHTMLWindowEvents, /*dispid*/2, OnZoom)
   SINK_ENTRY_EX(2, DIID__ILHTMLWindowEvents, /*dispid*/3, OnResize)

   SINK_ENTRY_EX(3, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
//	SINK_ENTRY_EX(4, DIID__ILHTMLActiveDocumentEvents, 1, OnSelect)
END_SINK_MAP()
#endif
	void __stdcall OnScroll()
	{
		OnChangeViewBox();
	}

	void __stdcall OnZoom()
	{
		OnChangeViewBox();
	}

	void __stdcall OnResize()
	{
		OnChangeViewBox();
	}

	void OnChangeViewBox()
	{
		Invalidate();	// TODO, only rulers
	}

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);

//	virtual void CalculateBoundsAndChildren(LDraw::SizeD availSize);
	virtual void OnRender(UI::Graphics* pGraphics);

//	void __stdcall OnSelect(/*Web::Event* evt*/);


	/*
BEGIN_MSG_MAP(CEXMLLayoutView)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
END_MSG_MAP()
*/

//	ErrorCode(Draw)(ILCanvas* canvas);

//	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnCreate();
	long OnDestroy();
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnLButtonDown();
	long OnLButtonUp();
	long OnMouseMove();

DECLARE_CMD_MAP(CEXMLLayoutView)

	long OnEditClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditClearUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	long OnEditCopy(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnEditPasteSpecial(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditPasteSpecialUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnObjectConvertToPath(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnObjectConvertToPathUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnShowMarkup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnShowMarkupUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnViewZoomIn(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnViewZoomOut(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnViewActualSize(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnViewRulers(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewRulersUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	long OnViewTransparencyGrid(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewTransparencyGridUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	long OnMakeGuides(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnReleaseGuides(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnObjectAlignHorizontalLeft(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnEditPaint(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectEditMask(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectEditClippingPath(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnObjectEditFilter(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnObjectEditPaintUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnObjectEditMaskUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnObjectEditClippingPathUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnObjectEditFilterUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnInsertImage(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertTable(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// IXMLDocumentInMemoryProvider,
//	STDMETHODIMP GetInMemoryDocument(BSTR uri, Web::Document* *pVal);

// IEXMLLayoutView
public:
//	ErrorCode(get_webEditControl)(/*[out, retval]*/ IWebEditControl* *pVal);
//	ErrorCode(get_ESvgDocument)(/*[out, retval]*/ IEXMLDocument* *pVal);
// IUIDlg
	ErrorCode OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView);
#if 0
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Layout");
		return S_OK;
	}
#endif
// ICommandTarget
//	ErrorCode(OnCmdMsg)(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled);

// Web::EventListener
	void handleEvent(Web::Event* evt);

#if 0
// IAdviseSink
     virtual /* [local] */ void STDMETHODCALLTYPE OnDataChange( 
         /* [unique][in] */ FORMATETC __RPC_FAR *pFormatetc,
         /* [unique][in] */ STGMEDIUM __RPC_FAR *pStgmed)
	{
		  ::MessageBox(NULL, "ActivateMe", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnViewChange( 
         /* [in] */ DWORD dwAspect,
         /* [in] */ LONG lindex)
	{
		  ::MessageBox(NULL, "OnViewChange", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnRename( 
         /* [in] */ IMoniker __RPC_FAR *pmk)
	{
		  ::MessageBox(NULL, "OnRename", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnSave( void)
	{
		  ::MessageBox(NULL, "OnSave", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnClose( void)
	{
		  ::MessageBox(NULL, "OnClose", "", MB_OK);
	}

// IOleDocumentSite

	  virtual ErrorCode STDMETHODCALLTYPE ActivateMe( 
            /* [in] */ IOleDocumentView __RPC_FAR *pViewToActivate);

// IOleClientSite
        virtual ErrorCode STDMETHODCALLTYPE SaveObject( void)
	{
		  ::MessageBox(NULL, "SaveObject", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE GetMoniker( 
            /* [in] */ DWORD dwAssign,
            /* [in] */ DWORD dwWhichMoniker,
            /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	{
    return E_NOTIMPL;
	 ::MessageBox(NULL, "GetMoniker", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE GetContainer( 
            /* [out] */ IOleContainer __RPC_FAR *__RPC_FAR *ppContainer)
	{
			  if (ppContainer == NULL) return NULL;

	  		(*ppContainer=this)->AddRef();
//		 MessageBox(NULL, "GetContainer", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE ShowObject( void)
	{
			  return S_OK;
			  ::MessageBox(NULL, "ShowObject", "", MB_OK);
		 return S_OK;
	}

        virtual ErrorCode STDMETHODCALLTYPE OnShowWindow( 
            /* [in] */ bool fShow)
	{
			  return S_OK;
			  ::MessageBox(NULL, "OnShowWindow", "", MB_OK);
		 return S_OK;
	}

        virtual ErrorCode STDMETHODCALLTYPE RequestNewObjectLayout( void)
	{
	    return E_NOTIMPL;
		 ::MessageBox(NULL, "RequestNewObjectLayout", "", MB_OK);
		 return S_OK;
	}
#endif

		// IOleWindow
#if 0
   ErrorCode(GetWindow)(/*[out]*/ UI::Control* __RPC_FAR *phwnd)
	{
		ATLASSERT(phwnd != NULL);
		if (phwnd == NULL) return E_POINTER;
		*phwnd = m_hWnd;
		return S_OK;
	}

	virtual ErrorCode STDMETHODCALLTYPE ContextSensitiveHelp( 
            /* [in] */ bool fEnterMode)
	{
			  ::MessageBox(NULL, "ContextSensitiveHelp", "", MB_OK);
		 return S_OK;
	}

	// IOleInPlaceSite
        virtual ErrorCode STDMETHODCALLTYPE CanInPlaceActivate( void)
	{
		 return S_OK;
		 ::MessageBox(NULL, "CanInPlaceActivate", "", MB_OK);
		 return S_OK;
	}

   virtual ErrorCode STDMETHODCALLTYPE OnInPlaceActivate( void);
        

/*
 * CImpIOleInPlaceSite::OnUIActivate
 *
 * Purpose:
 *  Informs the container that the object is going to start munging
 *  around with user interface, like replacing the menu.  The
 *  container should remove any relevant UI in preparation.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  ErrorCode         NOERROR or an appropriate error code.
 */
    virtual ErrorCode STDMETHODCALLTYPE OnUIActivate( void)
	{
		 //MessageBox(NULL, "OnUIActivate", "", MB_OK);
		 return S_OK;
	}
        
	 virtual ErrorCode STDMETHODCALLTYPE GetWindowContext( 
		 /* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame,
		 /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc,
		 /* [out] */ LPRECT lprcPosRect,
		 /* [out] */ LPRECT lprcClipRect,
		 /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo);
        
        virtual ErrorCode STDMETHODCALLTYPE Scroll( 
            /* [in] */ SIZE scrollExtant)
	{
		 ::MessageBox(NULL, "Scroll", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE OnUIDeactivate( 
            /* [in] */ bool fUndoable)
	{
			  ::MessageBox(NULL, "OnUIDeactivate", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE OnInPlaceDeactivate( void)
	{
			  ::MessageBox(NULL, "OnInPlaceDeactivate", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE DiscardUndoState( void)
	{
			  ::MessageBox(NULL, "DiscardUndoState", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE DeactivateAndUndo( void)
	{
			  ::MessageBox(NULL, "DeactivateAndUndo", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE OnPosRectChange( 
            /* [in] */ LPCRECT lprcPosRect)
	{
			  ::MessageBox(NULL, "OnPosRectChange", "", MB_OK);
		 return S_OK;
	}
#endif

#if 0
// IOleInPlaceUIWindow
     virtual /* [input_sync] */ ErrorCode STDMETHODCALLTYPE GetBorder( 
         /* [out] */ LPRECT lprectBorder)
	  {
		  GetClientRect(lprectBorder);
		  return S_OK;
	  }
     
     virtual /* [input_sync] */ ErrorCode STDMETHODCALLTYPE RequestBorderSpace( 
         /* [unique][in] */ LPCBORDERWIDTHS pborderwidths)
	  {
	//Framer has no border space restrictions
	return NOERROR;
	  }
     
     virtual /* [input_sync] */ ErrorCode STDMETHODCALLTYPE SetBorderSpace( 
         /* [unique][in] */ LPCBORDERWIDTHS pborderwidths)
	  {
		  ::MessageBox(NULL, "IOleInPlaceUIWindow::SetBorderSpace", "", MB_OK);

		  CRect rc;
		  GetClientRect(&rc);
	     m_pIOleDocView->SetRect(&rc);
		  return S_OK;
	  }
     
     virtual ErrorCode STDMETHODCALLTYPE SetActiveObject( 
         /* [unique][in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
         /* [unique][string][in] */ LPCOLESTR pszObjName)
	  {
		  //ATLASSERT(0);
//			m_pIOleIPActiveObject = pActiveObject;

		 // MessageBox(NULL, "IOleInPlaceUIWindow::SetActiveObject", "", MB_OK);
		  return S_OK;
	  }
#endif

	  /*
// IHlinkSite
	ErrorCode(QueryService)(DWORD dwSiteData, REFGUID guidService,
		REFIID riid, IUnknown __RPC_FAR *__RPC_FAR *ppiunk);     
	ErrorCode(GetMoniker)(DWORD dwSiteData, DWORD dwAssign,
		DWORD dwWhich, IMoniker __RPC_FAR *__RPC_FAR *ppimk);     
	ErrorCode(ReadyToNavigate)(DWORD dwSiteData, DWORD dwReserved); 
	ErrorCode(OnNavigationComplete)(DWORD dwSiteData, DWORD dwreserved,
		ErrorCode hrError, LPCWSTR pwzError);

// IHlinkTarget
	ErrorCode(SetBrowseContext)(IHlinkBrowseContext* pihlbc);
	ErrorCode(GetBrowseContext)(IHlinkBrowseContext** ppihlbc);
	ErrorCode(Navigate)(DWORD grfHLNF, LPCWSTR pwzJumpLocation);
	ErrorCode(GetMoniker)(LPCWSTR pwzLocation, DWORD dwAssign, IMoniker** ppimkLocation);
	ErrorCode(GetFriendlyName)(LPCWSTR pwzLocation, LPWSTR* ppwzFriendlyName);
*/
#if 0
// ILDocHostUIHandler
	ErrorCode(GetDropTarget)(/*[in]*/ IDropTarget* pDropTarget, /*[out,retval]*/ IDropTarget** ppDropTarget)
	{
		return E_NOTIMPL;
	}

// IParseDisplayName/IOleContainer
  virtual ErrorCode STDMETHODCALLTYPE ParseDisplayName( 
      /* [unique][in] */ IBindCtx *pbc,
      /* [in] */ LPOLESTR pszDisplayName,
      /* [out] */ ULONG *pchEaten,
      /* [out] */ IMoniker **ppmkOut)
  {
	  return S_OK;
  }

  virtual ErrorCode STDMETHODCALLTYPE EnumObjects( 
      /* [in] */ DWORD grfFlags,
      /* [out] */ IEnumUnknown **ppenum)
  {
	  return S_OK;
  }
  
  virtual ErrorCode STDMETHODCALLTYPE LockContainer( 
      /* [in] */ bool fLock)
  {
	  return S_OK;
  }
#endif
};

/*
class ATL_NO_VTABLE CEXMLLayoutFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILXUIControlSitedFactory
{
public:
	CEXMLLayoutFactory()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEXMLLayoutFactory)
	COM_INTERFACE_ENTRY(ILXUIControlSitedFactory)
END_COM_MAP()

public:
// ILXUIControlSitedFactory
	STDMETHODIMP FindBehavior(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILXUIControlSitedSite* pSite, ILXUIControlSited** ppBehavior)
	{
		CComObject<CEXMLLayoutView>* p;
		CComObject<CEXMLLayoutView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
		else
		{
			*ppBehavior = NULL;
		}

		return S_OK;
	}
};
*/

#endif //__EXMLLAYOUTVIEW_H_

}	// LXmlEdit
}
