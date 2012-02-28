// XSLTForEachDlg.h : Declaration of the CXSLTForEachDlg

#if 0
#ifndef __XSLTFOREACHDLG_H_
#define __XSLTFOREACHDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXSLTForEachDlg
class ATL_NO_VTABLE CXSLTForEachDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CXSLTForEachDlg, &CLSID_XSLTForEachDlg>,
	public IDispatchImpl<IXSLTForEachDlg, &IID_IXSLTForEachDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CXSLTForEachDlg, CAxDialogImpl<CXSLTForEachDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CXSLTForEachDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CXSLTForEachDlg()
	{
	}

	CComPtr<IEElement> m_webElement;

	enum { IDD = IDD_XSLTFOREACHDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_XSLTFOREACHDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXSLTForEachDlg)
	COM_INTERFACE_ENTRY(IXSLTForEachDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CXSLTForEachDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CXSLTForEachDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IXSLTForEachDlg
public:
// IInspectWebElementDlg
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"XSLT for-each");
		return S_OK;
	}
};

#endif //__XSLTFOREACHDLG_H_

#endif