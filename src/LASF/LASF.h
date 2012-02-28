

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Jan 19 17:44:38 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LASF\LASF.idl:
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

#ifndef __LASF_h__
#define __LASF_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IASFLoader_FWD_DEFINED__
#define __IASFLoader_FWD_DEFINED__
typedef interface IASFLoader IASFLoader;
#endif 	/* __IASFLoader_FWD_DEFINED__ */


#ifndef __ASFLoader_FWD_DEFINED__
#define __ASFLoader_FWD_DEFINED__

#ifdef __cplusplus
typedef class ASFLoader ASFLoader;
#else
typedef struct ASFLoader ASFLoader;
#endif /* __cplusplus */

#endif 	/* __ASFLoader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IASFLoader_INTERFACE_DEFINED__
#define __IASFLoader_INTERFACE_DEFINED__

/* interface IASFLoader */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IASFLoader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BAF42D70-1B4D-4C47-8C71-0577D553723E")
    IASFLoader : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IASFLoaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IASFLoader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IASFLoader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IASFLoader * This);
        
        END_INTERFACE
    } IASFLoaderVtbl;

    interface IASFLoader
    {
        CONST_VTBL struct IASFLoaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IASFLoader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IASFLoader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IASFLoader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IASFLoader_INTERFACE_DEFINED__ */



#ifndef __LASFLib_LIBRARY_DEFINED__
#define __LASFLib_LIBRARY_DEFINED__

/* library LASFLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LASFLib;

EXTERN_C const CLSID CLSID_ASFLoader;

#ifdef __cplusplus

class DECLSPEC_UUID("82C552AE-4241-409B-BBBB-7281EA18708A")
ASFLoader;
#endif
#endif /* __LASFLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


