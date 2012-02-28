namespace System
{
namespace Gui
{

class GUIEXT RenderContext : public Object
{
public:

	CTOR RenderContext();

	virtual Graphics::RenderTarget* GetRT() = 0;

	virtual void Pop() = 0;
	virtual void PushTransform(Transform* transform) = 0;
	virtual void PushTransform(const gm::matrix3f& transform) = 0;

	virtual void SetAntialiasPerPrimitive(bool antialias) = 0;

	virtual void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width) = 0;
	virtual void DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width, StrokeStyle* style) = 0;
	virtual void FillRectangle(gm::RectF rect, Brush* brush) = 0;
	virtual void FillEllipse(float cx, float cy, float rx, float ry, Brush* brush) = 0;
	virtual void FillGeometry(const geometry& geom, Brush* brush) = 0;
	virtual void DrawRectangle(gm::RectF rect, Brush* brush, float width) = 0;
	virtual void DrawEllipse(float cx, float cy, float rx, float ry, Brush* brush, float width) = 0;
	virtual void DrawGeometry(const geometry& geom, Brush* brush, float width) = 0;
	virtual void OutputText(StringIn text, Brush* brush, StringIn fontFamily, float fontSize, int fontWeight = 400) = 0;
	virtual void OutputText(StringIn text, Brush* brush, TextFormat* textFormat, gm::RectF layoutRect) = 0;
	virtual void DrawVisual(Visual* visual) = 0;
	virtual void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor) = 0;
	virtual void DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor, const gm::RectF& srcRect) = 0;
	virtual void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity) = 0;
	virtual void DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity, const gm::RectF& srcRect) = 0;

	gm::matrix4f m_colorTransform;
	gm::vector4f m_colorTranslate;
};

}	// Gui
}	// System
