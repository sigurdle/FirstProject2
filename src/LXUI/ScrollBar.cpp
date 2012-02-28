#include "stdafx.h"
#include "LXUI2.h"
#include "SolidColorBrush.h"
#include "ScrollBar.h"
#include "Track.h"

#include "Polyline.h"	// TODO remove

namespace System
{
namespace UI
{

ArrowButton::ArrowButton(long dir)
{
//	SetClipMode(false);

	m_dir = dir;

	set_Width(16);
	set_Height(16);

	Border* pBorder = new Border(new Thickness(1));
	pBorder->set_Background(new SolidColorBrush(Color::FromRgb(80, 114, 158)));
//	pBorder->set_Background(new SolidColorBrush(Color(255, 0, 0)));

	Shapes::Polyline* p = new Shapes::Polyline;
	PointCollection* points = new PointCollection;

	if (m_dir == 0)	// Left
	{
		points->Add(Point(14, 14));
		points->Add(Point(0, 7));
		points->Add(Point(14, 0));
	}
	else if (m_dir == 1)	// Right
	{
		points->Add(Point(0, 0));
		points->Add(Point(14, 7));
		points->Add(Point(0, 14));
	}
	else if (m_dir == 2)	// Up
	{
		points->Add(Point(0, 14));
		points->Add(Point(7, 0));
		points->Add(Point(14, 14));
	}
	else if (m_dir == 3)	// Down
	{
		points->Add(Point(14, 0));
		points->Add(Point(7, 14));
		points->Add(Point(0, 0));
	}
	else
		ASSERT(0);

	p->set_Points(points);
	pBorder->set_Child(p);

	set_VisualTree(pBorder);
}

#if 0
void ArrowButton::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
		//	MessageBeep(-1);
		//	OnLButtonDown(dynamic_cast<MouseEvent*>(evt));
		//	evt->stopPropagation();
		}
		else if (type == MouseEvent::mouseup)
		{
		//	OnLButtonUp(dynamic_cast<MouseEvent*>(evt));
		//	evt->stopPropagation();
		}
	}
}
#endif

//#include "../Color_Conversion.h"

//#include "UITheme.h"

//void Draw3dRect(LDraw::Graphics* pGraphics, CRect& rect, LDraw::Color clrTopLeft, LDraw::Color clrBottomRight);
void Draw3dRect(Graphics* pGraphics, float x, float y, float width, float height, LDraw::Color clrTopLeft, LDraw::Color clrBottomRight);

void Draw3dRect(Graphics* pGraphics, float x, float y, float width, float height, LDraw::Color clrTopLeft, LDraw::Color clrBottomRight)
{
	LDraw::Color clr0 = clrTopLeft;
	LDraw::Color clr1 = clrBottomRight;

	LDraw::SolidBrush* pBrush0 = new LDraw::SolidBrush(clr0);
	LDraw::SolidBrush* pBrush1 = new LDraw::SolidBrush(clr1);

//	Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
//		lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
	pGraphics->FillRectangle(pBrush0, x, y, 1, height);
	pGraphics->FillRectangle(pBrush0, x, y, width, 1);
	pGraphics->FillRectangle(pBrush1, x, y+height-1, width, 1);
	pGraphics->FillRectangle(pBrush1, x+width-1, y, 1, height);
}

void Draw3dRect(Graphics* pGraphics, const LDraw::RectD& rect, LDraw::Color clrTopLeft, LDraw::Color clrBottomRight)
{
	Draw3dRect(pGraphics, rect.X, rect.Y, rect.Width, rect.Height, clrTopLeft, clrBottomRight);
}


/*
#if _WINDOWS
//#pragma comment(lib, "uxtheme.lib")

typedef HTHEME  (STDAPICALLTYPE *fOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
typedef HRESULT (STDAPICALLTYPE *fCloseThemeData)(HTHEME hTheme);
typedef HRESULT (STDAPICALLTYPE *fDrawThemeBackground)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, OPTIONAL const RECT *pClipRect);

fOpenThemeData uxOpenThemeData;
fCloseThemeData uxCloseThemeData;
fDrawThemeBackground uxDrawThemeBackground;

extern fOpenThemeData uxOpenThemeData;
extern fCloseThemeData uxCloseThemeData;
extern fDrawThemeBackground uxDrawThemeBackground;
#endif
*/

