// SVGFontGlyphsDlg.h : Declaration of the CSVGFontGlyphsDlg

#ifndef __SVGFONTGLYPHSDLG_H_
#define __SVGFONTGLYPHSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSVGFontGlyphsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGFontGlyphsDlg, &CLSID_SVGFontGlyphsDlg>,
//	public IDispatchImpl<ISVGFontGlyphsDlg, &IID_ISVGFontGlyphsDlg, &LIBID_LXMLEDITORLib>,

public UI::Control,
//	public CUIDialogImpl<CSVGFontGlyphsDlg, CWindowImpl<CSVGFontGlyphsDlg> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// ILDOMEventListener

//	public IDispEventImpl<1, CSVGFontGlyphsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CSVGFontGlyphsDlg()
	{
		m_fontEElement = NULL;
	}

	int FinalConstruct();

	CEXMLViewGroup* m_viewGroup;

	Element* m_fontEElement;

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGFONTGLYPHSDLG)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGFontGlyphsDlg)
	COM_INTERFACE_ENTRY(ISVGFontGlyphsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

	void __stdcall OnViewGroupSelectionChanged();

#if 0
BEGIN_MSG_MAP(CSVGFontGlyphsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
/*
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
	long OnLButtonDblClk();

DECLARE_CMD_MAP(CSVGFontGlyphsDlg)

	long OnFontNewGlyph(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// ISVGFontGlyphsDlg
public:
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGFONTGLYPHSDLG_H_
