#include "stdafx.h"
#include "LXUI2.h"
#include "Track.h"
#include "Thumb.h"
#include "RepeatButton.h"

#include <cfloat>

namespace System
{
namespace UI
{

DependencyProperty* Track::s_OrientationProperty = RegisterProperty(WSTR("Orientation"), typeid(Orientation), typeid(Track), IntObject::GetObject(Orientation_Horizontal), PropertyMetaData(AffectsArrange));
DependencyProperty* Track::s_MinimumProperty = RegisterProperty(WSTR("Minimum"), typeid(double), typeid(Track), DoubleObject::GetObject(0.0), PropertyMetaData(AffectsArrange));
DependencyProperty* Track::s_MaximumProperty = RegisterProperty(WSTR("Maximum"), typeid(double), typeid(Track), DoubleObject::GetObject(1.0), PropertyMetaData(AffectsArrange));
DependencyProperty* Track::s_ValueProperty = RegisterProperty(WSTR("Value"), typeid(double), typeid(Track), DoubleObject::GetObject(0.0), PropertyMetaData(AffectsArrange));
DependencyProperty* Track::s_ViewportSizeProperty = RegisterProperty(WSTR("ViewportSize"), typeid(double), typeid(Track), DoubleObject::get_NaN(), PropertyMetaData(AffectsArrange));

/*

 Slider::Slider(long dir)
{
//	SetClipMode(false);

	m_dir = dir;
	m_pos = 0;
	m_min = 0;
	m_visible = 1;
	m_max = 1;

	m_dragging = 0;

	m_thumb = new Thumb;
	AddRChild(m_thumb);

	set_Background(new SolidColorBrush(new Color(110, 144, 188)));
}

*/

static bool bInited;

Track::Track()
{
	if (!bInited)
	{
		bInited = true;
		EventManager::RegisterClassHandler(typeid(Track), Thumb::get_DragDeltaEvent(), mem_fun(&Track::OnDragDelta));
	}

	m_thumb = NULL;
	m_increaseRepeatButton = NULL;
	m_decreaseRepeatButton = NULL;
}

Thumb* Track::get_Thumb()
{
	return m_thumb;
}

void Track::set_Thumb(Thumb* thumb)
{
	m_thumb = thumb;
	/*
	m_thumb->SetRParent(this);
	m_thumb->SetOwnerWindow(GetOwnerWindow());
	*/
	AddVisualChild(m_thumb);
}

RepeatButton* Track::get_IncreaseRepeatButton()
{
	return m_increaseRepeatButton;
}

void Track::set_IncreaseRepeatButton(RepeatButton* button)
{
	m_increaseRepeatButton = button;
	AddVisualChild(m_increaseRepeatButton);
	/*
	m_increaseRepeatButton->SetRParent(this);
	m_increaseRepeatButton->SetOwnerWindow(GetOwnerWindow());
	*/
}

RepeatButton* Track::get_DecreaseRepeatButton()
{
	return m_decreaseRepeatButton;
}

void Track::set_DecreaseRepeatButton(RepeatButton* button)
{
	m_decreaseRepeatButton = button;
	AddVisualChild(m_decreaseRepeatButton);
//	m_decreaseRepeatButton->SetRParent(this);
//	m_decreaseRepeatButton->SetOwnerWindow(GetOwnerWindow());
}

Orientation Track::get_Orientation()
{
	return (Orientation)static_cast<IntObject*>(GetValue(get_OrientationProperty()))->GetValue();
}

void Track::set_Orientation(Orientation orientation)
{
	SetValue(get_OrientationProperty(), IntObject::GetObject(orientation));
}

double Track::get_Value()
{
	return static_cast<DoubleObject*>(GetValue(get_ValueProperty()))->GetValue();
}

void Track::set_Value(double value)
{
	SetValue(get_ValueProperty(), DoubleObject::GetObject(value));
}

double Track::get_Minimum()
{
	return static_cast<DoubleObject*>(GetValue(get_MinimumProperty()))->GetValue();
}

void Track::set_Minimum(double minimum)
{
	SetValue(get_MinimumProperty(), DoubleObject::GetObject(minimum));
}

double Track::get_Maximum()
{
	return static_cast<DoubleObject*>(GetValue(get_MaximumProperty()))->GetValue();
}

void Track::set_Maximum(double maximum)
{
	SetValue(get_MaximumProperty(), DoubleObject::GetObject(maximum));
}

double Track::get_ViewportSize()
{
	return static_cast<DoubleObject*>(GetValue(get_ViewportSizeProperty()))->GetValue();
}

void Track::set_ViewportSize(double viewportSize)
{
	SetValue(get_ViewportSizeProperty(), DoubleObject::GetObject(viewportSize));
}

void Track::OnPropertyChanged(DependencyPropertyChangedEventArgs args)
{
	DependencyProperty* dp = args.get_Property();

	if (dp == get_MinimumProperty() ||
		dp == get_MaximumProperty() ||
		dp == get_ViewportSizeProperty())
	{
		/*
		double viewportSize = get_ViewportSize();
		double totalrange = get_Maximum()-get_Minimum();
		double abspos = get_Value() - get_Minimum();
		if (_isnan(viewportSize))
		{
			// TODO
		}
		else
		{
			if (abspos+viewportSize > totalrange)
			{
				abspos = totalrange - viewportSize;
				set_Value(abspos);
			}
		}
		*/
	}

	FrameworkElement::OnPropertyChanged(args);
}

void Track::SetInfo(double minv, double maxv, double visible)
{
	set_Minimum(minv);
	set_Maximum(maxv);
	set_ViewportSize(visible);
#if 0

	m_min = minv;
	m_max = maxv;
	m_visible = visible;
	if (m_visible < 0) m_visible = 0;

	double pos = m_pos;

	if (pos > m_max-(m_visible/*-1*/))
		pos = m_max-(m_visible/*-1*/);

	if (pos < m_min)
		pos = m_min;

	if (pos != m_pos)
	{
	//	Fire_SetPos(SB_THUMBTRACK, pos);
		SliderEvent* evt = new SliderEvent;
		evt->InitEvent(WSTR("posChange"), true, true);
		evt->m_pos = pos;
		bool doDefault = dispatchEvent(evt);
		if (doDefault)
		{
			set_pos(pos);
		//	Invalidate();
		}
	}
#endif

	//SetIt();
	//m_thumb->InvalidateMeasure();

#if 0
	Invalidate();	// ??
#endif
//#else
	//if (m_dir == 0)

#if 0
	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}
#endif
}

unsigned int Track::get_VisualChildrenCount()
{
	if (m_thumb != NULL && m_increaseRepeatButton != NULL && m_decreaseRepeatButton)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

Visual* Track::GetVisualChild(unsigned int index)
{
	if (m_thumb != NULL && m_increaseRepeatButton != NULL && m_decreaseRepeatButton)
	{
		switch (index)
		{
		case 0:	return m_decreaseRepeatButton;
		case 1:	return m_thumb;
		case 2:	return m_increaseRepeatButton;
		default:
			THROW(std::exception("Index out of range"));
		}
	}
	else
	{
		THROW(std::exception("Index out of range"));
	}
}

//virtual
LDraw::SizeD Track::MeasureOverride(LDraw::SizeD availSize)
{
//	SetIt();
	/*
	if (m_thumb->get_Width())
	{
		MessageBeep(-1);
	}
	*/

	m_thumb->Measure(LDraw::SizeD(0,0));
//	m_thumb->Measure(availSize);
	return m_thumb->get_DesiredSize();
}

// virtual
LDraw::SizeD Track::ArrangeOverride(LDraw::SizeD finalSize)
{
	/*
	int cx = rcPos.right-rcPos.left;
	int cy = rcPos.bottom-rcPos.top;

	int l = 0;//m_rcPos.left;
	int t = 0;//m_rcPos.top;
	int r = cx;
	int b = cy;

	if (m_dir == 0)
	{
//		m_leftR.SetRect(l, t, l+16, b);
//		m_rightR.SetRect(r-16, 0, r, b);
		m_slidR.SetRect(l, t, r, b);
	}
	else
	{
//		m_leftR.SetRect(l, t, r, t+16);
//		m_rightR.SetRect(l, b-16, r, b);
		m_slidR = LDraw::SizeD(l, t, r, b);
	}
	*/
	m_slidR = LDraw::RectD(0, 0, finalSize.Width, finalSize.Height);

	SetIt();

//	m_knobR.Width = MAX(m_knobR.Width, m_thumb->get_DesiredSize().Width);
//	m_knobR.Height = MAX(m_knobR.Height, m_thumb->get_DesiredSize().Height);

	//double start = 0;
	double viewportSize = get_ViewportSize();

	if (get_Orientation() == Orientation_Horizontal)
	{
		/*
		if (_isnan(viewportSize))
			start = m_knobR.Width / 2;
		else
			start = 0;
			*/

		m_decreaseRepeatButton->Arrange(LDraw::RectD(0, 0, m_knobR.X, finalSize.Height));
		m_thumb->Arrange(m_knobR);
		m_increaseRepeatButton->Arrange(LDraw::RectD(m_knobR.X+m_knobR.Width, 0, finalSize.Width-(m_knobR.X+m_knobR.Width), finalSize.Height));
	}
	else
	{
		/*
		if (_isnan(viewportSize))
			start = m_knobR.Height / 2;
		else
			start = 0;
			*/

		m_decreaseRepeatButton->Arrange(LDraw::RectD(0, 0, finalSize.Width, m_knobR.Y));
		m_thumb->Arrange(m_knobR);
		m_increaseRepeatButton->Arrange(LDraw::RectD(0, m_knobR.Y+m_knobR.Height, finalSize.Width, finalSize.Height-(m_knobR.Y+m_knobR.Height)));
	}

	return finalSize;
}

void Track::OnDragDelta(DragDeltaEventArgs* args)
{
	Orientation orientation = get_Orientation();

	double delta;
	if (orientation == Orientation_Horizontal)
		delta = args->m_HorizontalChange;
	else
		delta = args->m_VerticalChange;

	/*
	LDraw::PointD pt;
	pt.X = point.X - m_slidR.X;
	pt.Y = point.Y - m_slidR.Y;
	*/

	double width = (orientation == Orientation_Horizontal)? m_slidR.Width: m_slidR.Height;
	double ksize = (orientation == Orientation_Horizontal)? m_knobR.Width: m_knobR.Height;

	double totalrange = get_Maximum() - get_Minimum();

	double minimum = get_Minimum();
	double maximum = get_Maximum();

	double thumbProportion = get_ViewportSize();

	if (_isnan(thumbProportion))
	{
		double pos;

		pos = (delta)*(totalrange) / (width-ksize);
		pos += get_Value();

		if (pos > maximum) pos = maximum;
		if (pos < minimum) pos = minimum;

		set_Value(pos);
	}
	else
	{
		if (thumbProportion > totalrange) thumbProportion = totalrange;

	//	double m_visible = thumbProportion;

	//	int totalrange = m_max - m_min+1;// - m_visible;
		//if (width > ksize)
		{
			double pos;
			
		//	if (get_Orientation() == Orientation_Horizontal)
			{
				pos = (delta)*(totalrange-get_ViewportSize()) / (width-ksize);
				pos += get_Value();
			}
			/*
			else
			{
				abspos = (pt.Y-m_ptoffset)*(totalrange-get_ViewportSize()) / (width-ksize);
			}
			*/

		//	TRACE("pos: %f\n", pos);

			//double pos = abspos;// + m_min;

			/*
			if (pos < 0) pos = 0;
			else if (pos > 1) pos = 1;
			*/

		//	m_min = 0;
		//	m_max = 1;

			double viewportsize = get_ViewportSize();

			if (pos > maximum-viewportsize) pos = maximum-viewportsize;
			if (pos < minimum) pos = minimum;

			set_Value(pos);
		}
#if 0
		SliderEvent* evt = new SliderEvent;
		evt->InitEvent(WSTR("posChange"), true, true);
		evt->m_pos = pos;
		bool doDefault = dispatchEvent(evt);
		if (doDefault)
		{
			set_Value(pos);
		//	Invalidate();
		}
#endif
	}
}

#if 0
void Track::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*type == L"DragDelta")
		{
			DragDeltaEventArgs* dragdelta = static_cast<DragDeltaEvent*>(evt);

			Orientation orientation = get_Orientation();

			double delta;
			if (orientation == Orientation_Horizontal)
				delta = dragdelta->m_HorizontalChange;
			else
				delta = dragdelta->m_VerticalChange;

			/*
			LDraw::PointD pt;
			pt.X = point.X - m_slidR.X;
			pt.Y = point.Y - m_slidR.Y;
			*/

			double width = (orientation == Orientation_Horizontal)? m_slidR.Width: m_slidR.Height;
			double ksize = (orientation == Orientation_Horizontal)? m_knobR.Width: m_knobR.Height;

			double totalrange = get_Maximum() - get_Minimum();

			double thumbProportion = get_ViewportSize();
			if (thumbProportion > totalrange) thumbProportion = totalrange;

		//	double m_visible = thumbProportion;

		//	int totalrange = m_max - m_min+1;// - m_visible;
			//if (width > ksize)
			{
				double pos;
				
			//	if (get_Orientation() == Orientation_Horizontal)
				{
					pos = (delta)*(totalrange-get_ViewportSize()) / (width-ksize);
					pos += get_Value();
				}
				/*
				else
				{
					abspos = (pt.Y-m_ptoffset)*(totalrange-get_ViewportSize()) / (width-ksize);
				}
				*/

				TRACE("pos: %f\n", pos);

				//double pos = abspos;// + m_min;
	
				/*
				if (pos < 0) pos = 0;
				else if (pos > 1) pos = 1;
				*/

			//	m_min = 0;
			//	m_max = 1;


				double minimum = get_Minimum();
				double maximum = get_Maximum();
				double viewportsize = get_ViewportSize();

				if (pos > maximum-viewportsize) pos = maximum-viewportsize;
				if (pos < minimum) pos = minimum;

				SliderEvent* evt = new SliderEvent;
				evt->InitEvent(WSTR("posChange"), true, true);
				evt->m_pos = pos;
				bool doDefault = dispatchEvent(evt);
				if (doDefault)
				{
					set_pos(pos);
				//	Invalidate();
				}
			}
		}
		/*
		if (type == MouseEvent::mousedown)
		{
			OnLButtonDown(static_cast<MouseEvent*>(evt));
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mouseup)
		{
			OnLButtonUp(static_cast<MouseEvent*>(evt));
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mousemove)
		{
			OnMouseMove(static_cast<MouseEvent*>(evt));
			evt->stopPropagation();
		}
		*/
	}
}
#endif

