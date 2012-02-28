#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

// static
Gui::DependencyClass* SelectionTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());
	return &Class;
}

SelectionTool::SelectionTool(Gui::DependencyClass* depClass) : ImageTool(depClass)
{
}

/////////////////

// static
Gui::DependencyClass* RectangularSelectionTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());
	return &Class;
}

RectangularSelectionTool::RectangularSelectionTool() : SelectionTool(get_Class())
{
}

void RectangularSelectionTool::OnMouseDown(BitmapEditor* view, gm::PointF pos)
{
}

void RectangularSelectionTool::OnMouseUp(BitmapEditor* view, gm::PointF pos)
{
}

void RectangularSelectionTool::OnMouseMove(BitmapEditor* view, gm::PointF pos)
{
}

void RectangularSelectionTool::OnRender(BitmapEditor* view, Gui::ManagedRetainedRenderContext pGraphics)
{
}

}	// ImageEdit
}	// System
