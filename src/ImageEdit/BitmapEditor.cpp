#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

// static
Gui::DependencyClass* BitmapEditor::DrawBitmap::get_Class()
{
	static Gui::DependencyClass Class(typeid(DrawBitmap), baseClass::get_Class());
	return &Class;
}

// static
Gui::DependencyClass* BitmapEditor::get_Class()
{
	static Gui::DependencyClass Class(typeid(thisClass), baseClass::get_Class());

	static Gui::DependencyProperty* p[] =
	{
		get_ViewSelectionOutlineProperty(),
		get_ZoomFactorProperty(),
		get_ToolProperty(),
	};

	return &Class;
}

IMP_DEPENDENCY_PROPERTY(bool, BitmapEditor, ViewSelectionOutline, false)
IMP_DEPENDENCY_PROPERTY(float, BitmapEditor, ZoomFactor, 1.0f)
IMP_DEPENDENCY_PROPERTY(ImageTool*, BitmapEditor, Tool, Tools::get_Hand())

BitmapEditor::BitmapEditor() : UIElement(get_Class())
{
	m_elements = new Gui::Visuals;
	m_elements->SetRoot(this);

	m_drawBitmap = new DrawBitmap;
	m_drawBitmap->m_ed = this;
}

void BitmapEditor::set_Bitmap(Graphics::Bitmap* bitmap)
{
	ImageDocument* document = new ImageDocument;

	m_document = document;

	m_document->m_size = gm::SizeF(bitmap->GetWidth(), bitmap->GetHeight());

	m_elements->m_items.clear();

	m_compositeBitmaps[0] = CreateBitmap(bitmap->GetWidth(), bitmap->GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM);
	m_compositeBitmaps[1] = CreateBitmap(bitmap->GetWidth(), bitmap->GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM);

	m_compositeBitmap = m_compositeBitmaps[0];
	m_compositeRT = new Graphics::RenderTarget(Graphics::Direct3D10_I::GetCurrent(), m_compositeBitmap->m_d3d10_texture, m_compositeBitmap->m_d3d10_renderTargetView);

	Add(new Gui::DrawBitmapVisual(bitmap, gm::RectF(0, 0, bitmap->GetWidth(), bitmap->GetHeight())));

	UpdateBitmap();

	InvalidateVisual();

#if 0
	if (m_compositeBitmap != bitmap)
	{
		D3D10_TEXTURE2D_DESC desc;
		bitmap->m_d3d10_texture->GetDesc(&desc);

		if (!(desc.BindFlags & D3D10_BIND_RENDER_TARGET))
		{
			desc.Usage = D3D10_USAGE_DEFAULT;
			desc.BindFlags |= D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;

			ID3D10Texture2D* pTexture = NULL;
			HRESULT hr = GL::Direct10::get_D3DDevice()->CreateTexture2D(&desc, NULL, &pTexture);

			m_compositeBitmap = new LDraw::Bitmap(GL::Direct10::get_D3DDevice(), pTexture);
			m_compositeRT = new GL::RenderTarget(LDraw::Direct3D10_I::GetCurrent(), m_compositeBitmap->m_d3d10_texture, m_compositeBitmap->m_d3d10_renderTargetView);

			GL::Direct10::get_D3DDevice()->CopyResource(m_compositeBitmap->m_d3d10_texture, bitmap->m_d3d10_texture);

			/*
			float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // RGBA
			m_compositeRT->m_d3d10->m_device->ClearRenderTargetView(m_compositeRT->m_pRenderTargetView, clearColor);

			D3D10_VIEWPORT vp;
			vp.Width = bitmap->GetWidth();
			vp.Height = bitmap->GetHeight();
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			m_compositeRT->m_d3d10->m_device->RSSetViewports(1, &vp);

			m_compositeRT->m_projection = LDraw::matrix4f::getOrtho2D(0, bitmap->GetWidth(), bitmap->GetHeight(), 0);
			m_compositeRT->m_modelView = LDraw::matrix4f::getIdentity();
			m_compositeRT->m_modelViewProjection = m_compositeRT->m_projection * m_compositeRT->m_modelView;

			GL::Direct10::s.Imp::Render(m_compositeRT, bitmap, LDraw::RectF(0, 0, bitmap->GetWidth(), bitmap->GetHeight()));
			*/
		}
		else
		{
			m_compositeBitmap = bitmap;
			m_compositeRT = new GL::RenderTarget(LDraw::Direct3D10_I::GetCurrent(), m_compositeBitmap->m_d3d10_texture, m_compositeBitmap->m_d3d10_renderTargetView);
		}

		InvalidateVisual();
	}
#endif
}

