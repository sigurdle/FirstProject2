/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Aug 10 18:37:37 2003
 */
/* Compiler settings for C:\MMStudio\Extras\LQuant\LQuant.idl:
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

#ifndef __LQuant_h__
#define __LQuant_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILQuantizer_FWD_DEFINED__
#define __ILQuantizer_FWD_DEFINED__
typedef interface ILQuantizer ILQuantizer;
#endif 	/* __ILQuantizer_FWD_DEFINED__ */


#ifndef __LQuantizer_FWD_DEFINED__
#define __LQuantizer_FWD_DEFINED__

#ifdef __cplusplus
typedef class LQuantizer LQuantizer;
#else
typedef struct LQuantizer LQuantizer;
#endif /* __cplusplus */

#endif 	/* __LQuantizer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILQuantizer_INTERFACE_DEFINED__
#define __ILQuantizer_INTERFACE_DEFINED__

/* interface ILQuantizer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILQuantizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E94AEE1C-A0CB-4DC1-9DD7-A3594F0A1F9D")
    ILQuantizer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILQuantizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILQuantizer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILQuantizer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILQuantizer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILQuantizer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILQuantizer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILQuantizer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILQuantizer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ILQuantizerVtbl;

    interface ILQuantizer
    {
        CONST_VTBL struct ILQuantizerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILQuantizer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILQuantizer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILQuantizer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILQuantizer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILQuantizer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILQuantizer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILQuantizer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILQuantizer_INTERFACE_DEFINED__ */



#ifndef __LQUANTLib_LIBRARY_DEFINED__
#define __LQUANTLib_LIBRARY_DEFINED__

/* library LQUANTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LQUANTLib;

EXTERN_C const CLSID CLSID_LQuantizer;

#ifdef __cplusplus

class DECLSPEC_UUID("9712CD25-6316-4AE2-8B9E-7F8B37620676")
LQuantizer;
#endif
#endif /* __LQUANTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
