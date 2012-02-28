// NewsItemView.h : Declaration of the CNewsItemView

#ifndef __NEWSITEMVIEW_H_
#define __NEWSITEMVIEW_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CNewsItemView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CNewsItemView, &CLSID_NewsItemView>,
//	public IDispatchImpl<INewsItemView, &IID_INewsItemView, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CNewsItemView, CWindowImpl<CNewsItemView> >
{
public:
	CNewsItemView()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_NEWSITEMVIEW)

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNewsItemView)
	COM_INTERFACE_ENTRY(INewsItemView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()

BEGIN_MSG_MAP(CNewsItemView)
//	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
#endif

//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// INewsItemView
public:
// IUIDlg
//	STDMETHOD(OnActivate)(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"NewsItem");
		return S_OK;
	}
	*/
};

}
}

#endif //__NEWSITEMVIEW_H_
