// ToolPresetsDlg.h : Declaration of the CToolPresetsDlg

#ifndef __TOOLPRESETSDLG_H_
#define __TOOLPRESETSDLG_H_

#include "resource.h"       // main symbols

//#include "SVGDefinitionsDlgT.h"

#include "SVGElementsListView.h"

namespace System
{
namespace LXmlEdit
{

class CLXMLEditorApp;

class CToolPresetsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CToolPresetsDlg, &CLSID_ToolPresetsDlg>,
//	public IDispatchImpl<IToolPresetsDlg, &IID_IToolPresetsDlg, &LIBID_LXMLEDITORLib>,

	public UI::Control,
//	public CUIDialogImpl<CToolPresetsDlg, CWindowImpl<CToolPresetsDlg> >,
	public UI::ProcessTargetCommands	// ILDOMEventListener

//	public CSVGDefinitionsDlgT<CToolPresetsDlg>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CToolPresetsDlg()
	{
		m_app = NULL;
		m_view = NULL;
	}

	CLXMLEditorApp* m_app;
	UI::CView* m_view;

	void BuildItems()
	{
		m_listView.RemoveItems();
//		AddItems();
	}

	CSVGElementListView m_listView;
//	CScrollBar m_sizeGrip;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CToolPresetsDlg)
//	COM_INTERFACE_ENTRY(IToolPresetsDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

#if 0

BEGIN_MSG_MAP(CToolPresetsDlg)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	CHAIN_MSG_MAP(CSVGDefinitionsDlgT<CToolPresetsDlg>)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
#endif

#if 0
	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect rc(0,0,0,0);

		m_listView.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD, 0, 1/*nID*/);

		m_sizeGrip.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);//, , m_hWnd, 1/*NULL, _Module.m_hInst, NULL*/);

		return 0;
	}

	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_listView.DestroyWindow();
		m_sizeGrip.DestroyWindow();
		return 0;
	}

	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect client;
		GetClientRect(&client);

		m_listView.MoveWindow(0, 0, client.right, client.bottom-16);
		m_sizeGrip.MoveWindow(client.right-16, client.bottom-16, 16, 16);

		return 0;
	}
#endif
//	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	long OnDrawItem();

DECLARE_CMD_MAP(CToolPresetsDlg)

	long OnToolPresetsNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnListSmallThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(0);
		return 0;
	}

	long OnListLargeThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(1);
		return 0;
	}

	long OnListSmallListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(2);
		return 0;
	}

	long OnListLargeListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(3);
		return 0;
	}

	void OnListSmallThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 0);
	}

	void OnListLargeThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 1);
	}

	void OnListSmallListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 2);
	}

	void OnListLargeListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 3);
	}

// IToolPresetsDlg
public:
//	STDMETHOD(Load)(/*[in]*/ BSTR pathName);
};

}
}

#endif //__TOOLPRESETSDLG_H_
