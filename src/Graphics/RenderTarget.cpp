#include "stdafx.h"
#include "Graphics.h"

#include <D3D9Types.h>

namespace System
{
namespace Graphics
{

RenderTarget::RenderTarget(GraphicsI* gi, IDXGISwapChain* swapChain, ID3D10RenderTargetView* pRenderTargetView)
{
	Create(gi, swapChain, pRenderTargetView);
}

RenderTarget::RenderTarget(GraphicsI* gi, ID3D10Texture2D* pRenderTargetTexture, ID3D10RenderTargetView* pRenderTargetView)
{
	Create(gi, pRenderTargetTexture, pRenderTargetView);
}

void RenderTarget::Create(GraphicsI* gi,
	IDXGISwapChain* swapChain,
	ID3D10RenderTargetView* pRenderTargetView
	)
{
	m_spRT = NULL;
	m_hWnd = NULL;
	m_gi = gi;
	m_d3d10 = dynamic_cast<Direct3D10_I*>(gi);
	m_opengl = dynamic_cast<OpenGL_I*>(gi);

	m_swapChain = swapChain;
	m_pRenderTargetTexture = NULL;//pRenderTargetTexture;
	m_pRenderTargetView = pRenderTargetView;

	if (m_d3d10->m_device1)
	{
		HRESULT hr;

		// Create Direct2D RenderTarget
		IDXGISurface* dxgiSurface;
		hr = m_swapChain->GetBuffer(0, __uuidof(dxgiSurface), reinterpret_cast<void**>(&dxgiSurface));

		hr = Direct10::get_D2DFactory()->CreateDxgiSurfaceRenderTarget(dxgiSurface, 
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_HARDWARE,//D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM/*DXGI_FORMAT_UNKNOWN*/, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
			&m_spRT);

		dxgiSurface->Release();
	}
}

void RenderTarget::Create(GraphicsI* gi,
	ID3D10Texture2D* pRenderTargetTexture,
	ID3D10RenderTargetView* pRenderTargetView
	)
{
	m_spRT = NULL;
	m_hWnd = NULL;
	m_gi = gi;
	m_d3d10 = dynamic_cast<Direct3D10_I*>(gi);
	m_opengl = dynamic_cast<OpenGL_I*>(gi);

	m_pRenderTargetTexture = pRenderTargetTexture;
	m_pRenderTargetView = pRenderTargetView;
	m_pDepthStencilView = NULL;

	if (m_d3d10->m_device1)
	{
		HRESULT hr;

		// Create Direct2D RenderTarget
		IDXGISurface* dxgiSurface;
		hr = pRenderTargetTexture->QueryInterface(__uuidof(dxgiSurface), reinterpret_cast<void**>(&dxgiSurface));

		hr = Direct10::get_D2DFactory()->CreateDxgiSurfaceRenderTarget(dxgiSurface, 
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_HARDWARE,//D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM/*DXGI_FORMAT_UNKNOWN*/, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
			&m_spRT);

		dxgiSurface->Release();
	}
}

RenderTarget::RenderTarget(ID2D1RenderTarget* d2d1RenderTarget)
{
	m_spRT = d2d1RenderTarget;
	m_gi = NULL;
	m_d3d10 = dynamic_cast<Direct3D10_I*>(m_gi);
	m_opengl = dynamic_cast<OpenGL_I*>(m_gi);

	m_pDepthStencilView = NULL;

	m_hWnd = NULL;
}

RenderTarget::RenderTarget(GraphicsI* gi, HWND hWnd, WindowSurfDesc& desc)
{

	if (Direct10::get_D3DDevice() == NULL)
	{
		raise(Exception(L"D3DDevice10 = NULL"));
	}

	m_spRT = NULL;
	m_gi = gi;
	m_d3d10 = dynamic_cast<Direct3D10_I*>(gi);
	m_opengl = dynamic_cast<OpenGL_I*>(gi);

	m_pDepthStencilView = NULL;

	m_hWnd = hWnd;

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	int clientWidth = clientRect.right;
	int clientHeight = clientRect.bottom;

	if (clientWidth == 0) clientWidth = 8;
	if (clientHeight == 0) clientHeight = 8;

	HRESULT hr;

	// Create SwapChain
	DXGI_SWAP_CHAIN_DESC sdesc;
	ZeroMemory(&sdesc, sizeof(sdesc));
	sdesc.BufferCount = 1;
	sdesc.BufferDesc.Width = clientWidth;
	sdesc.BufferDesc.Height = clientHeight;
	sdesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sdesc.BufferDesc.RefreshRate.Numerator = 60;
	sdesc.BufferDesc.RefreshRate.Denominator = 1;
	sdesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sdesc.OutputWindow = hWnd;
	sdesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
//	sdesc.SwapEffect = D3DSWAPEFFECT_FLIPEX;

	sdesc.SampleDesc.Count = 1;
	sdesc.SampleDesc.Quality = 0;
	sdesc.Windowed = TRUE;

//	ID3D10Device1* pDevice;
//	IDXGISwapChain* pSwapChain;

	hr = Direct10::s.m_DXGIFactory->CreateSwapChain(Direct10::get_D3DDevice1(), &sdesc, &m_swapChain);
	if (FAILED(hr))
	{
		raise(Exception("Failed to create swapchain"));
	}

	if (true)
	{
		ASSERT(m_pRenderTargetView == nullptr);
		// Create a render target view
		ID3D10Texture2D* pBackBuffer;
		hr = m_swapChain->GetBuffer(0, __uuidof(pBackBuffer), reinterpret_cast<void**>(&pBackBuffer));
		if (FAILED(hr))
		{
			raise(Exception("Failed to get swapchain backbuffer"));
		}
		D3D10_RENDER_TARGET_VIEW_DESC rtd;
		rtd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		if (sdesc.SampleDesc.Count > 1)
			rtd.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2DMS;
		else
			rtd.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;

		rtd.Texture2D.MipSlice = 0;

		hr = m_d3d10->m_device1->CreateRenderTargetView(pBackBuffer, &rtd, &m_pRenderTargetView);

		pBackBuffer->Release();

		if (true)
		{
			D3D10_TEXTURE2D_DESC descDepth;
			descDepth.Width = clientWidth;
			descDepth.Height = clientHeight;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D32_FLOAT;
			descDepth.SampleDesc.Count = sdesc.SampleDesc.Count;
			descDepth.SampleDesc.Quality = sdesc.SampleDesc.Quality;
			descDepth.Usage = D3D10_USAGE_DEFAULT;
			descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;
			hr = m_d3d10->m_device1->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
			if (FAILED(hr))
			{
				raise(Exception("CreateTexture2D Failed"));
			}

			// Create the depth-stencil state
			D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
			descDSV.Format = descDepth.Format;
		//	descDSV.Flags = 0;
			if (descDepth.SampleDesc.Count > 1)
				descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2DMS;
			else
				descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;

		//	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;
			hr = m_d3d10->m_device1->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView);
			if (FAILED(hr))
			{
				raise(Exception("CreateDepthStencilView Failed"));
			}
		}

#if 0
		D3D10_RASTERIZER_DESC rasterizerState;
		rasterizerState.FillMode = D3D10_FILL_SOLID;
	//	rasterizerState.CullMode = D3D10_CULL_BACK;
		rasterizerState.CullMode = D3D10_CULL_NONE;
		rasterizerState.FrontCounterClockwise = true;
		rasterizerState.DepthBias = false;
		rasterizerState.DepthBiasClamp = 0;
		rasterizerState.SlopeScaledDepthBias = 0;
		rasterizerState.DepthClipEnable = false;//true;
		rasterizerState.ScissorEnable = false;
		rasterizerState.MultisampleEnable = false;
		rasterizerState.AntialiasedLineEnable = false;
		hr = m_device->CreateRasterizerState(&rasterizerState, &m_pRasterizerState);
		ASSERT(SUCCEEDED(hr));

		m_device->RSSetState(m_pRasterizerState);
#endif
	}

