// PageDesignerFrame.h : Declaration of the CPageDesignerFrame

#ifndef __PageDesignerFrame_H_
#define __PageDesignerFrame_H_

#include "resource.h"       // main symbols
#include "UICP.h"
//#include "WebEditorCP.h"
//#include "UICP.h"
//#include "UICP.h"

//#include "WebEditorCP.h"

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CPageDesignerFrame
class ATL_NO_VTABLE CPageDesignerFrame : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPageDesignerFrame, &CLSID_PageDesignerFrame>,
//	public IConnectionPointContainerImpl<CPageDesignerFrame>,

//	public IDispatchImpl<DispIPageDesignerFrame, &IID_DispIPageDesignerFrame, &LIBID_WEBEDITORLib>,

	public IPageDesignerFrame,

	public IPersist,
//	public IDispatchImpl<ICustomDraw, &IID_ICustomDraw, &LIBID_UILib>,

	public ICommandTarget,

	public IOleInPlaceFrame,
	public IOleCommandTarget,
	public CUIManagerImpl<CPageDesignerFrame>,
	public CUIMDIFrameImpl<CPageDesignerFrame, IUIFrame>,
	public IDispatchImpl<DispIPageDesignerFrame, &IID_DispIPageDesignerFrame, &LIBID_PAGEDESIGNERLib>
//	public CProxy_IUIManagerEvents< CPageDesignerFrame >
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_PAGEDESIGNERFRAME)

	CPageDesignerFrame()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	CComPtr<IOleInPlaceActiveObject> m_pIOleIPActiveObject;

//DECLARE_REGISTRY_RESOURCEID(IDR_PageDesignerFrame)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPageDesignerFrame)
	COM_INTERFACE_ENTRY(IPageDesignerFrame)
//	COM_INTERFACE_ENTRY2(IDispatch, DispIPageDesignerFrame)
	COM_INTERFACE_ENTRY(IDispatch)

	COM_INTERFACE_ENTRY(IPersist)

	COM_INTERFACE_ENTRY(ICommandTarget)
//	COM_INTERFACE_ENTRY(ICustomDraw)

	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceUIWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceFrame)
	COM_INTERFACE_ENTRY(IOleCommandTarget)

	COM_INTERFACE_ENTRY(IUIManager)

	COM_INTERFACE_ENTRY(IUIFrame)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

/*
BEGIN_CONNECTION_POINT_MAP(CPageDesignerFrame)
CONNECTION_POINT_ENTRY(DIID__IUIManagerEvents)
END_CONNECTION_POINT_MAP()
*/

	typedef CUIMDIFrameImpl<CPageDesignerFrame, IUIFrame> baseClass;

BEGIN_MSG_MAP(CPageDesignerFrame)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	CHAIN_MSG_MAP(baseClass)
END_MSG_MAP()

	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IPageDesignerFrame
public:

// IOleWindow
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow( 
         /* [out] */ HWND __RPC_FAR *phwnd)
	  {
		  *phwnd = m_hWnd;
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( 
         /* [in] */ BOOL fEnterMode)
	  {
		  return S_OK;
	  }

// IOleInPlaceUIWindow
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetBorder( 
         /* [out] */ LPRECT lprectBorder);
     
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE RequestBorderSpace( 
         /* [unique][in] */ LPCBORDERWIDTHS pborderwidths);
     
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetBorderSpace( 
         /* [unique][in] */ LPCBORDERWIDTHS pborderwidths)
	  {
		  ::MessageBox(NULL, "IOleInPlaceFrame::SetBorderSpace", "", MB_OK);
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetActiveObject( 
         /* [unique][in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
         /* [unique][string][in] */ LPCOLESTR pszObjName)
	  {
		  m_pIOleIPActiveObject = pActiveObject;
		  //MessageBox(NULL, "IOleInPlaceFrame::SetActiveObject", "", MB_OK);
		  return S_OK;
	  }

// IOleInPlaceFrame
	virtual HRESULT STDMETHODCALLTYPE InsertMenus( 
		/* [in] */ HMENU hmenuShared,
		/* [out][in] */ LPOLEMENUGROUPWIDTHS pMGW)
	{
	    pMGW->width[0]=0;//1;
	    pMGW->width[2]=0;
		 pMGW->width[4]=0;

		//MessageBox(NULL, "IOleInPlaceFrame::InsertMenus", "", MB_OK);
		return S_OK;
	}
	
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetMenu( 
	/* [in] */ HMENU hMenu,
	/* [in] */ HOLEMENU hOLEMenu,
	/* [in] */ HWND hWndObj)
	{
		HWND hwnd = m_hWnd;

    if (NULL!=hMenu)
        ::SetMenu(hwnd, hMenu);

    ::DrawMenuBar(hwnd);

	 HRESULT hr;

		hr=OleSetMenuDescriptor(hOLEMenu, hwnd, hWndObj, NULL, NULL);
		return hr;

//		MessageBox(NULL, "IOleInPlaceFrame::SetMenu", "", MB_OK);
		//return S_OK;
	}
	
	virtual HRESULT STDMETHODCALLTYPE RemoveMenus( 
	/* [in] */ HMENU hmenuShared)
	{
		::MessageBox(NULL, "IOleInPlaceFrame::RemoveMenus", "", MB_OK);
		return S_OK;
	}
	
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetStatusText( 
	/* [unique][in] */ LPCOLESTR pszStatusText);
	
	virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
	/* [in] */ BOOL fEnable)
	{
		//MessageBox(NULL, "IOleInPlaceFrame::EnableModeless", "", MB_OK);
		return S_OK;
	}
	
	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
	/* [in] */ LPMSG lpmsg,
	/* [in] */ WORD wID)
	{
		::MessageBox(NULL, "IOleInPlaceFrame::TranslateAccelerator", "", MB_OK);
		return S_OK;
	}

// IOleCommandTarget
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE QueryStatus( 
         /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
         /* [in] */ ULONG cCmds,
         /* [out][in][size_is] */ OLECMD __RPC_FAR prgCmds[  ],
         /* [unique][out][in] */ OLECMDTEXT __RPC_FAR *pCmdText)
	  {
		  return OLECMDERR_E_UNKNOWNGROUP;
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE Exec( 
         /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
         /* [in] */ DWORD nCmdID,
         /* [in] */ DWORD nCmdexecopt,
         /* [unique][in] */ VARIANT __RPC_FAR *pvaIn,
         /* [unique][out][in] */ VARIANT __RPC_FAR *pvaOut)
	  {
		  return OLECMDERR_E_UNKNOWNGROUP;
		  return S_OK;
	  }

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		*pClassID = CLSID_PageDesignerFrame;
		return S_OK;
	}
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
/*
// ICustomDraw
	STDMETHOD(Draw)(LONG type, GUID * iid, IUnknown * pItem, HDC hDC, LONG index, ULONG itemdata, ULONG flags, tagRECT rect);
*/

	virtual HRESULT CreateDlg(UINT nID, IUIDlg* *pVal);
};

#endif //__PageDesignerFrame_H_
