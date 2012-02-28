/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Aug 16 13:24:54 2003
 */
/* Compiler settings for C:\MMStudio\Extras\LXMoviePlayer\LXMoviePlayer.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __LXMoviePlayer_h__
#define __LXMoviePlayer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILXMoviePlayerCtl_FWD_DEFINED__
#define __ILXMoviePlayerCtl_FWD_DEFINED__
typedef interface ILXMoviePlayerCtl ILXMoviePlayerCtl;
#endif 	/* __ILXMoviePlayerCtl_FWD_DEFINED__ */


#ifndef ___ILXMoviePlayerCtlEvents_FWD_DEFINED__
#define ___ILXMoviePlayerCtlEvents_FWD_DEFINED__
typedef interface _ILXMoviePlayerCtlEvents _ILXMoviePlayerCtlEvents;
#endif 	/* ___ILXMoviePlayerCtlEvents_FWD_DEFINED__ */


#ifndef __LXMoviePlayerCtl_FWD_DEFINED__
#define __LXMoviePlayerCtl_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXMoviePlayerCtl LXMoviePlayerCtl;
#else
typedef struct LXMoviePlayerCtl LXMoviePlayerCtl;
#endif /* __cplusplus */

#endif 	/* __LXMoviePlayerCtl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILXMoviePlayerCtl_INTERFACE_DEFINED__
#define __ILXMoviePlayerCtl_INTERFACE_DEFINED__

/* interface ILXMoviePlayerCtl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILXMoviePlayerCtl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DC146849-8945-46DB-B12A-77B1D673A04E")
    ILXMoviePlayerCtl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_src( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_src( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILXMoviePlayerCtlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILXMoviePlayerCtl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILXMoviePlayerCtl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILXMoviePlayerCtl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILXMoviePlayerCtl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILXMoviePlayerCtl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILXMoviePlayerCtl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILXMoviePlayerCtl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_src )( 
            ILXMoviePlayerCtl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_src )( 
            ILXMoviePlayerCtl __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ILXMoviePlayerCtlVtbl;

    interface ILXMoviePlayerCtl
    {
        CONST_VTBL struct ILXMoviePlayerCtlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXMoviePlayerCtl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXMoviePlayerCtl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXMoviePlayerCtl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXMoviePlayerCtl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILXMoviePlayerCtl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILXMoviePlayerCtl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILXMoviePlayerCtl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILXMoviePlayerCtl_get_src(This,pVal)	\
    (This)->lpVtbl -> get_src(This,pVal)

#define ILXMoviePlayerCtl_put_src(This,newVal)	\
    (This)->lpVtbl -> put_src(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILXMoviePlayerCtl_get_src_Proxy( 
    ILXMoviePlayerCtl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ILXMoviePlayerCtl_get_src_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILXMoviePlayerCtl_put_src_Proxy( 
    ILXMoviePlayerCtl __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILXMoviePlayerCtl_put_src_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILXMoviePlayerCtl_INTERFACE_DEFINED__ */



#ifndef __LXMOVIEPLAYERLib_LIBRARY_DEFINED__
#define __LXMOVIEPLAYERLib_LIBRARY_DEFINED__

/* library LXMOVIEPLAYERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LXMOVIEPLAYERLib;

#ifndef ___ILXMoviePlayerCtlEvents_DISPINTERFACE_DEFINED__
#define ___ILXMoviePlayerCtlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILXMoviePlayerCtlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILXMoviePlayerCtlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E60563AB-206B-4C75-A37F-E814F23F795A")
    _ILXMoviePlayerCtlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILXMoviePlayerCtlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ILXMoviePlayerCtlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ILXMoviePlayerCtlEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ILXMoviePlayerCtlEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ILXMoviePlayerCtlEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ILXMoviePlayerCtlEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ILXMoviePlayerCtlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ILXMoviePlayerCtlEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ILXMoviePlayerCtlEventsVtbl;

    interface _ILXMoviePlayerCtlEvents
    {
        CONST_VTBL struct _ILXMoviePlayerCtlEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILXMoviePlayerCtlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ILXMoviePlayerCtlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ILXMoviePlayerCtlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ILXMoviePlayerCtlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ILXMoviePlayerCtlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ILXMoviePlayerCtlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ILXMoviePlayerCtlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILXMoviePlayerCtlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LXMoviePlayerCtl;

#ifdef __cplusplus

class DECLSPEC_UUID("05FF8398-3EFF-4134-B849-6ED9058C7FAB")
LXMoviePlayerCtl;
#endif
#endif /* __LXMOVIEPLAYERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
