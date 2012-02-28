namespace System
{
namespace Gui
{

class GUIEXT ManagedRetainedRenderContext
{
public:
	CTOR ManagedRetainedRenderContext(const ManagedRetainedRenderContext& other) :
		m_p(other.m_p),
		m_locallevel(0)
	{
	}

	CTOR ManagedRetainedRenderContext(RetainedRenderContext* p) :
		m_p(p), m_locallevel(0)
	{
	}

	~ManagedRetainedRenderContext()
	{
		/*
		if (m_locallevel > 0)
		{
			raise(Exception("RetainedRenderContext not popped to top"));
		}
		*/
		popall();
	}

	void popall()
	{
		while (m_locallevel)
		{
			m_p->Pop();
			--m_locallevel;
		}
	}

	void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width)
	{
		m_p->DrawLine(start, end, brush, width);
	}
	void FillRectangle(gm::RectF rect, Brush* brush)
	{
		m_p->FillRectangle(rect, brush);
	}
	void DrawRectangle(gm::RectF rect, Brush* brush, float width)
	{
		m_p->DrawRectangle(rect, brush, width);
	}
	void FillEllipse(float cx, float cy, float rx, float ry, Brush* brush)
	{
		m_p->FillEllipse(cx, cy, rx, ry, brush);
	}
	void DrawEllipse(float cx, float cy, float rx, float ry, Brush* brush, float width)
	{
		m_p->DrawEllipse(cx, cy, rx, ry, brush, width);
	}
	void FillGeometry(const geometry& geom, Brush* brush)
	{
		m_p->FillGeometry(geom, brush);
	}
	void DrawGeometry(const geometry& geom, Brush* brush, float width)
	{
		m_p->DrawGeometry(geom, brush, width);
	}
	void StrokeGeometry(const geometry& geom, Brush* brush, float width)
	{
		m_p->DrawGeometry(geom, brush, width);
	}

	void OutputText(StringIn text, Brush* brush, StringIn fontFamily, float fontSize, int fontWeight = 400)
	{
		m_p->OutputText(text, brush, fontFamily, fontSize, fontWeight);
	}

	void OutputText(typed<String> text, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight)
	{
		m_p->OutputText(text, brush, fontFamily, fontSize, fontStyle, fontWeight);
	}

	void OutputText(typed<String> text, typed<ITextSource*> textsource, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight)
	{
		m_p->OutputText(text, textsource, brush, fontFamily, fontSize, fontStyle, fontWeight);
	}

	void DrawVisual(Visual* visual)
	{
		m_p->DrawVisual(visual);
	}

	void DrawBitmap(IBitmapSource* bitmap)
	{
		m_p->DrawBitmap(bitmap);
	}

	void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, float opacity = 1.0f)
	{
		m_p->DrawBitmap(bitmap, dstRect, gm::vector4f(1.0f, 1.0f, 1.0f, opacity));
	}

	void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f colorMultiply)
	{
		m_p->DrawBitmap(bitmap, dstRect, colorMultiply);
	}

	/*
	void DrawBitmap(LDraw::Bitmap* bitmap, const LDraw::RectF& dstRect, LDraw::vector4f colorMultiply)
	{
		m_p->DrawBitmap(bitmap, dstRect, colorMultiply);
	}
	*/

	void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity = 1.0f)
	{
		m_p->DrawBitmap(bitmap, dstRect, opacity);
	}

	void Pop();

	void PushTransform(Transform* transform)
	{
		++m_locallevel;
		m_p->PushTransform(transform);
	}

// Retained with expressions
	void PushTransform(Expressive::typed_expression<Transform*> transform)
	{
		++m_locallevel;
		m_p->PushTransform(transform);
	}

	void StrokeGeometry(Expressive::typed_expression<Geometry*> geom, Expressive::typed_expression<Brush*> brush, Expressive::typed_expression<float> width)
	{
		m_p->StrokeGeometry(geom, brush, width);
	}
	void FillGeometry(Expressive::typed_expression<Geometry*> geom, Expressive::typed_expression<Brush*> brush)
	{
		m_p->FillGeometry(geom, brush);
	}

	void DrawLine(const typed<float>& x1, const typed<float>& y1, const typed<float>& x2, const typed<float>& y2, const typed<Brush*>& brush, const typed<float>& width)
	{
		m_p->DrawLine(x1, y1, x2, y2, brush, width);
	}

	RetainedRenderContext* m_p;
	int m_locallevel;
};

}	// Gui
}	// System
