// DataGrid.h : Declaration of the CDataGrid

#ifndef __DATAGRID_H_
#define __DATAGRID_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataGrid
class CDataGrid : 
	public CWindowImpl<CDataGrid>,

	public IDispEventImpl<1, CDataGrid, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CDataGrid();

	ADODB::_RecordsetPtr m_rs;

	CAxWindow	m_axvert;
	CComQIPtr<IUIScrollBar> m_vert;

	void OnSize();

	/*
BEGIN_COM_MAP(CDataGrid)
//	COM_INTERFACE_ENTRY(IDataGrid)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, IDataGrid)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)

//	COM_INTERFACE_ENTRY(IUITreeControlSite)
//	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()
*/
/*
BEGIN_CONNECTION_POINT_MAP(CDataGrid)
END_CONNECTION_POINT_MAP()
*/

BEGIN_SINK_MAP(CDataGrid)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	void __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CDataGrid)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
/*
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	*/
//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
//	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
};

#endif //__DATAGRID_H_
