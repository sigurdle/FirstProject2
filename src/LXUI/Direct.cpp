#include "stdafx.h"
#include "LXUI2.h"

//#undef _INC_WINDOWS
#include <windows.h>
//#include <ddraw.h>

//#include <d3d8.h>
#include <d3d9.h>
#include <D3dx9math.h>

//IDirectDraw2* dd2;

//IDirect3D8* pD3D;
IDirect3D9* pD3D9;

//IDirectDrawSurface* primaryDDSurface;

#if 1
#pragma comment(lib, "d3d9.lib")
#else
#pragma comment(lib, "d3d8.lib")
#endif

#pragma comment(lib, "D3dx9.lib")

namespace System
{
namespace MSWindows
{

IDirect3DDevice9* D3D_CreateDevice(HWND hWnd, D3DPRESENT_PARAMETERS9* d3dpp9)
{
	/*
	if (pD3D == NULL)
	{
		if((pD3D = Direct3DCreate8(D3D_SDK_VERSION)) == NULL)
		{
			return NULL;
		}
	}
	*/

	if (pD3D9 == NULL)
	{
		pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

		/*
		IDirect3D9Ex* pD3D9Ex = NULL;
		Direct3DCreate9Ex(D3D_SDK_VERSION, &pD3D9Ex);
		pD3D9 = pD3D9Ex;
		*/

		if (pD3D9 == NULL)
		{
			return NULL;
		}
	}

	::D3DPRESENT_PARAMETERS* d3dpp = (::D3DPRESENT_PARAMETERS*)d3dpp9;

	::D3DDISPLAYMODE d3ddm;
	pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	//D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(d3dpp, sizeof(*d3dpp));
	d3dpp->BackBufferCount = 1;
	d3dpp->BackBufferFormat = d3ddm.Format;
	d3dpp->Windowed = true;
	if (true)
	{
		d3dpp->SwapEffect = ::D3DSWAPEFFECT_DISCARD;
	}
	else
	{
		d3dpp->SwapEffect = ::D3DSWAPEFFECT_COPY;
	}

//	d3dpp->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp->PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	d3dpp->MultiSampleType = ::D3DMULTISAMPLE_NONE;

	d3dpp->hDeviceWindow = (::HWND)hWnd;

	d3dpp->EnableAutoDepthStencil = FALSE;
	d3dpp->AutoDepthStencilFormat = ::D3DFMT_D16;

//	D3DDEVTYPE devType = D3DDEVTYPE_REF;
	D3DDEVTYPE devType = D3DDEVTYPE_HAL;

//	d3dpp->MultiSampleType = ::D3DMULTISAMPLE_NONMASKABLE;
//	d3dpp->MultiSampleQuality = 1;

#if 0 
	if (SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
						devType, d3ddm.Format/*D3DFMT_R8G8B8*/, d3dpp->Windowed, 
						::D3DMULTISAMPLE_9_SAMPLES, NULL)))
	{
		d3dpp->MultiSampleType = ::D3DMULTISAMPLE_9_SAMPLES;
		//d3dpp->MultiSampleQuality;
	}
	else
#endif
	if (false)
	{
		if (SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
							devType, d3ddm.Format/*D3DFMT_R8G8B8*/, d3dpp->Windowed, 
							::D3DMULTISAMPLE_6_SAMPLES, NULL)))
		{
			d3dpp->MultiSampleType = ::D3DMULTISAMPLE_6_SAMPLES;
			//d3dpp->MultiSampleQuality;
		}
		else if (SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
							devType, d3ddm.Format/*D3DFMT_R8G8B8*/, d3dpp->Windowed, 
							::D3DMULTISAMPLE_5_SAMPLES, NULL)))
		{
			d3dpp->MultiSampleType = ::D3DMULTISAMPLE_5_SAMPLES;
			//d3dpp->MultiSampleQuality;
		}
		else if (SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
							devType, d3ddm.Format/*D3DFMT_R8G8B8*/, d3dpp->Windowed, 
							::D3DMULTISAMPLE_4_SAMPLES, NULL)))
		{
			d3dpp->MultiSampleType = ::D3DMULTISAMPLE_4_SAMPLES;
			//d3dpp->MultiSampleQuality;
		}
		else if (SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
							devType, d3ddm.Format/*D3DFMT_R8G8B8*/, d3dpp->Windowed, 
							::D3DMULTISAMPLE_3_SAMPLES, NULL)))
		{
			d3dpp->MultiSampleType = ::D3DMULTISAMPLE_3_SAMPLES;
			//d3dpp->MultiSampleQuality;
		}
		else if (SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
							devType, d3ddm.Format/*D3DFMT_R8G8B8*/, d3dpp->Windowed, 
							::D3DMULTISAMPLE_2_SAMPLES, NULL)))
		{
			d3dpp->MultiSampleType = ::D3DMULTISAMPLE_2_SAMPLES;
			//d3dpp->MultiSampleQuality;
		}
	}

	DWORD behaviorFlags = 0;

	behaviorFlags |= D3DCREATE_MULTITHREADED;

	if (true)
	{
		//behaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		behaviorFlags |= D3DCREATE_MIXED_VERTEXPROCESSING;
	}
	else
	{
		behaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	IDirect3DDevice9* pDevice;
	if (FAILED(pD3D9->CreateDevice(
		D3DADAPTER_DEFAULT,
		devType,
		(::HWND)hWnd,
		behaviorFlags,
		d3dpp,
		&pDevice)))
	{
		return NULL;
	}

	D3DCAPS9 d3dCaps;
	pDevice->GetDeviceCaps(&d3dCaps);
	if (d3dCaps.VertexProcessingCaps & D3DVTXPCAPS_TWEENING)
	{
	}

	return pDevice;
}

