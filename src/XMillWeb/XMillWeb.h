/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jan 21 23:10:19 2003
 */
/* Compiler settings for C:\MMStudio\Extras\XMillWeb\XMillWeb.idl:
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

#ifndef __XMillWeb_h__
#define __XMillWeb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILFileSystem_FWD_DEFINED__
#define __ILFileSystem_FWD_DEFINED__
typedef interface ILFileSystem ILFileSystem;
#endif 	/* __ILFileSystem_FWD_DEFINED__ */


#ifndef __IXmillWebSite_FWD_DEFINED__
#define __IXmillWebSite_FWD_DEFINED__
typedef interface IXmillWebSite IXmillWebSite;
#endif 	/* __IXmillWebSite_FWD_DEFINED__ */


#ifndef __ITest_FWD_DEFINED__
#define __ITest_FWD_DEFINED__
typedef interface ITest ITest;
#endif 	/* __ITest_FWD_DEFINED__ */


#ifndef __IXmillWorkgroup_FWD_DEFINED__
#define __IXmillWorkgroup_FWD_DEFINED__
typedef interface IXmillWorkgroup IXmillWorkgroup;
#endif 	/* __IXmillWorkgroup_FWD_DEFINED__ */


#ifndef __ILFileSystem_FWD_DEFINED__
#define __ILFileSystem_FWD_DEFINED__
typedef interface ILFileSystem ILFileSystem;
#endif 	/* __ILFileSystem_FWD_DEFINED__ */


#ifndef __XmillWebSite_FWD_DEFINED__
#define __XmillWebSite_FWD_DEFINED__

#ifdef __cplusplus
typedef class XmillWebSite XmillWebSite;
#else
typedef struct XmillWebSite XmillWebSite;
#endif /* __cplusplus */

#endif 	/* __XmillWebSite_FWD_DEFINED__ */


#ifndef __Test_FWD_DEFINED__
#define __Test_FWD_DEFINED__

#ifdef __cplusplus
typedef class Test Test;
#else
typedef struct Test Test;
#endif /* __cplusplus */

#endif 	/* __Test_FWD_DEFINED__ */


#ifndef __XmillWorkgroup_FWD_DEFINED__
#define __XmillWorkgroup_FWD_DEFINED__

#ifdef __cplusplus
typedef class XmillWorkgroup XmillWorkgroup;
#else
typedef struct XmillWorkgroup XmillWorkgroup;
#endif /* __cplusplus */

#endif 	/* __XmillWorkgroup_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILFileSystem_INTERFACE_DEFINED__
#define __ILFileSystem_INTERFACE_DEFINED__

