// ElementAttrsDlg.h : Declaration of the CElementAttrsDlg

#ifndef __ELEMENTATTRSDLG_H_
#define __ELEMENTATTRSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CAttrItem
{
public:
	CAttrItem()
	{
		m_attdecl = NULL;
	}

	System::StringW* m_name;
	Web::IASAttributeDeclaration* m_attdecl;
};

class CEElement;

class CElementAttrsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CElementAttrsDlg>,
//	public IDispatchImpl<IElementAttrsDlg, &IID_IElementAttrsDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
	//public CUIDialogImpl<CElementAttrsDlg, CWindowImpl<CElementAttrsDlg> >,
//	public CUIEventHandlerImpl

//	public IDispEventImpl<2, CElementAttrsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<3, CElementAttrsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,

#if 0
	public IDispEventImpl<4, CElementAttrsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CElementAttrsDlg();
	~CElementAttrsDlg();

	/*
	int FinalConstruct()
	{
		ErrorCode hr;

		hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
		if (FAILED(hr)) return hr;
		m_vert->put_direction(1);

		return S_OK;
	}

	void FinalRelease()
	{
	}
	*/

	CLXMLEditorApp* m_app;

	int m_splitx;

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar>	m_vert;
	UI::TextEdit * m_edit;
//	HFONT m_font;
	LDraw::BBoxi m_areaRect;
	CEElement* m_pElement;
//	IDOMElement* m_pElement;

	CEXMLViewGroup* m_viewGroup;

	Array<CAttrItem*>	m_attributes;
	CAttrItem* m_pActiveItem;

	void OnSize();
	void EndEdit();

#if 0
//DECLARE_REGISTRY_RESOURCEID(IDR_ELEMENTATTRSDLG)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementAttrsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IElementAttrsDlg)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CElementAttrsDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CElementAttrsDlg)
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

// IElementAttrsDlg
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

#endif //__ELEMENTATTRSDLG_H_
