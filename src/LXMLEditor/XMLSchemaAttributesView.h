#ifndef __XMLSCHEMAATTRIBUTESVIEW_H_
#define __XMLSCHEMAATTRIBUTESVIEW_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CXMLSchemaAttributesView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CXMLSchemaAttributesView, &CLSID_XMLSchemaAttributesView>,
//	public IConnectionPointContainerImpl<CXMLSchemaAttributesView>,
public UI::Control//CWindowImpl<CXMLSchemaAttributesView>

//	public IDispEventImpl<4, CXMLSchemaAttributesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
//	public IDispatchImpl<IUITreeControlSite, &IID_IUITreeControlSite, &LIBID_UILib>
{
public:
	//DECLARE_WND_CLASS(NULL)

	CXMLSchemaAttributesView()
	{
	}

	int FinalConstruct();

//	CAxWindow	m_axtreeCtl;
//	CComQIPtr<IUITreeControl> m_treeCtl;

#if 0
BEGIN_SINK_MAP(CXMLSchemaAttributesView)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemDblClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemClick)
END_SINK_MAP()
#endif
	ErrorCode __stdcall OnItemClick(ULONG_PTR item);
	ErrorCode __stdcall OnItemDblClick(ULONG_PTR item);

	/*
BEGIN_MSG_MAP(CXMLSchemaAttributesView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
*/
// IXMLSchemaAttributesView
public:
	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/

// IUITreeControlSite
	ErrorCode GetItemText(ULONG_PTR itemdata, LONG column, System::StringW* * pVal);
};

}	// LXmlEdit
}

#endif //__XMLSCHEMAATTRIBUTESVIEW_H_
