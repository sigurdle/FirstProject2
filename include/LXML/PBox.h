#ifndef Web_PBox_h
#define Web_PBox_h

#include "PNode.h"	// TODO remove

namespace System
{
namespace Web
{

class WEBEXT CHTMParentBox;
class WEBEXT CHTMRenderContext;

class WEBEXT CHTMLineBox;

class CCSSStackingContext;

enum
{
	boxTypeUnknown = 0,
	boxTypeBlock = -10,
	boxTypeInline = -11,
};

class WEBEXT CHTMRenderContext// : public CHTMContext
{
public:
	CTOR CHTMRenderContext();

//	UI::Graphics* m_pGraphics;	// TODO 
	Gui::RenderContext* m_renderContext;

///
	CHTMLWindow* m_pWindow;
	Range* m_range;
	Graphics::Bitmap* m_hBrokenImage;	// TODO Image, not bitmap

	bool m_bInSelection;

	gm::RectF m_clip;
//	LDraw::PointF m_outerPos;
	gm::Matrix3f* m_matrixToView;
};

class WEBEXT CHTMBoxItem : public Object
{
public:
	CTOR CHTMBoxItem();

	ULONG AddRef();
	ULONG Release();

	CCSSStackingContext* m_pStackingContext;	// The stacking context that this box belongs to

	ULONG m_refcount;

	int m_type;
	gm::RectF m_outerRect;
	CHTMParentBox* m_parentBox;	// layout parent
	//CHTMParentBox* m_renderParentBox;

	void SetParentNULL()
	{
		m_parentBox = NULL;
	}

	virtual double AdjustBottom()
	{
		return m_outerRect.Height;	// defaults to this ??
	}

	gm::RectF GetAbsOuterRect();

	virtual void Draw(CHTMRenderContext* pC) = 0;

	virtual bool getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset) = 0;

	virtual int HitTestElementBox(double x, double y, PElementBase** ppElement)
	{
		return 0;
	}

	/*
	virtual void OnButtonDown(LDraw::PointD point, int nhit)
	{
	}
	*/

// public methods
	virtual void Destroy();

protected:

	virtual ~CHTMBoxItem();
};

}	// Web
}

#endif // __PBox_h__
