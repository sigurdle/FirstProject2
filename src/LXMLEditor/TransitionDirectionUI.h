#ifndef __TRANSITIONDIRECTIONUI_H_
#define __TRANSITIONDIRECTIONUI_H_

namespace System
{
namespace LXmlEdit
{

class CTransitionDirectionUI;

class ArrowFlagsEvent : public System::Event
{
public:
	long arrowFlags;
};

class CTimerWnd : public MSWindows::WindowImpl
{
public:
	CTimerWnd()
	{
		m_pUI = NULL;
	}

	CTransitionDirectionUI* m_pUI;

	/*
BEGIN_MSG_MAP(CTimerWnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()
*/

	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SetTimer(1, 100);
		return 0;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		KillTimer(1);
		return 0;
	}

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	*/

	virtual bool ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult);
};

class LXMLEDITEXT CTransitionDirectionUI : 
public UI::Control
/*
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ITransitionDirectionUI, &IID_ITransitionDirectionUI, &LIBID_LXMLEDITORLib>,
	public CComControl<CTransitionDirectionUI>,
	public IPersistStreamInitImpl<CTransitionDirectionUI>,
	public IOleControlImpl<CTransitionDirectionUI>,
	public IOleObjectImpl<CTransitionDirectionUI>,
	public IOleInPlaceActiveObjectImpl<CTransitionDirectionUI>,
	public IViewObjectExImpl<CTransitionDirectionUI>,
	public IOleInPlaceObjectWindowlessImpl<CTransitionDirectionUI>,
	public IConnectionPointContainerImpl<CTransitionDirectionUI>,
	public IPersistStorageImpl<CTransitionDirectionUI>,
	public ISpecifyPropertyPagesImpl<CTransitionDirectionUI>,
	public IQuickActivateImpl<CTransitionDirectionUI>,
	public IDataObjectImpl<CTransitionDirectionUI>,
	public IProvideClassInfo2Impl<&CLSID_TransitionDirectionUI, NULL, &LIBID_LXMLEDITORLib>,
	public CComCoClass<CTransitionDirectionUI, &CLSID_TransitionDirectionUI>
//	public CProxy_ITransitionDirectionUIEvents< CTransitionDirectionUI >
*/
{
public:
	CTransitionDirectionUI();
	~CTransitionDirectionUI();

	/*
	int FinalConstruct()
	{
		LDraw::BBox rc(0,0,0,0);
		m_timerWnd.m_pUI = this;
//		m_timerWnd.Create(NULL, LDraw::BBox(0,0,0,0), NULL, WS_DISABLED, 0, 0, NULL);
		ATLASSERT(::IsWindow(m_timerWnd.m_hWnd));
		return 0;
	}

	void FinalRelease()
	{
		m_timerWnd.DestroyWindow();
	}
	*/

	double m_progress;

	uint8 m_bitCorners;
	uint8 m_arrowFlags;
	uint8 m_flags;

	System::StringW* m_type;
	System::StringW* m_subtype;
	long m_horzRepeat;
	long m_vertRepeat;

	LDraw::Bitmap* m_bitmap[2];

	CTimerWnd m_timerWnd;

#if 0
DECLARE_REGISTRY_RESOURCEID(IDR_TRANSITIONDIRECTIONUI)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransitionDirectionUI)
	COM_INTERFACE_ENTRY(ITransitionDirectionUI)
	COM_INTERFACE_ENTRY(IDispatch)
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
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTransitionDirectionUI)
//	CONNECTION_POINT_ENTRY(DIID__ITransitionDirectionUIEvents)
END_CONNECTION_POINT_MAP()

BEGIN_PROP_MAP(CTransitionDirectionUI)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CTransitionDirectionUI)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	CHAIN_MSG_MAP(CComControl<CTransitionDirectionUI>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
#endif
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	void OnLButtonDown(UI::MouseEvent* evt);

// IViewObjectEx
//	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	ErrorCode get_flags(/*[out, retval]*/ long *pVal);
	ErrorCode set_flags(/*[in]*/ long newVal);
	ErrorCode get_bitCorners(/*[out, retval]*/ long *pVal);
	ErrorCode set_bitCorners(/*[in]*/ long newVal);
	long get_arrowFlags();
	void set_arrowFlags(long newVal);
	bool get_reverse();
	void set_reverse(bool newVal);
	ErrorCode SetTransition(/*[in]*/ System::StringW* type, /*[in]*/ System::StringW* subtype, /*[in]*/ long horzRepeat, /*[in]*/ long vertRepeat, /*[in]*/ long borderWidth, /*[in]*/ LDraw::Color borderColor);

protected:

	virtual void OnRender(UI::Graphics* pGraphics);

	virtual void handleEvent(System::Event* evt);

	bool m_reverse;
};

}	// LXmlEdit
}

#endif //__TRANSITIONDIRECTIONUI_H_
