

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue May 25 21:59:50 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LXDocumentViewer\LXDocumentViewer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __LXDocumentViewer_h__
#define __LXDocumentViewer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILXDocumentViewerApp_FWD_DEFINED__
#define __ILXDocumentViewerApp_FWD_DEFINED__
typedef interface ILXDocumentViewerApp ILXDocumentViewerApp;
#endif 	/* __ILXDocumentViewerApp_FWD_DEFINED__ */


#ifndef ___IActiveCntDocumentEvents_FWD_DEFINED__
#define ___IActiveCntDocumentEvents_FWD_DEFINED__
typedef interface _IActiveCntDocumentEvents _IActiveCntDocumentEvents;
#endif 	/* ___IActiveCntDocumentEvents_FWD_DEFINED__ */


#ifndef __ILMoviePlayer_FWD_DEFINED__
#define __ILMoviePlayer_FWD_DEFINED__
typedef interface ILMoviePlayer ILMoviePlayer;
#endif 	/* __ILMoviePlayer_FWD_DEFINED__ */


#ifndef __LXDocumentViewerApp_FWD_DEFINED__
#define __LXDocumentViewerApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXDocumentViewerApp LXDocumentViewerApp;
#else
typedef struct LXDocumentViewerApp LXDocumentViewerApp;
#endif /* __cplusplus */

#endif 	/* __LXDocumentViewerApp_FWD_DEFINED__ */


#ifndef __LMoviePlayer_FWD_DEFINED__
#define __LMoviePlayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class LMoviePlayer LMoviePlayer;
#else
typedef struct LMoviePlayer LMoviePlayer;
#endif /* __cplusplus */

#endif 	/* __LMoviePlayer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dispex.h"
#include "LXUI.h"
#include "LXML.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ILXDocumentViewerApp_INTERFACE_DEFINED__
#define __ILXDocumentViewerApp_INTERFACE_DEFINED__

/* interface ILXDocumentViewerApp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILXDocumentViewerApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3EBCEAC1-F58D-4D3C-B77F-E5B1BEE6AF7D")
    ILXDocumentViewerApp : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILXDocumentViewerAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILXDocumentViewerApp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILXDocumentViewerApp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILXDocumentViewerApp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILXDocumentViewerApp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILXDocumentViewerApp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILXDocumentViewerApp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILXDocumentViewerApp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ILXDocumentViewerAppVtbl;

    interface ILXDocumentViewerApp
    {
        CONST_VTBL struct ILXDocumentViewerAppVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXDocumentViewerApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXDocumentViewerApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXDocumentViewerApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXDocumentViewerApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILXDocumentViewerApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILXDocumentViewerApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILXDocumentViewerApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILXDocumentViewerApp_INTERFACE_DEFINED__ */



#ifndef __LXDOCUMENTVIEWERLib_LIBRARY_DEFINED__
#define __LXDOCUMENTVIEWERLib_LIBRARY_DEFINED__

/* library LXDOCUMENTVIEWERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LXDOCUMENTVIEWERLib;

#ifndef ___IActiveCntDocumentEvents_DISPINTERFACE_DEFINED__
#define ___IActiveCntDocumentEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IActiveCntDocumentEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IActiveCntDocumentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("906202FC-347D-42C7-A95B-5799590F1124")
    _IActiveCntDocumentEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IActiveCntDocumentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IActiveCntDocumentEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IActiveCntDocumentEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IActiveCntDocumentEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IActiveCntDocumentEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IActiveCntDocumentEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IActiveCntDocumentEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IActiveCntDocumentEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IActiveCntDocumentEventsVtbl;

    interface _IActiveCntDocumentEvents
    {
        CONST_VTBL struct _IActiveCntDocumentEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IActiveCntDocumentEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IActiveCntDocumentEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IActiveCntDocumentEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IActiveCntDocumentEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IActiveCntDocumentEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IActiveCntDocumentEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IActiveCntDocumentEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IActiveCntDocumentEvents_DISPINTERFACE_DEFINED__ */


#ifndef __ILMoviePlayer_INTERFACE_DEFINED__
#define __ILMoviePlayer_INTERFACE_DEFINED__

/* interface ILMoviePlayer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILMoviePlayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B8AF2CD-001C-4ABD-B3EF-012457500A45")
    ILMoviePlayer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILMoviePlayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILMoviePlayer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILMoviePlayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILMoviePlayer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILMoviePlayer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILMoviePlayer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILMoviePlayer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILMoviePlayer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ILMoviePlayerVtbl;

    interface ILMoviePlayer
    {
        CONST_VTBL struct ILMoviePlayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMoviePlayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMoviePlayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMoviePlayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMoviePlayer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILMoviePlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILMoviePlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILMoviePlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILMoviePlayer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LXDocumentViewerApp;

#ifdef __cplusplus

class DECLSPEC_UUID("E33E6375-6143-4BB7-89E5-7496178CFF16")
LXDocumentViewerApp;
#endif

EXTERN_C const CLSID CLSID_LMoviePlayer;

#ifdef __cplusplus

class DECLSPEC_UUID("68844FCB-C864-45DA-9C1A-8F1EEC095D79")
LMoviePlayer;
#endif
#endif /* __LXDOCUMENTVIEWERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


