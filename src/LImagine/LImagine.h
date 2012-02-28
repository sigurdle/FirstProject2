

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Jan 12 07:21:50 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LImagine\LImagine.idl:
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

#ifndef __LImagine_h__
#define __LImagine_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITDDDLoader_FWD_DEFINED__
#define __ITDDDLoader_FWD_DEFINED__
typedef interface ITDDDLoader ITDDDLoader;
#endif 	/* __ITDDDLoader_FWD_DEFINED__ */


#ifndef __TDDDLoader_FWD_DEFINED__
#define __TDDDLoader_FWD_DEFINED__

#ifdef __cplusplus
typedef class TDDDLoader TDDDLoader;
#else
typedef struct TDDDLoader TDDDLoader;
#endif /* __cplusplus */

#endif 	/* __TDDDLoader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LX3D.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ITDDDLoader_INTERFACE_DEFINED__
#define __ITDDDLoader_INTERFACE_DEFINED__

/* interface ITDDDLoader */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITDDDLoader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E252185-3725-4A10-8BCA-FD5B77B591DC")
    ITDDDLoader : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITDDDLoaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITDDDLoader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITDDDLoader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITDDDLoader * This);
        
        END_INTERFACE
    } ITDDDLoaderVtbl;

    interface ITDDDLoader
    {
        CONST_VTBL struct ITDDDLoaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITDDDLoader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITDDDLoader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITDDDLoader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITDDDLoader_INTERFACE_DEFINED__ */



#ifndef __LIMAGINELib_LIBRARY_DEFINED__
#define __LIMAGINELib_LIBRARY_DEFINED__

/* library LIMAGINELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LIMAGINELib;

EXTERN_C const CLSID CLSID_TDDDLoader;

#ifdef __cplusplus

class DECLSPEC_UUID("06C36053-C0F8-4EA9-A6AA-E2BCA1CB5B2C")
TDDDLoader;
#endif
#endif /* __LIMAGINELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


