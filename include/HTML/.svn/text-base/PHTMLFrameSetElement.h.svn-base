#ifndef __Web_PHTMLFrameSetElement_h__
#define __Web_PHTMLFrameSetElement_h__

#include "PHTMLFrameSetBaseElement.h"

namespace System
{
namespace Web
{

class PHTMLFrameElement;
class HTMLFrameSetElement;

class HTMLEXT PHTMLFrameSetElement : public CHTMFrameNode
{
public:
	CTOR PHTMLFrameSetElement(HTMLFrameSetElement* element);
	~PHTMLFrameSetElement();

	PHTMLFrameElement* FindFrameByName(StringIn name);

	virtual void UIActivate();

#if 0
	void CreateFrames(ILHTMLFrameSetElement* pFrameSetElement, CPHTMLFrameElement* parentFrame);
#endif

	virtual void BuildRenderableChildren();

#if 0
	virtual void SetView(CLHTMLDocumentView* view)
	{
		UPOSITION pos = m_frames.GetHeadPosition();
		while (pos)
		{
			CHTMFrameNode* frame = (CHTMFrameNode*)m_frames.GetNext(pos);
			frame->SetView(view);
		}
	}
#endif

	virtual bool OnButtonDown(UINT nFlags, gm::PointI point, int iButton, bool bDblClk, CHTMFrameNode** pFrame);
	virtual void OnMouseMove(UINT nFlags, gm::PointI point);
	virtual void OnButtonUp(UINT nFlags, gm::PointI point, int iButton);

//	virtual void OnPaint(HDC hDC);
	virtual void Draw(Web::CHTMRenderContext* pC);

#if 0
	virtual void PositionFrames(HWND hWndParent);
#endif

	virtual void DistributeBlockChildren(Web::CHTMFlowBlockContext* pC, double oparentwidth);

#if 0
	virtual BOOL HasDistributableChildren()
	{
		return FALSE;
	}
#endif

//	virtual void PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC);

//	HTMLFrameSetElement* m_pElement;

	inline HTMLFrameSetElement* GetElement()
	{
		return (HTMLFrameSetElement*)m_pElement;
	}

protected:

	friend class HTMLFrameSetElement;

	vector<PElementBase*> m_frames;	// renderable children (all block-level elements)

	int m_ncols;
	int m_nrows;
	bool m_frameborder;
	int m_framespacing;
	vector<double, __gc_allocator> m_colWidth;
	vector<double, __gc_allocator> m_rowHeight;

	int m_dragging;
	gm::PointD m_oldpt;
};

}	// Web
}

#endif // __Web_PHTMLFrameSetElement_h__
