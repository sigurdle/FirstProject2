//------------------------------------------------------------------------------
// File: Allocator.h
//
// Desc: DirectShow sample code - interface for the CAllocator class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#if !defined(AFX_ALLOCATOR_H__F675D766_1E57_4269_A4B9_C33FB672B856__INCLUDED_)
#define AFX_ALLOCATOR_H__F675D766_1E57_4269_A4B9_C33FB672B856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vmr9.h>

namespace System
{
namespace DShow
{

class VMR9Allocator : public Object, public IVMRSurfaceAllocator9, IVMRImagePresenter9
{
public:
	VMR9Allocator(HWND hWnd, IDirect3D9* d3d = NULL, IDirect3DDevice9* d3dd = NULL);
	virtual ~VMR9Allocator();

	// IVMRSurfaceAllocator9
	virtual HRESULT STDMETHODCALLTYPE InitializeDevice( 
		/* [in] */ DWORD_PTR dwUserID,
		/* [in] */ VMR9AllocationInfo *lpAllocInfo,
		/* [out][in] */ DWORD *lpNumBuffers);

	virtual HRESULT STDMETHODCALLTYPE TerminateDevice( 
		/* [in] */ DWORD_PTR dwID);

	virtual HRESULT STDMETHODCALLTYPE GetSurface( 
		/* [in] */ DWORD_PTR dwUserID,
		/* [in] */ DWORD SurfaceIndex,
		/* [in] */ DWORD SurfaceFlags,
		/* [out] */ IDirect3DSurface9 **lplpSurface);

	virtual HRESULT STDMETHODCALLTYPE AdviseNotify( 
		/* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify);

	// IVMRImagePresenter9
	virtual HRESULT STDMETHODCALLTYPE StartPresenting(
		/* [in] */ DWORD_PTR dwUserID);

	virtual HRESULT STDMETHODCALLTYPE StopPresenting(
		/* [in] */ DWORD_PTR dwUserID);

	virtual HRESULT STDMETHODCALLTYPE PresentImage(
		/* [in] */ DWORD_PTR dwUserID,
		/* [in] */ VMR9PresentationInfo *lpPresInfo);

	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();

	IVideoPresenter* m_scene;

protected:

	void CreateDevice();

	// a helper function to erase every surface in the vector
	void DeleteSurfaces();

	bool NeedToHandleDisplayChange();

	// This function is here so we can catch the loss of surfaces.
	// All the functions are using the FAIL_RET macro so that they exit
	// with the last error code.  When this returns with the surface lost
	// error code we can restore the surfaces.
	HRESULT PresentHelper(VMR9PresentationInfo* lpPresInfo);

private:
	// needed to make this a thread safe object
	CriticalSection m_ObjectLock;
	HWND m_window;
	long m_refCount;

	ComPtr<IDirect3D9>						m_D3D;
	ComPtr<IDirect3D9Ex>					m_D3DEx;
	ComPtr<IDirect3DDevice9>				m_D3DDev;
	ComPtr<IDirect3DDevice9Ex>				m_D3DDevEx;
	ComPtr<IVMRSurfaceAllocatorNotify9>		m_lpIVMRSurfAllocNotify;

	struct Surf
	{
		ComPtr<IDirect3DTexture9> m_t;
		ComPtr<IDirect3DSurface9> m_p;
		HANDLE m_h;
	};

	vector<Surf> m_surfaces;
	ComPtr<IDirect3DSurface9>				m_renderTarget;
	ComPtr<IDirect3DTexture9>				m_privateTexture;
};

}	// DShow
}	// System

#endif // !defined(AFX_ALLOCATOR_H__F675D766_1E57_4269_A4B9_C33FB672B856__INCLUDED_)
