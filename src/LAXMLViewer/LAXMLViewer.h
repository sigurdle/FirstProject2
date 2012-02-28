

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue May 25 21:32:05 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LAXMLViewer\LAXMLViewer.idl:
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


#ifndef __LAXMLViewer_h__
#define __LAXMLViewer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __LHTMLActiveDocument_FWD_DEFINED__
#define __LHTMLActiveDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class LHTMLActiveDocument LHTMLActiveDocument;
#else
typedef struct LHTMLActiveDocument LHTMLActiveDocument;
#endif /* __cplusplus */

#endif 	/* __LHTMLActiveDocument_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LXUI.h"
#include "LHTML.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __LAXMLVIEWERLib_LIBRARY_DEFINED__
#define __LAXMLVIEWERLib_LIBRARY_DEFINED__

/* library LAXMLVIEWERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LAXMLVIEWERLib;

EXTERN_C const CLSID CLSID_LHTMLActiveDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("EBE43D44-10E0-4CA3-9EB2-EBCD22BF746A")
LHTMLActiveDocument;
#endif
#endif /* __LAXMLVIEWERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


