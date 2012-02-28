#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

VisualTreeController::VisualTreeController(Visual* root)
{
	m_root = root;
}

float VisualTreeController::GetItemHeight(TreeItem item)
{
	return 20;
}

int VisualTreeController::GetItemState(TreeItem item)
{
	return 0;
}

void VisualTreeController::RenderItem(TreeItem item, ManagedRenderContext renderContext, gm::RectF bounds)
{
	static SolidColorBrush* brush = new SolidColorBrush(0,0,0);
	static TextFormat* textFormat = new TextFormat("Arial", 20);

	renderContext.OutputText(static_cast<Visual*>(item.data0)->GetType()->ToString(), brush, textFormat, bounds);
}

int VisualTreeController::ClickItem(TreeItem item, gm::RectF bounds, gm::PointF pos)
{
	IInputElement* inputElement = dynamic_cast<IInputElement*>(item.data0);
	RoutedEventArgs* args = new RoutedEventArgs(UIElement::get_ActivateEvent());
	inputElement->RaiseEvent(args);

//	SelectionChanged(static_cast<Visual*>(item.data0));
	return 0;
}

size_t VisualTreeController::GetChildrenCount(TreeItem item)
{
	return static_cast<Visual*>(item.data0)->GetChildrenCount();
}

TreeItem VisualTreeController::GetChild(TreeItem item, size_t index)
{
	return TreeItem(item.controller, static_cast<Visual*>(item.data0)->GetChild(index));
}

TreeItem VisualTreeController::GetRoot()
{
	return TreeItem(this, m_root);
}

}
}
