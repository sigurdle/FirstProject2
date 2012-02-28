#ifndef Web_HTMFrameNode_h
#define Web_HTMFrameNode_h

#include "PHTMLElement.h"

namespace System
{
namespace Web
{

//class CHTMLWindow;
//class PHTMLFrameSetElement;

class HTMLEXT CHTMFrameNode : public PHTMLElement
{
public:
	CTOR CHTMFrameNode(HTMLElement* element);
	~CHTMFrameNode();

	int m_frameType;	// 0=frameset

#if 0	// Test without this (use m_parent instead ?)
	CHTMFrame* m_pParentFrame;
#endif

	CHTMLWindow* m_pParentWindow;
//	CPHTMLFrameSetElement* m_pPOuterFrameSet;
#if 0
	CLHTMLDocumentView*	m_pUI;
#endif
#if 0
	CRect	m_client;
#endif
	PHTMLFrameSetElement* m_pParentFrameSet;

#if 0	// Test without this
	CHTMFrame* GetTopFrame();
#endif

#if 0	// Try without this
	virtual void UIActivate() = 0;
#endif

#if 0
	virtual void SetView(CLHTMLDocumentView* view) = 0;
#endif

//	virtual void OnPaint(HDC hDC) = 0;
	virtual void DrawCaret(HDC hDC)
	{
	}

#if 0	// Removed this ??
	virtual void PositionFrames(HWND hWndParent) = 0;
#endif

	/*
	virtual bool OnButtonDown(UINT nFlags, POINT point, int iButton, bool bDblClk, CHTMFrameNode** pFrame) = 0;
	virtual void OnMouseMove(UINT nFlags, POINT point) = 0;
	virtual void OnButtonUp(UINT nFlags, POINT point, int iButton) = 0;
	*/
#if 0
	virtual void OnContextMenu(HWND hWnd, POINT point)
	{
	}
#endif
};

}	// Web
}

#endif // Web_HTMFrameNode_h
