#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

extern PaintBrush* brush;

IMP_DEPENDENCY_PROPERTY(float, PencilTool, Size, 30.0f)
IMP_DEPENDENCY_PROPERTY(Gui::Color*, PencilTool, Color, new Gui::Color(0.9f, 0.2f, 0))
IMP_DEPENDENCY_PROPERTY(float, PencilTool, Opacity, 0.5f)
IMP_DEPENDENCY_PROPERTY(float, PencilTool, Spacing, 0.15f)

// static
Gui::DependencyClass* PencilTool::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());

	static Gui::DependencyProperty* p[] =
	{
		get_SizeProperty(),
		get_ColorProperty(),
		get_OpacityProperty(),
		get_SpacingProperty(),
	};

	return &Class;
}

PencilTool::PencilTool() : ImageTool(get_Class())
{
}

void PencilTool::OnMouseDown(BitmapEditor* view, gm::PointF pos)
{
	if (!view->get_HasMouseCapture())
	{
		if (brush == NULL)
		{
			brush = new PaintBrush;
			brush->SetCircular();
		}

		StrokeVisual* visual = new StrokeVisual;
		visual->m_document = view->m_document;
		visual->m_mask = view->m_currentMask;
		visual->m_colorMultiply = gm::vector4f(get_Color()->getVec3f(), get_Opacity());
		visual->m_brushSize = get_Size();
		visual->m_spacing = get_Spacing();
		visual->m_brush = brush;

		view->m_hitVisual = visual;

		view->m_topelement = visual;
		view->m_elements->m_items.push_back(view->m_topelement);

		visual->m_points.push_back(pos);
		visual->MoveTo(pos);

		visual->m_bounds.left = pos.X;
		visual->m_bounds.top = pos.Y;
		visual->m_bounds.right = pos.X;
		visual->m_bounds.bottom = pos.Y;

		view->Invalidate(NULL);

		view->m_dragging = 1;
		view->CaptureMouse();
	}
}

void PencilTool::OnMouseUp(BitmapEditor* view, gm::PointF pos)
{
	if (view->get_HasMouseCapture())
	{
		StrokeVisual* topelement = dynamic_cast<StrokeVisual*>(view->m_topelement);

		if (topelement)
		{
			topelement = NULL;
		}

		view->m_dragging = 0;
		view->ReleaseMouseCapture();
	}
}

void PencilTool::OnMouseMove(BitmapEditor* view, gm::PointF pos)
{
	if (view->get_HasMouseCapture())
	{
		StrokeVisual* topelement = dynamic_cast<StrokeVisual*>(view->m_topelement);

		StrokeVisual::LoadEffect();

		if (topelement->m_mask)
		{
			topelement->CreateVertexBuffer();
		}
		else
		{
			ASSERT(0);
		}

		topelement->m_points.push_back(pos);

	//	gm::PointF pt = pos;
	//	float size = topelement->m_brushSize;

		D3D11_VIEWPORT vp;
		vp.Width = view->m_compositeBitmap->GetWidth();
		vp.Height = view->m_compositeBitmap->GetHeight();
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		view->m_compositeRT->m_d3d10->m_deviceContext->RSSetViewports(1, &vp);

		view->m_compositeRT->m_projection = gm::matrix4f::getOrtho2D(0, view->m_compositeBitmap->GetWidth(), view->m_compositeBitmap->GetHeight(), 0);
		view->m_compositeRT->m_modelView = gm::matrix4f::getIdentity();
		view->m_compositeRT->m_modelViewProjection = view->m_compositeRT->m_projection * view->m_compositeRT->m_modelView;

		Graphics::RenderTargetStoreState state;
		view->m_compositeRT->BeginDraw(&state);

		topelement->LineTo(view->m_compositeRT, pos);

		topelement->m_bounds.left = std::min(topelement->m_bounds.left, pos.X);
		topelement->m_bounds.top = std::min(topelement->m_bounds.top, pos.X);
		topelement->m_bounds.right = std::max(topelement->m_bounds.right, pos.X);
		topelement->m_bounds.bottom = std::max(topelement->m_bounds.bottom, pos.Y);

		view->m_compositeRT->EndDraw(&state);

		view->Invalidate(NULL);
	}
}

}	// ImageEdit
}	// System