void BitmapEditor::OnSetRoot(Gui::IRootVisual* root)
{
	Gui::TimeManager::manager.OnTick.Connect(EventHandler(this, &BitmapEditor::OnTimer));
}

void BitmapEditor::OnTimer(double)
{
	if (m_maskrender)
	{
		++m_marchingOffset;

		m_maskrender->m_patternSrcX = (float)m_marchingOffset;

		if (GetRoot())
		{
			GetRoot()->InvalidateRender();
		}
	}
}

void BitmapEditor::set_Mask(Mask* mask)
{
	m_currentMask = mask;
	InvalidateVisual();
}

Graphics::Bitmap* BitmapEditor::GetCompositeBitmap()
{
	return m_compositeBitmap;
}

Graphics::Bitmap* s_Texture;

Graphics::Bitmap* CreateCheckboardBitmap(int width, int height, Graphics::Color color0, Graphics::Color color1);

void BitmapEditor::RenderRetained(Gui::ManagedRetainedRenderContext renderContext)
{
	/*
	{
		static Gui::SolidColorBrush* brush = new Gui::SolidColorBrush(0.8f, 0.8f, 0.8f, 1.0f);
	renderContext.FillRectangle(LDraw::RectF(0, 0, 1000, 1000), brush);
	}
	*/

	if (!m_bitmapUpdated)
	{
		m_bitmapUpdated = true;
		UpdateBitmap();
	}

	Graphics::Bitmap* bitmap = GetCompositeBitmap();
	gm::RectF rect(0, 0, bitmap->GetWidth(), bitmap->GetHeight());

	renderContext.DrawBitmap(bitmap, rect, 1.0f);

	if (m_hitVisual)
	{
		static Gui::SolidColorBrush* brush = new Gui::SolidColorBrush(0, 0, 0.6, 1);

		if (Gui::FillGeometryVisual* g = dynamic_cast<Gui::FillGeometryVisual*>(m_hitVisual))
		{
			gm::RectF bounds = g->get_Geometry()->GetBounds();

			renderContext.DrawRectangle(bounds, brush, 1);
		}
		else
		{
			gm::RectF bounds = m_hitVisual->m_bounds;

			renderContext.PushTransform(m_hitVisual->get_Transform());
			renderContext.DrawRectangle(bounds, brush, 1);
			renderContext.Pop();
		}
	}

	if (m_currentMask)
	{
		m_maskrender = new MaskOutlineVisual;
		//LDraw::Bitmap* bitmap = m_document->m_selection->m_offscreenBitmap;

		if (s_Texture == NULL)
		{
			s_Texture = CreateCheckboardBitmap(12, 12, Graphics::Color(0,0,0), Graphics::Color(255,255,255));
		}

		m_maskrender->m_mask = m_currentMask;
		m_maskrender->m_pattern = s_Texture;
	//	pCmd->m_destRect = LDraw::RectF(0, 0, (float)m_bitmap->GetWidth(), (float)m_bitmap->GetHeight());
		m_maskrender->m_destRect = gm::RectF(0, 0, get_CanvasWidth(), get_CanvasHeight());
		m_maskrender->m_srcX = 0;
		m_maskrender->m_srcY = 0;
		m_maskrender->m_srcWidth = get_CanvasWidth();//bitmap->GetWidth();
		m_maskrender->m_srcHeight = get_CanvasHeight();//bitmap->GetHeight();

		m_maskrender->m_patternSrcX = (float)m_marchingOffset;

		renderContext.DrawVisual(m_maskrender);
	}
}

