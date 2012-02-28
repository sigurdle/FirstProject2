// DOK5Loader.h : Declaration of the CDOK5Loader

#ifndef __DOK5LOADER_H_
#define __DOK5LOADER_H_

#include "resource.h"       // main symbols

#include "DOK5.h"

/////////////////////////////////////////////////////////////////////////////
// CDOK5Loader
class ATL_NO_VTABLE CDOK5Loader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDOK5Loader, &CLSID_DOK5Loader>,
	public IDOK5Loader,
	public ILX3DLoader
{
public:
	CDOK5Loader()
	{
//		m_trackList = m_prevTrack = NULL;
		m_prevLayer = NULL;
		m_level = 0;
	}

	ILX3DNode* m_prevLayer;
//	TRACK* m_trackList;
//	TRACK* m_prevTrack;
	int m_level;

	CComPtr<ILX3DScene> m_scene;

	long LoadObject(IStream* pStream, ILMFNode* children);

	long Load(IStream* pStream, ILMFNode* parentRef);

	/*
	long LoadOLDSequenceChunk(IStream* pStream, CI3DLayer* layerRef, CIParam* paramRef, CI3DLayer* topLayer);
	long LoadSequenceChunk(IStream* pStream, CI3DLayer* layerRef, CIParam* paramRef, CI3DLayer* topLayer);
	long LoadTrack(IStream* pStream, CI3DLayer* layerRef, CI3DLayer* topLayer);
	long LoadLight(IStream* pStream, CI3DLayer*);
	long LoadObject(IStream* pStream, CI3DLayer* topLayer);
	long LoadMaterial(IStream* pStream, CI3DLayer* parentRef);
	*/

DECLARE_REGISTRY_RESOURCEID(IDR_DOK5LOADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDOK5Loader)
	COM_INTERFACE_ENTRY(IDOK5Loader)
	COM_INTERFACE_ENTRY(ILX3DLoader)
END_COM_MAP()

// IDOK5Loader
public:
// ILX3DLoader
	STDMETHOD(Load)(/*[in]*/ IStream* stream, /*[in]*/ ILX3DScene* scene, /*[in]*/ ILMFNode* children);
};

#endif //__DOK5LOADER_H_
