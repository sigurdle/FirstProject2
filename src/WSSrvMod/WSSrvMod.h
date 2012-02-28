/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jan 21 23:09:57 2003
 */
/* Compiler settings for C:\MMStudio\Extras\WSSrvMod\WSSrvMod.idl:
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

#ifndef __WSSrvMod_h__
#define __WSSrvMod_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWSSrv_FWD_DEFINED__
#define __IWSSrv_FWD_DEFINED__
typedef interface IWSSrv IWSSrv;
#endif 	/* __IWSSrv_FWD_DEFINED__ */


#ifndef ___IWSSrvEvents_FWD_DEFINED__
#define ___IWSSrvEvents_FWD_DEFINED__
typedef interface _IWSSrvEvents _IWSSrvEvents;
#endif 	/* ___IWSSrvEvents_FWD_DEFINED__ */


#ifndef __WSSrv_FWD_DEFINED__
#define __WSSrv_FWD_DEFINED__

#ifdef __cplusplus
typedef class WSSrv WSSrv;
#else
typedef struct WSSrv WSSrv;
#endif /* __cplusplus */

#endif 	/* __WSSrv_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IWSSrv_INTERFACE_DEFINED__
#define __IWSSrv_INTERFACE_DEFINED__

/* interface IWSSrv */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWSSrv;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09DD2FAE-EDB0-4ED5-82B6-91C91B296604")
    IWSSrv : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rootPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadDocument( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetHomepageFileId( 
            /* [in] */ unsigned long file_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHomepageFileId( 
            /* [retval][out] */ unsigned long __RPC_FAR *file_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewDocument( 
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR siteName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDBConnection( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveArrayAsFile( 
            /* [in] */ unsigned long folder_id,
            /* [in] */ BSTR fileName,
            /* [in] */ SAFEARRAY __RPC_FAR * dataArray,
            /* [in] */ BSTR user,
            /* [out][in] */ DWORD __RPC_FAR *file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenFileAsArray( 
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *dataArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFolderDisplayPath( 
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ BSTR __RPC_FAR *displayName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParentFolderId( 
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ DWORD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindOrCreateFolder( 
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD __RPC_FAR *folder_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteFilePermanently( 
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateFolder( 
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD __RPC_FAR *pfolder_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenameFile( 
            /* [in] */ DWORD file_id,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWSSrvVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWSSrv __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWSSrv __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWSSrv __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rootPath )( 
            IWSSrv __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadDocument )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHomepageFileId )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ unsigned long file_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHomepageFileId )( 
            IWSSrv __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *file_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewDocument )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR siteName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDBConnection )( 
            IWSSrv __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveArrayAsFile )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ unsigned long folder_id,
            /* [in] */ BSTR fileName,
            /* [in] */ SAFEARRAY __RPC_FAR * dataArray,
            /* [in] */ BSTR user,
            /* [out][in] */ DWORD __RPC_FAR *file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenFileAsArray )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *dataArray);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFolderDisplayPath )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ BSTR __RPC_FAR *displayName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentFolderId )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ DWORD __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindOrCreateFolder )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD __RPC_FAR *folder_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteFilePermanently )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateFolder )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD __RPC_FAR *pfolder_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenameFile )( 
            IWSSrv __RPC_FAR * This,
            /* [in] */ DWORD file_id,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);
        
        END_INTERFACE
    } IWSSrvVtbl;

    interface IWSSrv
    {
        CONST_VTBL struct IWSSrvVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWSSrv_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWSSrv_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWSSrv_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWSSrv_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWSSrv_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWSSrv_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWSSrv_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWSSrv_get_rootPath(This,pVal)	\
    (This)->lpVtbl -> get_rootPath(This,pVal)

#define IWSSrv_LoadDocument(This,pathName,success)	\
    (This)->lpVtbl -> LoadDocument(This,pathName,success)

#define IWSSrv_SetHomepageFileId(This,file_id)	\
    (This)->lpVtbl -> SetHomepageFileId(This,file_id)

#define IWSSrv_GetHomepageFileId(This,file_id)	\
    (This)->lpVtbl -> GetHomepageFileId(This,file_id)

#define IWSSrv_NewDocument(This,pathName,siteName)	\
    (This)->lpVtbl -> NewDocument(This,pathName,siteName)

#define IWSSrv_GetDBConnection(This,pVal)	\
    (This)->lpVtbl -> GetDBConnection(This,pVal)

#define IWSSrv_SaveArrayAsFile(This,folder_id,fileName,dataArray,user,file_id,pSuccess)	\
    (This)->lpVtbl -> SaveArrayAsFile(This,folder_id,fileName,dataArray,user,file_id,pSuccess)

#define IWSSrv_OpenFileAsArray(This,file_id,dataArray)	\
    (This)->lpVtbl -> OpenFileAsArray(This,file_id,dataArray)

#define IWSSrv_GetFolderDisplayPath(This,folder_id,displayName)	\
    (This)->lpVtbl -> GetFolderDisplayPath(This,folder_id,displayName)

#define IWSSrv_GetParentFolderId(This,folder_id,pVal)	\
    (This)->lpVtbl -> GetParentFolderId(This,folder_id,pVal)

#define IWSSrv_FindOrCreateFolder(This,parent_id,name,user,folder_id)	\
    (This)->lpVtbl -> FindOrCreateFolder(This,parent_id,name,user,folder_id)

#define IWSSrv_DeleteFilePermanently(This,file_id,pSuccess)	\
    (This)->lpVtbl -> DeleteFilePermanently(This,file_id,pSuccess)

#define IWSSrv_CreateFolder(This,parent_id,name,user,pfolder_id)	\
    (This)->lpVtbl -> CreateFolder(This,parent_id,name,user,pfolder_id)

#define IWSSrv_RenameFile(This,file_id,name,pSuccess)	\
    (This)->lpVtbl -> RenameFile(This,file_id,name,pSuccess)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWSSrv_get_rootPath_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWSSrv_get_rootPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_LoadDocument_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success);


