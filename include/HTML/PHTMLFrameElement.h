#ifndef __PHTMLFrameElement_h__
#define __PHTMLFrameElement_h__

#include "PHTMLFrameSetBaseElement.h"

namespace System
{
namespace Web
{

//class HTMLFrameElement;

class CPHTMLFrameElementControl : public Gui::Control
{
public:
};

class HTMLEXT PHTMLFrameElement : public CHTMFrameNode
{
public:

	CTOR PHTMLFrameElement(HTMLFrameElement* element) : CHTMFrameNode(element)
	{
		m_frameType = 1;
		m_bTriedLoading = false;
		//m_pElement = NULL;
		m_pControl = NULL;
	}

	~PHTMLFrameElement()
	{
	}

	inline HTMLFrameElement* GetElement()
	{
		return (HTMLFrameElement*)m_pElement;
	}

//	HTMLFrameElement* m_pElement;

	CPHTMLFrameElementControl* m_pControl;

	bool m_bTriedLoading;

	void OnReady();

	void Set();

//	virtual void handleEvent(System::Event* evt);

#if 0
	/*
	CComPtr<ILHTMLFrameElement> GetFrameElement()
	{
		return CComQIPtr<ILHTMLFrameElement>(m_pNode);
	}
	*/

//	virtual BOOL OnButtonDown(POINT point, CPElement* *pVal);
//	virtual void Draw(CHTMRenderContext* pC);
//	virtual void CalculateDimensions(CHTMCalcContext* pC);
//	virtual BOOL HasDistributableChildren();

	virtual bool OnButtonDown(UINT nFlags, POINT point, int iButton, bool bDblClk, CHTMFrameNode** pFrame);
	virtual void OnMouseMove(UINT nFlags, POINT point);
	virtual void OnButtonUp(UINT nFlags, POINT point, int iButton);
	//BOOL OnSetCursor(UINT nHittest, UINT wMouseMsg);
//	virtual void OnContextMenu(HWND hWnd, POINT point);

//	virtual void OnPaint(HDC hDC);
	virtual void DrawCaret(HDC hDC);

	virtual BOOL HasDistributableChildren()
	{
		return FALSE;
	}

//	virtual void PlaceControls(HWND hWndParent, CHTMFlowBlockContext* /*pC*/);

#endif
};

}	// Web
}

#endif // __PHTMLFrameElement_h__
