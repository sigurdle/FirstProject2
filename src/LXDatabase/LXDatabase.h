/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jul 20 02:07:40 2003
 */
/* Compiler settings for C:\MMStudio\Extras\LXDatabase\LXDatabase.idl:
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

#ifndef __LXDatabase_h__
#define __LXDatabase_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILXDatabaseApp_FWD_DEFINED__
#define __ILXDatabaseApp_FWD_DEFINED__
typedef interface ILXDatabaseApp ILXDatabaseApp;
#endif 	/* __ILXDatabaseApp_FWD_DEFINED__ */


#ifndef __LXDatabaseApp_FWD_DEFINED__
#define __LXDatabaseApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXDatabaseApp LXDatabaseApp;
#else
typedef struct LXDatabaseApp LXDatabaseApp;
#endif /* __cplusplus */

#endif 	/* __LXDatabaseApp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILXDatabaseApp_INTERFACE_DEFINED__
#define __ILXDatabaseApp_INTERFACE_DEFINED__

/* interface ILXDatabaseApp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILXDatabaseApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("615F3F3E-055E-4D44-AC2C-DA581EB8C421")
    ILXDatabaseApp : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILXDatabaseAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILXDatabaseApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILXDatabaseApp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILXDatabaseApp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILXDatabaseApp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILXDatabaseApp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILXDatabaseApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILXDatabaseApp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ILXDatabaseAppVtbl;

    interface ILXDatabaseApp
    {
        CONST_VTBL struct ILXDatabaseAppVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXDatabaseApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXDatabaseApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXDatabaseApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXDatabaseApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILXDatabaseApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILXDatabaseApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILXDatabaseApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILXDatabaseApp_INTERFACE_DEFINED__ */



#ifndef __LXDATABASELib_LIBRARY_DEFINED__
#define __LXDATABASELib_LIBRARY_DEFINED__

/* library LXDATABASELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LXDATABASELib;

EXTERN_C const CLSID CLSID_LXDatabaseApp;

#ifdef __cplusplus

class DECLSPEC_UUID("8CE80A13-C4E2-49AF-A66D-7D7713CCE676")
LXDatabaseApp;
#endif
#endif /* __LXDATABASELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
