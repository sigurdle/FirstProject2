// AnimateAttributesDlg.h : Declaration of the CAnimateAttributesDlg

#ifndef __ANIMATEATTRIBUTESDLG_H_
#define __ANIMATEATTRIBUTESDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

#define SET						1
#define ANIMATE				2
#define ANIMATECOLOR			4
#define ANIMATETRANSFORM	8
#define ANIMATEMOTION		16

struct AnimatableAttribute
{
	AnimatableAttribute(WCHAR* attributeType, WCHAR* attributeName, uint32 flags)
	{
		m_attributeType = attributeType;
		m_attributeName = attributeName;
		m_flags = flags;
	}
	WCHAR* m_attributeType;
	WCHAR* m_attributeName;
	uint32 m_flags;
};

class CAnimateAttributesDlg : 
//	public CComCoClass<CAnimateAttributesDlg, &CLSID_AnimateAttributesDlg>,
//	public IDispatchImpl<IAnimateAttributesDlg, &IID_IAnimateAttributesDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIEventHandlerImpl,

//	public IDispEventImpl<1, CAnimateAttributesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CAnimateAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CAnimateAttributesDlg()
	{
		m_app = NULL;
		m_index = -1;

		m_itemHeight = 18;
	}

	int FinalConstruct()
	{
		ErrorCode hr;

		/*
		hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
		if (FAILED(hr)) return hr;
		m_vert->put_direction(1);
		*/

		return 0;
	}

	void FinalRelease()
	{
//		m_vert.Release();
	}

	UI::CView* m_view;

	CLXMLEditorApp* m_app;

	CEXMLViewGroup* m_viewGroup;

	Web::ISMILAnimationTarget* m_targetElement;

	int m_index;
	Array<AnimatableAttribute> m_attributes;

	int m_itemHeight;
	LDraw::BBoxi m_areaRect;

//	CAxWindow m_axvert;
//	ScrollBar* m_vert;

	void ResetVScrollBar();

#if 0
BEGIN_SINK_MAP(CAnimateAttributesDlg)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(2, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()
#endif

	void __stdcall OnVertScroll(long code, long pos);
	void __stdcall OnViewGroupSelectionChanged();

	/*
BEGIN_MSG_MAP(CAnimateAttributesDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
//	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()
*/
	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/*
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int fActive = LOWORD(wParam);           // activation flag 
		if (fActive == WA_INACTIVE)
		{
			m_pDlgSite->Show(FALSE);
			//DestroyWindow();
		}
		return 0;
	}
	*/
	/*
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pDlgSite->Show(FALSE);
		return 0;
	}
	*/

	ErrorCode OnFrameActivate(long fActive)
	{
		if (fActive == 0)
		{
			ASSERT(0);
#if 0
			m_pDlgSite->Show(FALSE);
#endif
		}
		return Success;
	}

// IAnimateAttributesDlg
public:
// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__ANIMATEATTRIBUTESDLG_H_