void Track::OnRender(Graphics* pGraphics)
{
//	Control::OnRender(pGraphics);
#if 0
//	CRect rc(0, 0, m_computedSize.Width, m_computedSize.Height);
	/*
	if (rc.left != m_rcPos.left || rc.top != m_rcPos.top || rc.right != m_rcPos.right || rc.bottom != m_rcPos.bottom)
	{
		::MessageBox(NULL, "scrollbar size diff!!", "", MB_OK);
	}
	*/

//	CRect client = rc;
	//GetClientRect(&client);

	/*
	BITMAPINFO	bmi = {0};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = client.Width();
	bmi.bmiHeader.biHeight = client.Height();
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	*/

#if 0//_WINDOWS
	COLORREF clr = GetSysColor(COLOR_MENU);
	DWORD hsv = rgb_to_hsv(clr);

	int h = GetRValue(hsv);
	int s = GetGValue(hsv);
	int v = GetBValue(hsv);

	COLORREF bgdarkdark = hsv_to_rgb(RGB(h, s, v*0.4));
	COLORREF bgdark = hsv_to_rgb(RGB(h, s, v*0.6));
	COLORREF bglight = hsv_to_rgb(RGB(h, s, v*0.8));

	COLORREF fgdark = hsv_to_rgb(RGB(h, s, v*0.8));
	COLORREF fglight = hsv_to_rgb(RGB(h, s, v));
#else
	LDraw::Color bgdarkdark(0, 0, 0);
#endif

	/*
	LPBYTE bits;
	HBITMAP hBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
	if (hBitmap)
	{
		HDC hDC = CreateCompatibleDC(NULL);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

		CDCHandle dc = hDC;
*/
#if 0
		if (m_hTheme)
		{
			int iPartId;
			int iStateId;

		// left/up
			if (m_dir == 1)	// vertical
			{
				if (m_dragging == 2 && m_bIsInside)
					iStateId = ABS_UPPRESSED;
				else
					iStateId = ABS_UPNORMAL;
			}
			else
			{
				if (m_dragging == 2 && m_bIsInside)
					iStateId = ABS_LEFTPRESSED;
				else
					iStateId = ABS_LEFTNORMAL;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 SBP_ARROWBTN,
				 iStateId,
				 &m_leftR,
				 NULL);
		
		// right/down
			if (m_dir == 1)	// vertical
			{
				if (m_dragging == 3 && m_bIsInside)
					iStateId = ABS_DOWNPRESSED;
				else
					iStateId = ABS_DOWNNORMAL;
			}
			else
			{
				if (m_dragging == 3 && m_bIsInside)
					iStateId = ABS_RIGHTPRESSED;
				else
					iStateId = ABS_RIGHTNORMAL;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 SBP_ARROWBTN,
				 iStateId,
				 &m_rightR,
				 NULL);

			if (m_dir == 0)
			{
				CRect leftTR(m_leftR.right, m_knobR.top, m_knobR.left, m_knobR.bottom);
				CRect rightTR(m_knobR.right, m_knobR.top, m_rightR.left, m_knobR.bottom);

				iPartId = SBP_UPPERTRACKHORZ;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &leftTR,
				 NULL);

				iPartId = SBP_LOWERTRACKHORZ;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &rightTR,
				 NULL);
			}
			else
			{
				CRect leftTR(m_knobR.left, m_leftR.bottom, m_knobR.right, m_knobR.top);
				CRect rightTR(m_knobR.left, m_knobR.bottom, m_knobR.right, m_rightR.top);

				iPartId = SBP_UPPERTRACKVERT;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &leftTR,
				 NULL);

				iPartId = SBP_LOWERTRACKVERT;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &rightTR,
				 NULL);
			}

		//
			if (m_dir == 0)
			{
				iPartId = SBP_THUMBBTNHORZ;
			}
			else
			{
				iPartId = SBP_THUMBBTNVERT;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 (m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &m_knobR,
				 NULL);

		//
			if (m_dir == 0)
			{
				iPartId = SBP_GRIPPERHORZ;
			}
			else
			{
				iPartId = SBP_GRIPPERVERT;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 0,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &m_knobR,
				 NULL);
		}
		else
