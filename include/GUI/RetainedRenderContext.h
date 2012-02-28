namespace System
{
namespace Gui
{

class GUIEXT RetainedRenderContext : public RenderContext
{
public:
	CTOR RetainedRenderContext(IRootVisual* root);
	CTOR RetainedRenderContext(IRootVisual* root, GroupVisual* visuals);

	virtual Graphics::RenderTarget* GetRT() override
	{
		return nullptr;
	}

	virtual void SetAntialiasPerPrimitive(bool antialias) override;

	virtual void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width) override;
	virtual void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width, StrokeStyle* style) override;
	virtual void FillRectangle(gm::RectF rect, Brush* brush) override;
	virtual void FillEllipse(float cx, float cy, float rx, float ry, Brush* brush) override;
	virtual void FillGeometry(const geometry& geom, Brush* brush) override;
	virtual void DrawRectangle(gm::RectF rect, Brush* brush, float strokeWidth) override;
	virtual void DrawEllipse(float cx, float cy, float rx, float ry, Brush* brush, float strokeWidth) override;
	virtual void DrawGeometry(const geometry& geom, Brush* brush, float width) override;
	virtual void OutputText(StringIn text, Brush* brush, StringIn fontFamily, float fontSize, int fontWeight = 400) override;
	virtual void OutputText(StringIn text, Brush* brush, TextFormat* textFormat, gm::RectF layoutRect) override;
	virtual void DrawVisual(Visual* visual) override;

	void DrawBitmap(IBitmapSource* bitmap);

	virtual void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor) override;
	virtual void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor, const gm::RectF& srcRect) override;
	virtual void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity) override;
	virtual void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity, const gm::RectF& srcRect) override;

	virtual void Pop() override;
	virtual void PushTransform(Transform* transform) override;
	virtual void PushTransform(const gm::matrix3f& transform) override;

	void PushClip(const geometry& clip);

// Retained with expressions
	void PushTransform(Expressive::typed_expression<Transform*> transform);
	void StrokeGeometry(Expressive::typed_expression<Geometry*> geom, Expressive::typed_expression<Brush*> brush, Expressive::typed_expression<float> width);
	void FillGeometry(Expressive::typed_expression<Geometry*> geom, Expressive::typed_expression<Brush*> brush);
	void DrawLine(typed<float> x1, typed<float> y1, typed<float> x2, typed<float> y2, typed<Brush*> brush, typed<float> width);
	void OutputText(typed<String> text, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight);
	void OutputText(typed<String> text, typed<ITextSource*> textsource, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight);

	IRootVisual* m_root;
	GroupVisual* m_visuals;
	stack<GroupVisual*> m_stack;
};

}	// Gui
}	// System
