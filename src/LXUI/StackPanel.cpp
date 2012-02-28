#include "stdafx.h"
#include "LXUI2.h"
#include "StackPanel.h"

#include <cfloat>

namespace System
{
namespace UI
{

DependencyProperty* StackPanel::s_OrientationProperty = RegisterProperty(WSTR("Orientation"), typeid(Orientation), typeid(Track), IntObject::GetObject(Orientation_Vertical), PropertyMetaData(AffectsArrange));

StackPanel::StackPanel()
{
}

Orientation StackPanel::get_Orientation()
{
	return (Orientation)static_cast<IntObject*>(GetValue(get_OrientationProperty()))->GetValue();
}

void StackPanel::set_Orientation(Orientation orientation)
{
	SetValue(get_OrientationProperty(), IntObject::GetObject(orientation));
}

LDraw::SizeD StackPanel::MeasureOverride(LDraw::SizeD availSize)
{
	LDraw::SizeD desiredSize;

	unsigned int nchildren = get_InternalChildren()->GetCount();

	if (get_Orientation() == Orientation_Vertical)
	{
		for (int i = 0; i < nchildren; i++)
		{
			UIElement* child = get_InternalChildren()->get_Item(i);

			ASSERT(child->GetRParent() == this);
			// TODO remove this
			//child->SetRParent(this);

			child->Measure(LDraw::SizeD(availSize.Width, 999999));
			LDraw::SizeD size = child->get_DesiredSize();

			desiredSize.Width = MAX(desiredSize.Width, size.Width);
			desiredSize.Height += size.Height;
		}
	}
	else if (get_Orientation() == Orientation_Horizontal)
	{
		for (int i = 0; i < nchildren; i++)
		{
			UIElement* child = get_InternalChildren()->get_Item(i);//(*get_rchildList())[i];

			ASSERT(child->GetRParent() == this);
			// TODO remove this
			//child->SetRParent(this);

			child->Measure(LDraw::SizeD(999999, availSize.Height));
			LDraw::SizeD size = child->get_DesiredSize();

			desiredSize.Height = MAX(desiredSize.Height, size.Height);
			desiredSize.Width += size.Width;
		}
	}
	else
		ASSERT(0);

	return desiredSize;
}

LDraw::SizeD StackPanel::ArrangeOverride(LDraw::SizeD finalSize)
{
	unsigned int nchildren = get_InternalChildren()->GetCount();

	if (get_Orientation() == Orientation_Vertical)
	{
		double y = 0;

		for (unsigned int i = 0; i < nchildren; i++)
		{
			UIElement* child = get_InternalChildren()->get_Item(i);

			LDraw::SizeD dsize = child->get_DesiredSize();

			FrameworkElement* element = dynamic_cast<FrameworkElement*>(child);
			if (element)
			{
				LDraw::RectD finalRect;

				HorizontalAlignment horizontalAlignment = element->get_HorizontalAlignment();
				if (horizontalAlignment == HorizontalAlignment_Stretch)
				{
					finalRect = LDraw::RectD(0, y, finalSize.Width, dsize.Height);
				}
				else if (horizontalAlignment == HorizontalAlignment_Left)
				{
					finalRect = LDraw::RectD(0, y, dsize.Width, dsize.Height);
				}
				else if (horizontalAlignment == HorizontalAlignment_Right)
				{
					finalRect = LDraw::RectD(finalSize.Width-dsize.Width, y, dsize.Width, dsize.Height);
				}
				else if (horizontalAlignment == HorizontalAlignment_Center)
				{
					finalRect = LDraw::RectD((finalSize.Width-dsize.Width)/2, y, dsize.Width, dsize.Height);
				}
				else
				{
					ASSERT(0);
					throw std::exception("Invalid HorizontalAlignment value");
				}

				double width = element->get_Width();
				double height = element->get_Height();

				// ??
				if (!_isnan(width))
					finalRect.Width = width;

				// ??
				if (!_isnan(height))
					finalRect.Height = height;

			//	child->Arrange(LDraw::RectD(0, y, finalSize.Width, dsize.Height));
				child->Arrange(finalRect);
			}
			else
			{
				child->Arrange(LDraw::RectD(0, y, finalSize.Width, dsize.Height));
			}

#if 0
			if (child->get_Width() == NULL)
			{
				// fill
				child->Arrange(LDraw::RectD(0, y, finalSize.Width, dsize.Height));
				//child->SetLayoutOffset(0, y);
			}
			else
			{
				// center it
				double x = (finalSize.Width + dsize.Width) / 2;

				child->Arrange(LDraw::RectD(x, y, dsize.Width, dsize.Height));
				//child->SetLayoutOffset(x, y);
			}
#endif

			y += dsize.Height;
		}
	}
	else if (get_Orientation() == Orientation_Horizontal)
	{
		double x = 0;

		for (unsigned int i = 0; i < nchildren; i++)
		{
			UIElement* child = get_InternalChildren()->get_Item(i);

			LDraw::SizeD dsize = child->get_DesiredSize();

			child->Arrange(LDraw::RectD(x, 0, dsize.Width, finalSize.Height));
#if 0
			if (child->get_Height() == NULL)
			{
				// fill
				child->Arrange(LDraw::RectD(x, 0, dsize.Width, finalSize.Height));
				//child->SetLayoutOffset(x, 0);
			}
			else
			{
				// center it
				double y = (finalSize.Height + dsize.Height) / 2;

				child->Arrange(LDraw::RectD(x, y, dsize.Width, dsize.Height));
				//child->SetLayoutOffset(x, y);
			}
#endif

			x += dsize.Width;
		}
	}
	else
		ASSERT(0);

	return finalSize;
}

}	// UI
}
