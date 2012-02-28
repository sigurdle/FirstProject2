// SmilTimeGraphView.h : Declaration of the CSmilTimeGraphView

#ifndef __SMILTIMEGRAPHVIEW_H_
#define __SMILTIMEGRAPHVIEW_H_

//#include "resource.h"       // main symbols

#include "..\LXUI\PopupMenuButton.h"	// TODO, don't have it like this

namespace System
{
namespace LXmlEdit
{

class CTGNode;
class CTGElement;
class CTimeBlock;
class CTimeElement;

//class CEXMLViewGroup;
class CSmilTimeGraphView;

class CTGNode : public System::Object
{
public:
	CTGNode()
	{
		m_pGraphView = NULL;
		m_parent = NULL;
		m_height = 0;

		m_y = 0;
		m_height = 0;
		m_itemHeight = 0;

		m_selected = false;
		m_expanded = true;

		m_type = 0;
	}

	virtual void Free()
	{
//		Release();
		delete this;
	}

	int m_type;

	int m_y;

	int m_height;

	int m_itemHeight;

	bool m_expanded;
	bool m_selected;

	CSmilTimeGraphView* m_pGraphView;
	CTGElement* m_parent;

	virtual void Deselect()
	{
		m_selected = false;
	}

	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected) = 0;
	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging)
	{
		return NULL;
	}
	virtual void OnButtonDblClk(LDraw::PointD point, long& dragging)
	{
	}
	virtual void OnDrag(LDraw::PointD point, long dragging)
	{
	}

	virtual void CalculateSize()
	{
	}
};

class CTGElement : public CTGNode
{
public:
	CTGElement()
	{
		m_domElement = NULL;
		m_type = 1;
	}

	~CTGElement()
	{
	}

	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CTGNode* p = (CTGNode*)m_childList.GetNext(pos);
			p->Free();
		}
		m_childList.RemoveAll();
#endif
	}

	Element* m_domElement;
	Array<CTGNode*> m_childList;

	virtual void Deselect()
	{
		m_selected = false;

		ASSERT(0);
#if 0
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CTGNode* p = (CTGNode*)m_childList.GetNext(pos);
			p->Deselect();
		}
#endif
	}

	virtual void Free();
	virtual void SetElement(Element* domElement);

	virtual void BuildTimeGraph(Element* parentElement);

	void AddChildTail(CTGNode* pNode)
	{
		pNode->m_parent = this;
		m_childList.Add(pNode);
	}

	IESelectedElement* ActivateElement(UINT nFlags);
	virtual void CalculateSize();
	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected);
	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);
	virtual void OnButtonDblClk(LDraw::PointD point, long& dragging);
	virtual CTGNode* OnButtonDownChildren(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);
};

class CTransNode :
	public CTGNode
{
public:
	CTransNode()
	{
		m_type = -1;
		m_childSelectedIndex = -1;
	}

	int m_childSelectedIndex;	// The selected child transition

	System::StringW* m_name;

	/*
	TODO	// CTGNode::Deselect()
	*/

	virtual void Deselect()
	{
		m_selected = false;
		m_childSelectedIndex = -1;
	}

	virtual void CalculateSize();
	virtual void Draw(UI::Graphics* pGraphics, int nPane, LDraw::BBoxi rect, bool bSelected);
	virtual CTGNode* OnButtonDown(int nPane, LDraw::PointD point, UINT nFlags, long& dragging);

/*
	virtual void Draw(HDC hDC, int nPane, CRect rect, BOOL bSelected)
	{
		int dsty = TXHEIGHT;
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CTGNode* pNode = (CTGNode*)m_childList.GetNext(pos);

			int dstx = 0;//pElement->m_x*secondWidth;

			POINT oldOrg;
			OffsetViewportOrgEx(hDC, dstx, dsty, &oldOrg);

			pNode->Draw(hDC, nPane, textIndent + 1, bSelected);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			dsty += pNode->m_height;
		}
	}
	*/
};

class CSmilTimeGraphView : 
public UI::Control
//	public ProcessTargetCommands	// Web::EventListener
//	public IDropTarget
#if 0
	public IDispEventImpl<1, CSmilTimeGraphView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,

	public IDispEventImpl<3, CSmilTimeGraphView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
