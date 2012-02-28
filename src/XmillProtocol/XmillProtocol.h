/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 19 10:22:09 2002
 */
/* Compiler settings for C:\MMStudio\Extras\XmillProtocol\XmillProtocol.idl:
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

#ifndef __XmillProtocol_h__
#define __XmillProtocol_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IXmillFilesProtocol_FWD_DEFINED__
#define __IXmillFilesProtocol_FWD_DEFINED__
typedef interface IXmillFilesProtocol IXmillFilesProtocol;
#endif 	/* __IXmillFilesProtocol_FWD_DEFINED__ */


#ifndef __XmillFilesProtocol_FWD_DEFINED__
#define __XmillFilesProtocol_FWD_DEFINED__

#ifdef __cplusplus
typedef class XmillFilesProtocol XmillFilesProtocol;
#else
typedef struct XmillFilesProtocol XmillFilesProtocol;
#endif /* __cplusplus */

#endif 	/* __XmillFilesProtocol_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IXmillFilesProtocol_INTERFACE_DEFINED__
#define __IXmillFilesProtocol_INTERFACE_DEFINED__

/* interface IXmillFilesProtocol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IXmillFilesProtocol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11DC4161-9B00-4585-BA28-EE1ED85A18AA")
    IXmillFilesProtocol : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IXmillFilesProtocolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXmillFilesProtocol __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXmillFilesProtocol __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXmillFilesProtocol __RPC_FAR * This);
        
        END_INTERFACE
    } IXmillFilesProtocolVtbl;

    interface IXmillFilesProtocol
    {
        CONST_VTBL struct IXmillFilesProtocolVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXmillFilesProtocol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXmillFilesProtocol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXmillFilesProtocol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXmillFilesProtocol_INTERFACE_DEFINED__ */



#ifndef __XMILLPROTOCOLLib_LIBRARY_DEFINED__
#define __XMILLPROTOCOLLib_LIBRARY_DEFINED__

/* library XMILLPROTOCOLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_XMILLPROTOCOLLib;

EXTERN_C const CLSID CLSID_XmillFilesProtocol;

#ifdef __cplusplus

class DECLSPEC_UUID("7BD72C4B-4315-4AA9-ACD0-AF03FDBB6510")
XmillFilesProtocol;
#endif
#endif /* __XMILLPROTOCOLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
