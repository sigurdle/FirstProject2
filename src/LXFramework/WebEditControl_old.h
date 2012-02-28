// WebEditControl.h : Declaration of the CWebEditControl

#ifndef __WEBEDITCONTROL_H_
#define __WEBEDITCONTROL_H_

#include "resource.h"       // main symbols
//#import "D:\MMStudio\Extras\DOMCoreMod\DOMCoreMod.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

#include "Element.h"

#include "..\CmdHandler.h"
#include "WebEditorCP.h"

/////////////////////////////////////////////////////////////////////////////
// CWebEditControl
class ATL_NO_VTABLE CWebEditControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComControl<CWebEditControl>,

	public IConnectionPointContainerImpl<CWebEditControl>,
	public IDispatchImpl<IWebEditControl, &IID_IWebEditControl, &LIBID_WEBEDITORLib>,

	public IPersistStreamInitImpl<CWebEditControl>,
	public IOleControlImpl<CWebEditControl>,
	public IOleObjectImpl<CWebEditControl>,
	public IOleInPlaceActiveObjectImpl<CWebEditControl>,
	public IViewObjectExImpl<CWebEditControl>,
	public IOleInPlaceObjectWindowlessImpl<CWebEditControl>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CWebEditControl>,
	public ISpecifyPropertyPagesImpl<CWebEditControl>,
	public IQuickActivateImpl<CWebEditControl>,
	public IDataObjectImpl<CWebEditControl>,
	public IProvideClassInfo2Impl<&CLSID_WebEditControl, &DIID__IWebEditControlEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CWebEditControl>,

//	public IDispEventImpl<1, CWebEditControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CWebEditControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CWebEditControl, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>,
	public IDispEventImpl<5, CWebEditControl, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>,

	public CComCoClass<CWebEditControl, &CLSID_WebEditControl>,

	public ProcessTargetCommands,
	public IDropTarget,
	public CProxy_IWebEditControlEvents< CWebEditControl >
#if 0
	,
	public IHTMLEditorSite
#endif
{
public:
	DECLARE_WND_CLASS(NULL)

	CWebEditControl();

	int FinalConstruct()
	{
//		HRESULT hr;

	/*
		m_horz.CoCreateInstance(CLSID_UIScrollBar);
		m_vert.CoCreateInstance(CLSID_UIScrollBar);

		IDispEventImpl<1, CWebEditControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
		IDispEventImpl<2, CWebEditControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);
*/

		m_htmlControl.CoCreateInstance(CLSID_LHTMLControl);

		m_magnifyMatrix.CoCreateInstance(CLSID_LSVGMatrix);

		return S_OK;
	}

	void FinalRelease()
	{
//		IDispEventImpl<1, CWebEditControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
//		IDispEventImpl<2, CWebEditControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	}

	int m_dragging;
	POINT m_oldpt;
	POINT m_startpt;

//	SVGLib::ISVGMatrixPtr m_initialMatrix;

	CDblPoint m_pivotPt;
	double m_effectRadius;

	CArray<CDblPoint,CDblPoint> m_pointArray;

	int m_curveCp;
	int m_curveCtl;
	float m_radius;

//	CDrawSession m_drawSession;

//	CComQIPtr<IUIScrollBar>	m_horz;
//	CComQIPtr<IUIScrollBar>	m_vert;
/*
*/

	CDblPoint	m_centerPt;

	int m_hit;
	
	CComQIPtr<IWebXMLDocument> m_pDocument;

	CRect m_imageRect;
	POINT m_offset;
	BOOL m_bShowRulers;

	int m_numMoves;

	CPathElement* m_pActivePathElement;

	CRect m_zoomRect;

	CAxWindow m_axhtmlControl;
	CComQIPtr<ILHTMLControl> m_htmlControl;

	CTextElement* m_pTextElement;
	long m_cursorPos;
	int m_initSelCharPos;
	int m_startSelCharPos;
	int m_endSelCharPos;

	BSTR	m_sourceText;

	CComQIPtr<ILSVGMatrix> m_magnifyMatrix;
	double m_magnify;

	void OnSize();

	double GetMagnifyFactor()
	{
		return m_magnify;
		//SVGLib::ISVGSVGElementPtr svg = m_pDocument->GetDOMDocument()->documentElement;
		//return svg->currentScale;
	}

	void InvalidateInvalidRect();

	void UpdateRect(LPRECT updateRect);

	void UpdateRect(ILSVGRect* box)
	{
		ATLASSERT(0);
	/*
		RECT rc;
		rc.left = box.x;
		rc.top = box.y;
		rc.right = box.x + box.width+0.5;
		rc.bottom = box.y + box.height+0.5;

		UpdateRect(&rc);
		*/
	}

	//void ZoomToRect(double left, double top, double right, double bottom);
	void ZoomToRect2(double left, double top, double right, double bottom);

	void DrawTargetElementsPathCurves(HDC hDC);

	CElementImpl* MakeSelectedCompound();

	void OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk);
	void OnButtonUp(UINT nFlags, POINT point, int iButton);
	void OnMouseMove(UINT nFlags, POINT point);

DECLARE_REGISTRY_RESOURCEID(IDR_WEBEDITCONTROL)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWebEditControl)
	COM_INTERFACE_ENTRY(IWebEditControl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, IWebEditControl)

	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IDropTarget)
