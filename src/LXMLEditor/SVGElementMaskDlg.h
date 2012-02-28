
#ifndef __SVGELEMENTMASKDLG_H_
#define __SVGELEMENTMASKDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSVGElementMaskDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGElementMaskDlg, &CLSID_SVGElementMaskDlg>,
//	public IDispatchImpl<ISVGElementMaskDlg, &IID_ISVGElementMaskDlg, &LIBID_LXMLEDITORLib>,

public UI::Control,
//	public CUIDialogImpl<CSVGElementMaskDlg, CWindowImpl<CSVGElementMaskDlg> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// ILDOMEventListener
{
public:
	CSVGElementMaskDlg()
	{
	}

	int FinalConstruct();

	CEXMLViewGroup* m_viewGroup;

	Web::SVGElement* m_svgElement;

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGELEMENTMASKDLG)

	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/
/*
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

DECLARE_CMD_MAP(CSVGElementMaskDlg)

	long OnMakeMask(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// ISVGElementMaskDlg
public:
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGELEMENTMASKDLG_H_
