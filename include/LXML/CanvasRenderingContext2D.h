namespace System
{
namespace Web
{

interface CanvasGradient
{
	virtual void addColorStop(float offset, StringIn color) abstract;
};

interface CanvasPattern
{
  // opaque object
};

interface ICanvasRenderingContext
{
	// back-reference to the canvas
	virtual IWebCanvas* get_canvas() abstract;
};

interface ICanvasRenderingContext2D : public ICanvasRenderingContext
{
	// state
	virtual void save() abstract; // push state on state stack
	virtual void restore() abstract; // pop state stack and restore state

	// transformations (default transform is the identity matrix)
	virtual void scale(float x, float y) abstract;
	virtual void rotate(float angle) abstract;
	virtual void translate(float x, float y) abstract;
	virtual void transform(float m11, float m12, float m21, float m22, float dx, float dy) abstract;
	virtual void setTransform(float m11, float m12, float m21, float m22, float dx, float dy) abstract;

	// compositing
	virtual float get_globalAlpha() abstract; // (default 1.0)
	virtual void set_globalAlpha(float) abstract; // (default 1.0)

	virtual String get_globalCompositeOperation() abstract; // (default source-over)
	virtual void set_globalCompositeOperation(StringIn) abstract; // (default source-over)

	// colors and styles
	virtual Object* get_strokeStyle() abstract; // (default black)
	virtual Object* get_fillStyle() abstract; // (default black)
	virtual void set_fillStyle(Object* fillStyle) abstract;
#if 0
	CanvasGradient createLinearGradient(float x0, float y0, float x1, float y1);
	CanvasGradient createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1);
	CanvasPattern createPattern(in HTMLImageElement image, in DOMString repetition);
	CanvasPattern createPattern(in HTMLCanvasElement image, in DOMString repetition);

	// line caps/joins
		   attribute float lineWidth; // (default 1)
		   attribute DOMString lineCap; // "butt", "round", "square" (default "butt")
		   attribute DOMString lineJoin; // "round", "bevel", "miter" (default "miter")
		   attribute float miterLimit; // (default 10)

	// shadows
		   attribute float shadowOffsetX; // (default 0)
		   attribute float shadowOffsetY; // (default 0)
		   attribute float shadowBlur; // (default 0)
		   attribute DOMString shadowColor; // (default transparent black)
#endif

	// rects
	virtual void clearRect(float x, float y, float w, float h) abstract;
	virtual void fillRect(float x, float y, float w, float h) abstract;
	virtual void strokeRect(float x, float y, float w, float h) abstract;

	// path API
	virtual void beginPath() abstract;
	virtual void closePath() abstract;
	virtual void moveTo(float x, float y) abstract;
	virtual void lineTo(float x, float y) abstract;
#if 0
	virtual void quadraticCurveTo(float cpx, float cpy, float x, float y);
	virtual void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
	virtual void arcTo(float x1, float y1, float x2, float y2, float radius);
	virtual void rect(float x, float y, float w, float h);
	virtual void arc(float x, float y, float radius, float startAngle, float endAngle, in boolean anticlockwise);
#endif
	virtual void fill() abstract;
	virtual void stroke() abstract;
#if 0
	virtual void clip();
	virtual boolean isPointInPath(float x, float y);

	// text
		   attribute DOMString font; // (default 10px sans-serif)
		   attribute DOMString textAlign; // "start", "end", "left", "right", "center" (default: "start")
		   attribute DOMString textBaseline; // "top", "hanging", "middle", "alphabetic", "ideographic", "bottom" (default: "alphabetic")
	void fillText(in DOMString text, float x, float y);
	void fillText(in DOMString text, float x, float y, float maxWidth);
	void strokeText(in DOMString text, float x, float y);
	void strokeText(in DOMString text, float x, float y, float maxWidth);
	TextMetrics measureText(in DOMString text);
#endif
	// drawing images
	virtual void drawImage(IImageProviderElement* image, float dx, float dy) abstract;
	virtual void drawImage(IImageProviderElement* image, float dx, float dy, float dw, float dh) abstract;
	virtual void drawImage(IImageProviderElement* image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh) abstract;
	/*
	virtual void drawImage(HTMLCanvasElement* image, float dx, float dy) abstract;
	virtual void drawImage(HTMLCanvasElement* image, float dx, float dy, float dw, float dh) abstract;
	virtual void drawImage(HTMLCanvasElement* image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh) abstract;
	*/
#if 0
	// pixel manipulation
	ImageData createImageData(float sw, float sh);
	ImageData getImageData(float sx, float sy, float sw, float sh);
	void putImageData(in ImageData imagedata, float dx, float dy);
	void putImageData(in ImageData imagedata, float dx, float dy, float dirtyX, float dirtyY, float dirtyWidth, float dirtyHeight);
#endif
};

class WEBEXT CanvasRenderingContext2D : public Object, public ICanvasRenderingContext2D
{
public:

	CTOR CanvasRenderingContext2D(IWebCanvas* canvas);

	// back-reference to the canvas
	virtual IWebCanvas* get_canvas() override;

	// state
	virtual void save(); // push state on state stack
	virtual void restore(); // pop state stack and restore state

	// transformations (default transform is the identity matrix)
	virtual void scale(float x, float y);
	virtual void rotate(float angle);
	virtual void translate(float x, float y);
	virtual void transform(float m11, float m12, float m21, float m22, float dx, float dy);
	virtual void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);

	// compositing
	virtual float get_globalAlpha(); // (default 1.0)
	virtual void set_globalAlpha(float); // (default 1.0)

	virtual String get_globalCompositeOperation(); // (default source-over)
	virtual void set_globalCompositeOperation(StringIn); // (default source-over)

	// colors and styles
	virtual Object* get_strokeStyle(); // (default black)
	virtual Object* get_fillStyle(); // (default black)
	virtual void set_fillStyle(Object* fillStyle);
#if 0
	CanvasGradient createLinearGradient(float x0, float y0, float x1, float y1);
	CanvasGradient createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1);
	CanvasPattern createPattern(in HTMLImageElement image, in DOMString repetition);
	CanvasPattern createPattern(in HTMLCanvasElement image, in DOMString repetition);

	// line caps/joins
		   attribute float lineWidth; // (default 1)
		   attribute DOMString lineCap; // "butt", "round", "square" (default "butt")
		   attribute DOMString lineJoin; // "round", "bevel", "miter" (default "miter")
		   attribute float miterLimit; // (default 10)

	// shadows
		   attribute float shadowOffsetX; // (default 0)
		   attribute float shadowOffsetY; // (default 0)
		   attribute float shadowBlur; // (default 0)
		   attribute DOMString shadowColor; // (default transparent black)