HRESULT D3D_CreateAdditionalSwapChain(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS9* d3dpp, IDirect3DSwapChain9** pSwapChain)
{
	return pDevice->CreateAdditionalSwapChain((::D3DPRESENT_PARAMETERS*)d3dpp, pSwapChain);
}

void D3D_ResetDevice(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS9* d3dpp)
{
	HRESULT hr = pDevice->Reset((D3DPRESENT_PARAMETERS*)d3dpp);
	switch (hr)
	{
	case D3D_OK:
		break;

	case D3DERR_DEVICELOST:
		printf("Device lost\n");
		break;

	case D3DERR_DEVICEREMOVED:
		printf("Device removed\n");
		break;

	case D3DERR_DRIVERINTERNALERROR:
		printf("Driver internal error\n");
		break;

	case D3DERR_OUTOFVIDEOMEMORY:
		printf("Out of video memory\n");
		break;

	case D3DERR_DEVICENOTRESET:
		printf("Device not reset\n");
		break;
	}
	ASSERT(SUCCEEDED(hr));
}

void D3D_ReleaseDevice(IDirect3DDevice9* pDevice)
{
	ASSERT(pDevice);
	HRESULT hr = pDevice->Release();
	ASSERT(SUCCEEDED(hr));
}

void D3D_Clear(IDirect3DDevice9* pDevice)
{
//	HRESULT hr = pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0, 0);
	HRESULT hr = pDevice->Clear(0, NULL, D3DCLEAR_TARGET/* | D3DCLEAR_ZBUFFER*/, 0x00000000, 1.0, 0);
	ASSERT(SUCCEEDED(hr));
}

void D3D_BeginScene(IDirect3DDevice9* pDevice)
{
	HRESULT hr = pDevice->BeginScene();
	if (FAILED(hr))
	{
		MessageBeep(-1);
	}
	ASSERT(SUCCEEDED(hr));
}

void D3D_EndScene(IDirect3DDevice9* pDevice)
{
	HRESULT hr = pDevice->EndScene();
	ASSERT(SUCCEEDED(hr));
}

extern "C" void* D3D_CreateImageSurface(IDirect3DDevice9* pDevice, int width, int height)
{
	IDirect3DSurface9* surface = NULL;
	//pDevice->CreateImageSurface(width, height, D3DFMT_A8R8G8B8, &surface);

	HRESULT hr = pDevice->CreateOffscreenPlainSurface(width, height, ::D3DFMT_X8R8G8B8, D3DPOOL_SCRATCH/*D3DPOOL_SYSTEMMEM*/ /*D3DPOOL_MANAGED*/, &surface, NULL);
	//HRESULT hr = pDevice->CreateImageSurface(width, height, D3DFMT_X8R8G8B8, &surface);
	ASSERT(SUCCEEDED(hr));

	return surface;
}

extern "C" void D3D_ReleaseSurface(IDirect3DSurface9* pSurface)
{
	ASSERT(pSurface);
	HRESULT hr = pSurface->Release();
	ASSERT(SUCCEEDED(hr));
}

// Presents the next backbuffer
void D3D_Present(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect)
{
	HRESULT hr = pDevice->Present((const ::RECT*)pSourceRect, (const ::RECT*)pDestRect, NULL, NULL);
	VERIFY(SUCCEEDED(hr));
}

void D3D_Present(IDirect3DSwapChain9* pSwapChain, const RECT* pSourceRect, const RECT* pDestRect, HWND destWindowOverride)
{
	uint flags = 0;//D3DPRESENT_DONOTWAIT;
	HRESULT hr = pSwapChain->Present((const ::RECT*)pSourceRect, (const ::RECT*)pDestRect, destWindowOverride, NULL/*dirty region*/, flags);
	VERIFY(SUCCEEDED(hr));
}

