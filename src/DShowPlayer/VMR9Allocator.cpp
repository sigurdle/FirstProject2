//------------------------------------------------------------------------------
// File: Allocator.cpp
//
// Desc: DirectShow sample code - implementation of the CAllocator class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "DShowPlayer.h"

#include "VMR9Allocator.h"

namespace System
{
namespace DShow
{

/*
class MyWindow : public HWindow<0>
{
public:
};
*/

// Define a function pointer to the Direct3DCreate9Ex function.
typedef HRESULT (WINAPI *LPDIRECT3DCREATE9EX)( UINT, IDirect3D9Ex **);

// Obtain the address of the Direct3DCreate9Ex function. 
LPDIRECT3DCREATE9EX Direct3DCreate9ExPtr = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VMR9Allocator::VMR9Allocator(HWND hWnd, IDirect3D9* d3d, IDirect3DDevice9* d3dd) :
	m_refCount(1),
	m_D3D(d3d),
	m_D3DDev(d3dd),
	m_window(hWnd)
{
	CriticalSectionLock Lock(m_ObjectLock);

	if (!IsWindow(m_window))
	{
		raise(ArgumentException());
	}

	if (m_D3D == NULL)
	{
		HMODULE libHandle = NULL;

		// Manually load the d3d9.dll library.
		libHandle = LoadLibrary(L"d3d9.dll");

		if(libHandle != NULL)
		{
			Direct3DCreate9ExPtr = (LPDIRECT3DCREATE9EX)GetProcAddress( libHandle, "Direct3DCreate9Ex" );
		}

		ASSERT( d3dd ==  NULL ); 

		if (Direct3DCreate9ExPtr)
		{
			HRESULT hr = Direct3DCreate9ExPtr(D3D_SDK_VERSION, &m_D3DEx);

			m_D3D = m_D3DEx;

			if (hr == D3DERR_NOTAVAILABLE)
			{
				m_D3D.Attach(Direct3DCreate9(D3D_SDK_VERSION));
				if (m_D3D == NULL)
				{
					raise(Exception("Direct3DCreate9 failed"));
				}
			}
		}
	}

	if (m_D3DDev == NULL)
	{
		CreateDevice();
	}
}

VMR9Allocator::~VMR9Allocator()
{
    DeleteSurfaces();
}

void VMR9Allocator::CreateDevice()
{
	HRESULT hr;
	m_D3DDev = nullptr;
	D3DDISPLAYMODE dm;
	hr = m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

//	D3DDISPLAYMODEEX dmex;
	//dmex.Size = sizeof(D3DDISPLAYMODEEX);

	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.BackBufferWidth = 8;
	pp.BackBufferHeight = 8;
	pp.Windowed = TRUE;
	pp.hDeviceWindow = m_window;
	pp.SwapEffect = D3DSWAPEFFECT_COPY;

	if (m_D3DEx)
	{
	//	hr = m_D3DEx->GetAdapterDisplayModeEx(D3DADAPTER_DEFAULT, &dmex, NULL);
	//pp.BackBufferFormat = dmex.Format;

		hr = m_D3DEx->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_window,
			D3DCREATE_MIXED_VERTEXPROCESSING |
			//D3DCREATE_SOFTWARE_VERTEXPROCESSING |
			D3DCREATE_MULTITHREADED,
			&pp,
			NULL,	// must be NULL for windowed mode
			&m_D3DDevEx);

		m_D3DDev = m_D3DDevEx;
	}

	if (m_D3DDev == NULL)
	{
		hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_window,
			D3DCREATE_MIXED_VERTEXPROCESSING |
			//D3DCREATE_SOFTWARE_VERTEXPROCESSING |
			D3DCREATE_MULTITHREADED,
			&pp, &m_D3DDev);
	}

