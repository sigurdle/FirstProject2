#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

// static
Gui::DependencyClass* TransformTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());
	return &Class;
}

TransformTool::TransformTool() : ImageTool(get_Class())
{
}

void TransformTool::OnMouseDown(BitmapEditor* view, gm::PointF pos)
{
	if (view->m_hitVisual)
	{
		view->m_dragging = true;
		view->CaptureMouse();
	}
}

void TransformTool::OnMouseUp(BitmapEditor* view, gm::PointF pos)
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

void TransformTool::OnMouseMove(BitmapEditor* view, gm::PointF pt)
{
	if (view->get_HasMouseCapture())
	{
		gm::PointF dpt = pt - view->m_oldpt;

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

		view->InvalidateRender();	// TODO remove
		//view->InvalidateVisual();	// TODO remove
	}
}

void TransformTool::OnRender(BitmapEditor* view, Gui::ManagedRetainedRenderContext pGraphics)
{
}

}
}
