// DTDView.h : Declaration of the CDTDView

#ifndef __DTDVIEW_H_
#define __DTDVIEW_H_

#include "resource.h"       // main symbols

//class CEDTDDocument;
class CEXMLViewGroup;

//class CDTDGraphCtl;

namespace System
{

class CDTDView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CDTDView>,
//	public IDispatchImpl<IDTDView, &IID_IDTDView, &LIBID_LXMLEDITORLib>,

	public UI::Control,
//	public CUIDialogImpl<CDTDView, CWindowImpl<CDTDView> >,
	public UI::ProcessTargetCommands	// ILDOMEventListener

//	public IDispEventImpl<3, CDTDView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CDTDView()
	{
		m_viewGroup = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

//	CComObject<CDTDDocument>* m_document;
//	CEDTDDocument* m_document;

	CEXMLViewGroup* m_viewGroup;

//	CAxWindow m_axDTDGraph;
//	CComPtr<IASGraphCtl> m_DTDGraph;

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDTDView)
	COM_INTERFACE_ENTRY(IDTDView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDTDView)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CDTDView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
#endif

	long OnCreate();
	long OnDestroy();
	long OnSize();

#if 0
BEGIN_SINK_MAP(CDTDView)
   SINK_ENTRY_EX(3, DIID__IEXMLDocumentEvents, /*dispid*/2, OnDoneParsing)
END_SINK_MAP()
#endif

	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);

	ErrorCode __stdcall OnDoneParsing();

DECLARE_CMD_MAP(CDTDView)

	long OnContentModelOptional(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnContentModelUnbounded(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnContentModelOptionalUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnContentModelUnboundedUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// IDTDView
public:
};
}

#endif //__DTDVIEW_H_