	if (true)
//	if (m_d3d10->m_device1)
	{
		// Create Direct2D
		IDXGISurface* dxgiSurface;
		hr = m_swapChain->GetBuffer(0, __uuidof(dxgiSurface), reinterpret_cast<void**>(&dxgiSurface));
	
		hr = Direct10::get_D2DFactory()->CreateDxgiSurfaceRenderTarget(dxgiSurface, 
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
			&m_spRT);

		dxgiSurface->Release();
	}

	if (true)	// Here, or in another method?
	{
		RECT clientRect;
		GetClientRect(m_hWnd, &clientRect);

		int clientWidth = clientRect.right;
		int clientHeight = clientRect.bottom;

		if (clientHeight == 0) clientHeight = 1;	//??

		m_d3d10->m_device1->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		D3D10_VIEWPORT vp;
		vp.Width = clientWidth;
		vp.Height = clientHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_d3d10->m_device1->RSSetViewports(1, &vp);
	}
}

void RenderTarget::SetTransform(const D2D1_MATRIX_3X2_F& transform)
{
	if (m_spRT)
	{
		m_spRT->SetTransform(transform);
	}
}

void RenderTarget::Present()
{
	UINT syncInterval = 0;
	UINT flags = 0;

	m_swapChain->Present(syncInterval, flags);
}

bool RenderTarget::WindowResized()
{
	HRESULT hr;

	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);