#endif
		{
			if (false)
			{
#if 0
				if (m_dir == 0)
				{
					{
						Gdiplus::Graphics graphics(hDC);
						Gdiplus::Rect rect(m_slidR.left, m_slidR.top, m_slidR.Width(), m_slidR.Height());
						Gdiplus::LinearGradientBrush brush(rect, Gdiplus::Color(255, 230, 230, 230), Gdiplus::Color(255, 255, 255, 255), Gdiplus::LinearGradientModeVertical);
						graphics.FillRectangle(&brush, rect);
					}

					CRgn rgn;
					rgn.CreateRoundRectRgn(m_knobR.left, m_knobR.top, m_knobR.right, m_knobR.bottom, m_knobR.Height()/2, m_knobR.Height()/2);

				//	Gdiplus::GraphicsPath path;
				//	RoundRect(&path, m_knobR.left, m_knobR.top, m_knobR.Width(), m_knobR.Height(), m_knobR.Height()/2, m_knobR.Height()/2);

					SelectClipRgn(hDC, rgn);

					xThemeDrawBackground(hDC, &m_knobR);
					xThemeDrawEdge(hDC, &m_knobR, xTheme_EDGE_RECT, 0);
				}
				else
				{
					{
						Gdiplus::Graphics graphics(hDC);
						Gdiplus::Rect rect(m_slidR.left, m_slidR.top, m_slidR.Width(), m_slidR.Height());
						Gdiplus::LinearGradientBrush brush(rect, Gdiplus::Color(255, 230, 230, 230), Gdiplus::Color(255, 255, 255, 255), Gdiplus::LinearGradientModeHorizontal);
						graphics.FillRectangle(&brush, rect);
					}

				//	Gdiplus::GraphicsPath path;
				//	RoundRect(&path, m_knobR.left, m_knobR.top, m_knobR.Width(), m_knobR.Height(), m_knobR.Width()/2, m_knobR.Width()/2);
				//	graphics.SetClip(&path);

					CRgn rgn;
					rgn.CreateRoundRectRgn(m_knobR.left, m_knobR.top, m_knobR.right, m_knobR.bottom, m_knobR.Width()/2, m_knobR.Width()/2);

					SelectClipRgn(hDC, rgn);

					xThemeDrawBackground(hDC, &m_knobR);
					xThemeDrawEdge(hDC, &m_knobR, xTheme_EDGE_RECT, 0);
				}
#endif
			}
			else	// old-style scrollbar
			{
			//	dc.FillSolidRect(0, 0, client.Width(), client.Height(), RGB(255, 0, 0));
				pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(200, 200, 200)), 0, 0, m_computedSize.Width, m_computedSize.Height);

				/*
				if (m_dir == 0)
				{
					DrawVertGradient(hDC, m_leftR, fglight, fgdark);
					DrawVertGradient(hDC, m_rightR, fglight, fgdark);
				}
				else
				{
					DrawHorzGradient(hDC, m_leftR, fglight, fgdark);
					DrawHorzGradient(hDC, m_rightR, fglight, fgdark);
				}
				*/

				/*
				if (m_dragging == 2 && m_bIsInside)
				{
					Draw3dRect(pGraphics, m_leftR.left, m_leftR.top, m_leftR.Width(), m_leftR.Height(), bgdarkdark, LDraw::Color(255, 255, 255));
				}
				else
				{
					Draw3dRect(pGraphics, m_leftR.left, m_leftR.top, m_leftR.Width(), m_leftR.Height(), LDraw::Color(255, 255, 255), bgdarkdark);
					Draw3dRect(pGraphics, m_leftR.left+1, m_leftR.top+1, m_leftR.Width()-2, m_leftR.Height()-2, LDraw::Color(200, 200, 200), LDraw::Color(60, 60, 60));
				}

				if (m_dragging == 3 && m_bIsInside)
				{
					Draw3dRect(pGraphics, m_rightR.left, m_rightR.top, m_rightR.Width(), m_rightR.Height(), bgdarkdark, LDraw::Color(255, 255, 255));
				}
				else
				{
					Draw3dRect(pGraphics, m_rightR.left, m_rightR.top, m_rightR.Width(), m_rightR.Height(), LDraw::Color(255, 255, 255), bgdarkdark);
					Draw3dRect(pGraphics, m_rightR.left+1, m_rightR.top+1, m_rightR.Width()-2, m_rightR.Height()-2, LDraw::Color(200, 200, 200), LDraw::Color(60, 60, 60));
				}
				*/
				
				/*
				if (m_dir == 0)
				{
					DrawVertGradient(hDC, m_slidR, bgdark, bglight);
				}
				else
				{
					DrawHorzGradient(hDC, m_slidR, bgdark, bglight);
				}
				*/
				{
				//	CBrush brush = dc.GetHalftoneBrush();
				//	dc.SetTextColor(GetSysColor(COLOR_SCROLLBAR));
				//	dc.SetBkColor(RGB(255, 255, 255));
				//	FillRect(hDC, &m_slidR, brush);
					pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(220, 220, 220)), m_slidR.X, m_slidR.Y, m_slidR.Width, m_slidR.Height);
				}

			//	Draw3DRect(hDC, m_slidR.left, m_slidR.top, m_slidR.Width(), m_slidR.Height(), RGB(255, 255, 255), bgdark/*RGB(0, 0, 0)*/);
				
				/*
				HBRUSH	blackBrush = CreateSolidBrush(bgdarkdark);
				HBRUSH	hOldBrush = (HBRUSH)SelectObject(hDC, blackBrush);
				HPEN		blackPen = CreatePen(PS_SOLID, 1, bgdark);
				HPEN		hOldPen = (HPEN)SelectObject(hDC, blackPen);
				*/

				__release<LDraw::SolidBrush> blackBrush = new LDraw::SolidBrush(LDraw::Color(0, 0, 0));
				
				if (m_dir == 0)
				{
				//	DrawFrameControl(hDC, &m_leftR, DFC_SCROLL, DFCS_SCROLLLEFT | ((m_dragging == 2 && m_bIsInside)?DFCS_PUSHED:0));
				//	DrawFrameControl(hDC, &m_rightR, DFC_SCROLL, DFCS_SCROLLRIGHT | ((m_dragging == 3 && m_bIsInside)?DFCS_PUSHED:0));
					/*
					int o;
					
					o = 0;
					if (m_dragging == 3 && m_bIsInside) o++;

					LDraw::Point rpt[] =
					{
						LDraw::Point(m_rightR.left+4+o, m_rightR.top+4+o),
						LDraw::Point(m_rightR.left+4+o, m_rightR.bottom-4+o),
						LDraw::Point(m_rightR.right-4+o, m_rightR.Height()/2+o),
					};

					o = 0;
					if (m_dragging == 2 && m_bIsInside) o++;
					
					LDraw::Point lpt[] =
					{
						LDraw::Point(m_leftR.right-4+o, m_leftR.top+4+o),
						LDraw::Point(m_leftR.right-4+o, m_leftR.bottom-4+o),
						LDraw::Point(m_leftR.left+4+o, m_leftR.Height()/2+o),
					};
					
					pGraphics->FillPolygon(&blackBrush, lpt, 3);
					pGraphics->FillPolygon(&blackBrush, rpt, 3);
					*/
				}
				else
				{
				//	DrawFrameControl(hDC, &m_leftR, DFC_SCROLL, DFCS_SCROLLUP | ((m_dragging == 2 && m_bIsInside)?DFCS_PUSHED:0));
				//	DrawFrameControl(hDC, &m_rightR, DFC_SCROLL, DFCS_SCROLLDOWN | ((m_dragging == 3 && m_bIsInside)?DFCS_PUSHED:0));

					/*
					int o;
					
					o = 0;
					if (m_dragging == 3 && m_bIsInside) o++;

					LDraw::Point rpt[] =
					{
						LDraw::Point(m_rightR.left+4+o, m_rightR.top+4+o),
						LDraw::Point(m_rightR.right-4+o, m_rightR.top+4+o),
						LDraw::Point(m_rightR.left+m_rightR.Width()/2+o, m_rightR.bottom-4+o),
					};
					
					o = 0;
					if (m_dragging == 2 && m_bIsInside) o++;
					
					LDraw::Point lpt[] =
					{
						LDraw::Point(m_leftR.left+4+o, m_leftR.bottom-4+o),
						LDraw::Point(m_leftR.right-4+o, m_leftR.bottom-4+o),
						LDraw::Point(m_leftR.left+m_leftR.Width()/2+o, m_leftR.top+4+o),
					};
					
					pGraphics->FillPolygon(&blackBrush, lpt, 3);
					pGraphics->FillPolygon(&blackBrush, rpt, 3);
					*/
				}

				/*
				SelectObject(hDC, hOldBrush);
				SelectObject(hDC, hOldPen);
				*/
				
			// Draw the slider knob
				{
					SetIt();	// TODO, remove
					/*
					int kpos = 0;
					if (m_dir == 0)	// horizontal
					{
						int ksize = thumbProportion * m_slidR.Width();

						m_knobR.SetRect(
							m_slidR.left + kpos, m_slidR.top,
							m_slidR.left + kpos + ksize, m_slidR.bottom);
					}
					else	// vertical
					{
						int ksize = thumbProportion * m_slidR.Height();

						m_knobR.SetRect(
							m_slidR.left, m_slidR.top+kpos,
							m_slidR.right, m_slidR.top + kpos + ksize);
					}
					*/
					LDraw::RectD rc = m_knobR;

					Draw3dRect(pGraphics, rc, LDraw::Color(190, 190, 190)/*GetSysColor(COLOR_SCROLLBAR)*/, bgdarkdark);
					rc.Inflate(-1, -1);

					Draw3dRect(pGraphics, rc, LDraw::Color(255, 255, 255), bgdarkdark);
					rc.Inflate(-1, -1);

//					dc.FillSolidRect(&rc, GetSysColor(COLOR_SCROLLBAR));

					pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(200, 200, 200))/*::FromCOLORREF(GetSysColor(COLOR_SCROLLBAR))*/, rc.X, rc.Y, rc.Width, rc.Height);
				}
			}
		}
