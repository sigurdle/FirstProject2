

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Sep 30 19:58:36 2003
 */
/* Compiler settings for C:\MMStudio\Extras\LXWebSite\LXWebSite.idl:
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

#ifndef __LXWebSite_h__
#define __LXWebSite_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILXServer_FWD_DEFINED__
#define __ILXServer_FWD_DEFINED__
typedef interface ILXServer ILXServer;
#endif 	/* __ILXServer_FWD_DEFINED__ */


#ifndef __ILXWebSiteApp_FWD_DEFINED__
#define __ILXWebSiteApp_FWD_DEFINED__
typedef interface ILXWebSiteApp ILXWebSiteApp;
#endif 	/* __ILXWebSiteApp_FWD_DEFINED__ */


#ifndef __ILXLocalWebSite_FWD_DEFINED__
#define __ILXLocalWebSite_FWD_DEFINED__
typedef interface ILXLocalWebSite ILXLocalWebSite;
#endif 	/* __ILXLocalWebSite_FWD_DEFINED__ */


#ifndef __IWebSite_FWD_DEFINED__
#define __IWebSite_FWD_DEFINED__
typedef interface IWebSite IWebSite;
#endif 	/* __IWebSite_FWD_DEFINED__ */


#ifndef __ISiteFilesView_FWD_DEFINED__
#define __ISiteFilesView_FWD_DEFINED__
typedef interface ISiteFilesView ISiteFilesView;
#endif 	/* __ISiteFilesView_FWD_DEFINED__ */


#ifndef __ISiteLinksView_FWD_DEFINED__
#define __ISiteLinksView_FWD_DEFINED__
typedef interface ISiteLinksView ISiteLinksView;
#endif 	/* __ISiteLinksView_FWD_DEFINED__ */


#ifndef __ISiteFTPView_FWD_DEFINED__
#define __ISiteFTPView_FWD_DEFINED__
typedef interface ISiteFTPView ISiteFTPView;
#endif 	/* __ISiteFTPView_FWD_DEFINED__ */


#ifndef __LXWebSiteApp_FWD_DEFINED__
#define __LXWebSiteApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXWebSiteApp LXWebSiteApp;
#else
typedef struct LXWebSiteApp LXWebSiteApp;
#endif /* __cplusplus */

#endif 	/* __LXWebSiteApp_FWD_DEFINED__ */


#ifndef ___ILXLocalWebSiteEvents_FWD_DEFINED__
#define ___ILXLocalWebSiteEvents_FWD_DEFINED__
typedef interface _ILXLocalWebSiteEvents _ILXLocalWebSiteEvents;
#endif 	/* ___ILXLocalWebSiteEvents_FWD_DEFINED__ */


#ifndef __LXLocalWebSite_FWD_DEFINED__
#define __LXLocalWebSite_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXLocalWebSite LXLocalWebSite;
#else
typedef struct LXLocalWebSite LXLocalWebSite;
#endif /* __cplusplus */

#endif 	/* __LXLocalWebSite_FWD_DEFINED__ */


#ifndef ___IWebSiteEvents_FWD_DEFINED__
#define ___IWebSiteEvents_FWD_DEFINED__
typedef interface _IWebSiteEvents _IWebSiteEvents;
#endif 	/* ___IWebSiteEvents_FWD_DEFINED__ */


#ifndef __WebSite_FWD_DEFINED__
#define __WebSite_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebSite WebSite;
#else
typedef struct WebSite WebSite;
#endif /* __cplusplus */

#endif 	/* __WebSite_FWD_DEFINED__ */


#ifndef ___ISiteFilesViewEvents_FWD_DEFINED__
#define ___ISiteFilesViewEvents_FWD_DEFINED__
typedef interface _ISiteFilesViewEvents _ISiteFilesViewEvents;
#endif 	/* ___ISiteFilesViewEvents_FWD_DEFINED__ */


#ifndef ___ISiteLinksViewEvents_FWD_DEFINED__
#define ___ISiteLinksViewEvents_FWD_DEFINED__
typedef interface _ISiteLinksViewEvents _ISiteLinksViewEvents;
#endif 	/* ___ISiteLinksViewEvents_FWD_DEFINED__ */


#ifndef __Dummy_FWD_DEFINED__
#define __Dummy_FWD_DEFINED__

