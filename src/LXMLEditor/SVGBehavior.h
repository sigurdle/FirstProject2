#pragma once

namespace System
{
namespace LXmlEdit
{
class CEXMLDocument;
class CEXMLLayoutView;
class CPathElement;
class CTextElement;

class CESelectedSVGPathElement;	// TODO remove

class CHitData
{
public:
	int hit;
	long anchor;
	long segment;
	long ctl;
	double t;

	int m_curveDir;	// ??

	Web::Node* pNode;
	long offset;
//		CPathSelection* pPath;

//	CPathElement* path;
//	CESelectedSVGPathElement* path;	// ??
	IESelectedElement* path;	// ??

	CHitData()
	{
		hit = 0;

		anchor = -1;
		segment = -1;
		ctl = 0;
		t = -1;

		pNode = NULL;
		offset = -1;
		//pPath = NULL;
		path = NULL;
	}
};

#if 0	// Had this
class ATL_NO_VTABLE CLSVGBehavior :
	public CComObjectRootEx<CComSingleThreadModel>,

	public ILElementBehavior,
	public IElementBehaviorLayout,
	public IHTMLPainter,
	public ILHTMLPainter,

	public ISVGView,

	public CUIEventHandlerImpl,

	public IDispEventImpl<1, CLSVGBehavior, &DIID__ILSVGSVGElementEvents, &LIBID_LHTMLLib, 1, 0>,
	public IDispEventImpl<2, CLSVGBehavior, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>,
	public IDispEventImpl<3, CLSVGBehavior, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CLSVGBehavior()
	{
		m_pDocument = NULL;
		m_viewGroup = NULL;
		m_layoutView = NULL;

		m_pActivePath = NULL;

		m_dragging = 0;
		m_startDragCursor = NULL;

	//	m_bAlt = false;

		m_sourceText = NULL;

		m_hitdata = NULL;

		m_nFlags = 0;
		m_clientX = 0;
		m_clientY = 0;
	}

	int FinalConstruct();
	void FinalRelease();

	ILElementBehaviorSite* m_pBehaviorSite;
	CEXMLDocument* m_pDocument;
	CEXMLViewGroup* m_viewGroup;
	CEXMLLayoutView* m_layoutView;

	long m_dragging;
	HCURSOR m_startDragCursor;

	/*
	SVGPoint m_dpt;
	SVGPoint m_dstartpt;
	SVGPoint m_doldpt;
	*/
	LDraw::PointD m_dpt;
	LDraw::PointD m_dstartpt;
	LDraw::PointD m_doldpt;

	CPoint m_oldpt;
	CPoint m_startpt;

	CPoint m_point;
	CPoint m_oldpoint;
	CPoint m_startpoint;

	CHitData* m_hitdata;	// TODO
//	SVGLib::ISVGMatrixPtr m_initialMatrix;

	LDraw::PointD m_pivotPt;
	double m_effectRadius;

	CArray<LDraw::PointD,LDraw::PointD> m_pointArray;

	/* TODO, had these
	long m_curveCp;
	long m_curveCtl;
	long m_curveDir;
	*/

	CESelectedSVGPathElement* m_pActivePath;	// TODO ??
	float m_radius;

//	CComQIPtr<IUIScrollBar>	m_horz;
//	CComQIPtr<IUIScrollBar>	m_vert;
/*
*/

//	int m_svgActiveTool;
	CComPtr<ISVGTool> m_activeTool;

	LDraw::PointD	m_centerPt;

	long m_clientX;
	long m_clientY;
	UINT m_nFlags;

	int m_hit;
	
//	CComQIPtr<IWebXMLDocument> m_pDocument;

	CRect m_imageRect;
	POINT m_offset;
	BOOL m_bShowRulers;

	int m_numMoves;

#if 0
	CPathElement* m_pActivePathElement;	// TODO ??
#endif

	CRect m_zoomRect;

//	CAxWindow m_axhtmlControl;
//	CComQIPtr<ILHTMLControl> m_htmlControl;

	CTextElement* m_pTextElement;
	long m_cursorPos;
	int m_initSelCharPos;
	int m_startSelCharPos;
	int m_endSelCharPos;

	BSTR	m_sourceText;

//	CComQIPtr<ILSVGMatrix> m_viewMatrix;
	//double m_magnify;

	LDraw::RectD m_newObjectBounds;

//	bool m_bAlt;

	STDMETHODIMP HitTest(/*[in]*/ IEElement* element, /*[in]*/ double ptx, /*[in]*/ double pty, /*[in]*/ long options, /*[in,out]*/ _SVGHitData* hitdata);

	HRESULT GetObjectUnderPoint(IESVGElement* object, LSVG::SVGMatrix* matrix, LDraw::PointD pt, int tool, _SVGHitData* hit/*, IEElement** pVal*/);
//	HRESULT GetObjectUnderPoint(SVGPoint pt, int tool, _SVGHitData/*CHitData**/ * hit/*, IEElement** pVal*/);

	void OnSize();
	
//	void SetViewMatrix();

#if 0
	double GetMagnifyFactor()
	{
		return m_magnify;
		//SVGLib::ISVGSVGElementPtr svg = m_pDocument->GetDOMDocument()->documentElement;
		//return svg->currentScale;
	}
#endif

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

	void OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk);
	void OnButtonUp(UINT nFlags, POINT point, int iButton);
	void OnMouseMove(UINT nFlags, POINT point);
	void OnMouseMove(UINT nFlags);
	void OnKeyDown(long nKey);
	void OnKeyUp(long nKey);

