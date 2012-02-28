#ifndef __IMAGETOOLSDLG_H_
#define __IMAGETOOLSDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageToolsDlg
class ATL_NO_VTABLE CImageToolsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CImageToolsDlg, &CLSID_NULL/*ImageToolsDlg*/>,

//	public IDispatchImpl<IImageToolsDlg, &IID_IImageToolsDlg, &LIBID_WEBEDITORLib>,
	public CUIDialogImpl<CImageToolsDlg, CWindowImpl<CImageToolsDlg> >,

	public CUIEventHandlerImpl
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS/* | CS_OWNDC*/ | CS_SAVEBITS, -1/*no brush*/)

	CImageToolsDlg()
	{
		m_menuDlg = NULL;
	}

//	CComPtr<IEXMLViewGroup> m_viewGroup;
//	CComPtr<IWebXMLDocument> m_document;

	CComPtr<IUIMenuDlg> m_menuDlg;

	CRect m_strokerc;
	CRect m_fillrc;
	CRect m_drc[3];

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CImageToolsDlg)
//	COM_INTERFACE_ENTRY(IImageToolsDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_MSG_MAP(CImageToolsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IImageToolsDlg
public:
// IUIDlg
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Tools");
		return S_OK;
	}
	*/
	STDMETHODIMP CalcLayout(DWORD dwMode, long nLength, SIZE* pVal)
	{
		CSize size(0,0);
		if (m_menuDlg)
		{
			m_menuDlg->CalcLayout(dwMode, nLength, &size);
		}

		pVal->cx = size.cx;
		pVal->cy = size.cy+64;

		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__IMAGETOOLSDLG_H_
