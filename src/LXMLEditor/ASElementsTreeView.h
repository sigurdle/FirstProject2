// ASElementsTreeView.h : Declaration of the CASElementsTreeView

#ifndef __ASELEMENTSTREEVIEW_H_
#define __ASELEMENTSTREEVIEW_H_

#include "resource.h"       // main symbols

namespace System
{

class CEDTDDocument;

/////////////////////////////////////////////////////////////////////////////
// CASElementsTreeView
class CASElementsTreeView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CASElementsTreeView, &CLSID_ASElementsTreeView>,
//	public IDispatchImpl<IASElementsTreeView, &IID_IASElementsTreeView, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CASElementsTreeView, CWindowImpl<CASElementsTreeView> >,

//	public IUITreeControlSite,
//	public IDispEventImpl<4, CASElementsTreeView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>

{
public:
	CASElementsTreeView()
	{
		m_document = NULL;
//		m_hIcons = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CEDTDDocument* m_document;

	//CAxWindow m_axtreeCtl;
	UI::TreeControl* m_treeCtl;

#if 0
	HIMAGELIST m_hIcons;
#endif

#if 0
	void Populate(IUITreeItem* parentItem, IASContentModel* asCM);
	void Populate(IUITreeItem* item, IASElementDeclaration* elementDecl);
	void Populate(IUITreeItem* parentItem, IASNamedObjectMap* elementMap);
#endif

#if 0
BEGIN_SINK_MAP(CASElementsTreeView)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemDblClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemClick)
 //  SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
END_SINK_MAP()
#endif

#if 0
	HRESULT __stdcall OnItemClick(IUITreeItem* item);
//	HRESULT __stdcall OnItemDblClick(DWORD item);
//	HRESULT __stdcall OnContextMenu(long x, long y);
	HRESULT __stdcall OnItemExpanding(IUITreeItem* item, VARIANT_BOOL bExpanding, BOOL* bCancel);
#endif
	/*
BEGIN_MSG_MAP(CDTDView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
*/
//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

// IASElementsTreeView
public:
// IUIDlg
//	STDMETHOD(OnActivate)(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"AS Elements");
		return S_OK;
	}
	*/
// IUITreeControlSite
	ErrorCode GetItemText(ULONG_PTR itemdata, LONG column, System::StringW* * pVal);
};
}

#endif //__ASELEMENTSTREEVIEW_H_
