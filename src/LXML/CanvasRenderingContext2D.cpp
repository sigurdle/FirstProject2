#include "stdafx.h"
#include "LXML.h"
//#include "HTMLCanvasElement.h"

// TODO, shouldn't be needed ?
// Direct2D
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

namespace System
{
namespace Web
{

CanvasRenderingContext2D::CanvasRenderingContext2D(IWebCanvas* canvas) : m_canvas(canvas)
{
}

IWebCanvas* CanvasRenderingContext2D::get_canvas()
{
	return m_canvas;
}

// state
void CanvasRenderingContext2D::save() // push state on state stack
{
	m_state.push(m_state.top());
}

void CanvasRenderingContext2D::restore() // pop state stack and restore stat
{
	m_state.pop();
}

// transformations (default transform is the identity matrix)
void CanvasRenderingContext2D::scale(float x, float y)
{
	state().m_transform = state().m_transform * D2D1::Matrix3x2F::Scale(x, y);
}

void CanvasRenderingContext2D::rotate(float angle)
{
	state().m_transform = state().m_transform * D2D1::Matrix3x2F::Rotation(angle);
}

void CanvasRenderingContext2D::translate(float x, float y)
{
	state().m_transform = state().m_transform * D2D1::Matrix3x2F::Translation(x, y);
}

void CanvasRenderingContext2D::transform(float m11, float m12, float m21, float m22, float dx, float dy)
{
	state().m_transform = state().m_transform * D2D1::Matrix3x2F(m11, m12, m21, m22, dx, dy);
}

void CanvasRenderingContext2D::setTransform(float m11, float m12, float m21, float m22, float dx, float dy)
{
	state().m_transform._11 = m11;
	state().m_transform._12 = m12;
	state().m_transform._21 = m21;
	state().m_transform._22 = m22;
	state().m_transform._31 = dx;
	state().m_transform._32 = dy;
}

/*
The globalAlpha attribute gives an alpha value that is applied to shapes and images before they are composited onto the canvas. The value must be in the range from 0.0 (fully transparent) to 1.0 (no additional transparency). If an attempt is made to set the attribute to a value outside this range, the attribute must retain its previous value. When the context is created, the globalAlpha attribute must initially have the value 1.0. 
*/

// compositing
float CanvasRenderingContext2D::get_globalAlpha() // (default 1.0)
{
	return state().m_globalAlpha;
}

void CanvasRenderingContext2D::set_globalAlpha(float globalAlpha) // (default 1.0)
{
	if (globalAlpha >= 0.0f && globalAlpha <= 1.0f)
	{
		state().m_globalAlpha = globalAlpha;
	}
}

String CanvasRenderingContext2D::get_globalCompositeOperation() // (default source-over)
{
	return nullptr;
}

void CanvasRenderingContext2D::set_globalCompositeOperation(StringIn) // (default source-over)
{
}

// colors and styles
Object* CanvasRenderingContext2D::get_strokeStyle() // (default black)
{
	return nullptr;
}

Object* CanvasRenderingContext2D::get_fillStyle() // (default black)
{
	return NULL;
}

void CanvasRenderingContext2D::set_fillStyle(Object* value)
{
	if (StringObject* str = dynamic_cast<StringObject*>(value))
	{
		ASSERT(0);
	}
	else if (CanvasGradient* gradient = dynamic_cast<CanvasGradient*>(value))
	{
		ASSERT(0);
	}
	else if (CanvasGradient* gradient = dynamic_cast<CanvasGradient*>(value))
	{
		ASSERT(0);
	}
}

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
void CanvasRenderingContext2D::clearRect(float x, float y, float w, float h)
{
}

void CanvasRenderingContext2D::fillRect(float x, float y, float w, float h)
{
	m_renderContext->FillRectangle(gm::RectF(x, y, w, h), state().m_fill.m_brush);
}

void CanvasRenderingContext2D::strokeRect(float x, float y, float w, float h)
{
	ASSERT(0);
//	m_renderContext->DrawRectangle(LDraw::RectF(x, y, w, h), state().m_stroke.m_brush);
}

// path API
void CanvasRenderingContext2D::beginPath()
{
}

void CanvasRenderingContext2D::closePath()
{
}

void CanvasRenderingContext2D::moveTo(float x, float y)
{
}

void CanvasRenderingContext2D::lineTo(float x, float y)
{
}

#if 0
virtual void quadraticCurveTo(float cpx, float cpy, float x, float y);
virtual void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
virtual void arcTo(float x1, float y1, float x2, float y2, float radius);
virtual void rect(float x, float y, float w, float h);
virtual void arc(float x, float y, float radius, float startAngle, float endAngle, in boolean anticlockwise);
#endif

void CanvasRenderingContext2D::fill()
{
}

void CanvasRenderingContext2D::stroke()
{
}

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
void CanvasRenderingContext2D::drawImage(IImageProviderElement* image, float dx, float dy)
{
}

void CanvasRenderingContext2D::drawImage(IImageProviderElement* image, float dx, float dy, float dw, float dh)
{
}

void CanvasRenderingContext2D::drawImage(IImageProviderElement* image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh)
{
}

/*
void CanvasRenderingContext2D::drawImage(HTMLCanvasElement* image, float dx, float dy)
{
}

void CanvasRenderingContext2D::drawImage(HTMLCanvasElement* image, float dx, float dy, float dw, float dh)
{
}

void CanvasRenderingContext2D::drawImage(HTMLCanvasElement* image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh)
{
}
*/
#if 0
// pixel manipulation
ImageData createImageData(float sw, float sh);
ImageData getImageData(float sx, float sy, float sw, float sh);
void putImageData(in ImageData imagedata, float dx, float dy);
void putImageData(in ImageData imagedata, float dx, float dy, float dirtyX, float dirtyY, float dirtyWidth, float dirtyHeight);
#endif

}	// Web
}	// System
