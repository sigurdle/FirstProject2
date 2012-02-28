// XSLTTemplatesDlg.h : Declaration of the CXSLTTemplatesDlg

#ifndef __XSLTTEMPLATESDLG_H_
#define __XSLTTEMPLATESDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

/////////////////////////////////////////////////////////////////////////////
// CXSLTTemplatesDlg
class CXSLTTemplatesDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CXSLTTemplatesDlg, &CLSID_XSLTTemplatesDlg>,
//	public IDispatchImpl<IXSLTTemplatesDlg, &IID_IXSLTTemplatesDlg, &LIBID_LXMLEDITORLib>,

//	public CUIDialogImpl<CXSLTTemplatesDlg, CWindowImpl<CXSLTTemplatesDlg> >,
public UI::Control
//	public CUIEventHandlerImpl,
//	public IDropTarget

//	public IDispEventImpl<2, CXSLTTemplatesDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<4, CXSLTTemplatesDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
{
public:
	CXSLTTemplatesDlg()
	{
		m_viewGroup = NULL;
	}

	int FinalConstruct();

	//CComPtr<IDocumentsClass> m_documentsClass;
	CEXMLDocument* m_document;
	CEXMLViewGroup* m_viewGroup;

//	CAxWindow m_axtreeCtl;
	UI::TreeControl* m_treeCtl;

	void BuildTree();

//DECLARE_REGISTRY_RESOURCEID(IDR_XSLTTEMPLATESDLG)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXSLTTemplatesDlg)
	COM_INTERFACE_ENTRY(IXSLTTemplatesDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()
*/

#if 0
BEGIN_SINK_MAP(CXSLTTemplatesDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemDblClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemClick)
  // SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
 //  SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
END_SINK_MAP()
#endif

	ErrorCode __stdcall OnItemClick(ULONG_PTR item);
	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);

#if 0
BEGIN_MSG_MAP(CXSLTTemplatesDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
#endif

// IXSLTTemplatesDlg
public:
#if 0
// IDropTarget
	ErrorCode(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	ErrorCode(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	ErrorCode(DragLeave)();
	ErrorCode(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
#endif
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__XSLTTEMPLATESDLG_H_