/*
void ArrowButton::OnRender3(Graphics* pGraphics)
{
	if (m_dir == 0)	// left
	{
	}
}
*/

DependencyProperty* ScrollBar::s_OrientationProperty = RegisterProperty(WSTR("Orientation"), typeid(Orientation), typeid(ScrollBar), IntObject::GetObject(Orientation_Horizontal), PropertyMetaData(None));
DependencyProperty* ScrollBar::s_ViewportSizeProperty = RegisterProperty(WSTR("ViewportSize"), typeid(double), typeid(ScrollBar), DoubleObject::GetObject(0.0), PropertyMetaData(AffectsArrange));

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ScrollBarStyle;

ScrollBar::ScrollBar()
{
	if (ScrollBarStyle == NULL)
	{
		ScrollBarStyle = dynamic_cast<Style*>(FindResource(GetType()));

		/*
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ScrollBarStyle.lxui");
		document->load(filename);

		Type* returnType;
		ScrollBarStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
		*/
	}

	set_Style(ScrollBarStyle);
/*
	ApplyStyle(get_Style(), this);
	//	UpdatedVisualTree();	// ??
	InitScript();
	*/
}

ScrollBar::ScrollBar(Orientation orientation)
{
	if (ScrollBarStyle == NULL)
	{
		ScrollBarStyle = dynamic_cast<Style*>(FindResource(GetType()));

		/*
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ScrollBarStyle.lxui");
		document->load(filename);

		Type* returnType;
		ScrollBarStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
		*/
	}

	set_Style(ScrollBarStyle);

	/*
	ApplyStyle(get_Style(), this);
	//	UpdatedVisualTree();	// ??
	InitScript();
*/
	set_Orientation(orientation);

//	SetClipMode(false);

#if 0
	m_dir = dir;

	DockPanel* dockPanel = new DockPanel;

	m_up = new ArrowButton((m_dir<<1)+0);
	m_down = new ArrowButton((m_dir<<1)+1);

	ASSERT(0);

	if (m_dir == 0)
		m_slider = new HorizontalSlider;
	else
		m_slider = new VerticalSlider;

	if (m_dir == 0)
	{
		DockPanel::SetDock(m_up, DockPanel::Left);
		dockPanel->AddRChild(m_up);

		DockPanel::SetDock(m_down, DockPanel::Right);
		dockPanel->AddRChild(m_down);
	}
	else
	{
		DockPanel::SetDock(m_up, DockPanel::Top);
		dockPanel->AddRChild(m_up);

		DockPanel::SetDock(m_down, DockPanel::Bottom);
		dockPanel->AddRChild(m_down);
	}

	DockPanel::SetDock(m_slider, DockPanel::Fill);
	dockPanel->AddRChild(m_slider);
	set_VisualTree(dockPanel);
#endif
}

Orientation ScrollBar::get_Orientation()
{
	return (Orientation)static_cast<IntObject*>(GetValue(get_OrientationProperty()))->GetValue();
}

void ScrollBar::set_Orientation(Orientation orientation)
{
	SetValue(get_OrientationProperty(), IntObject::GetObject(orientation));
}

double ScrollBar::get_ViewportSize()
{
	return static_cast<DoubleObject*>(GetValue(get_ViewportSizeProperty()))->GetValue();
}

void ScrollBar::set_ViewportSize(double viewportSize)
{
	SetValue(get_ViewportSizeProperty(), DoubleObject::GetObject(viewportSize));
}

#if 0
void ScrollBar::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"posChange")
		{
			evt->stopPropagation();

			SliderEvent* scrollEvt = new SliderEvent;
			scrollEvt->InitEvent(WSTR("scroll"), true, true);
			scrollEvt->m_pos = static_cast<SliderEvent*>(evt)->m_pos;
			bool doDefault = dispatchEvent(scrollEvt);
			if (!doDefault)
				evt->preventDefault();
		}
	}
}
#endif

}	// UI
}