	if (FAILED(hr))
	{
		switch (hr)
		{
		case D3DERR_DEVICELOST:
			raise(Exception("D3D9: Device lost", NULL, hr));

		case D3DERR_INVALIDCALL:
			raise(Exception("D3D9: Invalid Call", NULL, hr));

		case D3DERR_NOTAVAILABLE:
			raise(Exception("D3D9: Not available", NULL, hr));

		case D3DERR_OUTOFVIDEOMEMORY:
			raise(Exception("D3D9: Out of video memory", NULL, hr));

		default:
			raise_(Exception::FromHResult(hr));
		}
	}

	hr = m_D3DDev->GetRenderTarget(0, &m_renderTarget);
	if (FAILED(hr))
	{
		raise_(Exception::FromHResult(hr));
	}
}

void VMR9Allocator::DeleteSurfaces()
{
    CriticalSectionLock Lock(m_ObjectLock);

    // clear out the private texture
    m_privateTexture = nullptr;

    for (size_t i = 0; i < m_surfaces.size(); ++i) 
    {
		m_surfaces[i].m_p = nullptr;
		m_surfaces[i].m_h = nullptr;
    }
}

//IVMRSurfaceAllocator9
HRESULT VMR9Allocator::InitializeDevice( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMR9AllocationInfo* lpAllocInfo,
            /* [out][in] */ DWORD* lpNumBuffers)
{
	D3DCAPS9 d3dcaps;
	float fTU = 1.f;
	float fTV = 1.f;

	if (lpNumBuffers == NULL)
	{
		return E_POINTER;
	}

	if (m_lpIVMRSurfAllocNotify == NULL)
	{
		return E_FAIL;
	}

	ThrowHr hr;

	m_D3DDev->GetDeviceCaps(&d3dcaps);

	if (d3dcaps.TextureCaps & D3DPTEXTURECAPS_POW2)
	{
		DWORD dwWidth = 1;
		while (dwWidth < lpAllocInfo->dwWidth) dwWidth <<= 1;

		DWORD dwHeight = 1;
		while (dwHeight < lpAllocInfo->dwHeight) dwHeight <<= 1;

		fTU = (float)(lpAllocInfo->dwWidth) / (float)(dwWidth);
		fTV = (float)(lpAllocInfo->dwHeight) / (float)(dwHeight);

#if 0
		m_scene->SetSrcRect(fTU, fTV);
#endif
		lpAllocInfo->dwWidth = dwWidth;
		lpAllocInfo->dwHeight = dwHeight;
	}

	// NOTE:
	// we need to make sure that we create textures because
	// surfaces can not be textured onto a primitive.
	lpAllocInfo->dwFlags |= VMR9AllocFlag_TextureSurface;

	DeleteSurfaces();
	m_surfaces.resize(*lpNumBuffers);

	ComPtr<ID3D10Texture2D> texture10;

	ASSERT(*lpNumBuffers == 1);	// TODO remove

	if (m_D3DDevEx)
	{
		for (size_t i = 0; i < *lpNumBuffers; ++i)
		{
			HANDLE hShared = nullptr;

			m_surfaces.at(i).m_h = nullptr;

			hr = m_D3DDevEx->CreateTexture(
				lpAllocInfo->dwWidth, lpAllocInfo->dwHeight, 1, D3DUSAGE_RENDERTARGET,
				D3DFMT_X8R8G8B8,
			//	D3DFMT_X8B8G8R8,//lpAllocInfo->Format,
				D3DPOOL_DEFAULT,
				&m_surfaces.at(i).m_t,
				&m_surfaces.at(i).m_h
				);

			m_surfaces.at(i).m_t->GetSurfaceLevel(0, &m_surfaces.at(i).m_p);

			hr = Graphics::Direct10::get_D3DDevice1()->OpenSharedResource(m_surfaces.at(i).m_h, __uuidof(ID3D11Texture2D), (void**)&texture10);
			ASSERT(texture10);
		}
	}
	else
	{
		/*
		for (size_t i = 0; i < *lpNumBuffers; ++i)
		{
			HANDLE hShared = NULL;

			hr = m_D3DDev->CreateTexture(
				lpAllocInfo->dwWidth, lpAllocInfo->dwHeight, lpAllocInfo->Format,
				D3DPOOL_DEFAULT,
				&m_surfaces.at(i).m_p,
				D3DUSAGE_RENDERTARGET);
		}
		*/

//		hr = m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, &m_surfaces.at(0).);
	}

	// If we couldn't create a texture surface and 
	// the format is not an alpha format,
	// then we probably cannot create a texture.
	// So what we need to do is create a private texture
	// and copy the decoded images onto it.
	if (FAILED(hr) && !(lpAllocInfo->dwFlags & VMR9AllocFlag_3DRenderTarget))
	{
		DeleteSurfaces();

		// is surface YUV ?
		if (lpAllocInfo->Format > '0000') 
		{
			D3DDISPLAYMODE dm;
			FAIL_RET( m_D3DDev->GetDisplayMode(0,  &dm));

			// create the private texture
			FAIL_RET( m_D3DDev->CreateTexture(lpAllocInfo->dwWidth, lpAllocInfo->dwHeight,
				1,
				D3DUSAGE_RENDERTARGET,
				dm.Format,
				D3DPOOL_DEFAULT /* default pool - usually video memory */,
				& m_privateTexture, nullptr));
		}

		lpAllocInfo->dwFlags &= ~VMR9AllocFlag_TextureSurface;
		lpAllocInfo->dwFlags |= VMR9AllocFlag_OffscreenSurface;

		ASSERT(0);
		//FAIL_RET(m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, &m_surfaces.at(0)));
	}

	return m_scene->Init(m_D3DDev, lpAllocInfo->dwWidth, lpAllocInfo->dwHeight, texture10);
}

