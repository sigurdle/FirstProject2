// FilterGraphDlg.h : Declaration of the CFilterGraphDlg

#ifndef __FILTERGRAPHDLG_H_
#define __FILTERGRAPHDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

class CPDDocumentView;

class CFilterPrimitiveElement;
class CFilter;

class CFilterPrimitiveElement
{
public:
	CFilterPrimitiveElement(IPDFilterPrimitive* pLayer)
	{
		ATLASSERT(pLayer);

		m_parent = NULL;
		m_pLayer = pLayer;
		m_rect = CRect(0, 0, 90, 22);

		BSTR bname;
		pLayer->get_name(&bname);
		m_name = _bstr_t(bname, false);
	}

	CRect m_rect;
	_bstr_t m_name;
	int m_type;
	IPDFilterPrimitive* m_pLayer;
	CFilter* m_parent;

	int GetInPinCount();
	CFilterPrimitiveElement* GetInPin(int n);
};

class CFilter
{
public:
//	CFilterPrimitiveElement* m_cItems[4];
	CUPtrList m_items;

	~CFilter()
	{
		while (!m_items.IsEmpty())
		{
			CFilterPrimitiveElement* p = (CFilterPrimitiveElement*)m_items.RemoveTail();
			delete p;
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
// CFilterGraphDlg
class ATL_NO_VTABLE CFilterGraphDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFilterGraphDlg, &CLSID_FilterGraphDlg>,
	public IDispatchImpl<IFilterGraphDlg, &IID_IFilterGraphDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CFilterGraphDlg, CWindowImpl<CFilterGraphDlg> >,
	public CNotifyGetImpl<CFilterGraphDlg>,
	public CUIEventHandlerImpl,
	public IDropTarget,
	public IDispEventImpl<2, CFilterGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CFilterGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CFilterGraphDlg()
	{
		m_view = NULL;

		m_pLayer = NULL;

		m_dragging = 0;
		m_pItemDrag = NULL;
		m_pNearItem = NULL;
	}

	~CFilterGraphDlg()
	{
		if (m_pLayer)
		{
			delete m_pLayer;
			m_pLayer = NULL;
		}
	}

	int FinalConstruct()
	{
		m_horz.CoCreateInstance(CLSID_UIScrollBar);
		m_horz->put_direction(0);

		m_vert.CoCreateInstance(CLSID_UIScrollBar);
		m_vert->put_direction(1);

		return 0;
	}

	void FinalRelease()
	{
	}

	CFilter* m_pLayer;

	CPoint m_oldpt;
	int m_inpin;
	int m_dragging;
	CFilterPrimitiveElement* m_pItemDrag;
	CFilterPrimitiveElement* m_pNearItem;

	CComObject<CPDDocumentView>* m_view;

	CComPtr<IPDAppearance> m_filter;

	CAxWindow	m_axvert;
	CAxWindow	m_axhorz;
	CComQIPtr<IUIScrollBar> m_vert;
	CComQIPtr<IUIScrollBar> m_horz;
	CRect m_areaRect;

	void BuildItems();
	void OnSize();

DECLARE_REGISTRY_RESOURCEID(IDR_FILTERGRAPHDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFilterGraphDlg)
	COM_INTERFACE_ENTRY(IFilterGraphDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_SINK_MAP(CFilterGraphDlg)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(3, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	HRESULT __stdcall OnHorzScroll(long code, long pos);
	HRESULT __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CFilterGraphDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
/*		CComQIPtr<IPDImage> image = targetObject;
		if (image)
		{
			if (m_hWnd)
			{
				//OnSize();
				Invalidate();
			}
		}
*/
		Invalidate();

		return S_OK;
	}

// IFilterGraphDlg
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Filter Graph");
		return S_OK;
	}
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__FILTERGRAPHDLG_H_