#endif
}

void Track::SetIt()
{
//	double thumbProportion = m_ThumbProportion;
//	if (thumbProportion > 1) thumbProportion = 1;

	double width = (get_Orientation() == Orientation_Horizontal)? m_slidR.Width: m_slidR.Height;

	double viewportSize = get_ViewportSize();

	/*
	double kpos = m_pos * width;
*/	double totalrange = get_Maximum()-get_Minimum();
//	int minsize = 10;

	double abspos = get_Value() - get_Minimum();

	double kpos;
	double ksize;

	/*
	if (get_Orientation() == Orientation_Horizontal)	// horizontal
	{
		double start;

		if (_isnan(viewportSize))
			start = ksize / 2;
		else
			start = 0;
			*/

	if (_isnan(viewportSize))
	{
		if (get_Orientation() == Orientation_Horizontal)
			ksize = m_thumb->get_DesiredSize().Width;
		else
			ksize = m_thumb->get_DesiredSize().Height;

		kpos = (abspos * (width-ksize)) / (totalrange);
	}
	else
	{
		if (totalrange > viewportSize)
		{
			ksize = (width * viewportSize) / (totalrange);

		//	if (ksize < minsize) ksize = minsize;	// Don't allow smaller than this

		//	kpos = (abspos * width) / totalrange;
			kpos = (abspos * (width-ksize)) / (totalrange-viewportSize);

			if (ksize > width) ksize = width;
		}
		else
		{
			kpos = 0;
			ksize = width;
		}
	}

//	double ksize = m_visible * width / totalrange;//m_slidR.Width();

	if (get_Orientation() == Orientation_Horizontal)	// horizontal
	{
		m_knobR = LDraw::RectD(kpos, m_slidR.Y, ksize, m_slidR.Height);
		//if (m_knobR.X < 1) m_knobR.X = 1;
	}
	else	// vertical
	{
	//	int ksize = thumbProportion * m_slidR.Height();

		/*
		double start;

		if (_isnan(viewportSize))
			start = ksize / 2;
		else
			start = 0;
			*/

		m_knobR = LDraw::RectD(m_slidR.X, m_slidR.Y+kpos, m_slidR.Width, ksize);
	}

	/*
	if (m_dir == 0)	// horizontal
	{
		m_knobR.SetRect(
			m_slidR.left + kpos, m_slidR.top,
			m_slidR.left + kpos + ksize, m_slidR.bottom);
	}
	else	// vertical
	{
		m_knobR.SetRect(
			m_slidR.left, m_slidR.top+kpos,
			m_slidR.right, m_slidR.top + kpos + ksize);
	}
	*/

	//m_thumb->m_width = new Length(m_knobR.Width);
	//m_thumb->m_height = new Length(m_knobR.Height);
	//m_thumb->SetLayoutOffset(m_knobR.X, m_knobR.Y);
}

