#include "stdafx.h"
#include "GUI2.h"

namespace System
{

namespace gm
{

GUIEXT gm::matrix4f mat4(const gm::matrix3f& transform)
{
	return gm::matrix4f(transform[0][0], transform[0][1], 0, 0,
						transform[1][0], transform[1][1], 0, 0,
						0, 0, 1, 0,
						transform[2][0], transform[2][1], 0, 1);
}

}

namespace Gui
{

TextFormat::TextFormat(StringIn fontFamily, float fontSize, int fontWeight)
{
	Graphics::Direct10::get_DWriteFactory()->CreateTextFormat(
		fontFamily.c_strw(),							// Font family name.
		nullptr,								// Font collection (NULL sets it to use the system font collection).
		(DWRITE_FONT_WEIGHT)fontWeight,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"en-us",
		&m_pDWriteTextFormat
		);
}

////////////////

ImmediateRenderContext::ImmediateRenderContext(Graphics::RenderTarget* rt) :
	m_rt(rt),
	m_transform(gm::matrix3f::getIdentity()),
	m_nLight(0)
{
}

	/*
ImmediateRenderContext::ImmediateRenderContext(ImmediateRenderContext* parent) :
//	m_parent(parent),
	m_rt(parent->m_rt),
	m_transform(gm::matrix3f::getIdentity()),
	m_nLight(parent->m_nLight)
{
}
*/

void ImmediateRenderContext::SetAntialiasPerPrimitive(bool antialias)
{
	if (GetRT()->m_spRT)
	{
		GetRT()->m_spRT->SetAntialiasMode(antialias? D2D1_ANTIALIAS_MODE_PER_PRIMITIVE: D2D1_ANTIALIAS_MODE_ALIASED);
	}
}

D3DXMATRIX& ImmediateRenderContext::modelViewMatrix()
{
	/*
	if (!m_modelViewMatrix_Valid)
	{
		m_modelViewMatrix_Valid = true;
		m_modelViewMatrix = m_modelMatrix * viewMatrix();
	}
	*/

	return m_modelViewMatrix;
}

D3DXMATRIX& ImmediateRenderContext::modelViewProjectionMatrix()
{
	if (!m_modelViewProjectionMatrix_Valid)
	{
		m_modelViewProjectionMatrix_Valid = true;
		m_modelViewProjectionMatrix = m_modelViewMatrix * m_projectionMatrix;
	}

	return m_modelViewProjectionMatrix;
}

D3DXMATRIX& ImmediateRenderContext::modelViewIMatrix()
{
	if (!m_modelViewIMatrix_Valid)
	{
		float determinant;
		D3DXMatrixInverse(&m_modelViewIMatrix, &determinant, &m_modelViewMatrix);

		m_modelViewIMatrix_Valid = true;
	}
	return m_modelViewIMatrix;
}

void ImmediateRenderContext::Pop()
{
	m_transform = m_transformStack.top();
	m_transformStack.pop();

	D2D_MATRIX_3X2_F d2d_transform =
	{
		m_transform[0][0], m_transform[0][1],
		m_transform[1][0], m_transform[1][1],
		m_transform[2][0], m_transform[2][1],
	};

	GetRT()->SetTransform(d2d_transform);
	GetRT()->m_transform3x3 = m_transform;
	GetRT()->m_modelView = mat4(m_transform);
	GetRT()->m_modelViewProjection = GetRT()->m_projection * GetRT()->m_modelView;
}

void ImmediateRenderContext::PushTransform(Transform* transform)
{
	m_transformStack.push(m_transform);
	m_transform = transform->get_Matrix() * m_transform;

	D2D_MATRIX_3X2_F d2d_transform =
	{
		m_transform[0][0], m_transform[0][1],
		m_transform[1][0], m_transform[1][1],
		m_transform[2][0], m_transform[2][1],
	};

	GetRT()->SetTransform(d2d_transform);
	GetRT()->m_transform3x3 = m_transform;
	GetRT()->m_modelView = mat4(m_transform);
	GetRT()->m_modelViewProjection = GetRT()->m_projection * GetRT()->m_modelView;
}

void ImmediateRenderContext::PushTransform(const gm::matrix3f& transform)
{
	m_transformStack.push(m_transform);
	m_transform = transform * m_transform;

	D2D_MATRIX_3X2_F d2d_transform =
	{
		m_transform[0][0], m_transform[0][1],
		m_transform[1][0], m_transform[1][1],
		m_transform[2][0], m_transform[2][1],
	};

	GetRT()->SetTransform(d2d_transform);
	GetRT()->m_transform3x3 = m_transform;
	GetRT()->m_modelView = mat4(m_transform);
	GetRT()->m_modelViewProjection = GetRT()->m_projection * GetRT()->m_modelView;
}

/*
void ImmediateRenderContext::PushTransform(const D2D_MATRIX_3X2_F& transform)
{
	m_transformStack.push(m_transform);
	m_transform = transform * m_transform;

	D2D_MATRIX_3X2_F d2d_transform =
	{
		m_transform[0][0], m_transform[0][1],
		m_transform[1][0], m_transform[1][1],
		m_transform[2][0], m_transform[2][1],
	};

	GetRT()->SetTransform(d2d_transform);
	GetRT()->m_transform3x3 = m_transform;
	GetRT()->m_modelView = mat4(m_transform);
	GetRT()->m_modelViewProjection = GetRT()->m_projection * GetRT()->m_modelView;
}
*/

void ImmediateRenderContext::DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width)
{
	if (brush)
	{
		ID2D1StrokeStyle* strokeStyle = nullptr;
		GetRT()->m_spRT->DrawLine(D2D1::Point2F(start.X, start.Y), D2D1::Point2F(end.X, end.Y), brush->Create(this, nullptr), width, strokeStyle);
	}
}

void ImmediateRenderContext::DrawLine(gm::PointF start, gm::PointF end, Brush* brush, float width, StrokeStyle* style)
{
	if (brush)
	{
		ID2D1StrokeStyle* strokeStyle = style->GetD2D1(GetRT());
		GetRT()->m_spRT->DrawLine(D2D1::Point2F(start.X, start.Y), D2D1::Point2F(end.X, end.Y), brush->Create(this, nullptr), width, strokeStyle);
	}
}

void ImmediateRenderContext::FillRectangle(gm::RectF rect, Brush* brush)
{
	if (brush)
	{
		D2D1_RECT_F r;
		r.left = rect.GetLeft();
		r.top = rect.GetTop();
		r.right = rect.GetRight();
		r.bottom = rect.GetBottom();

		GetRT()->m_spRT->FillRectangle(r, brush->Create(this, nullptr));
	}
}

void ImmediateRenderContext::FillEllipse(float cx, float cy, float rx, float ry, Brush* brush)
{
	if (brush)
	{
		D2D1_ELLIPSE ellipse;
		ellipse.point.x = cx;
		ellipse.point.y = cy;
		ellipse.radiusX = rx;
		ellipse.radiusY = ry;
		GetRT()->m_spRT->FillEllipse(ellipse, brush->Create(this, nullptr));
	}
}

void ImmediateRenderContext::DrawEllipse(float cx, float cy, float rx, float ry, Brush* brush, float strokeWidth)
{
	if (brush)
	{
		D2D1_ELLIPSE ellipse;
		ellipse.point.x = cx;
		ellipse.point.y = cy;
		ellipse.radiusX = rx;
		ellipse.radiusY = ry;

		ID2D1StrokeStyle* strokeStyle = nullptr;

		GetRT()->m_spRT->DrawEllipse(ellipse, brush->Create(this, nullptr), strokeWidth, strokeStyle);
	}
}

void ImmediateRenderContext::DrawRectangle(gm::RectF rect, Brush* brush, float width)
{
	if (brush)
	{
		D2D1_RECT_F d2rect;
		d2rect.left = rect.GetLeft();
		d2rect.top = rect.GetTop();
		d2rect.right = rect.GetRight();
		d2rect.bottom = rect.GetBottom();

		ID2D1StrokeStyle* strokeStyle = nullptr;

		GetRT()->m_spRT->DrawRectangle(d2rect, brush->Create(this, nullptr/*this*/), width, strokeStyle);
	}
}

void ImmediateRenderContext::FillGeometry(const geometry& geom, Brush* brush)
{
	if (brush)
	{
		GetRT()->m_spRT->FillGeometry(geom.GetD2DGeometry(), brush->Create(this, nullptr), nullptr);
	}
}

void ImmediateRenderContext::DrawGeometry(const geometry& geom, Brush* brush, float width)
{
	if (brush)
	{
		GetRT()->m_spRT->DrawGeometry(geom.GetD2DGeometry(), brush->Create(this, nullptr), width, nullptr);
	}
}

void ImmediateRenderContext::OutputText(StringIn text, Brush* brush, StringIn fontFamily, float fontSize, int fontWeight)
{
	ASSERT(0);
#if 0

	GetRT()->m_spRT->DrawText(text.GetData16(), text.GetLength(),
		pTextFormat,    // The text format.
		&layoutRect,       // The region of the window where the text will be rendered.
		brush->GetBrush()     // The brush used to draw the text.
    );
#endif
}

void ImmediateRenderContext::OutputText(StringIn text, Brush* brush, TextFormat* textFormat, gm::RectF layoutRect)
{
	IDWriteTextFormat* pTextFormat = textFormat->m_pDWriteTextFormat;

	D2D1_RECT_F d2layoutRect;
	d2layoutRect.left = layoutRect.GetLeft();
	d2layoutRect.top = layoutRect.GetTop();
	d2layoutRect.right = layoutRect.GetRight();
	d2layoutRect.bottom = layoutRect.GetBottom();

	// TODO: data16

	if (text.GetCharSize() == 2)
	{
		GetRT()->m_spRT->DrawText(text.GetData16(), text.GetLength32(),
			pTextFormat,    // The text format.
			&d2layoutRect,       // The region of the window where the text will be rendered.
			brush->Create(this, nullptr)     // The brush used to draw the text.
		);
	}
	else
	{
		GetRT()->m_spRT->DrawText(text.c_strw(), text.GetLength32(),
			pTextFormat,    // The text format.
			&d2layoutRect,       // The region of the window where the text will be rendered.
			brush->Create(this, nullptr)     // The brush used to draw the text.
		);
	}
}

void ImmediateRenderContext::DrawVisual(Visual* visual)
{
	visual->Render_(this);
}

void ImmediateRenderContext::DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor)
{
	ASSERT(0);
//	DrawBitmap(bitmap->GetBitmap(), dstRect, mulcolor);
}

