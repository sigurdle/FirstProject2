/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 03 17:05:55 2002
 */
/* Compiler settings for C:\MMStudio\Extras\LHTMLHelp\LHTMLHelp.idl:
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

#ifndef __LHTMLHelp_h__
#define __LHTMLHelp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILHTMLHelpWindow_FWD_DEFINED__
#define __ILHTMLHelpWindow_FWD_DEFINED__
typedef interface ILHTMLHelpWindow ILHTMLHelpWindow;
#endif 	/* __ILHTMLHelpWindow_FWD_DEFINED__ */


#ifndef __LHTMLHelpWindow_FWD_DEFINED__
#define __LHTMLHelpWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class LHTMLHelpWindow LHTMLHelpWindow;
#else
typedef struct LHTMLHelpWindow LHTMLHelpWindow;
#endif /* __cplusplus */

#endif 	/* __LHTMLHelpWindow_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LHTML.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILHTMLHelpWindow_INTERFACE_DEFINED__
#define __ILHTMLHelpWindow_INTERFACE_DEFINED__

/* interface ILHTMLHelpWindow */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILHTMLHelpWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52EAF84D-FED7-4A91-9BF5-6F4C227AC1B3")
    ILHTMLHelpWindow : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowHelp( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BOOL __RPC_FAR *success) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILHTMLHelpWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILHTMLHelpWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILHTMLHelpWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILHTMLHelpWindow __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowHelp )( 
            ILHTMLHelpWindow __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BOOL __RPC_FAR *success);
        
        END_INTERFACE
    } ILHTMLHelpWindowVtbl;

    interface ILHTMLHelpWindow
    {
        CONST_VTBL struct ILHTMLHelpWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILHTMLHelpWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILHTMLHelpWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILHTMLHelpWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILHTMLHelpWindow_ShowHelp(This,pathName,success)	\
    (This)->lpVtbl -> ShowHelp(This,pathName,success)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILHTMLHelpWindow_ShowHelp_Proxy( 
    ILHTMLHelpWindow __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ BOOL __RPC_FAR *success);


void __RPC_STUB ILHTMLHelpWindow_ShowHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILHTMLHelpWindow_INTERFACE_DEFINED__ */



#ifndef __LHTMLHELPLib_LIBRARY_DEFINED__
#define __LHTMLHELPLib_LIBRARY_DEFINED__

/* library LHTMLHELPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LHTMLHELPLib;

EXTERN_C const CLSID CLSID_LHTMLHelpWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("6E524608-0305-4753-983A-F1274D783288")
LHTMLHelpWindow;
#endif
#endif /* __LHTMLHELPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