HRESULT VMR9Allocator::TerminateDevice(/* [in] */ DWORD_PTR dwID)
{
	DeleteSurfaces();
	return S_OK;
}

HRESULT VMR9Allocator::GetSurface( 
        /* [in] */ DWORD_PTR dwUserID,
        /* [in] */ DWORD SurfaceIndex,
        /* [in] */ DWORD SurfaceFlags,
        /* [out] */ IDirect3DSurface9 **lplpSurface)
{
	if (lplpSurface == nullptr)
	{
		return E_POINTER;
	}

	if (SurfaceIndex >= m_surfaces.size())
	{
		return E_FAIL;
	}

	CriticalSectionLock Lock(m_ObjectLock);

	*lplpSurface = m_surfaces[SurfaceIndex].m_p;
	(*lplpSurface)->AddRef();

	return S_OK;
//    return m_surfaces[SurfaceIndex].CopyTo(lplpSurface) ;
}
    
HRESULT VMR9Allocator::AdviseNotify(/* [in] */ IVMRSurfaceAllocatorNotify9* lpIVMRSurfAllocNotify)
{
    CriticalSectionLock Lock(m_ObjectLock);

    HRESULT hr;

    m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;

    HMONITOR hMonitor = m_D3D->GetAdapterMonitor(D3DADAPTER_DEFAULT);

	// NOTE: This could return E_NOINTERFACE if using D3D9 Debug version
    FAIL_RET(m_lpIVMRSurfAllocNotify->SetD3DDevice(m_D3DDev, hMonitor));

    return hr;
}

