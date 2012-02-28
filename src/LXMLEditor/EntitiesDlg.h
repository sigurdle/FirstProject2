// EntitiesDlg.h : Declaration of the CEntitiesDlg

#ifndef __ENTITIESDLG_H_
#define __ENTITIESDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CEntitiesDlg
class CEntitiesDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CEntitiesDlg>,
//	public IDispatchImpl<IEntitiesDlg, &IID_IEntitiesDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CEntitiesDlg, CWindowImpl<CEntitiesDlg> >,
//	public CUIEventHandlerImpl

//	public IDispEventImpl<2, CEntitiesDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<3, CEntitiesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>

//	public IDispEventImpl<4, CEntitiesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CEntitiesDlg();
	~CEntitiesDlg();

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar> m_vert;
	UI::TextEdit * m_edit;
	//CFont m_font;
	LDraw::BBoxi m_areaRect;

	int m_itemHeight;

	Array<Web::IASEntityDeclaration*> m_entities;

	CEXMLDocument* m_edocument;
//	CComPtr<IEXMLViewGroup> m_viewGroup;

	void OnSize();
//	void ResetVScrollBar();

#if 0
//DECLARE_REGISTRY_RESOURCEID(IDR_EntitiesDlg)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEntitiesDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEntitiesDlg)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEntitiesDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CEntitiesDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
   SINK_ENTRY_EX(3, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(4, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()
#endif

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);
	void __stdcall OnVertScroll(long code, long pos);
//	void __stdcall OnViewGroupSelectionChanged();

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

// IEntitiesDlg
public:
// IUIDlg
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__ENTITIESDLG_H_