	void OnSetCursor();

BEGIN_COM_MAP(CLSVGBehavior)
	COM_INTERFACE_ENTRY(ILElementBehavior)
	COM_INTERFACE_ENTRY(IElementBehaviorLayout)
	COM_INTERFACE_ENTRY(IHTMLPainter)
	COM_INTERFACE_ENTRY(ILHTMLPainter)

	COM_INTERFACE_ENTRY(ISVGView)

	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_SINK_MAP(CLSVGBehavior)
	SINK_ENTRY_EX(1, DIID__ILSVGSVGElementEvents, /*dispid*/1, onmousedown)
	SINK_ENTRY_EX(1, DIID__ILSVGSVGElementEvents, /*dispid*/2, onmouseup)
	SINK_ENTRY_EX(1, DIID__ILSVGSVGElementEvents, /*dispid*/3, onmousemove)
	SINK_ENTRY_EX(1, DIID__ILSVGSVGElementEvents, /*dispid*/4, onkeydown)
	SINK_ENTRY_EX(1, DIID__ILSVGSVGElementEvents, /*dispid*/5, onkeyup)
	SINK_ENTRY_EX(1, DIID__ILSVGSVGElementEvents, /*dispid*/6, oncontextmenu)
	SINK_ENTRY_EX(1, DIID__ILSVGSVGElementEvents, /*dispid*/7, onselect)

	SINK_ENTRY_EX(2, DIID__ILXMLEditorAppEvents, 4, OnActiveToolChange)

   SINK_ENTRY_EX(3, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()

	void __stdcall onmousedown(ILDOMEvent* evt);
	void __stdcall onmouseup(ILDOMEvent* evt);
	void __stdcall onmousemove(ILDOMEvent* evt);
	void __stdcall onkeydown(ILDOMEvent* evt);
	void __stdcall onkeyup(ILDOMEvent* evt);
	void __stdcall oncontextmenu(ILDOMEvent* evt);
	void __stdcall onselect(ILDOMEvent* evt);

	void __stdcall OnActiveToolChange();
	void __stdcall OnViewGroupSelectionChanged();

public:
	STDMETHOD(GetEElement)(/*[out,retval]*/ IEElement* *pVal);
// ISVGView
	STDMETHOD(GetSVGSVGElement)(/*[out,retval]*/ ILSVGSVGElement* *pVal);
	STDMETHOD(GetViewGroup)(/*[out,retval]*/ IEXMLViewGroup* *pVal);
	STDMETHOD(GetHTMLWindow)(/*[out,retval]*/ ILHTMLWindow* *pVal);
	STDMETHOD(GetPaintSite)(/*[out,retval]*/ IHTMLPaintSite* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
		*pVal = paintSite.Detach();
		return S_OK;
	}
	STDMETHOD(GetViewMatrix)(/*[out,retval]*/ LSVG::SVGMatrix* *pVal);

// IElementBehaviorLayout
	virtual HRESULT STDMETHODCALLTYPE GetSize( 
      /* [in] */ LONG dwFlags,
      /* [in] */ SIZE sizeContent,
      /* [out][in] */ POINT *pptTranslateBy,
      /* [out][in] */ POINT *pptTopLeft,
      /* [out][in] */ SIZE *psizeProposed)
	{
		// Make room for rulers
		pptTranslateBy->x = 20;
		pptTranslateBy->y = 20;
		
		return S_OK;
	}
	
	virtual HRESULT STDMETHODCALLTYPE GetLayoutInfo( 
      /* [out][retval] */ LONG *plLayoutInfo)
	{
		return S_OK;
	}
	
	virtual HRESULT STDMETHODCALLTYPE GetPosition( 
      /* [in] */ LONG lFlags,
      /* [out][in] */ POINT *pptTopLeft)
	{
		return S_OK;
	}
	
	virtual HRESULT STDMETHODCALLTYPE MapSize( 
      /* [in] */ SIZE *psizeIn,
      /* [out] */ RECT *prcOut)
	{
		return S_OK;
	}

// ILElementBehavior
	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite);
	STDMETHODIMP Detach();

// ILHTMLPainter
	STDMETHODIMP SetCursor(/*[in]*/ POINT pt);

// IHTMLPainter
	STDMETHODIMP Draw( 
            /* [in] */ RECT rcBounds,
            /* [in] */ RECT rcUpdate,
            /* [in] */ LONG lDrawFlags,
            /* [in] */ HDC hdc,
            /* [in] */ LPVOID pvDrawObject);

	STDMETHODIMP OnResize( 
            /* [in] */ SIZE size)
	{
		return S_OK;
	}

	STDMETHODIMP GetPainterInfo( 
            /* [out] */ HTML_PAINTER_INFO *pInfo)
	{
	// Make room for ruler
		pInfo->rcExpand.left = 20;
		pInfo->rcExpand.top = 20;
		return S_OK;
	}

	STDMETHODIMP HitTestPoint( 
            /* [in] */ POINT pt,
            /* [out] */ BOOL *pbHit,
            /* [out] */ LONG *plPartID)
	{
			// Setting pbHit to TRUE will trigger an event that can be handled
			// by IEventSink::Invoke
		*pbHit = TRUE;
		return S_OK;
	}

// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie)
	{
#if 0
		CComQIPtr<IEElement> element = object;
		if (element)
		{
			CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
			paintSite->InvalidateRect(NULL);

			*cookie = 1;
		}
#endif

		return S_OK;
	}

	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow)
	{
#if 0
		CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
		paintSite->InvalidateRect(NULL);
#endif
		return S_OK;
	}
};
#endif

}	// LXmlEdit
}
