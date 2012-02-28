// LHTMLScreen.h : Declaration of the CLHTMLScreen

#ifndef __LHTMLSCREEN_H_
#define __LHTMLSCREEN_H_

//#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLHTMLScreen
class HTMLEXT CLHTMLScreen
//	public CComObjectRootEx<CComMultiThreadModel>,

//	public IDispatchImpl<DispILHTMLScreen, &IID_DispILHTMLScreen, &LIBID_LHTMLLib>,

/*
// MSHTML interfaces
	public IHTMLScreen,	// IDispatch
	public IHTMLScreen2	// IDispatch
	*/
{
public:
	CLHTMLScreen()
	{
	}

#if 0
	int FinalConstruct()
	{
		HRESULT hr;

		return S_OK;
	}

	void FinalRelease()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHTMLScreen)
	COM_INTERFACE_ENTRY2(IDispatch, DispILHTMLScreen)

// MSHTML interfaces
	COM_INTERFACE_ENTRY(IHTMLScreen)
	COM_INTERFACE_ENTRY(IHTMLScreen2)
END_COM_MAP()

// IDispatch
	STDMETHODIMP GetTypeInfoCount( 
         /* [out] */ UINT *pctinfo)
	{
		return IDispatchImpl<DispILHTMLScreen, &IID_DispILHTMLScreen, &LIBID_LHTMLLib>::GetTypeInfoCount(pctinfo);
	}

	STDMETHODIMP GetTypeInfo( 
         /* [in] */ UINT iTInfo,
         /* [in] */ LCID lcid,
         /* [out] */ ITypeInfo **ppTInfo)
	{
		return IDispatchImpl<DispILHTMLScreen, &IID_DispILHTMLScreen, &LIBID_LHTMLLib>::GetTypeInfo(iTInfo, lcid, ppTInfo);
	}

	STDMETHODIMP GetIDsOfNames( 
         /* [in] */ REFIID riid,
         /* [size_is][in] */ LPOLESTR *rgszNames,
         /* [in] */ UINT cNames,
         /* [in] */ LCID lcid,
         /* [size_is][out] */ DISPID *rgDispId)
	{
		return IDispatchImpl<DispILHTMLScreen, &IID_DispILHTMLScreen, &LIBID_LHTMLLib>::GetIDsOfNames(riid, rgszNames, cNames, lcid, rgDispId);
	}

	STDMETHODIMP Invoke( 
         /* [in] */ DISPID dispIdMember,
         /* [in] */ REFIID riid,
         /* [in] */ LCID lcid,
         /* [in] */ WORD wFlags,
         /* [out][in] */ DISPPARAMS *pDispParams,
         /* [out] */ VARIANT *pVarResult,
         /* [out] */ EXCEPINFO *pExcepInfo,
         /* [out] */ UINT *puArgErr)
	{
		return IDispatchImpl<DispILHTMLScreen, &IID_DispILHTMLScreen, &LIBID_LHTMLLib>::Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	}

// ILHTMLScreen
public:

// HTMLScreen
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_colorDepth( 
            /* [out][retval] */ long *p);
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_bufferDepth( 
            /* [in] */ long v);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_bufferDepth( 
            /* [out][retval] */ long *p);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_width( 
            /* [out][retval] */ long *p);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_height( 
            /* [out][retval] */ long *p);
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_updateInterval( 
            /* [in] */ long v);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_updateInterval( 
            /* [out][retval] */ long *p);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_availHeight( 
            /* [out][retval] */ long *p);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_availWidth( 
            /* [out][retval] */ long *p);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_fontSmoothingEnabled( 
            /* [out][retval] */ bool *p);

// IHTMLScreen2
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_logicalXDPI( /* [out][retval] */ long *p);
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_logicalYDPI( /* [out][retval] */ long *p);
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_deviceXDPI( 
            /* [out][retval] */ long *p)
				{
				return E_NOTIMPL;
				}
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_deviceYDPI( 
            /* [out][retval] */ long *p)
				{
				return E_NOTIMPL;
				}
#endif
};

#endif //__LHTMLSCREEN_H_
