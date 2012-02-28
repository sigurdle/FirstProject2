// SVGAnimateMotionDlg.h : Declaration of the CSVGAnimateMotionDlg

#ifndef __SVGANIMATEMOTIONDLG_H_
#define __SVGANIMATEMOTIONDLG_H_

#if 0
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSVGAnimateMotionDlg
class ATL_NO_VTABLE CSVGAnimateMotionDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGAnimateMotionDlg, &CLSID_SVGAnimateMotionDlg>,
	public IDispatchImpl<ISVGAnimateMotionDlg, &IID_ISVGAnimateMotionDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CSVGAnimateMotionDlg, CAxDialogImpl<CSVGAnimateMotionDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CSVGAnimateMotionDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CSVGAnimateMotionDlg()
	{
	}

	CComPtr<IEElement> m_webElement;

	enum { IDD = IDD_SVGANIMATEMOTIONDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGANIMATEMOTIONDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGAnimateMotionDlg)
	COM_INTERFACE_ENTRY(ISVGAnimateMotionDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CSVGAnimateMotionDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CSVGAnimateMotionDlg)
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

// ISVGAnimateMotionDlg
public:
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"AnimateMotion");
		return S_OK;
	}
};

#endif //__SVGANIMATEMOTIONDLG_H_

#endif