#if 0
long Track::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nID = wParam;

	//CIUIWnd* pParent = GetParent();

	if (m_dragging > 1)
	{
		if (m_bIsInside)
		{
			if (m_dragging == 2)
			{
				if (m_pos > m_min)
					;//Fire_SetPos(SB_LINELEFT, 0);//pParent->TOP()->OnScroll(SB_LINELEFT, 0, this);
			}
			else if (m_dragging == 3)
			{
				if (m_pos < m_max-m_visible)
					;//Fire_SetPos(SB_LINERIGHT, 0);//pParent->TOP()->OnScroll(SB_LINERIGHT, 0, this);
			}
		}
	}

	return 0;
}
#endif

#if 0
void Track::OnLButtonDown(MouseEvent* evt)
{
	/*
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;
	*/
//	MessageBeep(-1);

//	POINT point;
//	point.x = evt->get_ScreenX();
//	point.y = evt->get_ScreenY();
	LDraw::PointD point = ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());


#if 0
	if (m_leftR.PtInRect(point))	// Left arrow
	{
		m_dragging = 2;
		m_spInPlaceSite->InvalidateRect(&m_leftR, TRUE);
	}
	else if (m_rightR.PtInRect(point))	// Right arrow
	{
		m_dragging = 3;
		m_spInPlaceSite->InvalidateRect(&m_rightR, TRUE);
	}
	else
