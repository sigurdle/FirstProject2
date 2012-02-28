// SiteLinksView.h : Declaration of the CSiteLinksView

#ifndef __SITELINKSVIEW_H_
#define __SITELINKSVIEW_H_

//#include "resource.h"       // main symbols

class CLinkableFile;

/////////////////////////////////////////////////////////////////////////////
// CSiteLinksView
class ATL_NO_VTABLE CSiteLinksView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSiteLinksView, &CLSID_SiteLinksView>,
	public IConnectionPointContainerImpl<CSiteLinksView>,
	public IDispatchImpl<ISiteLinksView, &IID_ISiteLinksView, &LIBID_LXWEBSITELib>,
	public IDispEventImpl<1, CSiteLinksView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CSiteLinksView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CSiteLinksView, &DIID__IWebSiteEvents, &LIBID_LXWEBSITELib, 1, 0>,
	public ProcessTargetCommands,
	public CUIDialogImpl<CSiteLinksView, CWindowImpl<CSiteLinksView> >
{
public:
	DECLARE_WND_CLASS(NULL)

	CSiteLinksView()
	{
		m_pRootFile = NULL;
		m_imgIconLarge = NULL;
		m_dragging = 0;
		m_magnify = 1;
	}

	int FinalConstruct()
	{
		m_vert.CoCreateInstance(CLSID_UIScrollBar);
		m_horz.CoCreateInstance(CLSID_UIScrollBar);

		return S_OK;
	}

	void FinalRelease()
	{
	}

	CComQIPtr<IWebSite>	m_document;

	CComQIPtr<IUIScrollBar> m_horz;
	CComQIPtr<IUIScrollBar> m_vert;

	CLinkableFile* m_pRootFile;

	HIMAGELIST	m_imgIconLarge;

	POINT m_startpt;
	CRect m_areaRect;
	int m_dragging;
	CRect m_zoomRect;
	double m_magnify;

	void OnSize();
	void ZoomToRect2(double left, double top, double right, double bottom);

//DECLARE_REGISTRY_RESOURCEID(IDR_SITELINKSVIEW)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSiteLinksView)
	COM_INTERFACE_ENTRY(ISiteLinksView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, ISiteLinksView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSiteLinksView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSiteLinksView)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)

   SINK_ENTRY_EX(3, DIID__IWebSiteEvents, /*dispid*/2, OnOutLinksChanged)
END_SINK_MAP()

	void __stdcall OnVertScroll(long code, long pos);
	void __stdcall OnHorzScroll(long code, long pos);

	HRESULT __stdcall OnOutLinksChanged(long file_id);

DECLARE_CMD_MAP(CSiteLinksView)

BEGIN_MSG_MAP(CSiteLinksView)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
/*
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
*/
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

/*
	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// ISiteLinksView
public:
	STDMETHOD(get_document)(/*[out, retval]*/ IWebSite* *pVal);
	STDMETHOD(put_document)(/*[in]*/ IWebSite* newVal);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Links");
		return S_OK;
	}
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
	{
	// Try us
		ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;

		CComQIPtr<ICommandTarget> target;
		
	// Try document
		target = m_document;
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;

		return S_OK;
	}
};

#endif //__SITELINKSVIEW_H_