	int clientWidth = clientRect.right;
	int clientHeight = clientRect.bottom;

	if (clientWidth == 0) clientWidth = 8;
	if (clientHeight == 0) clientHeight = 8;

	if (m_spRT)
	{
		m_spRT->Release();
		m_spRT = NULL;
	}

	m_d3d10->m_device1->OMSetRenderTargets(0, NULL, NULL);

	if (m_pDepthStencilView)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView = NULL;
	}

	if (m_pDepthStencil)
	{
		m_pDepthStencil->Release();
		m_pDepthStencil = NULL;
	}

	if (m_pRenderTargetView)
	{
		if (m_pRenderTargetView)
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		m_swapChain->GetDesc(&swapChainDesc);

		hr = m_swapChain->ResizeBuffers(
			1,	// BufferCount
			clientWidth,	// Width
			clientHeight,	// Height
			DXGI_FORMAT_R8G8B8A8_UNORM,
			0);
		ASSERT(SUCCEEDED(hr));

		// Create a render target view
		ID3D10Texture2D* pBackBuffer;
		hr = m_swapChain->GetBuffer(0, __uuidof(pBackBuffer), reinterpret_cast<void**>(&pBackBuffer));
		if (FAILED(hr))
		{
			ASSERT(0);
			return false;
		}
		D3D10_RENDER_TARGET_VIEW_DESC rtd;
		rtd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		if (false)
			rtd.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2DMS;
		else
			rtd.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	//	rtd.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
		rtd.Texture2D.MipSlice = 0;

		hr = m_d3d10->m_device->CreateRenderTargetView(pBackBuffer, &rtd, &m_pRenderTargetView);
		ASSERT(SUCCEEDED(hr));

		pBackBuffer->Release();
		
		if (true)
		{
			D3D10_TEXTURE2D_DESC descDepth;
			descDepth.Width = clientWidth;
			descDepth.Height = clientHeight;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D32_FLOAT;
			descDepth.SampleDesc.Count = swapChainDesc.SampleDesc.Count;
			descDepth.SampleDesc.Quality = swapChainDesc.SampleDesc.Quality;
			descDepth.Usage = D3D10_USAGE_DEFAULT;
			descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;
			hr = m_d3d10->m_device->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
			ASSERT(SUCCEEDED(hr));

			// Create the depth-stencil
			D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
			descDSV.Format = descDepth.Format;
		//	descDSV.Flags = 0;
			if (descDepth.SampleDesc.Count > 1)
				descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2DMS;
			else
				descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;

			descDSV.Texture2D.MipSlice = 0;
			hr = m_d3d10->m_device->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView);
			ASSERT(SUCCEEDED(hr));
		}

		if (m_d3d10->m_device1)
		{
			// Create Direct2D
			IDXGISurface* dxgiSurface;
			hr = m_swapChain->GetBuffer(0, __uuidof(dxgiSurface), reinterpret_cast<void**>(&dxgiSurface));
		
			hr = Direct10::get_D2DFactory()->CreateDxgiSurfaceRenderTarget(dxgiSurface, 
				D2D1::RenderTargetProperties(
					D2D1_RENDER_TARGET_TYPE_DEFAULT,
					D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
				&m_spRT);

			dxgiSurface->Release();
		}

		if (m_pRenderTargetView)
		{
			D3D10_VIEWPORT vp;
			vp.Width = clientWidth;
			vp.Height = clientHeight;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			m_d3d10->m_device1->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
			m_d3d10->m_device1->RSSetViewports(1, &vp);
		}

	//	m_device->RSSetState(m_pRasterizerState);
	}

	return true;
}