void ImmediateRenderContext::DrawBitmap(IBitmapSource* bitmap, const gm::RectF& dstRect, gm::vector4f mulcolor, const gm::RectF& srcRect)
{
	ASSERT(0);
//	DrawBitmap(bitmap->GetBitmap(), dstRect, mulcolor);
}

void ImmediateRenderContext::DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity, const gm::RectF& srcRect)
{
	ID2D1Bitmap* d2d1bitmap = bitmap->GetD2D1Bitmap(GetRT());

	if (d2d1bitmap)
	{
		GetRT()->m_spRT->DrawBitmap(d2d1bitmap,
			D2D1::RectF(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom()),
			opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(srcRect.GetLeft(), srcRect.GetTop(), srcRect.GetRight(), srcRect.GetBottom()));
	}
}

void ImmediateRenderContext::DrawBitmap(Graphics::Bitmap* bitmap, const gm::RectF& dstRect, float opacity)
{
	if (false)
	{
		ID2D1Bitmap* d2d1bitmap = bitmap->GetD2D1Bitmap(GetRT());

		if (d2d1bitmap)
		{
			GetRT()->m_spRT->DrawBitmap(d2d1bitmap,
				D2D1::RectF(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom()),
				opacity,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
		}
	}
	else
	{
		// TODO: not like this
		GetRT()->m_modelView = m_transform;
		GetRT()->m_modelViewProjection = GetRT()->m_projection * GetRT()->m_modelView;

		Graphics::Direct10::s.Render(GetRT(), bitmap, dstRect, gm::vector4f(1, 1, 1, opacity));
	}
}

}	// Gui
}	// System