void BitmapEditor::UpdateBitmap()
{
	/*
	if (m_compositeRT->m_spRT)
	{
		m_compositeRT->m_spRT->Flush();
	}
	*/

	UINT oldnvp = 8;
	D3D11_VIEWPORT oldvp[8];
	m_compositeRT->m_d3d10->m_deviceContext->RSGetViewports(&oldnvp, oldvp);

	D3D11_VIEWPORT vp;
	vp.Width = m_compositeBitmap->GetWidth();
	vp.Height = m_compositeBitmap->GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_compositeRT->m_d3d10->m_deviceContext->RSSetViewports(1, &vp);

	m_compositeRT->m_projection = gm::matrix4f::getOrtho2D(0, m_compositeBitmap->GetWidth(), m_compositeBitmap->GetHeight(), 0);
	m_compositeRT->m_transform3x3 = gm::matrix3f::getIdentity();
	m_compositeRT->m_modelView = gm::matrix4f::getIdentity();
//	m_compositeRT->m_viewProjection = m_compositeRT->m_projection * m_compositeRT->m_modelView;
	m_compositeRT->m_modelViewProjection = m_compositeRT->m_projection * m_compositeRT->m_modelView;

	Graphics::RenderTargetStoreState state;
	m_compositeRT->BeginDraw(&state);

	m_compositeRT->m_d3d10->m_deviceContext->ClearRenderTargetView(m_compositeBitmap->m_d3d10_renderTargetView, gm::vector4f(0,0,0,0));

	Gui::ImmediateRenderContext imm(m_compositeRT);
 //	m_elements->Render_(&imm);

	for (auto it = m_elements->m_items.begin(); it != m_elements->m_items.end(); ++it)
	{
		Gui::Visual* v = *it;

		Gui::DrawBitmapVisual* bv = dynamic_cast<Gui::DrawBitmapVisual*>(v);
		if (bv)
		{
			Graphics::Bitmap* bitmap = bv->get_Bitmap();

			gm::RectF dstRect = bv->get_DestRect();

			imm.DrawBitmap(bitmap, dstRect, get_Opacity());

#if 0
		//	Graphics::Direct10::get_DeviceContext()->PSSetShader(m_normalShader);

			GetRT()->m_modelView = m_transform;
			GetRT()->m_modelViewProjection = GetRT()->m_projection * GetRT()->m_modelView;

			m_texture0Variable->SetResource(bitmap->GetD3D10ShaderResourceView());
			m_textureMatrix0Variable->SetMatrix((float*)(textureMatrix));

			m_colorMultiplyVariable->SetFloatVector((float*)colorMultiply);
			m_colorTranslateVariable->SetFloatVector((float*)colorTranslate);

			D3D10_TECHNIQUE_DESC techDesc;
			m_RenderTextureTechnique->GetDesc(&techDesc);

			for (UINT nPass = 0; nPass < techDesc.Passes; ++nPass)
			{
				m_RenderTextureTechnique->GetPassByIndex(nPass)->Apply(0);

				rt->m_d3d10->m_device->Draw(
					4, // VertexCount
					0 // StartVertexLocation
					);
			}

			Graphics::Direct10::s.Render(GetRT(), bitmap, dstRect, gm::vector4f(1, 1, 1, opacity));
#endif
		}
	}

	m_compositeRT->EndDraw(&state);

	m_compositeRT->m_d3d10->m_deviceContext->RSSetViewports(oldnvp, oldvp);

	m_compositeRT->m_d3d10->m_deviceContext->CopyResource(m_compositeBitmaps[1]->m_d3d10_texture, m_compositeBitmaps[0]->m_d3d10_texture);


#if 0
//	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // RGBA
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // RGBA
	m_compositeRT->m_d3d10->m_device->ClearRenderTargetView(m_compositeRT->m_pRenderTargetView, clearColor);

	D3D10_VIEWPORT vp;
	vp.Width = 500;
	vp.Height = 500;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_compositeRT->m_d3d10->m_device->RSSetViewports(1, &vp);

//	m_compositeRT->m_d3d10->m_device->OMSetDepthStencilState(GL::Direct10.s.m_pDepthStencilState[false], 0);

	m_compositeRT->m_projection = LDraw::matrix4f::getOrtho2D(0, 500, 500, 0);
	m_compositeRT->m_modelView = LDraw::matrix4f::getIdentity();
	m_compositeRT->m_modelViewProjection = m_compositeRT->m_projection * m_compositeRT->m_modelView;

	GL::RenderTargetStoreState state;
	m_compositeRT->BeginDraw(&state);

	Gui::ImmediateRenderContext rc(m_compositeRT);

	m_elements->Render(&rc);

	m_compositeRT->EndDraw(&state);
	m_compositeRT->m_spRT->Flush();
#endif
}