//	public IDispEventImpl<5, CSmilTimeGraphView, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>
{
public:
	class CPane
//		public IDispEventImpl<1, CPane, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//		public IDispEventImpl<2, CPane, &DIID__IUISliderEvents, &LIBID_UILib, 1, 0>
	{
	public:
		CPane(CSmilTimeGraphView* pGraphView, System::StringW* name, int width)
		{
			m_pGraphView = pGraphView;

			m_name = name;
			m_width = width;

			m_subwidth = 0;
			m_scrollbarLeft = 0;
		}

		CSmilTimeGraphView* m_pGraphView;

		LDraw::RectD m_client;

		System::StringW* m_name;
		int m_width;

		/*
		CAxWindow m_axhorz;
		CComPtr<IUIScrollBar> m_horz;

		CAxWindow m_axslider;
		CComPtr<IUISlider> m_slider;
		*/

		int m_scrollbarLeft;

		int m_subwidth;
		Array<CPane*> m_subpanes;

#if 0
	BEGIN_SINK_MAP(CPane)
//	   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
//	   SINK_ENTRY_EX(2, DIID__IUISliderEvents, /*dispid*/1, OnSliderPos)
	END_SINK_MAP()
#endif
		void __stdcall OnHorzScroll(long code, long pos);
		void __stdcall OnSliderPos(long code, long pos);
	};

	CSmilTimeGraphView();

	int FinalConstruct();
	void FinalRelease();

	double m_iconDuration;

	System::StringW* m_userDataKey;

	int m_mode;

	Array<CPane*> m_panes;

	CEXMLViewGroup* m_viewGroup;
//	CComQIPtr<IEXMLDocument> m_document;

#if 0
	CAxWindow m_axvert;
	CComPtr<IUIScrollBar> m_vert;
#endif

	CTimeBlock* m_body;
	LDraw::Font* m_hSmallFont;

	CTGNode* m_pActiveNode;

	double m_compDuration;
	double m_secondWidth;

	long m_dragging;
	LDraw::PointD m_point;
	LDraw::PointD m_startpoint;
	LDraw::PointD m_oldpoint;
	int m_nPane;
//	int m_paneLeft;
	int m_oldwidth;

	int m_iconSize;
	int m_trackFormat;

	CPopupMenuButton m_menuButton;

	void OnLButtonDown(LDraw::PointD point, UINT nFlags, int parentPane, Array<CPane*>& panes);
	void OnMouseMove(LDraw::PointD point, UINT nFlags, int nPane, Array<CPane*>& panes);
	void DrawPanes(UI::Graphics* pGraphics, LDraw::BBoxi client, int parentPane, Array<CPane*>& panes);

	void BuildTree();

	void DrawBlock(CTimeBlock* pParent, UI::Graphics* pGraphics, int& x, int& y);
	void CalculateMaxSize(CTimeBlock* pParent, int& x, int& y);

	void DrawSecondTicks(UI::Graphics* pGraphics);

	void OnSize();
	void ResetVScrollBar();

	double GetCurrentTime();
	void SetCurrentTime(double currentTime);

	CTGElement* CreateTGElement(Element* element);

	/*
	void GetClientRect(LPRECT lprect)
	{
		lprect->left = 0;
		lprect->top = 0;
		lprect->right = 300;
		lprect->bottom = 200;
	}*/

	void SetCapture()
	{
		// TODO
	}

	/*
	void InvalidateRect(LPRECT lprect)
	{
	//	CComQIPtr<IHTMLPaintSite> paintSite = m_behaviorSite;
	//	paintSite->InvalidateRect(lprect);
	}

	void Invalidate()
	{
		InvalidateRect(NULL);
	}
	*/

// ILElementBehavior
#if 0
	CComPtr<ILElementBehaviorSite> m_behaviorSite;

	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
	{
		m_behaviorSite = pBehaviorSite;
		OnCreate();

		return S_OK;
	}
	STDMETHODIMP Detach()
	{
		OnDestroy();
		m_behaviorSite.Release();

		return S_OK;
	}
#endif
	virtual void OnRender(UI::Graphics* pGraphics);
#if 0
	STDMETHOD(SetCursor)(/*[in]*/ POINT pt)
	{
		return S_OK;
	}
#endif

#if 0
BEGIN_SINK_MAP(CSmilTimeGraphView)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(3, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()
#endif
//	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);
	void __stdcall OnDOMEvent(Web::Event* evt);

//	HRESULT __stdcall OnActivatedObject(IUnknown* object);
//	HRESULT __stdcall OnDeactivatedObject(IUnknown* object);

#if 0
BEGIN_MSG_MAP(CSmilTimeGraphView)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);

END_MSG_MAP()
#endif

/*
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnCreate();
	long OnDestroy();
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/
	long OnLButtonDown(UINT nFlags, LDraw::PointD point);

	long OnLButtonDblClk();

	long OnLButtonUp(LDraw::PointD point);
	long OnMouseMove();
	/*
	long OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
*/
	long OnContextMenu();
//DECLARE_CMD_MAP(CSmilTimeGraphView)

	long OnEditClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnTimeGraphOptions(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnElementTimeBegin(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnElementTimeEnd(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnAddBeginTime(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnAddEndTime(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnAnimationAddKeyframe(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
//	long OnTimeAttributes(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//	void OnTimeAttributesUpdate(long id, IUICmdUpdate* pCmdUI);

	long OnInsertTimelineSequence(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertTimelineParalell(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

#if 0
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
#endif

// Web::EventListener
	virtual void handleEvent(System::Event* evt);

// ISmilTimeGraphView
public:
	CEXMLViewGroup* get_viewGroup();
//	STDMETHOD(put_document)(/*[in]*/ IEXMLDocument* newVal);
// IUIDlg
//	STDMETHOD(OnActivate)(BOOL bActivate, Control* pActivateView, Control* pDeactivateView);
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"TimeGraph");
		return S_OK;
	}
	*/
// ICommandTarget
//	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

}	// LXmlEdit
}

#endif //__SMILTIMEGRAPHVIEW_H_
