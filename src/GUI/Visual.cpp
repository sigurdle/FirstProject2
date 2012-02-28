#include "stdafx.h"
#include "GUI2.h"

#include "physics.h"

namespace System
{
namespace Gui
{

D2D1_POINT_2F cnv(gm::PointF point)
{
	D2D1_POINT_2F p;
	p.x = point.X;
	p.y = point.Y;
	return p;
}

gm::PointF cnv(D2D1_POINT_2F point)
{
	return gm::PointF(point.x, point.y);
}

	/*
ID3D10Effect* Direct10::s_effect;
ID3D10EffectTechnique* Direct10::s_RenderTextureTechnique;
ID3D10EffectTechnique* Direct10::s_RenderTextureMaskTechnique;
ID3D10EffectMatrixVariable* Direct10::s_modelViewProjectionVariable;
ID3D10EffectShaderResourceVariable* Direct10::s_texture0Variable;
ID3D10EffectMatrixVariable* Direct10::s_textureMatrix0Variable;

ID3D10InputLayout* Direct10::s_vertexLayout0;
ID3D10InputLayout* Direct10::s_vertexLayout1;
ID3D10InputLayout* Direct10::s_vertexLayout2;
*/
	/*
void Bitmap::Create(int width, int height)
{
	// Create the render target texture
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
//	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;

	ID3D10Texture2D *pRenderTarget = NULL;
	PlatformWindow::get_D3D10Device()->CreateTexture2D(&desc, NULL, &pRenderTarget);
}
*/

IMP_DEPENDENCY_PROPERTY(UIElement*, Visual, Parent, nullptr/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(UIElement*, Visual, LogicalParent, nullptr/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(Visual*, Visual, NextSibling, nullptr/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(Visual*, Visual, PreviousSibling, nullptr/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(Window*, Visual, ParentWindow, nullptr/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY1(Transform*, Visual, Transform, nullptr, new PropertyMetadata(true))
IMP_DEPENDENCY_PROPERTY(geometry, Visual, VisibleGeometry, nullptr/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(geometry, Visual, HitGeometry, nullptr/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(float, Visual, Opacity, 1.0f)
IMP_DEPENDENCY_PROPERTY1(Brush*, Visual, OpacityMask, nullptr, new PropertyMetadata(true))
IMP_DEPENDENCY_PROPERTY1(geometry, Visual, Clip, nullptr, new PropertyMetadata(true))
IMP_DEPENDENCY_PROPERTY(bool, Visual, Antialias, true)
IMP_DEPENDENCY_PROPERTY(bool, Visual, IsVisible, true)
IMP_DEPENDENCY_PROPERTY(int, Visual, ChildPosition, -1)
IMP_DEPENDENCY_PROPERTY(int, Visual, TreeLevel, -1)

IMP_DEPENDENCY_PROPERTY(UIElement*, Visual, TemplatedOwner, nullptr/*, new PropertyMetadata()*/);

DependencyClass* Visual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_TemplatedOwnerProperty(),

		get_ParentProperty(),
		get_LogicalParentProperty(),
		get_NextSiblingProperty(),
		get_PreviousSiblingProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
		get_IsVisibleProperty(),
		get_ChildPositionProperty(),
		get_TreeLevelProperty(),
	};

	return &depclass;
}

Visual::Visual(DependencyClass* depClass) : Element(depClass)
{
}

size_t Visual::GetChildrenCount()
{
	return 0;
}

Visual* Visual::GetChild(size_t index)
{
	raise(ArgumentOutOfRangeException());
}

void Visual::SetTreeLevel(int level)
{
	set_TreeLevel(level);

	++level;

	size_t nchildren =  GetChildrenCount();
	for (size_t i = 0; i < nchildren; ++i)
	{
		Visual* child = GetChild(i);

		child->SetTreeLevel(level);
	}
}

void Visual::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	IRootVisual* root = GetRoot();

	if (root)
	{
		root->InvalidateRender();
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

Point Visual::WindowToElement(float ScreenX, float ScreenY)
{
	return Point(ScreenX, ScreenY);
}

geometry Visual::MakeVisibleGeometry(geometry clip)
{
	clip &= get_Clip();

	geometry geom = GetHitGeometry();
	clip &= geom;

	int nchildren = GetChildrenCount();
	for (int i = nchildren-1; i >= 0; --i)
	{
		Visual* child = GetChild(i);

		geometry geom2 = child->MakeVisibleGeometry(clip);

		clip |= geom2;
	}

	set_VisibleGeometry(clip);
	return clip;
}

bool Visual::IsDescendantOf(Visual* pVisual)
{
	UIElement* pParent = get_Parent();

	if (pParent == NULL)
		return false;

	if (pParent == pVisual)
		return true;

	return pParent->IsDescendantOf(pVisual);
}

bool Visual::IsAscendantOf(Visual* pVisual)
{
	if (pVisual == NULL) return false;
	return pVisual->IsDescendantOf(this);
}

#if 0
void Visual::RenderToTarget(GL::RenderTarget* rt, ID3D10Texture2D* tempTexture, ID3D10RenderTargetView* tempRenderTargetView, int scaledWidth, int scaledHeight, float scaleX, float scaleY)
{
	/*
	GL::RenderTarget rt2;
	rt2.m_gi = gi;
	rt2.m_d3d10 = dynamic_cast<LDraw::Direct3D10_I*>(gi);
	rt2.m_opengl = dynamic_cast<LDraw::OpenGL_I*>(gi);
	*/

	/*
	IDXGISurface* dxgiSurface;
	m_rt->m_renderTargetTexture->QueryInterface(__uuidof(IDXGISurface), reinterpret_cast<void**>(&dxgiSurface));
	ASSERT(dxgiSurface);

	GL::RenderTargetStoreState state;
	rt->BeginDraw(&state);

//	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // RGBA
//	rt->ClearRenderTargetView(tempRenderTargetView, ClearColor);
*/

	D3D10_VIEWPORT vp;
	vp.Width = scaledWidth;
	vp.Height = scaledHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	rt->m_d3d10->m_device->RSSetViewports(1, &vp);

//	ID2D1RenderTarget* oldSpRT = rt2.m_d3d10->m_spRT;
//	rt->m_d3d10->m_spRT = NULL;

	{
		Gui::ImmediateRenderContext rcontext(rt);
		rcontext.m_rt->m_projection = LDraw::matrix4f::getOrtho2D(0, scaledWidth, scaledHeight, 0);
		rcontext.m_rt->m_modelView = LDraw::matrix4f::getIdentity();

#if 0
		if (GL::Direct10::get_D3DDevice1())
		{
			HRESULT hr = GL::Direct10::get_D2DFactory()->CreateDxgiSurfaceRenderTarget(dxgiSurface, 
				D2D1::RenderTargetProperties(
					D2D1_RENDER_TARGET_TYPE_HARDWARE,//D2D1_RENDER_TARGET_TYPE_DEFAULT,
					D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM/*DXGI_FORMAT_UNKNOWN*/, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
				&rcontext.m_rt->m_spRT);
			ASSERT(SUCCEEDED(hr));
		}

		if (rcontext.GetRT()->m_spRT)
		{
			rcontext.GetRT()->m_spRT->BeginDraw();
		}
#endif

		D2D1_MATRIX_3X2_F transform =
		{
			1, 0,
			0, 1,
			-0, -0
		//	-m_expandedBBox.X, -m_expandedBBox.Y
		};
		if (rcontext.GetRT()->m_spRT)
		{
			rcontext.GetRT()->m_spRT->SetTransform(transform);
		}

	//	Render_(NULL/*pC*/, outImage, &rcontext, m_scaleX, m_scaleY, false, false);
		Render_(&rcontext);

		if (rcontext.GetRT()->m_spRT)
		{
			rcontext.GetRT()->m_spRT->EndDraw();
			rcontext.GetRT()->m_spRT->Flush();	// TODO, not
		//	rcontext.GetRT()->m_d3d10->m_spRT->Release();
		}
	}

//	rt2.m_spRT = oldSpRT;

	dxgiSurface->Release();
}
#endif

Graphics::Bitmap* Visual::GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY)
{
	ID3D10Device* device;
	if (rt)
		device = rt->m_d3d10->m_device;
	else
		device = Graphics::Direct10::get_D3DDevice();

	/*
	ID3D10Texture2D* tempTexture = NULL;
	ID3D10ShaderResourceView* tempShaderResourceView = NULL;
	ID3D10RenderTargetView* tempRenderTargetView = NULL;

	// Create the render target texture and view
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = scaledWidth;
	desc.Height = scaledHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;

	device->CreateTexture2D(&desc, NULL, &tempTexture);

	D3D10_RENDER_TARGET_VIEW_DESC rtDesc;
	rtDesc.Format = desc.Format;
	rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	rtDesc.Texture2D.MipSlice = 0;
	device->CreateRenderTargetView(tempTexture, &rtDesc, &tempRenderTargetView);

	D3D10_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = desc.Format;
	srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(tempTexture, &srDesc, &tempShaderResourceView);

	LDraw::Bitmap* outImage = new LDraw::Bitmap(scaledWidth, scaledHeight, 0, LDraw::PixelFormat_t::RGBAP_32, NULL);
	outImage->m_d3d10_texture = tempTexture;
	outImage->m_d3d10_texture->AddRef();

	outImage->m_d3d10_renderTargetView = tempRenderTargetView;
	outImage->m_d3d10_renderTargetView->AddRef();

	outImage->m_d3d10_shaderResourceView = tempShaderResourceView;
	outImage->m_d3d10_shaderResourceView->AddRef();

//	RenderToTarget(&GL::RenderTarget(rt->m_gi), tempTexture, tempRenderTargetView, scaledWidth, scaledHeight, scaleX, scaleY);

	GL::RenderTarget rt2(rt->m_gi, tempTexture, tempRenderTargetView);
*/

	Graphics::D3D10Texture2D texture(device, scaledWidth, scaledHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	Graphics::Bitmap* outImage = new Graphics::Bitmap(device, texture);
	//scaledWidth, scaledHeight, 0, LDraw::PixelFormat_t::RGBAP_32, NULL);

	Graphics::RenderTarget rt2(Graphics::Direct3D10_I::GetCurrent(), outImage->m_d3d10_texture, outImage->GetD3D10RenderTargetView());

	Graphics::RenderTargetStoreState state;
	rt2.BeginDraw(&state);

	Gui::ImmediateRenderContext rcontext(&rt2);
	Render_(&rcontext);

	rt2.EndDraw(&state);
//	rt2.m_spRT->Flush();
	if (rt2.m_spRT) rt2.m_spRT->Release();

	/*
	tempRenderTargetView->Release();
	tempTexture->Release();
	tempShaderResourceView->Release();
	*/

	return outImage;
#if 0
	LDraw::Bitmap* outImage = new LDraw::Bitmap(m_scaledWidth, m_scaledHeight, 0, LDraw::PixelFormat_t::RGBAP_32, NULL);

	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pO->m_device);

	HRESULT hr;

	IDirect3DTexture9* pTexture = NULL;
	IDirect3DSurface9* pTextureSurface = NULL;
	IDirect3DSurface9* pMultiSampleSurface = NULL;
	IDirect3DSurface9* pRenderTargetSurface = NULL;

	hr = pD3D9->m_d3dDevice->CreateTexture(m_scaledWidth, m_scaledHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture, NULL);
//	pD3D9->m_d3dDevice->CreateTexture(m_scaledWidth, m_scaledHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8, D3DPOOL_DEFAULT, &pTexture, NULL);
	ASSERT(pTexture);
	pTexture->GetSurfaceLevel(0, &pTextureSurface);

	outImage->m_texture = LDraw::Texture(pO->m_device, pTexture);

	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_4_SAMPLES;
//	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONMASKABLE;
	int quality = 0;

	if (MultiSample == D3DMULTISAMPLE_NONE)	// Create texture directly as RenderTarget
	{
		pRenderTargetSurface = pTextureSurface;
	}
	else	 // Create multisample RenderTarget
	{
		hr = pD3D9->m_d3dDevice->CreateRenderTarget(m_scaledWidth, m_scaledHeight, D3DFMT_A8R8G8B8, MultiSample, quality, FALSE/*lockable*/, &pMultiSampleSurface, NULL);
		ASSERT(pMultiSampleSurface);

		pRenderTargetSurface = pMultiSampleSurface;
	}

	IDirect3DSurface9* pOldRenderTarget;
	pD3D9->m_d3dDevice->GetRenderTarget(0, &pOldRenderTarget);

	pD3D9->m_d3dDevice->SetRenderTarget(0, pRenderTargetSurface);

	pD3D9->m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0);

//	LDraw::Direct3D9_I* device2 = new LDraw::Direct3D9_I(m_d3dDevice);
//	m_pGraphicsO->m_device = device2;

	if (true)
	{
		LDraw::Commands* commands = new LDraw::Commands;
		LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(pO->m_device, pO->m_bufferData, commands);
		UI::Graphics graphics(pMetafile);

		CHTMRenderContext rcontext;
		rcontext.m_clip = LDraw::RectF(0, 0, /*m_pReferencingElement->*/m_filterRect.Width, /*m_pReferencingElement->*/m_filterRect.Height);
		/*m_pReferencingElement->*/Render4(&rcontext, outImage, &graphics, m_scaleX, m_scaleY, false, false);

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PushMatrix();
		pD3D9->SetTransform(LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/));

		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PushMatrix();
		pD3D9->IdentityTransform();

		pO->PushTransform();
	//	pO->SetTransform(LDraw::Matrix3f::GetIdentity());
		pO->SetTransform(LDraw::Matrix3f::GetTranslate(-m_expandedBBox.X, -m_expandedBBox.Y));

	//	pD3D9->m_d3dDevice->BeginScene();
		pO->RenderCommands(commands);
	//	pD3D9->m_d3dDevice->EndScene();

		pO->PopTransform();

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PopMatrix();
		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PopMatrix();
	}
	else
	{
	//	Direct3D9_I
		LDraw::BufferData* bufferData = new LDraw::BufferData;
		LDraw::Direct3D9_I* device2 = new LDraw::Direct3D9_I(pD3D9->m_d3dDevice);

		LDraw::Commands* commands = new LDraw::Commands;
		LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(device2, bufferData, commands);
		UI::Graphics graphics(pMetafile);

		CHTMRenderContext rcontext;
		rcontext.m_clip = LDraw::RectF(0, 0, /*m_pReferencingElement->*/m_filterRect.Width, /*m_pReferencingElement->*/m_filterRect.Height);
		/*m_pReferencingElement->*/Render4(&rcontext, outImage, &graphics, m_scaleX, m_scaleY, false, false);

		LDraw::GraphicsO gO;
		
		gO.m_res = pO->m_res;
		/*
		gO.m_d3d9_effect = pO->m_d3d9_effect;
		gO.m_d3d9_technique0 = pO->m_d3d9_technique0;
		gO.m_d3d9_technique1 = pO->m_d3d9_technique1;
		gO.m_d3d9_technique2 = pO->m_d3d9_technique2;
		gO.m_d3d9_technique4 = pO->m_d3d9_technique4;

		gO.m_vertexDeclaration0 = pO->m_vertexDeclaration0;
		gO.m_vertexDeclaration1 = pO->m_vertexDeclaration1;

		gO.m_d3d9_modelViewVariable = pO->m_d3d9_modelViewVariable;
		gO.m_d3d9_projectionVariable = pO->m_d3d9_projectionVariable;
		gO.m_d3d9_modelViewProjectionVariable = pO->m_d3d9_modelViewProjectionVariable;
		gO.m_d3d9_textureMatrix0Variable = pO->m_d3d9_textureMatrix0Variable;
		gO.m_d3d9_solidColorVariable = pO->m_d3d9_solidColorVariable;
		gO.m_d3d9_texture0Variable = pO->m_d3d9_texture0Variable;
		*/

		gO.m_device = device2;
		gO.m_bufferData = bufferData;

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PushMatrix();
		pD3D9->SetTransform(LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/));

		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PushMatrix();
		pD3D9->IdentityTransform();

		device2->SetMatrixMode(GL_PROJECTION);
		device2->SetTransform(LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/));
		device2->SetMatrixMode(GL_MODELVIEW);
		device2->IdentityTransform();

	//	pD3D9->m_d3dDevice->BeginScene();
		gO.RenderCommands(commands);
	//	pD3D9->m_d3dDevice->EndScene();

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PopMatrix();
		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PopMatrix();
	}

	pD3D9->m_d3dDevice->SetRenderTarget(0, pOldRenderTarget);

	if (pMultiSampleSurface)
	{
		HRESULT hr;
		hr = pD3D9->m_d3dDevice->StretchRect(pMultiSampleSurface, NULL, pTextureSurface, NULL, D3DTEXF_POINT);
		ASSERT(SUCCEEDED(hr));

		pMultiSampleSurface->Release();
	}

	pTextureSurface->Release();

	return outImage;
#endif
}

D2D1_MATRIX_3X2_F Visual::get_TransformMatrix()
{
	return m_transformMatrix;
}

D2D1_MATRIX_3X2_F Visual::get_TransformToWindowMatrix()
{
	return m_transformToWindowMatrix;
}

void Visual::InvalidateMeasure()
{
	if (!m_inMeasure)
	//if (m_measureValid)
	{
		m_measureValid = false;
		if (!m_inMeasureList)
		{
			if (Window* p = dynamic_cast<Window*>(GetRoot()))
			{
				m_inMeasureList = true;
				p->AddMeasure(dynamic_cast<UIElement*>(this), get_TreeLevel());
			}
			else if (Window* p = dynamic_cast<Window*>(this))
			{
				m_inMeasureList = true;
				p->AddMeasure(dynamic_cast<UIElement*>(this), get_TreeLevel());
			}
		}
	}

#if 0
	if (m_bMeasureValid)
//	if (!m_bInMeasureList/* && m_availSize.Width != -1*/)
	{
		int level = GetLevel(this);

		VERIFY(!m_bInMeasureList);
		m_bMeasureValid = false;
		m_bInMeasureList = true;
	//	pLayoutManager->AddMeasure(this, level);
		GetOwnerWindow()->m_pSite->AddMeasure(this, level);

		if (!m_bInArrangeList)	// hmm ???
		{
			ASSERT(!m_bInArrangeList);
			m_bArrangeValid = false;
			m_bInArrangeList = true;
			GetOwnerWindow()->m_pSite->AddArrange(this, level);
		}
	}
#endif
}

void Visual::InvalidateArrange()
{
	if (!m_inMeasure && !m_inArrange)
//	if (m_arrangeValid)
	{
		m_arrangeValid = false;

		if (!m_inArrangeList)
		{
			if (Window* p = dynamic_cast<Window*>(GetRoot()))
			{
				m_inArrangeList = true;
				p->AddArrange(dynamic_cast<UIElement*>(this), get_TreeLevel());
			}
			else if (Window* p = dynamic_cast<Window*>(this))
			{
				m_inArrangeList = true;
				p->AddArrange(dynamic_cast<UIElement*>(this), get_TreeLevel());
			}
		}
	}

#if 0

//	if (!m_bInArrangeList)
	if (m_arrangeValid)
	{
		int level = get_TreeLevel();

		if (!m_bInArrangeList)
		{
			VERIFY(!m_bInArrangeList);
			m_bArrangeValid = false;
			m_bInArrangeList = true;
			GetOwnerWindow()->m_pSite->AddArrange(this, level);
		}
	}
#endif
}

void Visual::InvalidateVisual()
{
	if (m_visuals)
	{
		if (m_visuals->get_Children())
		{
			m_visuals->get_Children()->m_items.clear();
		}
	}

	m_visualValid = false;

	IRootVisual* root = GetRoot();
	if (root)
	{
		root->InvalidateRender();
	}
}

Visual* Visual::FindElement(StringIn id)
{
	if (get_ID() == id)
	{
		return this;
	}

	size_t nchildren = GetChildrenCount();

	for (size_t i = 0; i < nchildren; ++i)
	{
		Visual* visual = GetChild(i);
		Visual* element = visual->FindElement(id);
		if (element) return element;
	}

	return nullptr;
}

void Visual::Render_(ManagedRenderContext renderContext)
{
	if (m_visualOffset.X || m_visualOffset.Y)
	{
		renderContext.PushTransform(gm::matrix3f::getTranslate(m_visualOffset.X, m_visualOffset.Y));
	}

	Transform* pTransform = get_Transform();
	if (pTransform)
	{
		renderContext.PushTransform(pTransform);
	}

	bool antialias = get_Antialias();
	renderContext.SetAntialiasPerPrimitive(antialias);

	Brush* opacityBrush = get_OpacityMask();
	geometry clip = get_Clip();

	if (opacityBrush != nullptr || clip != nullptr)
	{
		ComPtr<ID2D1Layer> pLayer;
		if (renderContext.m_p->GetRT()->m_spRT)
		{
			HRESULT hr = renderContext.m_p->GetRT()->m_spRT->CreateLayer(nullptr, &pLayer);
			ASSERT(SUCCEEDED(hr));

			D2D1_LAYER_PARAMETERS layer_params;
			layer_params.contentBounds = D2D1::InfiniteRect();

			if (clip != nullptr)
				layer_params.geometricMask = clip.GetD2DGeometry();
			else
				layer_params.geometricMask = nullptr;

			if (opacityBrush)
				layer_params.opacityBrush = opacityBrush->Create(renderContext.m_p, this);
			else
				layer_params.opacityBrush = nullptr;

			layer_params.maskAntialiasMode = D2D1_ANTIALIAS_MODE_PER_PRIMITIVE;
			layer_params.maskTransform = D2D1::Matrix3x2F::Identity();
			layer_params.opacity = get_Opacity();
		//	layer_params.layerOptions = D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE;
			layer_params.layerOptions = D2D1_LAYER_OPTIONS_NONE;

			renderContext.m_p->GetRT()->m_spRT->PushLayer(layer_params, pLayer);
		}

	//	LDraw::Bitmap* offscreenBitmap = GetBitmap(renderContext.m_p->GetRT(), 400, 400, 1, 1);

		Render(renderContext);

	//	delete offscreenBitmap;

		if (renderContext.m_p->GetRT()->m_spRT)
		{
			renderContext.m_p->GetRT()->m_spRT->PopLayer();
		}
	}
	else
	{
		if (m_effect)
		{
			gm::RectF destRect(0, 0, 400, 400);

			m_effect->m_root->Render(renderContext.m_p, destRect, gm::matrix4f::getIdentity(), gm::matrix4f::getOrtho2D(0, 400, 400, 0));
		}
		else
		{
			Render(renderContext);
		}
	}

	/*
	if (pTransform)
	{
		renderContext.Pop();
	}
	*/
}

UIElement* Visual::HitTest_(gm::PointF point)
{
	Transform* transform = get_Transform();

	if (transform)
	{
		point = transform->InverseTransformPoint(point);
	}

	point -= m_visualOffset;

	return HitTest(point);
}

void VisualInstance::Render(ManagedRenderContext renderContext)
{
	m_visual->SetRoot(GetRoot());
	renderContext.m_p->DrawVisual(m_visual);
}

// virtual
void Visual::OnSetParent(Visual* parent)
{
}

void Visual::AddChild(Visual* child)
{
	ASSERT(0);
}

void Visual::RemoveChild(Visual* child)
{
	ASSERT(0);
}

void Visual::RenderRetained(ManagedRetainedRenderContext renderContext)
{
	ASSERT(0);
}

/*
Object* TemplatedOwnerExpression::Evaluate(Expressive::EvalContext* context)
{
	return context->m_templatedOwner;
}

void TemplatedOwnerExpression::TraceCallback(Expressive::EvalContext* context, Expressive::ExpTrace& trace, Expressive::ITraceCallback* callback)
{
	TRACE("TemplatedOwner");
}
*/

/*
PropertyBinding::PropertyBinding(PropertyValue* upStreamProperty) : m_upStreamProperty(upStreamProperty)
{
}
*/

/*
void PropertyValue::Set(Object* value)
{
	list<Binding*>::iterator it = m_outBindings.begin();
	while (it != m_outBindings.end())
	{
		Binding* binding = *it;
		++it;

		binding->set(value);
	}
}
*/

/*
Object* ObjectTemplate::Evaluate(Expressive::EvalContext* context)
{
	ASSERT(0);
	//return Create(context->m_templateOwner);
	return NULL;
}
*/

#if 0
tSetPropertyGroup tSetProperty::operator, (tSetProperty prop)
{
	tSetPropertyGroup group(new SetPropertyGroup());
	group.m_p->m_items.push_back(m_p);
	group.m_p->m_items.push_back(prop.m_p);
	return group;
}
#endif

// static
Expressive::Expression* get_Width()
{
	return nullptr;
}

// static
Expressive::Expression* get_Height()
{
	return nullptr;
}

GUIEXT void Edit(TextDocument* td)
{
	TextVisual* tv = new TextVisual;
	tv->set_TextSource(td);
	Window* win = new Window(tv);
	win->set_Width(600);
	win->set_Height(500);
	win->Show();
}

DependencyClass* VisualInstance::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

}	// Gui
}	// System
