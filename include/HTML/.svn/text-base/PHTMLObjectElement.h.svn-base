#pragma once

class CHTMPObject;
class CActiveXDispEvent;

//class CCOMObject;

#if 0
#include "OleClientItem.h"

class ATL_NO_VTABLE CCOMObjectBase : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public COleClientItem,
/*
	public CComObjectRootEx<CComSingleThreadModel>,
	public IServiceProviderImpl<CCOMObjectBase>,//, &IID_IServiceProvider>
	public IDispatchImpl<IDispatch, &IID_IDispatch>,
	public IDispatchImpl<IOleClientSite, &IID_IOleClientSite>,
	public IDispatchImpl<IOleWindow, &IID_IOleWindow>,
	public IDispatchImpl<IOleInPlaceSite, &IID_IOleInPlaceSite>,
	public IDispatchImpl<IOleInPlaceSiteEx, &IID_IOleInPlaceSiteEx>,
	public IDispatchImpl<IOleInPlaceSiteWindowless, &IID_IOleInPlaceSiteWindowless>,
*/
	public IServiceProviderImpl<CCOMObjectBase>,//, &IID_IServiceProvider>
//	public IDispatchImpl<IAdviseSink, &IID_IAdviseSink>,
	public IDispatchImpl<IPersistMoniker, &IID_IPersistMoniker>,
	public IBindHost
{
public:

	CTOR CCOMObjectBase()
	{
		m_PHTMElement = NULL;

		m_msDataSourceObjectDispID = 0;
	}

	CArray<CActiveXDispEvent*,CActiveXDispEvent*> m_dispEvents;

	CHTMPObject* m_PHTMElement;

	CLSID	m_clsid;

	DISPID	m_msDataSourceObjectDispID;

	IUnknown* GetDataSourceUnknown();
//	BOOL IsDataSource();

BEGIN_COM_MAP(CCOMObjectBase)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSite, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSiteEx, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY(IServiceProvider)

	COM_INTERFACE_ENTRY(IBindHost)

	COM_INTERFACE_ENTRY_BREAK(IPersistMoniker)
	COM_INTERFACE_ENTRY_BREAK(IAdviseSink)
	COM_INTERFACE_ENTRY_BREAK(IOleItemContainer)
END_COM_MAP()

#if 0
BEGIN_SERVICE_MAP(CCOMObjectBase)
//	SERVICE_ENTRY(SID_SBindHost)  // This object supports the SBindHost service
END_SERVICE_MAP
#endif
	HRESULT _InternalQueryService(REFGUID guidService, REFIID riid, void** ppvObject) \
	{
	ATLASSERT(0);
	//if (InlineIsEqualGUID(guidService, IID_IBindHost)) return QueryInterface(riid, ppvObject);
/*
#define SERVICE_ENTRY(x) \
		if (InlineIsEqualGUID(guidService, x)) \
			return QueryInterface(riid, ppvObject);

#define SERVICE_ENTRY_CHAIN(x) \
		CComQIPtr<IServiceProvider, &IID_IServiceProvider> spProvider(x); \
		if (spProvider != NULL) \
			return spProvider->QueryService(guidService, riid, ppvObject);

#define END_SERVICE_MAP() \
  */
		return E_NOINTERFACE; \
	}

	// IBindHost
     virtual HRESULT STDMETHODCALLTYPE CreateMoniker( 
         /* [in] */ LPOLESTR szName,
         /* [in] */ IBindCtx __RPC_FAR *pBC,
         /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk,
         /* [in] */ DWORD dwReserved)
	  {
		  ULONG eaten = 0;
		  //HRESULT hr = MkParseDisplayNameEx(pBC, szName, &eaten, ppmk);
		  HRESULT hr = CreateURLMoniker(NULL, szName, ppmk);
		  return hr;
	  }
     
     virtual /* [local] */ HRESULT STDMETHODCALLTYPE MonikerBindToStorage( 
         /* [in] */ IMoniker __RPC_FAR *pMk,
         /* [in] */ IBindCtx __RPC_FAR *pBC,
         /* [in] */ IBindStatusCallback __RPC_FAR *pBSC,
         /* [in] */ REFIID riid,
         /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObj)
	  {
		  HRESULT hr = pMk->BindToStorage(pBC, NULL, riid, ppvObj);
		  return hr;
	  }
     
     virtual /* [local] */ HRESULT STDMETHODCALLTYPE MonikerBindToObject( 
         /* [in] */ IMoniker __RPC_FAR *pMk,
         /* [in] */ IBindCtx __RPC_FAR *pBC,
         /* [in] */ IBindStatusCallback __RPC_FAR *pBSC,
         /* [in] */ REFIID riid,
         /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObj)
	  {
		  return S_OK;
	  }

// IPersistMoniker
        virtual HRESULT STDMETHODCALLTYPE GetClassID( 
            /* [out] */ CLSID __RPC_FAR *pClassID)
	  {
	MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE IsDirty( void)
	  {
	MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BOOL fFullyAvailable,
            /* [in] */ IMoniker __RPC_FAR *pimkName,
            /* [in] */ LPBC pibc,
            /* [in] */ DWORD grfMode)
	  {
	MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IMoniker __RPC_FAR *pimkName,
            /* [in] */ LPBC pbc,
            /* [in] */ BOOL fRemember)
	  {
	MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE SaveCompleted( 
            /* [in] */ IMoniker __RPC_FAR *pimkName,
            /* [in] */ LPBC pibc)
	  {
	MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	  }
        
        virtual HRESULT STDMETHODCALLTYPE GetCurMoniker( 
            /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppimkName)
	  {
	MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	  }
       
};

class CCOMObject : public CComObject<CCOMObjectBase>
{
};
#endif

#include "HTMPElement.h"

class ATL_NO_VTABLE CPHTMLObjectElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CHTMPElement
{
public:
	CPHTMLObjectElement()
	{
#if 0
		m_pControl = NULL;
#endif
	}

	~CPHTMLObjectElement()
	{
#if 0
		delete m_pControl;
#endif
	}

#if 0
	CCOMObject* m_pControl;

	void LoadObject();
#endif

	void GetObjectDataPaths();

	virtual BOOL HasDistributableChildren()
	{
		return FALSE;
	}

#if 0
	virtual void CreateControls(CHTMContext* pC);
#endif
	virtual void PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC);
	virtual void Draw(CHTMRenderContext* pC);
#if 0
	virtual void CalculateDimensions(CHTMCalcContext* pC);
	virtual BOOL OnButtonDown(CComObject<CHTMLWindow>* pFrame, POINT point);
#endif

BEGIN_COM_MAP(CPHTMLObjectElement)
	COM_INTERFACE_ENTRY(ILViewNode)
END_COM_MAP()
};
