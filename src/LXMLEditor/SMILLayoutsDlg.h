// SMILLayoutsDlg.h : Declaration of the CSMILLayoutsDlg

#ifndef __SMILLAYOUTSDLG_H_
#define __SMILLAYOUTSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSMILLayoutsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSMILLayoutsDlg, &CLSID_SMILLayoutsDlg>,
//	public IDispatchImpl<ISMILLayoutsDlg, &IID_ISMILLayoutsDlg, &LIBID_LXMLEDITORLib>,

	public UI::Control,
//	public CUIDialogImpl<CSMILLayoutsDlg, CWindowImpl<CSMILLayoutsDlg> >,
//	public CUIEventHandlerImpl,
	public UI::ProcessTargetCommands	// Web::EventListener

//	public IDispEventImpl<3, CSMILLayoutsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CSMILLayoutsDlg()
	{
	}

	int FinalConstruct();

	CEXMLViewGroup* m_viewGroup;

	Array<Web::Element*> m_layouts;

	void BuildItems();

//DECLARE_REGISTRY_RESOURCEID(IDR_SMILLAYOUTSDLG)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSMILLayoutsDlg)
	COM_INTERFACE_ENTRY(ISMILLayoutsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(Web::EventListener)
END_COM_MAP()
*/
#if 0
BEGIN_SINK_MAP(CSMILLayoutsDlg)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
//   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(3, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()
#endif

//	ErrorCode __stdcall OnHorzScroll(long code, long pos);
//	ErrorCode __stdcall OnVertScroll(long code, long pos);

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);

/*
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
*/

DECLARE_CMD_MAP(CSMILLayoutsDlg)

// ISMILLayoutsDlg
public:
// IUIDlg
	/*
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Animation");
		return S_OK;
	}
	*/
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
// ICommandTarget
	ErrorCode OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled);
};

}	// LXmlEdit
}

#endif //__SMILLAYOUTSDLG_H_
