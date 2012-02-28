/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jan 21 23:09:28 2003
 */
/* Compiler settings for C:\MMStudio\Extras\UICustomizeMod\UICustomizeMod.idl:
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

#ifndef __UICustomizeMod_h__
#define __UICustomizeMod_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IUICustomize_FWD_DEFINED__
#define __IUICustomize_FWD_DEFINED__
typedef interface IUICustomize IUICustomize;
#endif 	/* __IUICustomize_FWD_DEFINED__ */


#ifndef ___IUICustomizeEvents_FWD_DEFINED__
#define ___IUICustomizeEvents_FWD_DEFINED__
typedef interface _IUICustomizeEvents _IUICustomizeEvents;
#endif 	/* ___IUICustomizeEvents_FWD_DEFINED__ */


#ifndef __UICustomize_FWD_DEFINED__
#define __UICustomize_FWD_DEFINED__

#ifdef __cplusplus
typedef class UICustomize UICustomize;
#else
typedef struct UICustomize UICustomize;
#endif /* __cplusplus */

#endif 	/* __UICustomize_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IUICustomize_INTERFACE_DEFINED__
#define __IUICustomize_INTERFACE_DEFINED__

/* interface IUICustomize */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUICustomize;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("115B438C-048A-11D6-95F0-0002E3045703")
    IUICustomize : public IDispatch
    {
    public:
        virtual /* [helpstring][local][id] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ IUnknown __RPC_FAR *uiManager,
            /* [in] */ long hParent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUICustomizeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUICustomize __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUICustomize __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUICustomize __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUICustomize __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUICustomize __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUICustomize __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUICustomize __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][local][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IUICustomize __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *uiManager,
            /* [in] */ long hParent);
        
        END_INTERFACE
    } IUICustomizeVtbl;

    interface IUICustomize
    {
        CONST_VTBL struct IUICustomizeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUICustomize_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUICustomize_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUICustomize_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUICustomize_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUICustomize_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUICustomize_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUICustomize_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUICustomize_Show(This,uiManager,hParent)	\
    (This)->lpVtbl -> Show(This,uiManager,hParent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][local][id] */ HRESULT STDMETHODCALLTYPE IUICustomize_Show_Proxy( 
    IUICustomize __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *uiManager,
    /* [in] */ long hParent);


void __RPC_STUB IUICustomize_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUICustomize_INTERFACE_DEFINED__ */



#ifndef __UICUSTOMIZEMODLib_LIBRARY_DEFINED__
#define __UICUSTOMIZEMODLib_LIBRARY_DEFINED__

/* library UICUSTOMIZEMODLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_UICUSTOMIZEMODLib;

#ifndef ___IUICustomizeEvents_DISPINTERFACE_DEFINED__
#define ___IUICustomizeEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUICustomizeEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUICustomizeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("115B438E-048A-11D6-95F0-0002E3045703")
    _IUICustomizeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUICustomizeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IUICustomizeEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IUICustomizeEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IUICustomizeEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IUICustomizeEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IUICustomizeEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IUICustomizeEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IUICustomizeEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IUICustomizeEventsVtbl;

    interface _IUICustomizeEvents
    {
        CONST_VTBL struct _IUICustomizeEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUICustomizeEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUICustomizeEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUICustomizeEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUICustomizeEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUICustomizeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUICustomizeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUICustomizeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUICustomizeEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UICustomize;

#ifdef __cplusplus

class DECLSPEC_UUID("115B438D-048A-11D6-95F0-0002E3045703")
UICustomize;
#endif
#endif /* __UICUSTOMIZEMODLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
