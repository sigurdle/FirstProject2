#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

// static
Gui::DependencyClass* HandTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());
	return &Class;
}

HandTool::HandTool() : ImageTool(get_Class())
{
}

void HandTool::OnMouseDown(BitmapEditor* view, gm::PointF pos)
{
	if (view->m_hitVisual)
	{
		view->m_dragging = true;
		view->CaptureMouse();
	}
}

void HandTool::OnMouseUp(BitmapEditor* view, gm::PointF pos)
{
	if (view->m_hitVisual)
	{
		if (view->get_HasMouseCapture())
		{
			view->m_dragging = false;
			view->ReleaseMouseCapture();
		}
	}
}

void HandTool::OnMouseMove(BitmapEditor* view, gm::PointF pt)
{
	if (view->get_HasMouseCapture())
	{
		gm::PointF dpt = pt - view->m_oldpt;

		if (Gui::FillGeometryVisual* g = dynamic_cast<Gui::FillGeometryVisual*>(view->m_hitVisual))
		{
			gm::PointF oldcenter = gm::PointF(
				static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->get_CenterX(),
				static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->get_CenterY());

			gm::PointF newcenter = oldcenter + dpt;

			static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->set_CenterX(newcenter.X);
			static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->set_CenterY(newcenter.Y);
		}
		else if (Gui::DrawBitmapVisual* g = dynamic_cast<Gui::DrawBitmapVisual*>(view->m_hitVisual))
		{
			float x = g->get_DestLeft();
			float y = g->get_DestTop();

			g->set_DestLeft(x + dpt.X);
			g->set_DestTop(y + dpt.Y);
		}
		else
		{
			Gui::Visual* v = view->m_hitVisual;

			Gui::TranslateTransform* t = dynamic_cast<Gui::TranslateTransform*>(v->get_Transform());
			if (t == NULL)
			{
				t = new Gui::TranslateTransform();
				v->set_Transform(t);
			}

			float x = t->get_TranslateX();
			float y = t->get_TranslateY();

			t->set_TranslateX(x + dpt.X);
			t->set_TranslateY(y + dpt.Y);
		}

		view->InvalidateRender();	// TODO remove
		//view->InvalidateVisual();	// TODO remove
	}
}

}	// ImageEdit
}	// System
