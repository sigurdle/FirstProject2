/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jul 20 05:50:02 2003
 */
/* Compiler settings for C:\MMStudio\Extras\LXMedia\LXMedia.idl:
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

#ifndef __LXMedia_h__
#define __LXMedia_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMediaClipDocument_FWD_DEFINED__
#define __IEMediaClipDocument_FWD_DEFINED__
typedef interface IEMediaClipDocument IEMediaClipDocument;
#endif 	/* __IEMediaClipDocument_FWD_DEFINED__ */


#ifndef __IEPlayListDocument_FWD_DEFINED__
#define __IEPlayListDocument_FWD_DEFINED__
typedef interface IEPlayListDocument IEPlayListDocument;
#endif 	/* __IEPlayListDocument_FWD_DEFINED__ */


#ifndef __ILXMediaApp_FWD_DEFINED__
#define __ILXMediaApp_FWD_DEFINED__
typedef interface ILXMediaApp ILXMediaApp;
#endif 	/* __ILXMediaApp_FWD_DEFINED__ */


#ifndef __EMediaClipDocument_FWD_DEFINED__
#define __EMediaClipDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMediaClipDocument EMediaClipDocument;
#else
typedef struct EMediaClipDocument EMediaClipDocument;
#endif /* __cplusplus */

#endif 	/* __EMediaClipDocument_FWD_DEFINED__ */


#ifndef __EPlayListDocument_FWD_DEFINED__
#define __EPlayListDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class EPlayListDocument EPlayListDocument;
#else
typedef struct EPlayListDocument EPlayListDocument;
#endif /* __cplusplus */

#endif 	/* __EPlayListDocument_FWD_DEFINED__ */


#ifndef __LXMediaApp_FWD_DEFINED__
#define __LXMediaApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXMediaApp LXMediaApp;
#else
typedef struct LXMediaApp LXMediaApp;
#endif /* __cplusplus */

#endif 	/* __LXMediaApp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LXFramework.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEMediaClipDocument_INTERFACE_DEFINED__
#define __IEMediaClipDocument_INTERFACE_DEFINED__

/* interface IEMediaClipDocument */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMediaClipDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E3CD4792-4EB6-4A7D-9065-36FE09F61AD3")
    IEMediaClipDocument : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IEMediaClipDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMediaClipDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMediaClipDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMediaClipDocument __RPC_FAR * This);
        
        END_INTERFACE
    } IEMediaClipDocumentVtbl;

    interface IEMediaClipDocument
    {
        CONST_VTBL struct IEMediaClipDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMediaClipDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMediaClipDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMediaClipDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMediaClipDocument_INTERFACE_DEFINED__ */


#ifndef __IEPlayListDocument_INTERFACE_DEFINED__
#define __IEPlayListDocument_INTERFACE_DEFINED__

/* interface IEPlayListDocument */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEPlayListDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88E98AEB-9168-473D-91EC-7E46043F2858")
    IEPlayListDocument : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IEPlayListDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEPlayListDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEPlayListDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEPlayListDocument __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEPlayListDocument __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEPlayListDocument __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEPlayListDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEPlayListDocument __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IEPlayListDocumentVtbl;

    interface IEPlayListDocument
    {
        CONST_VTBL struct IEPlayListDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEPlayListDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEPlayListDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEPlayListDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEPlayListDocument_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEPlayListDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEPlayListDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEPlayListDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEPlayListDocument_INTERFACE_DEFINED__ */


#ifndef __ILXMediaApp_INTERFACE_DEFINED__
#define __ILXMediaApp_INTERFACE_DEFINED__

/* interface ILXMediaApp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILXMediaApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CEBDBAD6-DAEA-4141-B9AC-1A0AAFAD5187")
    ILXMediaApp : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILXMediaAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILXMediaApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILXMediaApp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILXMediaApp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILXMediaApp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILXMediaApp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILXMediaApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILXMediaApp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ILXMediaAppVtbl;

    interface ILXMediaApp
    {
        CONST_VTBL struct ILXMediaAppVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXMediaApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXMediaApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXMediaApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXMediaApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILXMediaApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILXMediaApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILXMediaApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILXMediaApp_INTERFACE_DEFINED__ */



#ifndef __LXMEDIALib_LIBRARY_DEFINED__
#define __LXMEDIALib_LIBRARY_DEFINED__

/* library LXMEDIALib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LXMEDIALib;

EXTERN_C const CLSID CLSID_EMediaClipDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("5584BDB6-252F-4B2F-9BA5-6264D0E0FA2F")
EMediaClipDocument;
#endif

EXTERN_C const CLSID CLSID_EPlayListDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("BA37C92F-555B-41EA-A747-6E3CF303D85A")
EPlayListDocument;
#endif

EXTERN_C const CLSID CLSID_LXMediaApp;

#ifdef __cplusplus

class DECLSPEC_UUID("0ED9BE03-9DDA-4542-BABE-261613EADE53")
LXMediaApp;
#endif
#endif /* __LXMEDIALib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
