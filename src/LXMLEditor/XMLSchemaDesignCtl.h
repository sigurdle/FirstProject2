#ifndef __XMLSCHEMADESIGNCTL_H_
#define __XMLSCHEMADESIGNCTL_H_

#include "resource.h"       // main symbols

class CSchemaDiagramView;

//#import "..\ASEditCtlsMod\ASEditCtlsMod.tlb" no_namespace, named_guids, raw_interfaces_only

namespace System
{
namespace LXmlEdit
{

class CXMLSchemaDesignCtl : 
//	public CComObjectRootEx<CComSingleThreadModel>,
public UI::Control,//CWindowImpl<CXMLSchemaDesignCtl>,
	public UI::ProcessTargetCommands	// ILDOMEventListener
{
public:
	CXMLSchemaDesignCtl()
	{
		m_pSchema = NULL;
	}

	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
	}

	CSchemaDiagramView* m_pSchema;

#if 0
	CAxWindow m_axasGraph;
	CComPtr<IASGraphCtl> m_asGraph;
#endif

	/*
BEGIN_COM_MAP(CXMLSchemaDesignCtl)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

	/*
BEGIN_SINK_MAP(CXMLSchemaDesignCtl)
END_SINK_MAP()
*/

#if 0
BEGIN_MSG_MAP(CXMLSchemaDesignCtl)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN,, OnLButtonDown)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
/*
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_CHAR, OnChar)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
*/
//MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
END_MSG_MAP()
#endif

DECLARE_CMD_MAP(CXMLSchemaDesignCtl)

void OnViewZoomout(long iid);
void OnViewZoomin(long iid);

// IXMLSchemaDesignCtl
public:
//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/*
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/
//	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

}
}

#endif //__XMLSCHEMADESIGNCTL_H_
