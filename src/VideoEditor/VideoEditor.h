/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Apr 09 04:04:52 2003
 */
/* Compiler settings for C:\MMStudio\Extras\VideoEditor\VideoEditor.idl:
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

#ifndef __VideoEditor_h__
#define __VideoEditor_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IProject_FWD_DEFINED__
#define __IProject_FWD_DEFINED__
typedef interface IProject IProject;
#endif 	/* __IProject_FWD_DEFINED__ */


#ifndef __IFootage_FWD_DEFINED__
#define __IFootage_FWD_DEFINED__
typedef interface IFootage IFootage;
#endif 	/* __IFootage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "UI.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __VIDEOEDITORLib_LIBRARY_DEFINED__
#define __VIDEOEDITORLib_LIBRARY_DEFINED__

/* library VIDEOEDITORLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VIDEOEDITORLib;

#ifndef __IProject_INTERFACE_DEFINED__
#define __IProject_INTERFACE_DEFINED__

/* interface IProject */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IProject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B69F408-7F96-4050-ACFB-F03DF062ED42")
    IProject : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IProjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IProject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IProject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IProject __RPC_FAR * This);
        
        END_INTERFACE
    } IProjectVtbl;

    interface IProject
    {
        CONST_VTBL struct IProjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProject_INTERFACE_DEFINED__ */


#ifndef __IFootage_INTERFACE_DEFINED__
#define __IFootage_INTERFACE_DEFINED__

/* interface IFootage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFootage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4FEDE5C-D079-49f8-B7D6-BB47AC23E53B")
    IFootage : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFootageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFootage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFootage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFootage __RPC_FAR * This);
        
        END_INTERFACE
    } IFootageVtbl;

    interface IFootage
    {
        CONST_VTBL struct IFootageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFootage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFootage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFootage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFootage_INTERFACE_DEFINED__ */

#endif /* __VIDEOEDITORLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