#if 0
	COM_INTERFACE_ENTRY(IHTMLEditorSite)
#endif
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CWebEditControl)
	CONNECTION_POINT_ENTRY(DIID__IWebEditControlEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_PROP_MAP(CWebEditControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_SINK_MAP(CWebEditControl)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
//   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(3, DIID__IESvgDocumentEvents, /*dispid*/1, OnDOMEvent)
   SINK_ENTRY_EX(5, DIID__IUIManagerEvents, /*dispid*/1, OnActivatedObject)
   SINK_ENTRY_EX(5, DIID__IUIManagerEvents, /*dispid*/2, OnDeactivatedObject)
END_SINK_MAP()

//	HRESULT __stdcall OnHorzScroll(long code, long pos);
//	HRESULT __stdcall OnVertScroll(long code, long pos);
	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

	HRESULT __stdcall OnActivatedObject(IUnknown* object);
	HRESULT __stdcall OnDeactivatedObject(IUnknown* object);

BEGIN_MSG_MAP(CWebEditControl)
	CHAIN_MSG_MAP(CComControl<CWebEditControl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_CHAR, OnChar)
END_MSG_MAP()

	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IWebEditControl,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		return 0;
	}

	DECLARE_CMD_MAP(CWebEditControl)

	LRESULT OnEditCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditCutCopyUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnObjectGroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectGroupUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnObjectUngroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectUngroupUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnObjectMakeCompound(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectMakeCompoundUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnViewZoomin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewZoomout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewActualSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);

// IWebEditControl
public:
//	STDMETHOD(get_documentContainer)(/*[out, retval]*/ IDOMDocumentContainer* *pVal);
//	STDMETHOD(put_documentContainer)(/*[in]*/ IDOMDocumentContainer* newVal);
	STDMETHOD(setScrollposXY)(/*[in]*/ long posx, /*[in]*/ long posy);
	STDMETHOD(get_currentScale)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_currentScale)(/*[in]*/ double newVal);
	STDMETHOD(GetViewBox)(/*[out,retval]*/ RECT* pbox);
	STDMETHOD(get_scrollposY)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_scrollposY)(/*[in]*/ long newVal);
	STDMETHOD(get_scrollposX)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_scrollposX)(/*[in]*/ long newVal);
	STDMETHOD(get_ESvgDocument)(/*[out, retval]*/ IWebXMLDocument* *pVal);
	STDMETHOD(put_ESvgDocument)(/*[in]*/ IWebXMLDocument* newVal);

// IHTMLEditorSite
	STDMETHOD(DrawOver)(HDC hDC, tagRECT rect);
	STDMETHOD(TranslateEvent)(ILDOMEvent * inevent, ILDOMEvent * * outevent, VARIANT_BOOL * bCancel);
	STDMETHOD(SetCursor)(LONG x, LONG y, VARIANT_BOOL * bHandled);
};

#endif //__WEBEDITCONTROL_H_