HRESULT VMR9Allocator::StartPresenting(/* [in] */ DWORD_PTR dwUserID)
{
    CriticalSectionLock Lock(m_ObjectLock);

    ASSERT(m_D3DDev);
    if (m_D3DDev == nullptr)
    {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT VMR9Allocator::StopPresenting(/* [in] */ DWORD_PTR dwUserID)
{
    return S_OK;
}

HRESULT VMR9Allocator::PresentImage(/* [in] */ DWORD_PTR dwUserID, /* [in] */ VMR9PresentationInfo *lpPresInfo)
{
	HRESULT hr;
	CriticalSectionLock Lock(m_ObjectLock);

	// if we are in the middle of the display change
	if (NeedToHandleDisplayChange())
	{
		// NOTE: this piece of code is left as a user exercise.  
		// The D3DDevice here needs to be switched
		// to the device that is using another adapter
	}

	hr = PresentHelper(lpPresInfo);

	// IMPORTANT: device can be lost when user changes the resolution
	// or when (s)he presses Ctrl + Alt + Delete.
	// We need to restore our video memory after that
	if (hr == D3DERR_DEVICELOST)
	{
		if (m_D3DDev->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) 
		{
			DeleteSurfaces();
			CreateDevice();

			HMONITOR hMonitor = m_D3D->GetAdapterMonitor(D3DADAPTER_DEFAULT);

			FAIL_RET(m_lpIVMRSurfAllocNotify->ChangeD3DDevice(m_D3DDev, hMonitor));
		}

		hr = S_OK;
	}

	return hr;
}

HRESULT VMR9Allocator::PresentHelper(VMR9PresentationInfo *lpPresInfo)
{
    // parameter validation
    if (lpPresInfo == NULL)
    {
        return E_POINTER;
    }
    else if (lpPresInfo->lpSurf == NULL)
    {
        return E_POINTER;
    }

    CriticalSectionLock Lock(m_ObjectLock);
    HRESULT hr;

    m_D3DDev->SetRenderTarget(0, m_renderTarget);
    // if we created a  private texture
    // blt the decoded image onto the texture.
    if (m_privateTexture != NULL)
    {   
        ComPtr<IDirect3DSurface9> surface;
        FAIL_RET( m_privateTexture->GetSurfaceLevel( 0 , & surface ) );

        // copy the full surface onto the texture's surface
        FAIL_RET( m_D3DDev->StretchRect( lpPresInfo->lpSurf, NULL,
                             surface, NULL,
                             D3DTEXF_NONE ) );

        FAIL_RET( m_scene->DrawScene(m_D3DDev, m_privateTexture ) );
    }
    else // this is the case where we have got the textures allocated by VMR
         // all we need to do is to get them from the surface
    {
        ComPtr<IDirect3DTexture9> texture;
        FAIL_RET( lpPresInfo->lpSurf->GetContainer(__uuidof(IDirect3DTexture9), (LPVOID*) &texture));    
        FAIL_RET( m_scene->DrawScene(m_D3DDev, texture ) );
    }

    FAIL_RET( m_D3DDev->Present( NULL, NULL, NULL, NULL ) );

    return hr;
}

bool VMR9Allocator::NeedToHandleDisplayChange()
{
    if( ! m_lpIVMRSurfAllocNotify )
    {
        return false;
    }

    D3DDEVICE_CREATION_PARAMETERS Parameters;
    if( FAILED( m_D3DDev->GetCreationParameters(&Parameters) ) )
    {
        ASSERT( false );
        return false;
    }

    HMONITOR currentMonitor = m_D3D->GetAdapterMonitor( Parameters.AdapterOrdinal );

    HMONITOR hMonitor = m_D3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );

    return hMonitor != currentMonitor;


}

// IUnknown
HRESULT VMR9Allocator::QueryInterface(REFIID riid, void** ppvObject)
{
    HRESULT hr = E_NOINTERFACE;

    if( ppvObject == NULL ) {
        hr = E_POINTER;
    } 
    else if( riid == IID_IVMRSurfaceAllocator9 ) {
        *ppvObject = static_cast<IVMRSurfaceAllocator9*>( this );
        AddRef();
        hr = S_OK;
    } 
    else if( riid == IID_IVMRImagePresenter9 ) {
        *ppvObject = static_cast<IVMRImagePresenter9*>( this );
        AddRef();
        hr = S_OK;
    } 
    else if( riid == IID_IUnknown ) {
        *ppvObject = 
            static_cast<IUnknown*>( 
            static_cast<IVMRSurfaceAllocator9*>( this ) );
        AddRef();
        hr = S_OK;    
    }

    return hr;
}

ULONG VMR9Allocator::AddRef()
{
    return InterlockedIncrement(& m_refCount);
}

ULONG VMR9Allocator::Release()
{
    ULONG ret = InterlockedDecrement(& m_refCount);
    if( ret == 0 )
    {
        delete this;
    }

    return ret;
}

}	// DShow
}	// System