/* interface ILFileSystem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILFileSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5CF3CE44-926E-4527-B84E-5A6370055160")
    ILFileSystem : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveArrayAsFile( 
            /* [in] */ BSTR filePath,
            /* [in] */ SAFEARRAY __RPC_FAR * dataArray,
            /* [in] */ BSTR user,
            /* [out][in] */ long __RPC_FAR *file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenFileAsArray( 
            /* [in] */ BSTR filePath,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *dataArray) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFolderDisplayPath( 
            /* [in] */ long folder_id,
            /* [retval][out] */ BSTR __RPC_FAR *displayName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetParentFolderId( 
            /* [in] */ long folder_id,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindOrCreateFolder( 
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR user,
            /* [retval][out] */ long __RPC_FAR *folder_id) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteFilePermanently( 
            /* [in] */ long file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateFolder( 
            /* [in] */ long parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ long __RPC_FAR *pfolder_id) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RenameFile( 
            /* [in] */ long file_id,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFolderDirectoryList( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPathSecurityDescriptor( 
            /* [in] */ BSTR pathName,
            /* [in] */ SAFEARRAY __RPC_FAR * sd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPathSecurityDescriptor( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILFileSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILFileSystem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILFileSystem __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveArrayAsFile )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ BSTR filePath,
            /* [in] */ SAFEARRAY __RPC_FAR * dataArray,
            /* [in] */ BSTR user,
            /* [out][in] */ long __RPC_FAR *file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenFileAsArray )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ BSTR filePath,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *dataArray);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFolderDisplayPath )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ long folder_id,
            /* [retval][out] */ BSTR __RPC_FAR *displayName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentFolderId )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ long folder_id,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindOrCreateFolder )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR user,
            /* [retval][out] */ long __RPC_FAR *folder_id);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteFilePermanently )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ long file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateFolder )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ long parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ long __RPC_FAR *pfolder_id);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenameFile )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ long file_id,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFolderDirectoryList )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPathSecurityDescriptor )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [in] */ SAFEARRAY __RPC_FAR * sd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPathSecurityDescriptor )( 
            ILFileSystem __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        END_INTERFACE
    } ILFileSystemVtbl;

    interface ILFileSystem
    {
        CONST_VTBL struct ILFileSystemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILFileSystem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILFileSystem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILFileSystem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILFileSystem_SaveArrayAsFile(This,filePath,dataArray,user,file_id,pSuccess)	\
    (This)->lpVtbl -> SaveArrayAsFile(This,filePath,dataArray,user,file_id,pSuccess)

#define ILFileSystem_OpenFileAsArray(This,filePath,dataArray)	\
    (This)->lpVtbl -> OpenFileAsArray(This,filePath,dataArray)

#define ILFileSystem_GetFolderDisplayPath(This,folder_id,displayName)	\
    (This)->lpVtbl -> GetFolderDisplayPath(This,folder_id,displayName)

#define ILFileSystem_GetParentFolderId(This,folder_id,pVal)	\
    (This)->lpVtbl -> GetParentFolderId(This,folder_id,pVal)

#define ILFileSystem_FindOrCreateFolder(This,pathName,user,folder_id)	\
    (This)->lpVtbl -> FindOrCreateFolder(This,pathName,user,folder_id)

#define ILFileSystem_DeleteFilePermanently(This,file_id,pSuccess)	\
    (This)->lpVtbl -> DeleteFilePermanently(This,file_id,pSuccess)

#define ILFileSystem_CreateFolder(This,parent_id,name,user,pfolder_id)	\
    (This)->lpVtbl -> CreateFolder(This,parent_id,name,user,pfolder_id)

#define ILFileSystem_RenameFile(This,file_id,name,pSuccess)	\
    (This)->lpVtbl -> RenameFile(This,file_id,name,pSuccess)

#define ILFileSystem_GetFolderDirectoryList(This,pathName,pVal)	\
    (This)->lpVtbl -> GetFolderDirectoryList(This,pathName,pVal)

#define ILFileSystem_SetPathSecurityDescriptor(This,pathName,sd)	\
    (This)->lpVtbl -> SetPathSecurityDescriptor(This,pathName,sd)

#define ILFileSystem_GetPathSecurityDescriptor(This,pathName,pVal)	\
    (This)->lpVtbl -> GetPathSecurityDescriptor(This,pathName,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_SaveArrayAsFile_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ BSTR filePath,
    /* [in] */ SAFEARRAY __RPC_FAR * dataArray,
    /* [in] */ BSTR user,
    /* [out][in] */ long __RPC_FAR *file_id,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);


void __RPC_STUB ILFileSystem_SaveArrayAsFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_OpenFileAsArray_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ BSTR filePath,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *dataArray);


void __RPC_STUB ILFileSystem_OpenFileAsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_GetFolderDisplayPath_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ long folder_id,
    /* [retval][out] */ BSTR __RPC_FAR *displayName);


void __RPC_STUB ILFileSystem_GetFolderDisplayPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_GetParentFolderId_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ long folder_id,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILFileSystem_GetParentFolderId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_FindOrCreateFolder_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [in] */ BSTR user,
    /* [retval][out] */ long __RPC_FAR *folder_id);


void __RPC_STUB ILFileSystem_FindOrCreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_DeleteFilePermanently_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ long file_id,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);


void __RPC_STUB ILFileSystem_DeleteFilePermanently_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_CreateFolder_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ long parent_id,
    /* [in] */ BSTR name,
    /* [in] */ BSTR user,
    /* [retval][out] */ long __RPC_FAR *pfolder_id);


void __RPC_STUB ILFileSystem_CreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_RenameFile_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ long file_id,
    /* [in] */ BSTR name,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);


void __RPC_STUB ILFileSystem_RenameFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_GetFolderDirectoryList_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ILFileSystem_GetFolderDirectoryList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_SetPathSecurityDescriptor_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [in] */ SAFEARRAY __RPC_FAR * sd);