void BitmapEditor::Invalidate(gm::RectI* rect)
{
	GetRoot()->InvalidateRender();
}

void BitmapEditor::OnLeftMouseButtonDown(Gui::MouseButtonEventArgs* args)
{
	Gui::Point pt = args->GetClientPosition();	// TODO
	m_startpt = pt;
	m_oldpt = pt;

	if (false)
	{
		Gui::UIElement* hitVisual = m_elements->HitTest_(pt);

		m_hitVisual = hitVisual;
		InvalidateVisual();
	}

	if (ImageTool* tool = get_Tool())
	{
		tool->OnMouseDown(this, pt / get_ZoomFactor());
	}
}

void BitmapEditor::OnLeftMouseButtonUp(Gui::MouseButtonEventArgs* args)
{
	Gui::Point pt = args->GetClientPosition();	// TODO

	if (ImageTool* tool = get_Tool())
	{
		tool->OnMouseUp(this, pt / get_ZoomFactor());
	}

	/*
	if (m_dragging)
	{
		m_dragging = false;
		ReleaseMouseCapture();
	}
	*/
}

void BitmapEditor::Add(Gui::Visual* visual)
{
	m_elements->Add(visual);
//	UpdateBitmap();
}

void BitmapEditor::InvalidateRender()
{
	m_bitmapUpdated = false;
	InvalidateVisual();
	if (GetRoot())
	{
		GetRoot()->InvalidateRender();
	}
}

void BitmapEditor::OnMouseMove(Gui::MouseEventArgs* args)
{
	Gui::Point pt = args->GetClientPosition();	// TODO
	gm::PointF dpt = pt - m_oldpt;

	/*
	if (m_hitVisual)
	{
		if (m_dragging)
		{
			if (Gui::FillGeometryVisual* g = dynamic_cast<Gui::FillGeometryVisual*>(m_hitVisual))
			{
				gm::PointF oldcenter = gm::PointF(
					static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->get_CenterX(),
					static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->get_CenterY());

				gm::PointF newcenter = oldcenter + dpt;

				static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->set_CenterX(newcenter.X);
				static_cast<Gui::EllipseGeometry*>(g->get_Geometry())->set_CenterY(newcenter.Y);
			}
			else if (Gui::DrawBitmapVisual* g = dynamic_cast<Gui::DrawBitmapVisual*>(m_hitVisual))
			{
				float x = g->get_DestLeft();
				float y = g->get_DestTop();

				g->set_DestLeft(x + dpt.X);
				g->set_DestTop(y + dpt.Y);
			}

			InvalidateVisual();	// TODO remove
		}
	}
	else
	*/
	if (ImageTool* tool = get_Tool())
	{
		tool->OnMouseMove(this, pt / get_ZoomFactor());
	}

	m_oldpt = pt;
}

}	// ImageEdit
}	// System
