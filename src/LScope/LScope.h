

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Feb 05 18:13:27 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LScope\LScope.idl:
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

#ifndef __LScope_h__
#define __LScope_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILScopeFilter_FWD_DEFINED__
#define __ILScopeFilter_FWD_DEFINED__
typedef interface ILScopeFilter ILScopeFilter;
#endif 	/* __ILScopeFilter_FWD_DEFINED__ */


#ifndef __LScopeFilter_FWD_DEFINED__
#define __LScopeFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class LScopeFilter LScopeFilter;
#else
typedef struct LScopeFilter LScopeFilter;
#endif /* __cplusplus */

#endif 	/* __LScopeFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ILScopeFilter_INTERFACE_DEFINED__
#define __ILScopeFilter_INTERFACE_DEFINED__

/* interface ILScopeFilter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILScopeFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0F094CCF-5860-47A7-9EB5-4B2634FACCED")
    ILScopeFilter : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILScopeFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILScopeFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILScopeFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILScopeFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILScopeFilter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILScopeFilter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILScopeFilter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILScopeFilter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ILScopeFilterVtbl;

    interface ILScopeFilter
    {
        CONST_VTBL struct ILScopeFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILScopeFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILScopeFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILScopeFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILScopeFilter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILScopeFilter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILScopeFilter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILScopeFilter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILScopeFilter_INTERFACE_DEFINED__ */



#ifndef __LSCOPELib_LIBRARY_DEFINED__
#define __LSCOPELib_LIBRARY_DEFINED__

/* library LSCOPELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LSCOPELib;

EXTERN_C const CLSID CLSID_LScopeFilter;

#ifdef __cplusplus

class DECLSPEC_UUID("365117ED-62B2-4188-BDD1-C83FE2F97F3A")
LScopeFilter;
#endif
#endif /* __LSCOPELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