#endif

	// rects
	virtual void clearRect(float x, float y, float w, float h);
	virtual void fillRect(float x, float y, float w, float h);
	virtual void strokeRect(float x, float y, float w, float h);

	// path API
	virtual void beginPath();
	virtual void closePath();
	virtual void moveTo(float x, float y);
	virtual void lineTo(float x, float y);
#if 0
	virtual void quadraticCurveTo(float cpx, float cpy, float x, float y);
	virtual void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
	virtual void arcTo(float x1, float y1, float x2, float y2, float radius);
	virtual void rect(float x, float y, float w, float h);
	virtual void arc(float x, float y, float radius, float startAngle, float endAngle, in boolean anticlockwise);
#endif
	virtual void fill();
	virtual void stroke();
#if 0
	virtual void clip();
	virtual boolean isPointInPath(float x, float y);

	// text
		   attribute DOMString font; // (default 10px sans-serif)
		   attribute DOMString textAlign; // "start", "end", "left", "right", "center" (default: "start")
		   attribute DOMString textBaseline; // "top", "hanging", "middle", "alphabetic", "ideographic", "bottom" (default: "alphabetic")
	void fillText(in DOMString text, float x, float y);
	void fillText(in DOMString text, float x, float y, float maxWidth);
	void strokeText(in DOMString text, float x, float y);
	void strokeText(in DOMString text, float x, float y, float maxWidth);
	TextMetrics measureText(in DOMString text);
#endif
	// drawing images
	virtual void drawImage(IImageProviderElement* image, float dx, float dy);
	virtual void drawImage(IImageProviderElement* image, float dx, float dy, float dw, float dh);
	virtual void drawImage(IImageProviderElement* image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);
//	virtual void drawImage(HTMLCanvasElement* image, float dx, float dy);
//	virtual void drawImage(HTMLCanvasElement* image, float dx, float dy, float dw, float dh);
//	virtual void drawImage(HTMLCanvasElement* image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);

#if 0
	// pixel manipulation
	ImageData createImageData(float sw, float sh);
	ImageData getImageData(float sx, float sy, float sw, float sh);
	void putImageData(in ImageData imagedata, float dx, float dy);
	void putImageData(in ImageData imagedata, float dx, float dy, float dirtyX, float dirtyY, float dirtyWidth, float dirtyHeight);
#endif

	class Style
	{
	public:
		Object* m_object;
//		D2D1::ColorF m_color;
		Gui::Brush* m_brush;
	};

	class State
	{
	public:

		D2D1::Matrix3x2F m_transform;
		Style m_stroke;
		Style m_fill;
		float m_globalAlpha;
		float m_lineWidth;
		float m_miterLimit;
	};

private:

	inline State& state()
	{
		return m_state.top();
	}

	/*
	inline const State& state() const
	{
		return m_state.top();
	}
	*/

	stack<State> m_state;

	IWebCanvas* m_canvas;
	Gui::RenderContext* m_renderContext;
	ImageData* m_imageData;
};

}	// Web
}	// System