#ifdef __cplusplus
typedef class Dummy Dummy;
#else
typedef struct Dummy Dummy;
#endif /* __cplusplus */

#endif 	/* __Dummy_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dispex.h"
#include "LXFramework.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ILXServer_INTERFACE_DEFINED__
#define __ILXServer_INTERFACE_DEFINED__

/* interface ILXServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILXServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F905DF2B-7027-466b-BB72-0D5707307362")
    ILXServer : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_serverName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_directory( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_userName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_password( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILXServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILXServer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILXServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILXServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILXServer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILXServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILXServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILXServer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            ILXServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_serverName )( 
            ILXServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_directory )( 
            ILXServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_userName )( 
            ILXServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_password )( 
            ILXServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ILXServerVtbl;

    interface ILXServer
    {
        CONST_VTBL struct ILXServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXServer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILXServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILXServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILXServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILXServer_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define ILXServer_get_serverName(This,pVal)	\
    (This)->lpVtbl -> get_serverName(This,pVal)

#define ILXServer_get_directory(This,pVal)	\
    (This)->lpVtbl -> get_directory(This,pVal)

#define ILXServer_get_userName(This,pVal)	\
    (This)->lpVtbl -> get_userName(This,pVal)

#define ILXServer_get_password(This,pVal)	\
    (This)->lpVtbl -> get_password(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILXServer_get_name_Proxy( 
    ILXServer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXServer_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILXServer_get_serverName_Proxy( 
    ILXServer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXServer_get_serverName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILXServer_get_directory_Proxy( 
    ILXServer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXServer_get_directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILXServer_get_userName_Proxy( 
    ILXServer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXServer_get_userName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILXServer_get_password_Proxy( 
    ILXServer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXServer_get_password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILXServer_INTERFACE_DEFINED__ */


#ifndef __ILXWebSiteApp_INTERFACE_DEFINED__
#define __ILXWebSiteApp_INTERFACE_DEFINED__

/* interface ILXWebSiteApp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILXWebSiteApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8EB5F443-C499-4D39-98C8-2FFD794E35CA")
    ILXWebSiteApp : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILXWebSiteAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILXWebSiteApp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILXWebSiteApp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILXWebSiteApp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILXWebSiteApp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILXWebSiteApp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILXWebSiteApp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILXWebSiteApp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ILXWebSiteAppVtbl;

    interface ILXWebSiteApp
    {
        CONST_VTBL struct ILXWebSiteAppVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXWebSiteApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXWebSiteApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXWebSiteApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXWebSiteApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILXWebSiteApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILXWebSiteApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILXWebSiteApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILXWebSiteApp_INTERFACE_DEFINED__ */


#ifndef __ILXLocalWebSite_INTERFACE_DEFINED__
#define __ILXLocalWebSite_INTERFACE_DEFINED__

