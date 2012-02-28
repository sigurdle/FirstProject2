// DTDView.h : Declaration of the CSchemaDiagramView

#ifndef __SCHEMADIAGRAMVIEW_H_
#define __SCHEMADIAGRAMVIEW_H_

#include "resource.h"       // main symbols

//class CDTDDocument;

//class CDTDGraphCtl;

//#import "..\ASEditCtlsMod\ASEditCtlsMod.tlb" no_namespace, raw_interfaces_only

#include "XMLSchemaGlobalsCtl.h"
#include "XMLSchemaDesignCtl.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CSchemaDiagramView
class CSchemaDiagramView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSchemaDiagramView, &CLSID_DTDView>,
//	public IConnectionPointContainerImpl<CSchemaDiagramView>,
//	public IDispatchImpl<IDTDView, &IID_IDTDView, &LIBID_WEBEDITORLib>,

public UI::Control,//CUIDialogImpl<CSchemaDiagramView, CWindowImpl<CSchemaDiagramView> >,
public UI::ProcessTargetCommands	// ILDOMEventListener

//	public IDispEventImpl<3, CSchemaDiagramView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CSchemaDiagramView()
	{
		m_asModel = NULL;

		m_pWndGraph = NULL;

		m_splity = 200;
	}

	int FinalConstruct();
	void FinalRelease();

//	CComPtr<IWebXMLDocument> m_document;
	CEXMLViewGroup* m_viewGroup;

	Web::IASModel* m_asModel;

//	CAxWindow m_axDTDGraph;
//	CComPtr<IASGraphCtl> m_DTDGraph;

	CXMLSchemaGlobalsCtl m_wndGlobals;
	CXMLSchemaDesignCtl* m_pWndGraph;

	int m_splity;

	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/

#if 0
BEGIN_SINK_MAP(CSchemaDiagramView)
//   SINK_ENTRY_EX(3, DIID__IWebXMLDocumentEvents, /*dispid*/2, OnDoneParsing)
END_SINK_MAP()
#endif
//	void __stdcall OnHorzScroll(long code, long pos);
//	void __stdcall OnVertScroll(long code, long pos);

//	HRESULT __stdcall OnDoneParsing();

DECLARE_CMD_MAP(CSchemaDiagramView)

// IDTDView
public:
// IUIDlg
	/*
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Schema Diagram");
		return S_OK;
	}
	*/
// ICommandTarget
	ErrorCode OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled);
};

}	// LXmlEdit
}

#endif //__SCHEMADIAGRAMVIEW_H_
