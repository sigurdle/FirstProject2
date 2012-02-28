// LWOLoader.h : Declaration of the CLWOLoader

#ifndef __LWOLOADER_H_
#define __LWOLOADER_H_

#include "resource.h"       // main symbols

#include "../iffparse.h"

/////////////////////////////////////////////////////////////////////////////
// CLWOLoader
class ATL_NO_VTABLE CLWOLoader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLWOLoader, &CLSID_LWOLoader>,
	public ILWOLoader,
	public ILX3DLoader
{
public:
	CLWOLoader()
	{
	}

	CComPtr<ILX3DScene> m_scene;

	HRESULT LoadLWOB(IStream* pStream, ILMFNode* children);

DECLARE_REGISTRY_RESOURCEID(IDR_LWOLOADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLWOLoader)
	COM_INTERFACE_ENTRY(ILWOLoader)
	COM_INTERFACE_ENTRY(ILX3DLoader)
END_COM_MAP()

// ILWOLoader
public:
// ILX3DLoader
	STDMETHOD(Load)(/*[in]*/ IStream* stream, /*[in]*/ ILX3DScene* scene, /*[in]*/ ILMFNode* children);
};

#endif //__LWOLOADER_H_
