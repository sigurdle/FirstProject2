// ToolsDlg.h : Declaration of the CToolsDlg

#ifndef __TOOLSDLG_H_
#define __TOOLSDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CToolsDlg
class ATL_NO_VTABLE CToolsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CToolsDlg, &CLSID_ToolsDlg>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CToolsDlg>,
	public IDispatchImpl<IToolsDlg, &IID_IToolsDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CToolsDlg, CWindowImpl<CToolsDlg> >,
	public CUIEventHandlerImpl
{
public:
	CToolsDlg()
	{
		m_menuDlg = NULL;

		m_strokeOrFill = 0;
	}

	CComPtr<IPageDesignerApp> m_default;
	CArray<IPDObjectWithBrush*,IPDObjectWithBrush*> m_targetObjects;

	int m_strokeOrFill;

	CComObject<CUIMenuDlg>* m_menuDlg;

	CRect m_brushTypeRect[3];

DECLARE_REGISTRY_RESOURCEID(IDR_TOOLSDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CToolsDlg)
	COM_INTERFACE_ENTRY(IToolsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CToolsDlg)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CToolsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IToolsDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Tools");
		return S_OK;
	}
	STDMETHODIMP CalcLayout(DWORD dwMode, long nLength, SIZE* pVal)
	{
		CSize size;
		m_menuDlg->CalcLayout(dwMode, nLength, &size);

		pVal->cx = size.cx;
		pVal->cy = size.cy+64;

		return S_OK;
	}

// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__TOOLSDLG_H_
