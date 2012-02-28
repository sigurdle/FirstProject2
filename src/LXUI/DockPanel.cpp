#include "stdafx.h"
#include "LXUI2.h"
#include "DockPanel.h"

namespace System
{
namespace UI
{

DependencyProperty* DockPanel::s_DockProperty = RegisterAttached(WSTR("Dock"), typeid(DockEnum), typeid(DockPanel), IntObject::GetObject(Left), PropertyMetaData(None));
DependencyProperty* DockPanel::s_LastChildFillProperty = RegisterProperty(WSTR("LastChildFill"), typeid(bool), typeid(DockPanel), BoolObject::get_True(), PropertyMetaData(None));

DockPanel::DockPanel()
{
}

bool DockPanel::get_LastChildFill()
{
	return static_cast<BoolObject*>(GetValue(get_LastChildFillProperty()))->GetValue();
}

void DockPanel::set_LastChildFill(bool lastChildFill)
{
	SetValue(get_LastChildFillProperty(), BoolObject::GetObject(lastChildFill));
}

// static
DockPanel::DockEnum DockPanel::GetDock(DependencyObject* pObject)
{
	Object* obj = pObject->GetValue(get_DockProperty());
	ASSERT(dynamic_cast<IntObject*>(obj));
	System::IntObject* pInt = static_cast<IntObject*>(obj);

	return (DockEnum)pInt->GetValue();
}

// static
void DockPanel::SetDock(DependencyObject* pObject, DockEnum newVal)
{
	if (newVal != Left &&
		newVal != Top &&
		newVal != Right &&
		newVal != Bottom &&
		newVal != Fill)
	{
		ASSERT(0);
		THROW(std::exception("Invalid Dock enum value"));
	}

	pObject->SetValue(get_DockProperty(), IntObject::GetObject(newVal));
}

// static
void DockPanel::ClearDock(DependencyObject* pObject)
{
	pObject->ClearValue(get_DockProperty());
}

void DockPanel::RemoveChildren()
{
	// ??
	get_Children()->m_items.clear();
//	ASSERT(0);
#if 0
	for (int i = get_rchildList()->get_Size()-1; i >= 0; i--)
	{
		RemoveRChild((*get_rchildList())[i]);
	}
#endif
	InvalidateMeasure();
}

// virtual
LDraw::SizeD DockPanel::MeasureOverride(LDraw::SizeD availSize)
{
	LDraw::BBoxD layoutRect(0, 0, availSize.Width, availSize.Height);

	double minWidth = 0;
	double minHeight = 0;
	double totalWidth = 0;
	double totalHeight = 0;

	unsigned int ncount = get_InternalChildren()->GetCount();

#if 0
	for (unsigned int i = 0; i < ncount; i++)
	{
		UIElement* pVisual = get_InternalChildren()->GetItem(i);//(*get_rchildList())[i];

		// TODO remove this
	//	pVisual->SetRParent(this);
	}
#endif

	for (unsigned int i = 0; i < ncount; i++)
	{
		UIElement* pVisual = get_InternalChildren()->get_Item(i);//(*get_rchildList())[i];

		ASSERT(pVisual->GetRParent() == this);

		if (pVisual->get_Visibility() != Collapsed)
		{
			DockEnum dock = GetDock(pVisual);

			if (dock == Fill || ((i == ncount-1) && get_LastChildFill()))
			{
				pVisual->Measure(LDraw::SizeD(layoutRect.GetWidth(), layoutRect.GetHeight()));
				totalWidth += pVisual->get_DesiredSize().Width;
				totalHeight += pVisual->get_DesiredSize().Height;
				break;
			}
			else if (dock == Left)
			{
				pVisual->Measure(LDraw::SizeD(0, layoutRect.GetHeight()));
				layoutRect.left += pVisual->get_DesiredSize().Width;
				totalWidth += pVisual->get_DesiredSize().Width;
			//	totalHeight = max(totalHeight, pVisual->m_desiredHeight);
				minHeight = MAX(minHeight, pVisual->get_DesiredSize().Height);
			}
			else if (dock == Top)
			{
				pVisual->Measure(LDraw::SizeD(layoutRect.GetWidth(), 0));
				layoutRect.top += pVisual->get_DesiredSize().Height;
				totalHeight += pVisual->get_DesiredSize().Height;
			//	totalWidth = max(totalWidth, pVisual->m_desiredWidth);
				minWidth = MAX(minWidth, pVisual->get_DesiredSize().Width);
			}
			else if (dock == Right)
			{
				pVisual->Measure(LDraw::SizeD(0, layoutRect.GetHeight()));
				layoutRect.right -= pVisual->get_DesiredSize().Width;
				totalWidth += pVisual->get_DesiredSize().Width;
			//	totalHeight = max(totalHeight, pVisual->m_desiredHeight);
				minHeight = MAX(minHeight, pVisual->get_DesiredSize().Height);
			}
			else if (dock == Bottom)
			{
				pVisual->Measure(LDraw::SizeD(layoutRect.GetWidth(), 0));
				layoutRect.bottom -= pVisual->get_DesiredSize().Height;
				totalHeight += pVisual->get_DesiredSize().Height;
			//	totalWidth = max(totalWidth, pVisual->m_desiredWidth);
				minWidth = MAX(minWidth, pVisual->get_DesiredSize().Width);
			}
			else
				ASSERT(0);

		//	pVisual->SetLayoutOffset(fLeft, fTop);
		//	pVisual->Arrange(LDraw::SizeF(pVisual->m_computedWidth, pVisual->m_computedHeight));

			/*
			if (dock == Fill ||

				layoutRect.GetWidth() <= 0 ||
				layoutRect.GetHeight() <= 0)
			{
				break;
			}
			*/
		}
	}

	return LDraw::SizeD(MAX(minWidth, totalWidth), MAX(minHeight, totalHeight));
}

// virtual
LDraw::SizeD DockPanel::ArrangeOverride(LDraw::SizeD finalSize)
{
	LDraw::BBoxD layoutRect(0, 0, finalSize.Width, finalSize.Height);

	unsigned int ncount = get_InternalChildren()->GetCount();//get_rchildList()->get_Size();
	for (unsigned int i = 0; i < ncount; i++)
	{
		UIElement* pVisual = get_InternalChildren()->get_Item(i);//(*get_rchildList())[i];

		if (pVisual->get_Visibility() != Collapsed)
		{
		//	long dockValue;
			DockEnum dock = GetDock(pVisual);

			ASSERT(pVisual->get_DesiredSize().Width >= 0 && pVisual->get_DesiredSize().Height >= 0);

		//	double fLeft;
		//	double fTop;

			if (dock == Fill || ((i == ncount-1) && get_LastChildFill()))
			{
				pVisual->Arrange(layoutRect);//LDraw::RectD(layoutRect.GetWidth(), layoutRect.GetHeight()));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.top;
			}
			else if (dock == Left)
			{
				pVisual->Arrange(LDraw::RectD(layoutRect.left, layoutRect.top, pVisual->get_DesiredSize().Width, layoutRect.GetHeight()));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.top;
				layoutRect.left += pVisual->get_ActualSize().Width;
			}
			else if (dock == Top)
			{
				pVisual->Arrange(LDraw::RectD(layoutRect.left, layoutRect.top, layoutRect.GetWidth(), pVisual->get_DesiredSize().Height));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.top;
				layoutRect.top += pVisual->get_ActualSize().Height;
			}
			else if (dock == Right)
			{
				pVisual->Arrange(LDraw::RectD(layoutRect.right - pVisual->get_DesiredSize().Width, layoutRect.top, pVisual->get_DesiredSize().Width, layoutRect.GetHeight()));
			//	fLeft = layoutRect.right - pVisual->get_ActualSize().Width;
			//	fTop = layoutRect.top;
				layoutRect.right -= pVisual->get_ActualSize().Width;
			}
			else if (dock == Bottom)
			{
				pVisual->Arrange(LDraw::RectD(layoutRect.left, layoutRect.bottom - pVisual->get_DesiredSize().Height, layoutRect.GetWidth(), pVisual->get_DesiredSize().Height));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.bottom - pVisual->get_ActualSize().Height;
				layoutRect.bottom -= pVisual->get_ActualSize().Height;
			}
			else
				ASSERT(0);

		//	pVisual->SetLayoutOffset(fLeft, fTop);

			if (dock == Fill ||

				layoutRect.GetWidth() <= 0 ||
				layoutRect.GetHeight() <= 0)
			{
				break;
			}
		}
	}

	return finalSize;
}

}	// UI
}
