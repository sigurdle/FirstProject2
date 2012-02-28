// ElementEventsDlg.h : Declaration of the CElementEventsDlg

#ifndef __ELEMENTEVENTSDLG_H_
#define __ELEMENTEVENTSDLG_H_

#include "resource.h"       // main symbols
//#import "C:\MMStudio\Extras\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

namespace System
{

class CElementEventsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CElementEventsDlg, &CLSID_ElementEventsDlg>,
//	public IConnectionPointContainerImpl<CElementEventsDlg>,
//	public IDispatchImpl<IElementEventsDlg, &IID_IElementEventsDlg, &LIBID_LXMLEDITORLib>,
//	public CUIDialogImpl<CElementEventsDlg, CWindowImpl<CElementEventsDlg> >
public UI::Control
{
public:
	CElementEventsDlg()
	{
//		m_puiwnd = NULL;

//		m_hIcons = NULL;
	}


//	CAxWindow	m_axtreeCtl;
	UI::TreeControl* m_treeCtl;

#if 0
//DECLARE_REGISTRY_RESOURCEID(IDR_ELEMENTEVENTSDLG)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementEventsDlg)
	COM_INTERFACE_ENTRY(IElementEventsDlg)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, IElementEventsDlg)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CElementEventsDlg)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CElementEventsDlg)
/*
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
*/
/*
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
*/
END_MSG_MAP()
#endif

// IElementEventsDlg
public:
};
}

#endif //__ELEMENTEVENTSDLG_H_
