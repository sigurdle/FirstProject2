// ESceneDocument.h : Declaration of the CESceneDocument

#ifndef __ESCENEDOCUMENT_H_
#define __ESCENEDOCUMENT_H_

#include "resource.h"       // main symbols

#include "..\LXFramework\WebDocumentImpl.h"

#if 0
#include "LXMLEditorApp.h"	// TODO Remove

/////////////////////////////////////////////////////////////////////////////
// CESceneDocument
class ATL_NO_VTABLE CESceneDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CESceneDocument, &CLSID_ESceneDocument>,
	public IConnectionPointContainerImpl<CESceneDocument>,
	public IDispatchImpl<IESceneDocument, &IID_IESceneDocument, &LIBID_LXMLEDITORLib>,

	public CEDocumentImpl<CESceneDocument>,
	public CViewGroup,
	public IPersistMoniker
{
public:
	CESceneDocument()
	{
	}

	CComQIPtr<ILXMLEditorApp> m_app;

	CComPtr<ILX3DScene> m_scene;

	CArray<ILX3DChildNode*,ILX3DChildNode*> m_selectedNodes;

// CViewGroup
	virtual HRESULT OnActivate(BOOL bActive);
	virtual HRESULT OnClose();

DECLARE_REGISTRY_RESOURCEID(IDR_ESCENEDOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CESceneDocument)
	COM_INTERFACE_ENTRY(IESceneDocument)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(IEDocument)

	COM_INTERFACE_ENTRY(IPersistMoniker)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CESceneDocument)
END_CONNECTION_POINT_MAP()

// IESceneDocument
public:
// IEDocument
	STDMETHOD(ShowViews)(IEFrame* pFrame);
	STDMETHOD(Activate)();
	STDMETHOD(CloseDocument)();

// IPersist
	STDMETHOD(GetClassID)(CLSID __RPC_FAR *pClassID);
	STDMETHOD(IsDirty)();

// IPersistMoniker
	STDMETHOD(Load)(/* [in] */ BOOL fFullyAvailable, /* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc, /* [in] */ DWORD grfMode);
	STDMETHOD(Save)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ BOOL fRemember);
	STDMETHOD(SaveCompleted)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc);
	STDMETHOD(GetCurMoniker)(/* [out] */ IMoniker **ppimkName);
};

#endif //__ESCENEDOCUMENT_H_

#endif