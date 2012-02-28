namespace System
{
namespace Gui
{

class GUIEXT ManagedRenderContext
{
public:
	CTOR ManagedRenderContext(const ManagedRenderContext& other) :
		m_p(other.m_p),
		m_level(0)
	{
	}

	CTOR ManagedRenderContext(RenderContext* p) :
		m_p(p), m_level(0)
	{
	}

	~ManagedRenderContext()
	{
		popall();
	}

	void popall()
	{
		while (m_level)
		{
			--m_level;
			m_p->Pop();
		}
	}

	void SetAntialiasPerPrimitive(bool antialias)
	{
		m_p->SetAntialiasPerPrimitive(antialias);
	}

	void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width)
	{
		m_p->DrawLine(start, end, brush, width);
	}

	void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width, StrokeStyle* strokeStyle)
	{
		m_p->DrawLine(start, end, brush, width, strokeStyle);
	}

	void FillRectangle(gm::RectF rect, Brush* brush)
	{
		m_p->FillRectangle(rect, brush);
	}
	void FillEllipse(float cx, float cy, float rx, float ry, Brush* brush)
	{
		m_p->FillEllipse(cx, cy, rx, ry, brush);
	}
	void StrokeEllipse(float cx, float cy, float rx, float ry, Brush* brush, float width)
	{
		m_p->DrawEllipse(cx, cy, rx, ry, brush, width);
	}
	void DrawEllipse(float cx, float cy, float rx, float ry, Brush* brush, float width)
	{
		m_p->DrawEllipse(cx, cy, rx, ry, brush, width);
	}

	void StrokeRectangle(gm::RectF rect, Brush* brush, float width)
	{
		m_p->DrawRectangle(rect, brush, width);
	}
	void DrawRectangle(gm::RectF rect, Brush* brush, float width)
	{
		m_p->DrawRectangle(rect, brush, width);
	}

	void FillGeometry(const geometry& geom, Brush* brush)
	{
		m_p->FillGeometry(geom, brush);
	}
	void DrawGeometry(const geometry& geom, Brush* brush, float width)
	{
		m_p->DrawGeometry(geom, brush, width);
	}

	void OutputText(StringIn text, Brush* brush, StringIn fontFamily, float fontSize, int fontWeight = 400)
	{
		m_p->OutputText(text, brush, fontFamily, fontSize, fontWeight);
	}

	void OutputText(StringIn text, Brush* brush, TextFormat* textFormat, gm::RectF layoutRect)
	{
		m_p->OutputText(text, brush, textFormat, layoutRect);
	}

	void DrawVisual(Visual* visual)
	{
		m_p->DrawVisual(visual);
	}

	void PushTransform(const gm::matrix3f& transform)
	{
		++m_level;
		m_p->PushTransform(transform);
	}

	void PushTransform(Transform* transform)
	{
		++m_level;
		m_p->PushTransform(transform);
	}

	void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, float opacity)
	{
		m_p->DrawBitmap(bitmap, dstRect, gm::vector4f(1.0f, 1.0f, 1.0f, opacity));
	}

	void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor)
	{
		m_p->DrawBitmap(bitmap, dstRect, mulcolor);
	}

	void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, float opacity, const gm::RectF& srcRect)
	{
		m_p->DrawBitmap(bitmap, dstRect, gm::vector4f(1.0f, 1.0f, 1.0f, opacity), srcRect);
	}

	void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity)
	{
		m_p->DrawBitmap(bitmap, dstRect, opacity);
	}

	/*
	void DrawBitmap(LDraw::Bitmap* bitmap, const LDraw::RectF& dstRect, LDraw::vector4f mulcolor)
	{
		m_p->DrawBitmap(bitmap, dstRect, mulcolor);
	}
	*/

	void Pop();

	RenderContext* m_p;
	int m_level;
};

}	// Gui
}	// System
