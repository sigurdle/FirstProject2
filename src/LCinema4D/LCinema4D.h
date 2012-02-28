

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Fri Dec 19 10:13:08 2003
 */
/* Compiler settings for C:\MMStudio\Extras\LCinema4D\LCinema4D.idl:
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

#ifndef __LCinema4D_h__
#define __LCinema4D_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDOK5Loader_FWD_DEFINED__
#define __IDOK5Loader_FWD_DEFINED__
typedef interface IDOK5Loader IDOK5Loader;
#endif 	/* __IDOK5Loader_FWD_DEFINED__ */


#ifndef __DOK5Loader_FWD_DEFINED__
#define __DOK5Loader_FWD_DEFINED__

#ifdef __cplusplus
typedef class DOK5Loader DOK5Loader;
#else
typedef struct DOK5Loader DOK5Loader;
#endif /* __cplusplus */

#endif 	/* __DOK5Loader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LX3D.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IDOK5Loader_INTERFACE_DEFINED__
#define __IDOK5Loader_INTERFACE_DEFINED__

/* interface IDOK5Loader */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDOK5Loader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0456369-0EF0-4840-B115-46EF9BF21174")
    IDOK5Loader : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDOK5LoaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDOK5Loader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDOK5Loader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDOK5Loader * This);
        
        END_INTERFACE
    } IDOK5LoaderVtbl;

    interface IDOK5Loader
    {
        CONST_VTBL struct IDOK5LoaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDOK5Loader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDOK5Loader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDOK5Loader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDOK5Loader_INTERFACE_DEFINED__ */



#ifndef __LCINEMA4DLib_LIBRARY_DEFINED__
#define __LCINEMA4DLib_LIBRARY_DEFINED__

/* library LCINEMA4DLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LCINEMA4DLib;

EXTERN_C const CLSID CLSID_DOK5Loader;

#ifdef __cplusplus

class DECLSPEC_UUID("3F591FC9-3C94-43AB-B4BA-7E4ED1BF03E3")
DOK5Loader;
#endif
#endif /* __LCINEMA4DLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