void __RPC_STUB IWSSrv_LoadDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_SetHomepageFileId_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ unsigned long file_id);


void __RPC_STUB IWSSrv_SetHomepageFileId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_GetHomepageFileId_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [retval][out] */ unsigned long __RPC_FAR *file_id);


void __RPC_STUB IWSSrv_GetHomepageFileId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_NewDocument_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ BSTR pathName,
    /* [in] */ BSTR siteName);


void __RPC_STUB IWSSrv_NewDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_GetDBConnection_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWSSrv_GetDBConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_SaveArrayAsFile_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ unsigned long folder_id,
    /* [in] */ BSTR fileName,
    /* [in] */ SAFEARRAY __RPC_FAR * dataArray,
    /* [in] */ BSTR user,
    /* [out][in] */ DWORD __RPC_FAR *file_id,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);


void __RPC_STUB IWSSrv_SaveArrayAsFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_OpenFileAsArray_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ unsigned long file_id,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *dataArray);


void __RPC_STUB IWSSrv_OpenFileAsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_GetFolderDisplayPath_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ DWORD folder_id,
    /* [retval][out] */ BSTR __RPC_FAR *displayName);


void __RPC_STUB IWSSrv_GetFolderDisplayPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_GetParentFolderId_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ DWORD folder_id,
    /* [retval][out] */ DWORD __RPC_FAR *pVal);


void __RPC_STUB IWSSrv_GetParentFolderId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_FindOrCreateFolder_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ DWORD parent_id,
    /* [in] */ BSTR name,
    /* [in] */ BSTR user,
    /* [retval][out] */ DWORD __RPC_FAR *folder_id);


void __RPC_STUB IWSSrv_FindOrCreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_DeleteFilePermanently_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ unsigned long file_id,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);


void __RPC_STUB IWSSrv_DeleteFilePermanently_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_CreateFolder_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ DWORD parent_id,
    /* [in] */ BSTR name,
    /* [in] */ BSTR user,
    /* [retval][out] */ DWORD __RPC_FAR *pfolder_id);


void __RPC_STUB IWSSrv_CreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWSSrv_RenameFile_Proxy( 
    IWSSrv __RPC_FAR * This,
    /* [in] */ DWORD file_id,
    /* [in] */ BSTR name,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);


void __RPC_STUB IWSSrv_RenameFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWSSrv_INTERFACE_DEFINED__ */



#ifndef __WSSRVMODLib_LIBRARY_DEFINED__
#define __WSSRVMODLib_LIBRARY_DEFINED__

/* library WSSRVMODLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WSSRVMODLib;

#ifndef ___IWSSrvEvents_DISPINTERFACE_DEFINED__
#define ___IWSSrvEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWSSrvEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWSSrvEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6D31D709-D855-437F-AE85-6251A8193B24")
    _IWSSrvEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWSSrvEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IWSSrvEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IWSSrvEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IWSSrvEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IWSSrvEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IWSSrvEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IWSSrvEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IWSSrvEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IWSSrvEventsVtbl;

    interface _IWSSrvEvents
    {
        CONST_VTBL struct _IWSSrvEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWSSrvEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWSSrvEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWSSrvEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWSSrvEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWSSrvEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWSSrvEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWSSrvEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWSSrvEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WSSrv;

#ifdef __cplusplus

class DECLSPEC_UUID("CF5EA7B4-B0E4-43E7-A22A-4591D9DE79B7")
WSSrv;
#endif
#endif /* __WSSRVMODLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
