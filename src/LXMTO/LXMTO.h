

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Feb 12 22:03:06 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LXMTO\LXMTO.idl:
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

#ifndef __LXMTO_h__
#define __LXMTO_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILXMTODocument_FWD_DEFINED__
#define __ILXMTODocument_FWD_DEFINED__
typedef interface ILXMTODocument ILXMTODocument;
#endif 	/* __ILXMTODocument_FWD_DEFINED__ */


#ifndef __LXMTODocument_FWD_DEFINED__
#define __LXMTODocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXMTODocument LXMTODocument;
#else
typedef struct LXMTODocument LXMTODocument;
#endif /* __cplusplus */

#endif 	/* __LXMTODocument_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ILXMTODocument_INTERFACE_DEFINED__
#define __ILXMTODocument_INTERFACE_DEFINED__

/* interface ILXMTODocument */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILXMTODocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9AE89A6C-7BC6-4D69-93E3-200CAFC715EF")
    ILXMTODocument : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILXMTODocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILXMTODocument * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILXMTODocument * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILXMTODocument * This);
        
        END_INTERFACE
    } ILXMTODocumentVtbl;

    interface ILXMTODocument
    {
        CONST_VTBL struct ILXMTODocumentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXMTODocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXMTODocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXMTODocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILXMTODocument_INTERFACE_DEFINED__ */



#ifndef __LXMTOLib_LIBRARY_DEFINED__
#define __LXMTOLib_LIBRARY_DEFINED__

/* library LXMTOLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LXMTOLib;

EXTERN_C const CLSID CLSID_LXMTODocument;

#ifdef __cplusplus

class DECLSPEC_UUID("6B865270-BF00-487D-A31A-F80CEC09925F")
LXMTODocument;
#endif
#endif /* __LXMTOLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