#endif
		if (m_knobR.Contains(point.X, point.Y))	// Knob
	{
		m_dragging = 1;

		if (get_Orientation() == Orientation_Horizontal)
			m_ptoffset = point.X - m_knobR.X;
		else
			m_ptoffset = point.Y - m_knobR.Y;
	}
#if 0
	else if (m_slidR.PtInRect(point))	// Either on left or right side of knob
	{
		if (m_dir == 0)
		{
			if (point.x < m_knobR.left)
				m_dragging = 4;
			else
				m_dragging = 5;
		}
		else
		{
			if (point.y < m_knobR.top)
				m_dragging = 4;
			else
				m_dragging = 5;
		}

		//CIUIWnd* pParent = GetParent();

		if (m_dragging == 4)
		{
			if (m_pos > m_min)
				;//Fire_SetPos(SB_PAGELEFT, 0);//pParent->TOP()->OnScroll(SB_PAGELEFT, 0, this);
		}
		else
		{
			if (m_pos < m_max-m_visible)
				;//Fire_SetPos(SB_PAGERIGHT, 0);//pParent->TOP()->OnScroll(SB_PAGERIGHT, 0, this);
		}

		m_dragging = 0;
	}
#endif

	if (m_dragging)
	{
#if 0
		m_bIsInside = TRUE;
#endif
		if (m_dragging > 1)
		{
#if _WINDOWS
//			BOOL bHandled = TRUE;
//			OnTimer(WM_TIMER, 1, 0, bHandled);
#endif

#if 0
			HWND hwnd;
			get_hwnd(&hwnd);

			SetTimer(hwnd, 1, 200, NULL);
#endif
		}

		CaptureMouse();
		//m_spInPlaceSite->SetCapture(TRUE);
	}
}

