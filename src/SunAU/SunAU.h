/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 27 11:34:44 2003
 */
/* Compiler settings for C:\MMStudio\Extras\SunAU\SunAU.idl:
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

#ifndef __SunAU_h__
#define __SunAU_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAUDecoder_FWD_DEFINED__
#define __IAUDecoder_FWD_DEFINED__
typedef interface IAUDecoder IAUDecoder;
#endif 	/* __IAUDecoder_FWD_DEFINED__ */


#ifndef __AUDecoder_FWD_DEFINED__
#define __AUDecoder_FWD_DEFINED__

#ifdef __cplusplus
typedef class AUDecoder AUDecoder;
#else
typedef struct AUDecoder AUDecoder;
#endif /* __cplusplus */

#endif 	/* __AUDecoder_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAUDecoder_INTERFACE_DEFINED__
#define __IAUDecoder_INTERFACE_DEFINED__

/* interface IAUDecoder */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAUDecoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C71D895D-0DE1-4899-AB3A-A1D8E30E5609")
    IAUDecoder : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAUDecoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAUDecoder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAUDecoder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAUDecoder __RPC_FAR * This);
        
        END_INTERFACE
    } IAUDecoderVtbl;

    interface IAUDecoder
    {
        CONST_VTBL struct IAUDecoderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAUDecoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAUDecoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAUDecoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAUDecoder_INTERFACE_DEFINED__ */



#ifndef __SUNAULib_LIBRARY_DEFINED__
#define __SUNAULib_LIBRARY_DEFINED__

/* library SUNAULib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SUNAULib;

EXTERN_C const CLSID CLSID_AUDecoder;

#ifdef __cplusplus

class DECLSPEC_UUID("564F6C30-30F8-4EFF-98AF-B7530DC7FDC6")
AUDecoder;
#endif
#endif /* __SUNAULib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
