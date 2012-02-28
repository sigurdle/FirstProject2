/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Aug 10 21:31:19 2003
 */
/* Compiler settings for C:\MMStudio\Extras\SVGM\SVGM.idl:
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

#ifndef __SVGM_h__
#define __SVGM_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISVGMDecoder_FWD_DEFINED__
#define __ISVGMDecoder_FWD_DEFINED__
typedef interface ISVGMDecoder ISVGMDecoder;
#endif 	/* __ISVGMDecoder_FWD_DEFINED__ */


#ifndef __SVGMDecoder_FWD_DEFINED__
#define __SVGMDecoder_FWD_DEFINED__

#ifdef __cplusplus
typedef class SVGMDecoder SVGMDecoder;
#else
typedef struct SVGMDecoder SVGMDecoder;
#endif /* __cplusplus */

#endif 	/* __SVGMDecoder_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISVGMDecoder_INTERFACE_DEFINED__
#define __ISVGMDecoder_INTERFACE_DEFINED__

/* interface ISVGMDecoder */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISVGMDecoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1BF2E473-D653-47F9-8A20-31024E36FB38")
    ISVGMDecoder : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDocument( 
            /* [in] */ IUnknown __RPC_FAR *document) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISVGMDecoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISVGMDecoder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISVGMDecoder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISVGMDecoder __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDocument )( 
            ISVGMDecoder __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *document);
        
        END_INTERFACE
    } ISVGMDecoderVtbl;

    interface ISVGMDecoder
    {
        CONST_VTBL struct ISVGMDecoderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISVGMDecoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISVGMDecoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISVGMDecoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISVGMDecoder_SetDocument(This,document)	\
    (This)->lpVtbl -> SetDocument(This,document)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISVGMDecoder_SetDocument_Proxy( 
    ISVGMDecoder __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *document);


void __RPC_STUB ISVGMDecoder_SetDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISVGMDecoder_INTERFACE_DEFINED__ */



#ifndef __SVGMLib_LIBRARY_DEFINED__
#define __SVGMLib_LIBRARY_DEFINED__

/* library SVGMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SVGMLib;

EXTERN_C const CLSID CLSID_SVGMDecoder;

#ifdef __cplusplus

class DECLSPEC_UUID("B9DCA8D4-BA04-474D-BEC6-655BA8E2D335")
SVGMDecoder;
#endif
#endif /* __SVGMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
