

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Dec 22 03:09:39 2003
 */
/* Compiler settings for C:\MMStudio\Extras\LLWO\LLWO.idl:
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

#ifndef __LLWO_h__
#define __LLWO_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILWOLoader_FWD_DEFINED__
#define __ILWOLoader_FWD_DEFINED__
typedef interface ILWOLoader ILWOLoader;
#endif 	/* __ILWOLoader_FWD_DEFINED__ */


#ifndef __LWOLoader_FWD_DEFINED__
#define __LWOLoader_FWD_DEFINED__

#ifdef __cplusplus
typedef class LWOLoader LWOLoader;
#else
typedef struct LWOLoader LWOLoader;
#endif /* __cplusplus */

#endif 	/* __LWOLoader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LX3D.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ILWOLoader_INTERFACE_DEFINED__
#define __ILWOLoader_INTERFACE_DEFINED__

/* interface ILWOLoader */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILWOLoader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("01DD6457-CD2F-4E25-94BA-196FDAE37960")
    ILWOLoader : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILWOLoaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILWOLoader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILWOLoader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILWOLoader * This);
        
        END_INTERFACE
    } ILWOLoaderVtbl;

    interface ILWOLoader
    {
        CONST_VTBL struct ILWOLoaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILWOLoader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILWOLoader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILWOLoader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILWOLoader_INTERFACE_DEFINED__ */



#ifndef __LLWOLib_LIBRARY_DEFINED__
#define __LLWOLib_LIBRARY_DEFINED__

/* library LLWOLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LLWOLib;

EXTERN_C const CLSID CLSID_LWOLoader;

#ifdef __cplusplus

class DECLSPEC_UUID("8B74B25F-FD0E-4A82-8C2F-DF50E3BFF00E")
LWOLoader;
#endif
#endif /* __LLWOLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


