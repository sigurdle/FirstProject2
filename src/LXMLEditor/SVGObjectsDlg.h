// SVGObjectsDlg.h : Declaration of the CSVGObjectsDlg

#ifndef __SVGOBJECTSDLG_H_
#define __SVGOBJECTSDLG_H_

#include "resource.h"       // main symbols

#include "item.h"

class CView;

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

class CSVGObjectsDlg;

class Node;
class CElement;

class CBaseNode :
	public System::Object,
	public C2Obj
{
public:
	Node* m_node;

	CBaseNode()
	{
		m_node = NULL;
	}

	CElement* FindElement(Node* node);

	CBaseNode* GetParentNode()
	{
		return (CBaseNode*)m_parent;
	}

	void DeselectAll()
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CBaseNode* pNode = (CBaseNode*)(C2Obj*)m_childList.GetNext(pos);
			pNode->m_selected = false;
		}
#endif
	}

	bool MakeExpanded(Element* eElement);
};

class CNode :
	public CBaseNode
{
public:
	CNode()
	{
	}
};

class CElement :
	public CBaseNode
{
public:
	Element* m_eElement;

	bool m_bAllTargeted;
	bool m_bAnyTargeted;

	CElement()
	{
		m_eElement = NULL;

		m_bAllTargeted = false;
		m_bAnyTargeted = false;
	}
};

class CSVGRenderableObjectsWnd
//	public CWindowImpl<CSVGObjectsDlg>,
//	public IDispEventImpl<1, CSVGRenderableObjectsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CSVGRenderableObjectsWnd();

	CSVGObjectsDlg* m_dlg;

	C2Obj* m_pRoot;
	int m_itemHeight;

	LDraw::Bitmap* m_expandedBitmap;
	LDraw::Bitmap* m_visibleBitmap;

	LDraw::BBoxi m_areaRect;

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar> m_vert;

	LDraw::Font* m_font;
	LDraw::Font* m_boldFont;

	void ResetVScrollSize();

	void DrawItem(CElement* pItem, int level, int& y, LDraw::BBoxi& clip, UI::Graphics* pGraphics, Web::Element* rulerElement);
	void DrawItemChildren(C2Obj* pParentItem, int level, int& y, LDraw::BBoxi& clip, UI::Graphics* pGraphics, Web::Element* rulerElement);

	/*
	void InvalidateRect(LPRECT lprect)
	{
	}
	*/
#if 0
BEGIN_SINK_MAP(CSVGRenderableObjectsWnd)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()
#endif
	void __stdcall OnVertScroll(long code, long pos);

/*
BEGIN_MSG_MAP(CSVGRenderableObjectsWnd)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
*/

	long OnCreate();
	long OnDestroy();
//	ErrorCode(Draw)(ILCanvas* canvas);
	//long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

class CSVGObjectsDlg : 

#if 0
	public CUIDialogImpl<CSVGObjectsDlg, CWindowImpl<CSVGObjectsDlg> >,
#endif
//	public ILElementBehavior,
//	public ILHTMLPainter,
public UI::Control,

public UI::ProcessTargetCommands	// Web::EventListener

#if 0
	public IDispEventImpl<2, CSVGObjectsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
	public IDispEventImpl<3, CSVGObjectsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGObjectsDlg()
	{
		m_app = NULL;

		m_pTree = NULL;

	//	m_pActiveSelection = NULL;
		m_referencedElement = NULL;

		m_elementType = 0;
	}

	int FinalConstruct();
	void FinalRelease();

	CView* m_view;
	ILXMLEditorApp* m_app;

	Element* m_referencedElement;

	System::StringW* m_userDataKey;

	CEXMLDocument* m_document;
	CEXMLViewGroup* m_viewGroup;

	CNode* m_pTree;

	int m_elementType;

	//CElement* m_pActiveSelection;

	CSVGRenderableObjectsWnd m_renderableWnd;

	UI::Control * m_sizeGrip;

	LDraw::BBoxi m_areaRect;

//	bool AllChildrensTargeted(CElement* pElement);

	void SetIsTargeted(CElement* pElement);

	void BuildChildren(CBaseNode* pNode, CEXMLDocument* edocument);
	bool IsAddableElement(Web::Node* element);

	void OnSize();

	void SetRoot();

	void BuildTree();

// ILElementBehavior
//	CComPtr<ILElementBehaviorSite> m_behaviorSite;

	/*
	void InvalidateRect(LPRECT lprect)
	{
	}
  */

//	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite);
//	STDMETHODIMP Detach();

#if 0
BEGIN_SINK_MAP(CSVGObjectsDlg)
	SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
   SINK_ENTRY_EX(3, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()
#endif

	void __stdcall OnDOMEvent(Web::Event* evt);
	void __stdcall OnViewGroupSelectionChanged();

	long OnCreate();
	long OnDestroy();

//	ErrorCode(Draw)(ILCanvas* canvas);

//	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

DECLARE_CMD_MAP(CSVGObjectsDlg)

	long OnNewLayer(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewSubLayer(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnDeleteSelection(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnDeleteSelectionUpdate(long wID, UI::IUICmdUpdate* pCmdUI);
	long OnSelectionOptions(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// ISVGObjectsDlg
public:
	ErrorCode OnDragOut(UI::CUIDockBar* dockBar);

// ICommandTarget
//	ErrorCode(OnCmdMsg)(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, BOOL * bHandled);

// IUIEventHandler
//	ErrorCode(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	ErrorCode(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGOBJECTSDLG_H_
