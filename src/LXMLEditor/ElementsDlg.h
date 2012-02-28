// ElementsDlg.h : Declaration of the CElementsDlg

#ifndef __ELEMENTSDLG_H_
#define __ELEMENTSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CElementsDlg
class CElementsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CElementsDlg>,
//	public IDispatchImpl<IElementsDlg, &IID_IElementsDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CElementsDlg, CWindowImpl<CElementsDlg> >,
//	public CUIEventHandlerImpl

//	public IDispEventImpl<2, CElementsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<3, CElementsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,

//	public IDispEventImpl<4, CElementsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CElementsDlg();
	~CElementsDlg();

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar> m_vert;
	UI::TextEdit * m_edit;
//	CFont m_font;
	LDraw::BBoxi m_areaRect;

	int m_itemHeight;

	Array<System::StringW*> m_elements;

	CEXMLViewGroup* m_viewGroup;

	void AddCMElements(Web::IASContentModel* asCM);
	void OnSize();
//	void ResetVScrollBar();

#if 0
//DECLARE_REGISTRY_RESOURCEID(IDR_ElementsDlg)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IElementsDlg)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CElementsDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CElementsDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
   SINK_ENTRY_EX(3, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(4, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()
#endif

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);
	void __stdcall OnVertScroll(long code, long pos);
	void __stdcall OnViewGroupSelectionChanged();

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

// IElementsDlg
public:
// IUIDlg
/*
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"AS Attributes");
		return S_OK;
	}
	*/
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__ELEMENTSDLG_H_
