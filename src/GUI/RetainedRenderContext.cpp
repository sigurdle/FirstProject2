#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

RetainedRenderContext::RetainedRenderContext(IRootVisual* root) : m_root(root), m_visuals(nullptr)
{
}

RetainedRenderContext::RetainedRenderContext(IRootVisual* root, GroupVisual* visuals) : m_root(root), m_visuals(visuals)
{
	visuals->SetRoot(m_root);
}

void RetainedRenderContext::Pop()
{
	m_stack.pop();
	m_visuals = m_stack.top();
}

void RetainedRenderContext::DrawVisual(Visual* visual)
{
	m_visuals->Add(visual);
}

void RetainedRenderContext::PushTransform(Transform* transform)
{
	GroupVisual* transformVisual = new GroupVisual;
	transformVisual->set_Transform(transform);

	m_visuals->Add(transformVisual);

	m_stack.push(transformVisual);
	m_visuals = transformVisual;
}

void RetainedRenderContext::PushTransform(const gm::matrix3f& transform)
{
	// TODO
	ASSERT(0);
}

void RetainedRenderContext::PushClip(const geometry& clip)
{
	GroupVisual* transformVisual = new GroupVisual;
	transformVisual->set_Clip(clip);
	ASSERT(0);

	m_visuals->Add(transformVisual);

	m_stack.push(transformVisual);
	m_visuals = transformVisual;
//	RetainedRenderContext* p = new RetainedRenderContext(m_root, this, transformVisual);
//	return p;
}

void RetainedRenderContext::PushTransform(Expressive::typed_expression<Transform*> transform)
{
	ASSERT(0);
}

void RetainedRenderContext::SetAntialiasPerPrimitive(bool antialias)
{
	ASSERT(0);
}

void RetainedRenderContext::DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width)
{
	LineVisual* visual = new LineVisual(start.X, start.Y, end.X, end.Y);
	visual->set_Brush(brush);
	visual->set_Width(width);

	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width, StrokeStyle* style)
{
	LineVisual* visual = new LineVisual(start.X, start.Y, end.X, end.Y);
	visual->set_Brush(brush);
	visual->set_Width(width);
	visual->set_Style(style);

	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawLine(typed<float> x1, typed<float> y1, typed<float> x2, typed<float> y2, typed<Brush*> brush, typed<float> width)
{
	LineVisual* visual = new LineVisual(x1, y1, x2, y2, brush, width);
	m_visuals->Add(visual);
}

void RetainedRenderContext::StrokeGeometry(Expressive::typed_expression<Geometry*> geometry, Expressive::typed_expression<Brush*> brush, Expressive::typed_expression<float> width)
{
	ASSERT(0);
}

void RetainedRenderContext::FillGeometry(Expressive::typed_expression<Geometry*> geometry, Expressive::typed_expression<Brush*> brush)
{
	ASSERT(0);
}

void RetainedRenderContext::FillRectangle(gm::RectF rect, Brush* brush)
{
	FillGeometryVisual* visual = new FillGeometryVisual;
	visual->set_Geometry(new RectangleGeometry(rect));
	visual->set_Brush(brush);

	m_visuals->Add(visual);
}

void RetainedRenderContext::FillEllipse(float cx, float cy, float rx, float ry, Brush* brush) 
{
	FillEllipseVisual* visual = new FillEllipseVisual(cx, cy, rx, ry, brush);
	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawEllipse(float cx, float cy, float rx, float ry, Brush* brush, float strokeWidth)
{
	StrokeGeometryVisual* visual = new StrokeGeometryVisual;
	visual->set_Geometry(new EllipseGeometry(cx, cy, rx, ry));
	visual->set_Brush(brush);
	visual->set_Width(strokeWidth);

	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawRectangle(gm::RectF rect, Brush* brush, float strokeWidth)
{
	StrokeGeometryVisual* visual = new StrokeGeometryVisual;
	visual->set_Geometry(new RectangleGeometry(rect));
	visual->set_Brush(brush);
	visual->set_Width(strokeWidth);

	m_visuals->Add(visual);
}

void RetainedRenderContext::FillGeometry(const geometry& geom, Brush* brush)
{
	FillGeometryVisual* visual = new FillGeometryVisual;
	visual->set_Brush(brush);
	visual->set_Geometry(geom);

	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawGeometry(const geometry& geom, Brush* brush, float width)
{
	StrokeGeometryVisual* visual = new StrokeGeometryVisual;
	visual->set_Brush(brush);
	visual->set_Geometry(geom);
	visual->set_Width(width);

	m_visuals->Add(visual);
}

void RetainedRenderContext::OutputText(StringIn text, Brush* brush, StringIn fontFamily, float fontSize, int fontWeight)
{
	TextVisual* visual = new TextVisual;
	visual->set_Text(String(text));
	visual->set_Brush(brush);
	visual->set_FontFamily(fontFamily);
	visual->set_FontSize(fontSize);
	visual->set_FontWeight(fontWeight);

	m_visuals->Add(visual);
}

void RetainedRenderContext::OutputText(StringIn text, Brush* brush, TextFormat* textFormat, gm::RectF layoutRect)
{
	ASSERT(0);
}

void RetainedRenderContext::OutputText(typed<String> text, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight)
{
	TextVisual* visual = new TextVisual(text, brush, fontFamily, fontSize, fontStyle, fontWeight);
	m_visuals->Add(visual);
}

void RetainedRenderContext::OutputText(typed<String> text, typed<ITextSource*> textsource, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight)
{
	TextVisual* visual = new TextVisual(text, textsource, brush, fontFamily, fontSize, fontStyle, fontWeight);
	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawBitmap(IBitmapSource* bitmap)
{
	BitmapVisual* visual = new BitmapVisual;

	visual->set_Bitmap(bitmap);
//	visual->set_DestRect(new RectangleGeometry(dstRect));

	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f colorMultiply)
{
	BitmapVisual* visual = new BitmapVisual;

	visual->set_Bitmap(bitmap);
	visual->set_DestRect(new RectangleGeometry(dstRect));

	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f colorMultiply, const gm::RectF& srcRect)
{
	BitmapVisual* visual = new BitmapVisual;

	ASSERT(0);

//	visual->set_Bitmap(bitmap);
//	visual->set_DestRect(new RectangleGeometry(dstRect));

	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity)
{
	DrawBitmapVisual* visual = new DrawBitmapVisual(bitmap, dstRect, opacity);
	m_visuals->Add(visual);
}

void RetainedRenderContext::DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity, const gm::RectF& srcRect)
{
	DrawBitmapVisual* visual = new DrawBitmapVisual(bitmap, dstRect);
	m_visuals->Add(visual);
}

void ManagedRenderContext::Pop()
{
	if (m_level == 0)
	{
		raise(Exception(S("Popping past top")));
	}

	--m_level;
	m_p->Pop();
}

}	// Gui
}	// System