/* interface ILXLocalWebSite */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILXLocalWebSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7936022-0BD9-4667-8436-24746B7F382B")
    ILXLocalWebSite : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rootPath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadDocument( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetHomepageFileId( 
            /* [in] */ unsigned long file_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHomepageFileId( 
            /* [retval][out] */ unsigned long *file_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewDocument( 
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR siteName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDBConnection( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveArrayAsFile( 
            /* [in] */ unsigned long folder_id,
            /* [in] */ BSTR fileName,
            /* [in] */ SAFEARRAY * dataArray,
            /* [in] */ BSTR user,
            /* [out][in] */ DWORD *file_id,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenFileAsArray( 
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ SAFEARRAY * *dataArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFolderDisplayPath( 
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ BSTR *displayName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParentFolderId( 
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindOrCreateFolder( 
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD *folder_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteFilePermanently( 
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateFolder( 
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD *pfolder_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenameFile( 
            /* [in] */ DWORD file_id,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFolderList( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemAttributes( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileMoniker( 
            /* [in] */ BSTR pathName,
            /* [retval][out] */ IMoniker **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateItem( 
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR xmltext) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILXLocalWebSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILXLocalWebSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILXLocalWebSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILXLocalWebSite * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_rootPath )( 
            ILXLocalWebSite * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadDocument )( 
            ILXLocalWebSite * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetHomepageFileId )( 
            ILXLocalWebSite * This,
            /* [in] */ unsigned long file_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHomepageFileId )( 
            ILXLocalWebSite * This,
            /* [retval][out] */ unsigned long *file_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewDocument )( 
            ILXLocalWebSite * This,
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR siteName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDBConnection )( 
            ILXLocalWebSite * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveArrayAsFile )( 
            ILXLocalWebSite * This,
            /* [in] */ unsigned long folder_id,
            /* [in] */ BSTR fileName,
            /* [in] */ SAFEARRAY * dataArray,
            /* [in] */ BSTR user,
            /* [out][in] */ DWORD *file_id,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenFileAsArray )( 
            ILXLocalWebSite * This,
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ SAFEARRAY * *dataArray);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFolderDisplayPath )( 
            ILXLocalWebSite * This,
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ BSTR *displayName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetParentFolderId )( 
            ILXLocalWebSite * This,
            /* [in] */ DWORD folder_id,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindOrCreateFolder )( 
            ILXLocalWebSite * This,
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD *folder_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteFilePermanently )( 
            ILXLocalWebSite * This,
            /* [in] */ unsigned long file_id,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateFolder )( 
            ILXLocalWebSite * This,
            /* [in] */ DWORD parent_id,
            /* [in] */ BSTR name,
            /* [in] */ BSTR user,
            /* [retval][out] */ DWORD *pfolder_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RenameFile )( 
            ILXLocalWebSite * This,
            /* [in] */ DWORD file_id,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFolderList )( 
            ILXLocalWebSite * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemAttributes )( 
            ILXLocalWebSite * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileMoniker )( 
            ILXLocalWebSite * This,
            /* [in] */ BSTR pathName,
            /* [retval][out] */ IMoniker **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateItem )( 
            ILXLocalWebSite * This,
            /* [in] */ BSTR pathName,
            /* [in] */ BSTR xmltext);
        
        END_INTERFACE
    } ILXLocalWebSiteVtbl;

    interface ILXLocalWebSite
    {
        CONST_VTBL struct ILXLocalWebSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXLocalWebSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXLocalWebSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXLocalWebSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXLocalWebSite_get_rootPath(This,pVal)	\
    (This)->lpVtbl -> get_rootPath(This,pVal)

#define ILXLocalWebSite_LoadDocument(This,pathName,success)	\
    (This)->lpVtbl -> LoadDocument(This,pathName,success)

#define ILXLocalWebSite_SetHomepageFileId(This,file_id)	\
    (This)->lpVtbl -> SetHomepageFileId(This,file_id)

#define ILXLocalWebSite_GetHomepageFileId(This,file_id)	\
    (This)->lpVtbl -> GetHomepageFileId(This,file_id)

#define ILXLocalWebSite_NewDocument(This,pathName,siteName)	\
    (This)->lpVtbl -> NewDocument(This,pathName,siteName)

#define ILXLocalWebSite_GetDBConnection(This,pVal)	\
    (This)->lpVtbl -> GetDBConnection(This,pVal)

#define ILXLocalWebSite_SaveArrayAsFile(This,folder_id,fileName,dataArray,user,file_id,pSuccess)	\
    (This)->lpVtbl -> SaveArrayAsFile(This,folder_id,fileName,dataArray,user,file_id,pSuccess)

#define ILXLocalWebSite_OpenFileAsArray(This,file_id,dataArray)	\
    (This)->lpVtbl -> OpenFileAsArray(This,file_id,dataArray)

#define ILXLocalWebSite_GetFolderDisplayPath(This,folder_id,displayName)	\
    (This)->lpVtbl -> GetFolderDisplayPath(This,folder_id,displayName)

#define ILXLocalWebSite_GetParentFolderId(This,folder_id,pVal)	\
    (This)->lpVtbl -> GetParentFolderId(This,folder_id,pVal)

#define ILXLocalWebSite_FindOrCreateFolder(This,parent_id,name,user,folder_id)	\
    (This)->lpVtbl -> FindOrCreateFolder(This,parent_id,name,user,folder_id)

#define ILXLocalWebSite_DeleteFilePermanently(This,file_id,pSuccess)	\
    (This)->lpVtbl -> DeleteFilePermanently(This,file_id,pSuccess)

#define ILXLocalWebSite_CreateFolder(This,parent_id,name,user,pfolder_id)	\
    (This)->lpVtbl -> CreateFolder(This,parent_id,name,user,pfolder_id)

#define ILXLocalWebSite_RenameFile(This,file_id,name,pSuccess)	\
    (This)->lpVtbl -> RenameFile(This,file_id,name,pSuccess)

#define ILXLocalWebSite_GetFolderList(This,pathName,pVal)	\
    (This)->lpVtbl -> GetFolderList(This,pathName,pVal)

#define ILXLocalWebSite_GetItemAttributes(This,pathName,pVal)	\
    (This)->lpVtbl -> GetItemAttributes(This,pathName,pVal)

#define ILXLocalWebSite_GetFileMoniker(This,pathName,pVal)	\
    (This)->lpVtbl -> GetFileMoniker(This,pathName,pVal)

#define ILXLocalWebSite_UpdateItem(This,pathName,xmltext)	\
    (This)->lpVtbl -> UpdateItem(This,pathName,xmltext)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_get_rootPath_Proxy( 
    ILXLocalWebSite * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXLocalWebSite_get_rootPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_LoadDocument_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ VARIANT_BOOL *success);


void __RPC_STUB ILXLocalWebSite_LoadDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_SetHomepageFileId_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ unsigned long file_id);


void __RPC_STUB ILXLocalWebSite_SetHomepageFileId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_GetHomepageFileId_Proxy( 
    ILXLocalWebSite * This,
    /* [retval][out] */ unsigned long *file_id);


void __RPC_STUB ILXLocalWebSite_GetHomepageFileId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_NewDocument_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ BSTR pathName,
    /* [in] */ BSTR siteName);


void __RPC_STUB ILXLocalWebSite_NewDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_GetDBConnection_Proxy( 
    ILXLocalWebSite * This,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB ILXLocalWebSite_GetDBConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_SaveArrayAsFile_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ unsigned long folder_id,
    /* [in] */ BSTR fileName,
    /* [in] */ SAFEARRAY * dataArray,
    /* [in] */ BSTR user,
    /* [out][in] */ DWORD *file_id,
    /* [retval][out] */ VARIANT_BOOL *pSuccess);


void __RPC_STUB ILXLocalWebSite_SaveArrayAsFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_OpenFileAsArray_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ unsigned long file_id,
    /* [retval][out] */ SAFEARRAY * *dataArray);


void __RPC_STUB ILXLocalWebSite_OpenFileAsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_GetFolderDisplayPath_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ DWORD folder_id,
    /* [retval][out] */ BSTR *displayName);


void __RPC_STUB ILXLocalWebSite_GetFolderDisplayPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_GetParentFolderId_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ DWORD folder_id,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB ILXLocalWebSite_GetParentFolderId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_FindOrCreateFolder_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ DWORD parent_id,
    /* [in] */ BSTR name,
    /* [in] */ BSTR user,
    /* [retval][out] */ DWORD *folder_id);


void __RPC_STUB ILXLocalWebSite_FindOrCreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_DeleteFilePermanently_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ unsigned long file_id,
    /* [retval][out] */ VARIANT_BOOL *pSuccess);


void __RPC_STUB ILXLocalWebSite_DeleteFilePermanently_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_CreateFolder_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ DWORD parent_id,
    /* [in] */ BSTR name,
    /* [in] */ BSTR user,
    /* [retval][out] */ DWORD *pfolder_id);


void __RPC_STUB ILXLocalWebSite_CreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_RenameFile_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ DWORD file_id,
    /* [in] */ BSTR name,
    /* [retval][out] */ VARIANT_BOOL *pSuccess);


void __RPC_STUB ILXLocalWebSite_RenameFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_GetFolderList_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXLocalWebSite_GetFolderList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_GetItemAttributes_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILXLocalWebSite_GetItemAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_GetFileMoniker_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ BSTR pathName,
    /* [retval][out] */ IMoniker **pVal);


void __RPC_STUB ILXLocalWebSite_GetFileMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILXLocalWebSite_UpdateItem_Proxy( 
    ILXLocalWebSite * This,
    /* [in] */ BSTR pathName,
    /* [in] */ BSTR xmltext);


void __RPC_STUB ILXLocalWebSite_UpdateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILXLocalWebSite_INTERFACE_DEFINED__ */


#ifndef __IWebSite_INTERFACE_DEFINED__
#define __IWebSite_INTERFACE_DEFINED__

/* interface IWebSite */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDC54E2D-86C8-49A8-BE55-2F843ECCCE8D")
    IWebSite : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyMoveFile( 
            /* [in] */ DWORD folder_id,
            /* [in] */ BSTR filepath,
            /* [in] */ VARIANT_BOOL bSilent,
            /* [retval][out] */ long *nFilesCopied) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyMoveFiles( 
            /* [in] */ DWORD folder_id,
            /* [in] */ SAFEARRAY * filepaths,
            /* [in] */ VARIANT_BOOL bSilent,
            /* [retval][out] */ long *nFilesCopied) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadDocument( 
            /* [in] */ BSTR pathName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebSite * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebSite * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebSite * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebSite * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CopyMoveFile )( 
            IWebSite * This,
            /* [in] */ DWORD folder_id,
            /* [in] */ BSTR filepath,
            /* [in] */ VARIANT_BOOL bSilent,
            /* [retval][out] */ long *nFilesCopied);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CopyMoveFiles )( 
            IWebSite * This,
            /* [in] */ DWORD folder_id,
            /* [in] */ SAFEARRAY * filepaths,
            /* [in] */ VARIANT_BOOL bSilent,
            /* [retval][out] */ long *nFilesCopied);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadDocument )( 
            IWebSite * This,
            /* [in] */ BSTR pathName);
        
        END_INTERFACE
    } IWebSiteVtbl;

    interface IWebSite
    {
        CONST_VTBL struct IWebSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebSite_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebSite_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebSite_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebSite_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebSite_CopyMoveFile(This,folder_id,filepath,bSilent,nFilesCopied)	\
    (This)->lpVtbl -> CopyMoveFile(This,folder_id,filepath,bSilent,nFilesCopied)

#define IWebSite_CopyMoveFiles(This,folder_id,filepaths,bSilent,nFilesCopied)	\
    (This)->lpVtbl -> CopyMoveFiles(This,folder_id,filepaths,bSilent,nFilesCopied)

#define IWebSite_LoadDocument(This,pathName)	\
    (This)->lpVtbl -> LoadDocument(This,pathName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebSite_CopyMoveFile_Proxy( 
    IWebSite * This,
    /* [in] */ DWORD folder_id,
    /* [in] */ BSTR filepath,
    /* [in] */ VARIANT_BOOL bSilent,
    /* [retval][out] */ long *nFilesCopied);


void __RPC_STUB IWebSite_CopyMoveFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebSite_CopyMoveFiles_Proxy( 
    IWebSite * This,
    /* [in] */ DWORD folder_id,
    /* [in] */ SAFEARRAY * filepaths,
    /* [in] */ VARIANT_BOOL bSilent,
    /* [retval][out] */ long *nFilesCopied);


void __RPC_STUB IWebSite_CopyMoveFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebSite_LoadDocument_Proxy( 
    IWebSite * This,
    /* [in] */ BSTR pathName);


void __RPC_STUB IWebSite_LoadDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebSite_INTERFACE_DEFINED__ */


#ifndef __ISiteFilesView_INTERFACE_DEFINED__
#define __ISiteFilesView_INTERFACE_DEFINED__

/* interface ISiteFilesView */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISiteFilesView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7244D67C-176A-44FE-AA79-B311F344A358")
    ISiteFilesView : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_webSiteDocument( 
            /* [retval][out] */ IWebSite **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRootFolderId( 
            /* [in] */ unsigned long folder_id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRootFolderId( 
            /* [retval][out] */ unsigned long *folder_id) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISiteFilesViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISiteFilesView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISiteFilesView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISiteFilesView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISiteFilesView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISiteFilesView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISiteFilesView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISiteFilesView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_webSiteDocument )( 
            ISiteFilesView * This,
            /* [retval][out] */ IWebSite **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRootFolderId )( 
            ISiteFilesView * This,
            /* [in] */ unsigned long folder_id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRootFolderId )( 
            ISiteFilesView * This,
            /* [retval][out] */ unsigned long *folder_id);
        
        END_INTERFACE
    } ISiteFilesViewVtbl;

    interface ISiteFilesView
    {
        CONST_VTBL struct ISiteFilesViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISiteFilesView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISiteFilesView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISiteFilesView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISiteFilesView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISiteFilesView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISiteFilesView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISiteFilesView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISiteFilesView_get_webSiteDocument(This,pVal)	\
    (This)->lpVtbl -> get_webSiteDocument(This,pVal)

#define ISiteFilesView_SetRootFolderId(This,folder_id)	\
    (This)->lpVtbl -> SetRootFolderId(This,folder_id)

#define ISiteFilesView_GetRootFolderId(This,folder_id)	\
    (This)->lpVtbl -> GetRootFolderId(This,folder_id)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISiteFilesView_get_webSiteDocument_Proxy( 
    ISiteFilesView * This,
    /* [retval][out] */ IWebSite **pVal);


void __RPC_STUB ISiteFilesView_get_webSiteDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISiteFilesView_SetRootFolderId_Proxy( 
    ISiteFilesView * This,
    /* [in] */ unsigned long folder_id);


void __RPC_STUB ISiteFilesView_SetRootFolderId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISiteFilesView_GetRootFolderId_Proxy( 
    ISiteFilesView * This,
    /* [retval][out] */ unsigned long *folder_id);


void __RPC_STUB ISiteFilesView_GetRootFolderId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISiteFilesView_INTERFACE_DEFINED__ */


#ifndef __ISiteLinksView_INTERFACE_DEFINED__
#define __ISiteLinksView_INTERFACE_DEFINED__

/* interface ISiteLinksView */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISiteLinksView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC256255-0F04-422B-BDF1-D077B743E6D9")
    ISiteLinksView : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_document( 
            /* [retval][out] */ IWebSite **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISiteLinksViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISiteLinksView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISiteLinksView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISiteLinksView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISiteLinksView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISiteLinksView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISiteLinksView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISiteLinksView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_document )( 
            ISiteLinksView * This,
            /* [retval][out] */ IWebSite **pVal);
        
        END_INTERFACE
    } ISiteLinksViewVtbl;

    interface ISiteLinksView
    {
        CONST_VTBL struct ISiteLinksViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISiteLinksView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISiteLinksView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISiteLinksView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISiteLinksView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISiteLinksView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISiteLinksView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISiteLinksView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISiteLinksView_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISiteLinksView_get_document_Proxy( 
    ISiteLinksView * This,
    /* [retval][out] */ IWebSite **pVal);


void __RPC_STUB ISiteLinksView_get_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISiteLinksView_INTERFACE_DEFINED__ */


#ifndef __ISiteFTPView_INTERFACE_DEFINED__
#define __ISiteFTPView_INTERFACE_DEFINED__

/* interface ISiteFTPView */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISiteFTPView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1F339E90-AC4A-463B-B9B3-1D7AE8859591")
    ISiteFTPView : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_document( 
            /* [retval][out] */ IWebSite **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISiteFTPViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISiteFTPView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISiteFTPView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISiteFTPView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISiteFTPView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISiteFTPView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISiteFTPView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISiteFTPView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_document )( 
            ISiteFTPView * This,
            /* [retval][out] */ IWebSite **pVal);
        
        END_INTERFACE
    } ISiteFTPViewVtbl;

    interface ISiteFTPView
    {
        CONST_VTBL struct ISiteFTPViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISiteFTPView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISiteFTPView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISiteFTPView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISiteFTPView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISiteFTPView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISiteFTPView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISiteFTPView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISiteFTPView_get_document(This,pVal)	\
    (This)->lpVtbl -> get_document(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISiteFTPView_get_document_Proxy( 
    ISiteFTPView * This,
    /* [retval][out] */ IWebSite **pVal);


void __RPC_STUB ISiteFTPView_get_document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISiteFTPView_INTERFACE_DEFINED__ */



#ifndef __LXWEBSITELib_LIBRARY_DEFINED__
#define __LXWEBSITELib_LIBRARY_DEFINED__

/* library LXWEBSITELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LXWEBSITELib;

EXTERN_C const CLSID CLSID_LXWebSiteApp;

#ifdef __cplusplus

class DECLSPEC_UUID("D251A4C2-ECC2-431D-903F-24E98611B8CA")
LXWebSiteApp;
#endif

#ifndef ___ILXLocalWebSiteEvents_DISPINTERFACE_DEFINED__
#define ___ILXLocalWebSiteEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILXLocalWebSiteEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILXLocalWebSiteEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E838C421-9856-46FC-BFEA-5A54BEA1616D")
    _ILXLocalWebSiteEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILXLocalWebSiteEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ILXLocalWebSiteEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ILXLocalWebSiteEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ILXLocalWebSiteEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ILXLocalWebSiteEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ILXLocalWebSiteEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ILXLocalWebSiteEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ILXLocalWebSiteEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ILXLocalWebSiteEventsVtbl;

    interface _ILXLocalWebSiteEvents
    {
        CONST_VTBL struct _ILXLocalWebSiteEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILXLocalWebSiteEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ILXLocalWebSiteEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ILXLocalWebSiteEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ILXLocalWebSiteEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ILXLocalWebSiteEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ILXLocalWebSiteEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ILXLocalWebSiteEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILXLocalWebSiteEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LXLocalWebSite;

#ifdef __cplusplus

class DECLSPEC_UUID("76511BA7-2B25-4BFE-BB18-319E081C44D1")
LXLocalWebSite;
#endif

#ifndef ___IWebSiteEvents_DISPINTERFACE_DEFINED__
#define ___IWebSiteEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWebSiteEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWebSiteEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1ADBAE98-831E-46FD-BD7E-2D868E30ED09")
    _IWebSiteEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWebSiteEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWebSiteEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWebSiteEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWebSiteEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWebSiteEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWebSiteEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWebSiteEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWebSiteEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWebSiteEventsVtbl;

    interface _IWebSiteEvents
    {
        CONST_VTBL struct _IWebSiteEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWebSiteEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWebSiteEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWebSiteEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWebSiteEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWebSiteEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWebSiteEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWebSiteEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWebSiteEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebSite;

#ifdef __cplusplus

class DECLSPEC_UUID("A12A1F3F-D613-4C62-8403-92BBC4DA71A7")
WebSite;
#endif

#ifndef ___ISiteFilesViewEvents_DISPINTERFACE_DEFINED__
#define ___ISiteFilesViewEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISiteFilesViewEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISiteFilesViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5CA038E3-6070-41C4-AAE7-5C1CA1A8F89F")
    _ISiteFilesViewEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISiteFilesViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISiteFilesViewEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISiteFilesViewEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISiteFilesViewEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISiteFilesViewEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISiteFilesViewEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISiteFilesViewEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISiteFilesViewEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ISiteFilesViewEventsVtbl;

    interface _ISiteFilesViewEvents
    {
        CONST_VTBL struct _ISiteFilesViewEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISiteFilesViewEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISiteFilesViewEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISiteFilesViewEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISiteFilesViewEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISiteFilesViewEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISiteFilesViewEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISiteFilesViewEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISiteFilesViewEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ISiteLinksViewEvents_DISPINTERFACE_DEFINED__
#define ___ISiteLinksViewEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISiteLinksViewEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISiteLinksViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7EB9FFE3-7854-4764-91C5-FDBDFBA901E9")
    _ISiteLinksViewEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISiteLinksViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISiteLinksViewEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISiteLinksViewEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISiteLinksViewEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISiteLinksViewEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISiteLinksViewEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISiteLinksViewEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISiteLinksViewEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ISiteLinksViewEventsVtbl;

    interface _ISiteLinksViewEvents
    {
        CONST_VTBL struct _ISiteLinksViewEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISiteLinksViewEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISiteLinksViewEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISiteLinksViewEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISiteLinksViewEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISiteLinksViewEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISiteLinksViewEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISiteLinksViewEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISiteLinksViewEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Dummy;

#ifdef __cplusplus

class DECLSPEC_UUID("DBF9A971-F7B8-4bf8-B353-E1F7912B1A8D")
Dummy;
#endif
#endif /* __LXWEBSITELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


