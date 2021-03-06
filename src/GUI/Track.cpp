#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(Orientation, Track, Orientation, Orientation_Horizontal)
IMP_DEPENDENCY_PROPERTY(float, Track, Minimum, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Track, Maximum, 1.0f)
IMP_DEPENDENCY_PROPERTY(float, Track, ViewportSize, float_NaN.value)
IMP_DEPENDENCY_PROPERTY(float, Track, Value, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Track, PreviousValue, 0.0f)

DependencyClass* Track::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_OrientationProperty(),
		get_MinimumProperty(),
		get_MaximumProperty(),
		get_ViewportSizeProperty(),
		get_ValueProperty(),
		get_PreviousValueProperty(),
	};

	return &depclass;
}

DependencyClass* Track::pClass(get_Class());

Track::Track() : FrameworkElement(get_Class())
{
//	set_Width(400);
//	set_Height(20);
}

void Track::OnComputedPropertyValueChanged(PropertyValue* pPropertyValue, bool handled)
{
	if (
		pPropertyValue->m_dp == get_OrientationProperty() ||
		pPropertyValue->m_dp == get_ViewportSizeProperty() ||
		pPropertyValue->m_dp == get_ValueProperty() ||
		pPropertyValue->m_dp == get_MinimumProperty() ||
		pPropertyValue->m_dp == get_MaximumProperty() ||

		//
		pPropertyValue->m_dp == get_ActualWidthProperty() ||
		pPropertyValue->m_dp == get_ActualHeightProperty())
	{
		SetIt();
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyValue, handled);
}

void Track::Render(ManagedRenderContext renderContext)
{
//	LDraw::RectF rect(0, 0, get_Width(), get_Height());
	renderContext.FillRectangle(m_slidR, new SolidColorBrush(0.75f, 0.75f, 0.75f));
	renderContext.DrawRectangle(m_slidR, new SolidColorBrush(0.1f, 0.1f, 0.1f), 1);

	renderContext.FillRectangle(m_knobR, new SolidColorBrush(0.5f, 0.5f, 0.5f));
	renderContext.DrawRectangle(m_knobR, new SolidColorBrush(0.2f, 0.2f, 0.2f), 1);
}

void Track::OnMouseLeftButtonDown(MouseButtonEventArgs* args)
{
	if (!get_IsMouseCaptured())
	{
		CaptureMouse();
		Point mousepos = args->GetPosition(this);
		m_mousepos = mousepos;
		m_totalDelta = 0;
		set_PreviousValue(get_Value());
	}
}

void Track::OnMouseMove(MouseEventArgs* args)
{
	if (get_IsMouseCaptured())
	{
		Point mousepos = args->GetPosition(this);

		Orientation orientation = get_Orientation();

		double delta;
		if (orientation == Orientation_Horizontal)
			delta = mousepos.X - m_mousepos.X;
		else
			delta = mousepos.Y - m_mousepos.Y;

		m_mousepos = mousepos;
		m_totalDelta += delta;

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

			pos = (m_totalDelta)*(totalrange) / (width-ksize);
			pos += get_PreviousValue();

			if (pos > maximum) pos = maximum;
			if (pos < minimum) pos = minimum;

			set_Value(pos);
		}
		else
		{
			if (thumbProportion > totalrange) thumbProportion = totalrange;

			double pos;
			
			pos = (m_totalDelta)*(totalrange-get_ViewportSize()) / (width-ksize);
			pos += get_PreviousValue();

			double viewportsize = get_ViewportSize();

			if (pos > maximum-viewportsize) pos = maximum-viewportsize;
			if (pos < minimum) pos = minimum;

			set_Value(pos);
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
}

void Track::OnMouseLeftButtonUp(MouseButtonEventArgs* args)
{
	if (get_IsMouseCaptured())
	{
		ReleaseMouseCapture();
	}
}

void Track::SetIt()
{

	Orientation orientation = get_Orientation();

//	double thumbProportion = m_ThumbProportion;
//	if (thumbProportion > 1) thumbProportion = 1;

	m_slidR = gm::RectF(0, 0, get_ActualWidth(), get_ActualHeight());

	double width = (get_Orientation() == Orientation_Horizontal)? m_slidR.Width: m_slidR.Height;

	double viewportSize = get_ViewportSize();

	double totalrange = get_Maximum() - get_Minimum();

	double abspos = get_Value() - get_Minimum();

	double kpos;
	double ksize;

	if (_isnan(viewportSize))
	{
		if (orientation == Orientation_Horizontal)
			ksize = 20;//m_thumb->get_DesiredSize().Width;
		else
			ksize = 20;//m_thumb->get_DesiredSize().Height;

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

	if (orientation == Orientation_Horizontal)	// horizontal
	{
		m_knobR = gm::RectF(kpos, m_slidR.Y, ksize, m_slidR.Height);
		//if (m_knobR.X < 1) m_knobR.X = 1;
	}
	else	// vertical
	{
		m_knobR = gm::RectF(m_slidR.X, m_slidR.Y+kpos, m_slidR.Width, ksize);
	}

	//m_thumb->m_width = new Length(m_knobR.Width);
	//m_thumb->m_height = new Length(m_knobR.Height);
	//m_thumb->SetLayoutOffset(m_knobR.X, m_knobR.Y);
}

}	// Gui
}	// System