void Track::OnMouseMove(MouseEvent* evt)
{
	LDraw::PointD point = ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());

//	point.x = evt->get_ScreenX();
//	point.y = evt->get_ScreenY();
//	point.x -= m_rcPos.left;
//	point.y -= m_rcPos.top;

	if (m_dragging)
	{
		if (m_dragging == 1)
		{
	//	MessageBeep(-1);

		//	CIUIWnd* pParent = GetParent();
			
			LDraw::PointD pt;
			pt.X = point.X - m_slidR.X;
			pt.Y = point.Y - m_slidR.Y;

			Orientation orientation = get_Orientation();

			double width = (orientation == Orientation_Horizontal)? m_slidR.Width: m_slidR.Height;
			double ksize = (orientation == Orientation_Horizontal)? m_knobR.Width: m_knobR.Height;

			double totalrange = get_Maximum() - get_Minimum();

			double thumbProportion = get_ViewportSize();
			if (thumbProportion > totalrange) thumbProportion = totalrange;

		//	double m_visible = thumbProportion;

		//	int totalrange = m_max - m_min+1;// - m_visible;
			//if (width > ksize)
			{
				double abspos;
				
				if (get_Orientation() == Orientation_Horizontal)
				{
					abspos = (pt.X-m_ptoffset)*(totalrange-get_ViewportSize()) / (width-ksize);
				}
				else
				{
					abspos = (pt.Y-m_ptoffset)*(totalrange-get_ViewportSize()) / (width-ksize);
				}
				
				double pos = abspos;// + m_min;
	
				/*
				if (pos < 0) pos = 0;
				else if (pos > 1) pos = 1;
				*/

			//	m_min = 0;
			//	m_max = 1;


				double minimum = get_Minimum();
				double maximum = get_Maximum();
				double viewportsize = get_ViewportSize();

				if (pos > maximum-viewportsize) pos = maximum-viewportsize;
				if (pos < minimum) pos = minimum;

				SliderEvent* evt = new SliderEvent;
				evt->InitEvent(WSTR("posChange"), true, true);
				evt->m_pos = pos;
				bool doDefault = dispatchEvent(evt);
				if (doDefault)
				{
					set_Value(pos);
				//	Invalidate();
				}
			}
		}
		else
		{
#if 0
			BOOL bInside;

			if (m_dragging == 2) bInside = m_leftR.PtInRect(point);
			else if (m_dragging == 3) bInside = m_rightR.PtInRect(point);

			if (m_bIsInside != bInside)
			{
				if (m_dragging == 2) m_spInPlaceSite->InvalidateRect(&m_leftR, TRUE);
				else if (m_dragging == 3) m_spInPlaceSite->InvalidateRect(&m_rightR, TRUE);

				m_bIsInside = bInside;
			}
#endif
		}
	}
}

