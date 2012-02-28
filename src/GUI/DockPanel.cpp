#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(Dock, DockPanel, Dock, Dock_Left)	// Attached property
IMP_DEPENDENCY_PROPERTY(bool, DockPanel, LastChildFill, true)

DependencyClass* DockPanel::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_DockProperty(),
		get_LastChildFillProperty(),
	};

	return &depclass;
}

DependencyClass* DockPanel::pClass(get_Class());

DockPanel::DockPanel() : Panel(get_Class())
{
}

// static
Dock DockPanel::GetDock(DependencyObject* pObject)
{
	return pObject->GetPropertyValue(get_DockProperty());
}

// static
void DockPanel::SetDock(DependencyObject* pObject, Dock newVal)
{
	pObject->SetPropertyValue(get_DockProperty(), newVal);
}

// static
void DockPanel::ClearDock(DependencyObject* pObject)
{
	pObject->ClearPropertyValue(get_DockProperty());
}

// virtual
gm::SizeF DockPanel::MeasureOverride(gm::SizeF availSize)
{
	gm::BBoxF layoutRect(0, 0, availSize.Width, availSize.Height);

	float minWidth = 0;
	float minHeight = 0;
	float totalWidth = 0;
	float totalHeight = 0;

	size_t ncount = GetChildrenCount();

	for (size_t i = 0; i < ncount; ++i)
	{
		UIElement* pVisual = dynamic_cast<UIElement*>(GetChild(i));

		ASSERT(pVisual->get_Parent() == this);

	//	if (pVisual->get_Visibility() != Visibility_Collapsed)
		{
			Dock dock = GetDock(pVisual);

			if (dock == Dock_Fill || ((i == ncount-1) && get_LastChildFill()))
			{
				pVisual->Measure(gm::SizeF(layoutRect.GetWidth(), layoutRect.GetHeight()));
				totalWidth += pVisual->get_DesiredSize().Width;
				totalHeight += pVisual->get_DesiredSize().Height;
				break;
			}
			else if (dock == Dock_Left)
			{
				pVisual->Measure(gm::SizeF(layoutRect.GetWidth(), layoutRect.GetHeight()));

			//	pVisual->Measure(gm::SizeF(0, layoutRect.GetHeight()));
				layoutRect.left += pVisual->get_DesiredSize().Width;
				totalWidth += pVisual->get_DesiredSize().Width;
			//	totalHeight = max(totalHeight, pVisual->m_desiredHeight);
				minHeight = MAX(minHeight, pVisual->get_DesiredSize().Height);
			}
			else if (dock == Dock_Top)
			{
				pVisual->Measure(gm::SizeF(layoutRect.GetWidth(), layoutRect.GetHeight()));

			//	pVisual->Measure(gm::SizeF(layoutRect.GetWidth(), 0));
				layoutRect.top += pVisual->get_DesiredSize().Height;
				totalHeight += pVisual->get_DesiredSize().Height;
			//	totalWidth = max(totalWidth, pVisual->m_desiredWidth);
				minWidth = MAX(minWidth, pVisual->get_DesiredSize().Width);
			}
			else if (dock == Dock_Right)
			{
				pVisual->Measure(gm::SizeF(layoutRect.GetWidth(), layoutRect.GetHeight()));

			//	pVisual->Measure(gm::SizeF(0, layoutRect.GetHeight()));
				layoutRect.right -= pVisual->get_DesiredSize().Width;
				totalWidth += pVisual->get_DesiredSize().Width;
			//	totalHeight = max(totalHeight, pVisual->m_desiredHeight);
				minHeight = MAX(minHeight, pVisual->get_DesiredSize().Height);
			}
			else if (dock == Dock_Bottom)
			{
				pVisual->Measure(gm::SizeF(layoutRect.GetWidth(), layoutRect.GetHeight()));

			//	pVisual->Measure(gm::SizeF(layoutRect.GetWidth(), 0));
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

	return gm::SizeF(MAX(minWidth, totalWidth), MAX(minHeight, totalHeight));
}

// virtual
gm::SizeF DockPanel::ArrangeOverride(gm::SizeF finalSize)
{
	gm::BBoxF layoutRect(0, 0, finalSize.Width, finalSize.Height);

	size_t ncount = GetChildrenCount();
	for (size_t i = 0; i < ncount; ++i)
	{
		UIElement* pVisual = dynamic_cast<UIElement*>(GetChild(i));

		//if (pVisual->get_Visibility() != Collapsed)
		{
			Dock dock = GetDock(pVisual);

			ASSERT(pVisual->get_DesiredSize().Width >= 0 && pVisual->get_DesiredSize().Height >= 0);

		//	double fLeft;
		//	double fTop;

			if (dock == Dock_Fill || ((i == ncount-1) && get_LastChildFill()))
			{
				pVisual->Arrange(layoutRect);//LDraw::RectD(layoutRect.GetWidth(), layoutRect.GetHeight()));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.top;
			}
			else if (dock == Dock_Left)
			{
				pVisual->Arrange(gm::RectF(layoutRect.left, layoutRect.top, pVisual->get_DesiredSize().Width, layoutRect.GetHeight()));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.top;
				layoutRect.left += pVisual->get_ActualSize().Width;
			}
			else if (dock == Dock_Top)
			{
				pVisual->Arrange(gm::RectF(layoutRect.left, layoutRect.top, layoutRect.GetWidth(), pVisual->get_DesiredSize().Height));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.top;
				layoutRect.top += pVisual->get_ActualSize().Height;
			}
			else if (dock == Dock_Right)
			{
				pVisual->Arrange(gm::RectF(layoutRect.right - pVisual->get_DesiredSize().Width, layoutRect.top, pVisual->get_DesiredSize().Width, layoutRect.GetHeight()));
			//	fLeft = layoutRect.right - pVisual->get_ActualSize().Width;
			//	fTop = layoutRect.top;
				layoutRect.right -= pVisual->get_ActualSize().Width;
			}
			else if (dock == Dock_Bottom)
			{
				pVisual->Arrange(gm::RectF(layoutRect.left, layoutRect.bottom - pVisual->get_DesiredSize().Height, layoutRect.GetWidth(), pVisual->get_DesiredSize().Height));
			//	fLeft = layoutRect.left;
			//	fTop = layoutRect.bottom - pVisual->get_ActualSize().Height;
				layoutRect.bottom -= pVisual->get_ActualSize().Height;
			}
			else
				ASSERT(0);

		//	pVisual->SetLayoutOffset(fLeft, fTop);

			if (dock == Dock_Fill ||

				layoutRect.GetWidth() <= 0 ||
				layoutRect.GetHeight() <= 0)
			{
				break;
			}
		}
	}

	return finalSize;
}

}	// Gui
}	// System