void __RPC_STUB ILFileSystem_SetPathSecurityDescriptor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILFileSystem_GetPathSecurityDescriptor_Proxy( 
    ILFileSystem __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ILFileSystem_GetPathSecurityDescriptor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILFileSystem_INTERFACE_DEFINED__ */


#ifndef __IXmillWebSite_INTERFACE_DEFINED__
#define __IXmillWebSite_INTERFACE_DEFINED__

/* interface IXmillWebSite */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IXmillWebSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8686A01F-5EF1-45E5-B4AB-CDA09DA6839E")
    IXmillWebSite : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IXmillWebSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXmillWebSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXmillWebSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXmillWebSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXmillWebSite __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXmillWebSite __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXmillWebSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXmillWebSite __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IXmillWebSiteVtbl;

    interface IXmillWebSite
    {
        CONST_VTBL struct IXmillWebSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXmillWebSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXmillWebSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXmillWebSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXmillWebSite_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXmillWebSite_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXmillWebSite_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXmillWebSite_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXmillWebSite_INTERFACE_DEFINED__ */


#ifndef __ITest_INTERFACE_DEFINED__
#define __ITest_INTERFACE_DEFINED__

/* interface ITest */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A221D27-77EA-408F-B267-D900CF42F30C")
    ITest : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITest __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITest __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITest __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITest __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITest __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITest __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITest __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ITestVtbl;

    interface ITest
    {
        CONST_VTBL struct ITestVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITest_INTERFACE_DEFINED__ */


#ifndef __IXmillWorkgroup_INTERFACE_DEFINED__
#define __IXmillWorkgroup_INTERFACE_DEFINED__

/* interface IXmillWorkgroup */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IXmillWorkgroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EB430710-FDB7-4EC7-ABDF-AAE428A6C303")
    IXmillWorkgroup : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TestMethod( 
            /* [in] */ BSTR testString,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWebSiteList( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewWebSite( 
            /* [in] */ BSTR websitexml,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXmillWorkgroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXmillWorkgroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXmillWorkgroup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TestMethod )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [in] */ BSTR testString,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWebSiteList )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewWebSite )( 
            IXmillWorkgroup __RPC_FAR * This,
            /* [in] */ BSTR websitexml,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IXmillWorkgroupVtbl;

    interface IXmillWorkgroup
    {
        CONST_VTBL struct IXmillWorkgroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXmillWorkgroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXmillWorkgroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXmillWorkgroup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXmillWorkgroup_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXmillWorkgroup_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXmillWorkgroup_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXmillWorkgroup_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXmillWorkgroup_TestMethod(This,testString,pVal)	\
    (This)->lpVtbl -> TestMethod(This,testString,pVal)

#define IXmillWorkgroup_GetWebSiteList(This,pVal)	\
    (This)->lpVtbl -> GetWebSiteList(This,pVal)

#define IXmillWorkgroup_NewWebSite(This,websitexml,pVal)	\
    (This)->lpVtbl -> NewWebSite(This,websitexml,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXmillWorkgroup_TestMethod_Proxy( 
    IXmillWorkgroup __RPC_FAR * This,
    /* [in] */ BSTR testString,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IXmillWorkgroup_TestMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXmillWorkgroup_GetWebSiteList_Proxy( 
    IXmillWorkgroup __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IXmillWorkgroup_GetWebSiteList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXmillWorkgroup_NewWebSite_Proxy( 
    IXmillWorkgroup __RPC_FAR * This,
    /* [in] */ BSTR websitexml,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IXmillWorkgroup_NewWebSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXmillWorkgroup_INTERFACE_DEFINED__ */



#ifndef __XMILLWEBLib_LIBRARY_DEFINED__
#define __XMILLWEBLib_LIBRARY_DEFINED__

/* library XMILLWEBLib */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_XMILLWEBLib;

EXTERN_C const CLSID CLSID_XmillWebSite;

#ifdef __cplusplus

class DECLSPEC_UUID("DEF145E8-94F5-4E0E-9469-4EA189544DF7")
XmillWebSite;
#endif

EXTERN_C const CLSID CLSID_Test;

#ifdef __cplusplus

class DECLSPEC_UUID("EC82D4C6-3F98-40F0-920C-8DE6C582B78D")
Test;
#endif

EXTERN_C const CLSID CLSID_XmillWorkgroup;

#ifdef __cplusplus

class DECLSPEC_UUID("04A324B3-E39F-43A4-BCAC-9140D426AD8D")
XmillWorkgroup;
#endif
#endif /* __XMILLWEBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
