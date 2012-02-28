// SVGFontsDlg.h : Declaration of the CSVGFontsDlg

#ifndef __SVGFONTSDLG_H_
#define __SVGFONTSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSVGFontsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGFontsDlg, &CLSID_SVGFontsDlg>,
//	public IDispatchImpl<ISVGFontsDlg, &IID_ISVGFontsDlg, &LIBID_LXMLEDITORLib>,

public UI::Control,
//	public CUIDialogImpl<CSVGFontsDlg, CWindowImpl<CSVGFontsDlg> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// ILDOMEventListener
{
public:
	CSVGFontsDlg()
	{
	}

	CEXMLDocument* m_document;

	int FinalConstruct();

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGFONTSDLG)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGFontsDlg)
	COM_INTERFACE_ENTRY(ISVGFontsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

#if 0
BEGIN_MSG_MAP(CSVGFontsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
/*
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	*/
/*
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	*/
END_MSG_MAP()
#endif

	long OnCreate();
	long OnDestroy();
	long OnPaint();
	long OnLButtonDown();

DECLARE_CMD_MAP(CSVGFontsDlg)

	long OnFontNewFont(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// ISVGFontsDlg
public:
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGFONTSDLG_H_
