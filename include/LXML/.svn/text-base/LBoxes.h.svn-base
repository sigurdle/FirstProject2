#ifndef __LBoxes_h__
#define __LBoxes_h__

namespace System
{
namespace Web
{

enum
{
	BackgroundRepeat_repeat = 0,
	BackgroundRepeat_repeat_x,
	BackgroundRepeat_repeat_y,
	BackgroundRepeat_no_repeat,
};

enum
{
	BorderStyle_none = 0,
	BorderStyle_hidden,			// CSS3
	BorderStyle_dotted,
	BorderStyle_dashed,
	BorderStyle_solid,
	BorderStyle_double,
	BorderStyle_dot_dash,		// CSS3
	BorderStyle_dot_dot_dash,	// CSS3
	BorderStyle_wave,				// CSS3
	BorderStyle_groove,
	BorderStyle_ridge,
	BorderStyle_inset,
	BorderStyle_outset,
};

//#include "../LXUI/WindowBase.h"

//class CHTMBlockBox;

//namespace UI
//{

	// TODO
class WEBEXT ControlHost : public Object//VisualContentSource
{
public:
	virtual void SetCapture(Gui::UIElement* p);
	virtual void ReleaseCapture(Gui::UIElement* p);
//	virtual void InvalidateChildRect(const LDraw::RectD& rect, LDraw::Matrix3f* transform);

	Gui::UIElement* GetVisualTree()
	{
		ASSERT(0);
		return NULL;
	}

	gm::PointD TransformPointToClient(gm::PointD point);

public:

	PElementBase* m_pElement;
	CHTMLWindow* m_pWindow;
};

//}

class CHTMElementBox;

/*
class WEBEXT ILBoxHandler
{
public:

// hm...
	DWORD m_computedBackgroundRepeat : 2;

	//left,top,right,bottom
	uint8 m_computedBorderStyle[4];
	CRGBColor m_computedBorderColor[4];

	uint8 m_computedOutlineStyle;
	double m_computedOutlineWidth;

	virtual void Draw(CHTMRenderContext* pC) = 0;
	virtual void EndDraw(CHTMRenderContext* pC) = 0;
	virtual void OnRemoveBox(CHTMElementBox* pBox) = 0;
//	virtual void OnButtonDown(LDraw::PointD point, int nhit);

//	void DrawScrollBars(CHTMRenderContext* pC);

// TODO, manage to not have these here
	CHTMBlockBox*	m_pBox;

	double m_computedLeft;
	double m_computedTop;
	DWORD	m_computedPosition : 2,
			m_computedFloat : 4,
			m_computedClear : 4,
			m_computedVisibility : 2,
			m_computedOverflowX : 2,
			m_computedOverflowY : 2;

	double m_computedBorderRadius[4][2];
};
*/

}	// w3c
}	// System

#endif	// __LBoxes_h__
