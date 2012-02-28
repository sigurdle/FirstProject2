// SVGShapesDlg.h : Declaration of the CSVGShapesDlg

#ifndef __SVGSHAPESDLG_H_
#define __SVGSHAPESDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

/////////////////////////////////////////////////////////////////////////////
// CSVGShapesDlg
class ATL_NO_VTABLE CSVGShapesDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGShapesDlg, &CLSID_SVGShapesDlg>,
//	public IDispatchImpl<ISVGShapesDlg, &IID_ISVGShapesDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CSVGShapesDlg, CWindowImpl<CSVGShapesDlg> >,

//	public CSVGDefinitionsDlgT<CSVGShapesDlg>
{
public:
	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGShapesDlg()
	{
		m_type = 2;
	}

	void BuildItems()
	{
		m_listView.RemoveItems();
		AddItems();
	}

	CSVGElementListView m_listView;
	CScrollBar m_sizeGrip;

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGShapesDlg)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGShapesDlg)
//	COM_INTERFACE_ENTRY(ISVGShapesDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_MSG_MAP(CSVGShapesDlg)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	CHAIN_MSG_MAP(CSVGDefinitionsDlgT<CSVGShapesDlg>)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect rc(0,0,0,0);

		m_listView.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD, 0, 1/*nID*/);

		m_sizeGrip.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);//, , m_hWnd, 1/*NULL, _Module.m_hInst, NULL*/);

		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_listView.DestroyWindow();
		m_sizeGrip.DestroyWindow();
		return 0;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect client;
		GetClientRect(&client);

		m_listView.MoveWindow(0, 0, client.right, client.bottom-16);
		m_sizeGrip.MoveWindow(client.right-16, client.bottom-16, 16, 16);

		return 0;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;

		HDC hDC = lpdis->hDC;
		CRect& rc = *(CRect*)&lpdis->rcItem;

		return 0;
	}

	LRESULT OnFiltersSmallThumbnails(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_listView.SetView(0);
		return 0;
	}

	LRESULT OnFiltersLargeThumbnails(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_listView.SetView(1);
		return 0;
	}

	LRESULT OnFiltersSmallListView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_listView.SetView(2);
		return 0;
	}

	LRESULT OnFiltersLargeListView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_listView.SetView(3);
		return 0;
	}

	void OnFiltersSmallThumbnailsUpdate(long iid, IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 0);
	}

	void OnFiltersLargeThumbnailsUpdate(long iid, IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 1);
	}

	void OnFiltersSmallListViewUpdate(long iid, IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 2);
	}

	void OnFiltersLargeListViewUpdate(long iid, IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 3);
	}

// ISVGShapesDlg
public:
	STDMETHOD(Load)(/*[in]*/ BSTR pathName);
};

#endif //__SVGShapesDlg_H_
