#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

// static
Gui::DependencyClass* ShapeTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());

	/*
	static Gui::DependencyProperty* p[] =
	{
		get_BrushSizeProperty(),
	};
	*/

	return &Class;
}

ShapeTool::ShapeTool(Gui::DependencyClass* depClass) : ImageTool(depClass)
{
}

void ShapeTool::OnMouseDown(BitmapEditor* view, gm::PointF pos)
{
	if (!view->get_HasMouseCapture())
	{
		Gui::RectangleGeometry* geom = new Gui::RectangleGeometry(pos, gm::SizeF(0, 0));

		Gui::FillGeometryVisual* visual = new Gui::FillGeometryVisual();
		visual->set_Geometry(geom);

	//	visual->m_mask = view->m_currentMask;
		view->m_topelement = visual;
		view->m_elements->m_items.push_back(view->m_topelement);

		view->Invalidate(NULL);

		view->CaptureMouse();
	}
}

void ShapeTool::OnMouseUp(BitmapEditor* view, gm::PointF pos)
{
	if (view->get_HasMouseCapture())
	{
		Gui::FillGeometryVisual* topelement = dynamic_cast<Gui::FillGeometryVisual*>(view->m_topelement);

		if (view->m_topelement)
		{
			view->m_topelement = NULL;
		}

		view->ReleaseMouseCapture();
	}
}

void ShapeTool::OnMouseMove(BitmapEditor* view, gm::PointF pos)
{
	if (view->get_HasMouseCapture())
	{
		Gui::FillGeometryVisual* topelement = dynamic_cast<Gui::FillGeometryVisual*>(view->m_topelement);

		gm::PointF size = pos - view->m_startpt;

		Gui::RectangleGeometry* geom = dynamic_cast<Gui::RectangleGeometry*>(topelement->get_Geometry());
		geom->set_Width(size.X);
		geom->set_Height(size.Y);

	//	view->Invalidate(NULL);
		view->InvalidateRender();
	}
}

// static
Gui::DependencyClass* RectangleTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());

	/*
	static Gui::DependencyProperty* p[] =
	{
		get_BrushSizeProperty(),
	};
	*/

	return &Class;
}

RectangleTool::RectangleTool() : ShapeTool(get_Class())
{
}

// static
Gui::DependencyClass* RoundedRectangleTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());

	/*
	static Gui::DependencyProperty* p[] =
	{
		get_BrushSizeProperty(),
	};
	*/

	return &Class;
}

RoundedRectangleTool::RoundedRectangleTool() : ShapeTool(get_Class())
{
}

// static
Gui::DependencyClass* EllipseTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());

	/*
	static Gui::DependencyProperty* p[] =
	{
		get_BrushSizeProperty(),
	};
	*/

	return &Class;
}

EllipseTool::EllipseTool() : ShapeTool(get_Class())
{
}

}	// ImageEdit
}	// System
