// XSLTTemplateDlg.h : Declaration of the CXSLTTemplateDlg

#if 0
#ifndef __XSLTTEMPLATEDLG_H_
#define __XSLTTEMPLATEDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXSLTTemplateDlg
class ATL_NO_VTABLE CXSLTTemplateDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CXSLTTemplateDlg, &CLSID_XSLTTemplateDlg>,
	public IDispatchImpl<IXSLTTemplateDlg, &IID_IXSLTTemplateDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CXSLTTemplateDlg, CAxDialogImpl<CXSLTTemplateDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CXSLTTemplateDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CXSLTTemplateDlg()
	{
	}

	CComPtr<IEElement> m_webElement;

	enum { IDD = IDD_XSLTTEMPLATEDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_XSLTTEMPLATEDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXSLTTemplateDlg)
	COM_INTERFACE_ENTRY(IXSLTTemplateDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CXSLTTemplateDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CXSLTTemplateDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IXSLTTemplateDlg
public:
// IInspectWebElementDlg
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"XSLT template");
		return S_OK;
	}
};

#endif //__XSLTTEMPLATEDLG_H_

#endif