void Track::OnLButtonUp(MouseEvent* evt)
{
#if 0
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;
#endif
	if (m_dragging)
	{
		if (m_dragging > 1)
		{
#if 0
			HWND hwnd;
			get_hwnd(&hwnd);
			KillTimer(hwnd, 1);
#endif
		}

		ReleaseMouseCapture();

#if 0
		m_spInPlaceSite->SetCapture(FALSE);
#endif
		m_dragging = 0;

	//	InvalidateRect(&m_leftR, TRUE);
#if 0
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);

		Fire_SetPos(SB_ENDSCROLL, m_pos);//pParent->OnScroll(SB_ENDSCROLL, 0, this);
#endif
	}
}

/*
double Track::get_visible() const
{
	return m_visible;
}

double Track::get_pos() const
{
	return m_pos;
}
*/
#endif

#if 0
void Track::set_pos(double newVal)
{
//	if (newVal > m_max-m_visible+1) newVal = m_max-m_visible+1;
//	if (newVal < m_min) newVal = m_min;

	if (newVal != m_pos)
	{
		//MessageBeep(-1);
		m_pos = newVal;

		SetIt();

		m_thumb->SetPosition(m_knobR.X, m_knobR.Y);
	}
}
#endif

/*
void Track::put_ThumbProportion(double newVal)
{
	m_ThumbProportion = newVal;
	SetIt();
	Invalidate();
}
*/

}	// UI
}