extern "C" void D3D_CopyRect(IDirect3DDevice9* pDevice, int dstx, int dsty, IDirect3DSurface9* pSurface, int srcx, int srcy, int width, int height)
{
	HRESULT hr;

	IDirect3DSurface9* backBuffer;
	hr = pDevice->GetBackBuffer(0/*iSwapChain*/, 0/*iBackBuffer*/, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	if (SUCCEEDED(hr))
	{
		::RECT srcrect = {srcx, srcy, srcx+width, srcy+height};
		::POINT dstpoint = {dstx, dsty};
//		hr = pDevice->CopyRects(pSurface, &srcrect, 1, backBuffer, &dstpoint);
		hr = pDevice->UpdateSurface(pSurface, &srcrect, backBuffer, &dstpoint);
		if (hr == D3DERR_DEVICELOST)
		{
			ASSERT(0);
		}
		else if (hr == D3DERR_INVALIDCALL)
		{
			ASSERT(0);
		}
		else
			ASSERT(SUCCEEDED(hr));

		backBuffer->Release();
	}
}

// TODO, pass in rect
extern "C" System::LDraw::Bitmap* D3D_GetBitmap(IDirect3DSurface9* d3dSurface)
{
	D3DSURFACE_DESC desc;
	d3dSurface->GetDesc(&desc);

	D3DLOCKED_RECT lockedRect;
	HRESULT hr = d3dSurface->LockRect(&lockedRect, NULL/*TODO*/, D3DLOCK_NO_DIRTY_UPDATE /*??*/);
	ASSERT(SUCCEEDED(hr));
	return new System::LDraw::Bitmap(desc.Width, desc.Height, lockedRect.Pitch, System::LDraw::PixelFormat_t::RGB_32, lockedRect.pBits);
}

extern "C" void D3D_UnlockBitmap(IDirect3DSurface9* d3dSurface, System::LDraw::Bitmap* /*bitmap*/)
{
	HRESULT hr = d3dSurface->UnlockRect();
	ASSERT(SUCCEEDED(hr));
}

#if 0
extern "C" void BltPrimary(int window_x, int window_y, IDirectDrawSurface* src, int x, int y, int width, int height)
{
	RECT dstrc;
	dstrc.left = window_x + x;
	dstrc.top = window_y + y;
	dstrc.right = window_x + x+width;
	dstrc.bottom = window_y + y+height;

	RECT srcrc;
	srcrc.left = x;
	srcrc.top = y;
	srcrc.right = x+width;
	srcrc.bottom = y+height;

#if 0
	HRESULT hr = primaryDDSurface->Blt(&dstrc, src, &srcrc, DDBLT_WAIT, NULL);

	/*
	if (hr == DDERR_SURFACELOST)
	{
		primaryDDSurface->Restore();
		
	}
	else if (hr < 0)
	{
		int code = hr & 0xffff;

		MessageBeep(-1);
	}
	*/
#endif
}
#endif

/*
extern "C" System::LDraw::Bitmap* GetBitmap(IDirectDrawSurface* dds)
{
	DDSURFACEDESC sd;
	sd.dwSize = sizeof(sd);
	HRESULT hr = dds->Lock(NULL, &sd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	ASSERT(hr >= 0);
	return new System::LDraw::Bitmap((System::MSWindows::_DDSURFACEDESC*)&sd);
}

extern "C" void UnlockBitmap(IDirectDrawSurface* dds, System::LDraw::Bitmap* bitmap)
{
	dds->Unlock(bitmap->GetPointer());
}

extern "C" void ReleaseDDSurface(IDirectDrawSurface* dds)
{
	dds->Release();
}
*/
#if 0
extern "C" IDirectDrawSurface* DoDirect(HWND hWnd, int width, int height)
{
	if (dd2 == NULL)
	{
	//	CoInitialize(NULL);

		IDirectDraw* dd;
		HRESULT hr = DirectDrawCreate(NULL, &dd, NULL);

		hr = dd->QueryInterface(IID_IDirectDraw2, reinterpret_cast<void**>(&dd2));
		ASSERT(SUCCEEDED(hr));

#if 0
		hr = dd2->SetCooperativeLevel(hWnd, DDSCL_NORMAL/*DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN*/);
		ASSERT(SUCCEEDED(hr));

		DDSURFACEDESC ddsd;
		ddsd.dwSize = sizeof(ddsd); 
		ddsd.dwFlags = DDSD_CAPS; 
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		hr = dd2->CreateSurface(&ddsd, &primaryDDSurface, NULL);
		ASSERT(SUCCEEDED(hr));
#endif
	}

	DDSURFACEDESC ddsd;
	ddsd.dwSize = sizeof(ddsd); 
	// Tell DirectDraw which members are valid. 
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT; 

	ddsd.dwWidth = width;
	ddsd.dwHeight = height;
	DDPIXELFORMAT pixelfmt;
	pixelfmt.dwSize = sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat = pixelfmt;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//DDSCAPS_PRIMARYSURFACE;
	ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;	// planning on using software drawing, will be reading from the buffer, having it in video memory would be slower

	HRESULT hr;

	IDirectDrawSurface* dds;
	hr = dd2->CreateSurface(&ddsd, &dds, NULL);
	ASSERT(SUCCEEDED(hr));

	/*
	IDirectDrawClipper* clipper;
	dd2->CreateClipper(0, &clipper, NULL);
	// clipper->Initialize(dd2, 0);	// Always returns DDERR_ALREADYINITIALIZED
	clipper->SetHWnd(0, (HWND)hWnd);

	hr = primaryDDSurface->SetClipper(clipper);
	ASSERT(SUCCEEDED(hr));
*/
	return dds;
}

#endif

}	// MSWindows
}
