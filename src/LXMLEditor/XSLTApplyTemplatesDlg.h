// XSLTApplyTemplatesDlg.h : Declaration of the CXSLTApplyTemplatesDlg

#if 0
#ifndef __XSLTAPPLYTEMPLATESDLG_H_
#define __XSLTAPPLYTEMPLATESDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXSLTApplyTemplatesDlg
class ATL_NO_VTABLE CXSLTApplyTemplatesDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CXSLTApplyTemplatesDlg, &CLSID_XSLTApplyTemplatesDlg>,
	public IDispatchImpl<IXSLTApplyTemplatesDlg, &IID_IXSLTApplyTemplatesDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CXSLTApplyTemplatesDlg, CAxDialogImpl<CXSLTApplyTemplatesDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CXSLTApplyTemplatesDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CXSLTApplyTemplatesDlg()
	{
	}

	CComPtr<IEElement> m_webElement;

	enum { IDD = IDD_XSLTAPPLYTEMPLATESDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_XSLTAPPLYTEMPLATESDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXSLTApplyTemplatesDlg)
	COM_INTERFACE_ENTRY(IXSLTApplyTemplatesDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CXSLTApplyTemplatesDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CXSLTApplyTemplatesDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IXSLTApplyTemplatesDlg
public:
// IInspectWebElementDlg
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"XSLT apply-templates");
		return S_OK;
	}
};

#endif //__XSLTAPPLYTEMPLATESDLG_H_

#endif