void RenderTarget::Destroy()
{
	if (m_spRT)
	{
		m_spRT->Release();
		m_spRT = NULL;
	}

	m_d3d10->m_deviceContext->OMSetRenderTargets(0, NULL, NULL);

	if (m_pDepthStencilView)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView = NULL;
	}

	if (m_pDepthStencil)
	{
		m_pDepthStencil->Release();
		m_pDepthStencil = NULL;
	}

	if (m_pRenderTargetView)
	{
		if (m_pRenderTargetView)
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
	}
}

RenderTarget::~RenderTarget()
{
}

void RenderTarget::BeginDraw(RenderTargetStoreState* state)
{
	UINT numOldViewports = 8;
//	D3D10_VIEWPORT pOldViewports[8];
	m_d3d10->m_device1->RSGetViewports(&numOldViewports, state->m_oldViewports);
	state->m_numOldViewports = numOldViewports;

	m_d3d10->m_device1->OMGetRenderTargets(1, &state->m_pOldRenderTargetView, &state->m_pOldDepthStencilView);

	if (m_hWnd)
	{
		RECT clientRect;
		GetClientRect(m_hWnd, &clientRect);

		int clientWidth = clientRect.right;
		int clientHeight = clientRect.bottom;

		D3D10_VIEWPORT vp;
		vp.Width = clientWidth;
		vp.Height = clientHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_d3d10->m_device1->RSSetViewports(1, &vp);
	}

	ASSERT(m_pRenderTargetView);
	m_d3d10->m_device1->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	if (m_spRT)
	{
		m_spRT->BeginDraw();
		m_spRT->SetTransform(D2D1::Matrix3x2F::Identity());	// ??
	}

	//m_gi->BeginDraw();
}

/*
void RenderTarget::Flush()
{
	ASSERT(0);
}
*/

void RenderTarget::EndDraw(RenderTargetStoreState* state)
{
	HRESULT hr;

	if (m_spRT)
	{
	//	hr = m_spRT->Flush();	// TODO, find a way to not always need this, e.g at beginning of BeginDraw instead

		hr = m_spRT->EndDraw();
	//	ASSERT(SUCCEEDED(hr));

	//	hr = m_spRT->Flush();	// TODO, find a way to not always need this, e.g at beginning of BeginDraw instead
	//	ASSERT(SUCCEEDED(hr));
	}

	// Restore state
	m_d3d10->m_device1->RSSetViewports(state->m_numOldViewports, state->m_oldViewports);

	m_d3d10->m_device1->OMSetRenderTargets(1, &state->m_pOldRenderTargetView, state->m_pOldDepthStencilView);
	if (state->m_pOldRenderTargetView) state->m_pOldRenderTargetView->Release();
	if (state->m_pOldDepthStencilView) state->m_pOldDepthStencilView->Release();
}

}	// Graphics
}	// System
