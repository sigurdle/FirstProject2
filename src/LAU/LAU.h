

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Feb 03 19:37:02 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LAU\LAU.idl:
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

#ifndef __LAU_h__
#define __LAU_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILAUParser_FWD_DEFINED__
#define __ILAUParser_FWD_DEFINED__
typedef interface ILAUParser ILAUParser;
#endif 	/* __ILAUParser_FWD_DEFINED__ */


#ifndef __LAUParser_FWD_DEFINED__
#define __LAUParser_FWD_DEFINED__

#ifdef __cplusplus
typedef class LAUParser LAUParser;
#else
typedef struct LAUParser LAUParser;
#endif /* __cplusplus */

#endif 	/* __LAUParser_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ILAUParser_INTERFACE_DEFINED__
#define __ILAUParser_INTERFACE_DEFINED__

/* interface ILAUParser */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILAUParser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6AD7764-4EEF-42D1-B189-ADA403886744")
    ILAUParser : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILAUParserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILAUParser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILAUParser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILAUParser * This);
        
        END_INTERFACE
    } ILAUParserVtbl;

    interface ILAUParser
    {
        CONST_VTBL struct ILAUParserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILAUParser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILAUParser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILAUParser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILAUParser_INTERFACE_DEFINED__ */



#ifndef __LAULib_LIBRARY_DEFINED__
#define __LAULib_LIBRARY_DEFINED__

/* library LAULib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LAULib;

EXTERN_C const CLSID CLSID_LAUParser;

#ifdef __cplusplus

class DECLSPEC_UUID("DD92D3FB-DB6D-4492-BCFF-691B4A98B431")
LAUParser;
#endif
#endif /* __LAULib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


