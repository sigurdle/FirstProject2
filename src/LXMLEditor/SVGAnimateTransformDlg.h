// SVGAnimateTransformDlg.h : Declaration of the CSVGAnimateTransformDlg

#ifndef __SVGANIMATETRANSFORMDLG_H_
#define __SVGANIMATETRANSFORMDLG_H_

#if 0

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSVGAnimateTransformDlg
class ATL_NO_VTABLE CSVGAnimateTransformDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGAnimateTransformDlg, &CLSID_SVGAnimateTransformDlg>,
	public IDispatchImpl<ISVGAnimateTransformDlg, &IID_ISVGAnimateTransformDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CSVGAnimateTransformDlg, CAxDialogImpl<CSVGAnimateTransformDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CSVGAnimateTransformDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CSVGAnimateTransformDlg()
	{
	}

	CComPtr<IEElement> m_webElement;

	enum { IDD = IDD_SVGANIMATETRANSFORMDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGANIMATETRANSFORMDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGAnimateTransformDlg)
	COM_INTERFACE_ENTRY(ISVGAnimateTransformDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CSVGAnimateTransformDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CSVGAnimateTransformDlg)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	COMMAND_HANDLER(IDC_NITF_TITLE, EN_KILLFOCUS, OnTitle)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISVGAnimateTransformDlg
public:
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"AnimateTransform");
		return S_OK;
	}
};

#endif //__SVGANIMATETRANSFORMDLG_H_

#endif