

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Apr 04 05:17:00 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LXFramework\LXFramework.idl:
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

#ifndef __LXFramework_h__
#define __LXFramework_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILXFrameworkApp_FWD_DEFINED__
#define __ILXFrameworkApp_FWD_DEFINED__
typedef interface ILXFrameworkApp ILXFrameworkApp;
#endif 	/* __ILXFrameworkApp_FWD_DEFINED__ */


#ifndef __IWorkgroupDocument_FWD_DEFINED__
#define __IWorkgroupDocument_FWD_DEFINED__
typedef interface IWorkgroupDocument IWorkgroupDocument;
#endif 	/* __IWorkgroupDocument_FWD_DEFINED__ */


#ifndef __IXMiLFilesControl_FWD_DEFINED__
#define __IXMiLFilesControl_FWD_DEFINED__
typedef interface IXMiLFilesControl IXMiLFilesControl;
#endif 	/* __IXMiLFilesControl_FWD_DEFINED__ */


#ifndef __IWorkgroupFilesView_FWD_DEFINED__
#define __IWorkgroupFilesView_FWD_DEFINED__
typedef interface IWorkgroupFilesView IWorkgroupFilesView;
#endif 	/* __IWorkgroupFilesView_FWD_DEFINED__ */


#ifndef __IPointLightUI_FWD_DEFINED__
#define __IPointLightUI_FWD_DEFINED__
typedef interface IPointLightUI IPointLightUI;
#endif 	/* __IPointLightUI_FWD_DEFINED__ */


#ifndef ___ILXFrameworkAppEvents_FWD_DEFINED__
#define ___ILXFrameworkAppEvents_FWD_DEFINED__
typedef interface _ILXFrameworkAppEvents _ILXFrameworkAppEvents;
#endif 	/* ___ILXFrameworkAppEvents_FWD_DEFINED__ */


#ifndef __LXFrameworkApp_FWD_DEFINED__
#define __LXFrameworkApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class LXFrameworkApp LXFrameworkApp;
#else
typedef struct LXFrameworkApp LXFrameworkApp;
#endif /* __cplusplus */

#endif 	/* __LXFrameworkApp_FWD_DEFINED__ */


#ifndef ___ILXFrameworkFrameEvents_FWD_DEFINED__
#define ___ILXFrameworkFrameEvents_FWD_DEFINED__
typedef interface _ILXFrameworkFrameEvents _ILXFrameworkFrameEvents;
#endif 	/* ___ILXFrameworkFrameEvents_FWD_DEFINED__ */


#ifndef ___IWorkgroupDocumentEvents_FWD_DEFINED__
#define ___IWorkgroupDocumentEvents_FWD_DEFINED__
typedef interface _IWorkgroupDocumentEvents _IWorkgroupDocumentEvents;
#endif 	/* ___IWorkgroupDocumentEvents_FWD_DEFINED__ */


#ifndef __WorkgroupDocument_FWD_DEFINED__
#define __WorkgroupDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class WorkgroupDocument WorkgroupDocument;
#else
typedef struct WorkgroupDocument WorkgroupDocument;
#endif /* __cplusplus */

#endif 	/* __WorkgroupDocument_FWD_DEFINED__ */


#ifndef ___IXMiLFilesControlEvents_FWD_DEFINED__
#define ___IXMiLFilesControlEvents_FWD_DEFINED__
typedef interface _IXMiLFilesControlEvents _IXMiLFilesControlEvents;
#endif 	/* ___IXMiLFilesControlEvents_FWD_DEFINED__ */


#ifndef __XMiLFilesControl_FWD_DEFINED__
#define __XMiLFilesControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class XMiLFilesControl XMiLFilesControl;
#else
typedef struct XMiLFilesControl XMiLFilesControl;
#endif /* __cplusplus */

#endif 	/* __XMiLFilesControl_FWD_DEFINED__ */


#ifndef ___IWorkgroupFilesViewEvents_FWD_DEFINED__
#define ___IWorkgroupFilesViewEvents_FWD_DEFINED__
typedef interface _IWorkgroupFilesViewEvents _IWorkgroupFilesViewEvents;
#endif 	/* ___IWorkgroupFilesViewEvents_FWD_DEFINED__ */


#ifndef __WorkgroupFilesView_FWD_DEFINED__
#define __WorkgroupFilesView_FWD_DEFINED__

#ifdef __cplusplus
typedef class WorkgroupFilesView WorkgroupFilesView;
#else
typedef struct WorkgroupFilesView WorkgroupFilesView;
#endif /* __cplusplus */

#endif 	/* __WorkgroupFilesView_FWD_DEFINED__ */


#ifndef ___IPointLightUIEvents_FWD_DEFINED__
#define ___IPointLightUIEvents_FWD_DEFINED__
typedef interface _IPointLightUIEvents _IPointLightUIEvents;
#endif 	/* ___IPointLightUIEvents_FWD_DEFINED__ */


#ifndef __PointLightUI_FWD_DEFINED__
#define __PointLightUI_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointLightUI PointLightUI;
#else
typedef struct PointLightUI PointLightUI;
#endif /* __cplusplus */

#endif 	/* __PointLightUI_FWD_DEFINED__ */


#ifndef __IEScoreDocument_FWD_DEFINED__
#define __IEScoreDocument_FWD_DEFINED__
typedef interface IEScoreDocument IEScoreDocument;
#endif 	/* __IEScoreDocument_FWD_DEFINED__ */


#ifndef __EScoreDocument_FWD_DEFINED__
#define __EScoreDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class EScoreDocument EScoreDocument;
#else
typedef struct EScoreDocument EScoreDocument;
#endif /* __cplusplus */

#endif 	/* __EScoreDocument_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dispex.h"
//#include "UI.h"
#include "LXUI.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_LXFramework_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_LXFramework_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LXFramework_0000_v0_0_s_ifspec;

#ifndef __ILXFrameworkApp_INTERFACE_DEFINED__
#define __ILXFrameworkApp_INTERFACE_DEFINED__

/* interface ILXFrameworkApp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILXFrameworkApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC68D90C-42E2-461D-B59A-35A23673C4A2")
    ILXFrameworkApp : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [in] */ ILXUIDocument **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILXFrameworkAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILXFrameworkApp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILXFrameworkApp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILXFrameworkApp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILXFrameworkApp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILXFrameworkApp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILXFrameworkApp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILXFrameworkApp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Run )( 
            ILXFrameworkApp * This,
            /* [retval][out] */ long *result);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            ILXFrameworkApp * This,
            /* [in] */ ILXUIDocument **pVal);
        
        END_INTERFACE
    } ILXFrameworkAppVtbl;

    interface ILXFrameworkApp
    {
        CONST_VTBL struct ILXFrameworkAppVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILXFrameworkApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILXFrameworkApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILXFrameworkApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILXFrameworkApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILXFrameworkApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILXFrameworkApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILXFrameworkApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILXFrameworkApp_Run(This,result)	\
    (This)->lpVtbl -> Run(This,result)

#define ILXFrameworkApp_get_Document(This,pVal)	\
    (This)->lpVtbl -> get_Document(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILXFrameworkApp_Run_Proxy( 
    ILXFrameworkApp * This,
    /* [retval][out] */ long *result);


void __RPC_STUB ILXFrameworkApp_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILXFrameworkApp_get_Document_Proxy( 
    ILXFrameworkApp * This,
    /* [in] */ ILXUIDocument **pVal);


void __RPC_STUB ILXFrameworkApp_get_Document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILXFrameworkApp_INTERFACE_DEFINED__ */


#ifndef __IWorkgroupDocument_INTERFACE_DEFINED__
#define __IWorkgroupDocument_INTERFACE_DEFINED__

/* interface IWorkgroupDocument */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWorkgroupDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F30218C-1458-47D9-BBEA-6803D89F8656")
    IWorkgroupDocument : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyMoveFiles( 
            /* [in] */ DWORD folder_id,
            /* [in] */ SAFEARRAY * filepaths,
            /* [in] */ VARIANT_BOOL bSilent,
            /* [retval][out] */ long *nFilesCopied) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWorkgroupDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWorkgroupDocument * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWorkgroupDocument * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWorkgroupDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CopyMoveFiles )( 
            IWorkgroupDocument * This,
            /* [in] */ DWORD folder_id,
            /* [in] */ SAFEARRAY * filepaths,
            /* [in] */ VARIANT_BOOL bSilent,
            /* [retval][out] */ long *nFilesCopied);
        
        END_INTERFACE
    } IWorkgroupDocumentVtbl;

    interface IWorkgroupDocument
    {
        CONST_VTBL struct IWorkgroupDocumentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWorkgroupDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWorkgroupDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWorkgroupDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWorkgroupDocument_CopyMoveFiles(This,folder_id,filepaths,bSilent,nFilesCopied)	\
    (This)->lpVtbl -> CopyMoveFiles(This,folder_id,filepaths,bSilent,nFilesCopied)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWorkgroupDocument_CopyMoveFiles_Proxy( 
    IWorkgroupDocument * This,
    /* [in] */ DWORD folder_id,
    /* [in] */ SAFEARRAY * filepaths,
    /* [in] */ VARIANT_BOOL bSilent,
    /* [retval][out] */ long *nFilesCopied);


void __RPC_STUB IWorkgroupDocument_CopyMoveFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWorkgroupDocument_INTERFACE_DEFINED__ */


#ifndef __IXMiLFilesControl_INTERFACE_DEFINED__
#define __IXMiLFilesControl_INTERFACE_DEFINED__

/* interface IXMiLFilesControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IXMiLFilesControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2E32AC4E-DA2D-46D1-9442-5BFA05296DC5")
    IXMiLFilesControl : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp **ppFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFileSystemInterface( 
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRootFolderPath( 
            /* [in] */ BSTR folderPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRootFolderPath( 
            /* [retval][out] */ BSTR *folderPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTreeControl( 
            /* [retval][out] */ IUITreeControl **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemFullPathName( 
            /* [in] */ DWORD item,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMiLFilesControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXMiLFilesControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXMiLFilesControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXMiLFilesControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXMiLFilesControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXMiLFilesControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXMiLFilesControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXMiLFilesControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IXMiLFilesControl * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IXMiLFilesControl * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IXMiLFilesControl * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IXMiLFilesControl * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IXMiLFilesControl * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IXMiLFilesControl * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IXMiLFilesControl * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFileSystemInterface )( 
            IXMiLFilesControl * This,
            /* [in] */ IUnknown *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRootFolderPath )( 
            IXMiLFilesControl * This,
            /* [in] */ BSTR folderPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRootFolderPath )( 
            IXMiLFilesControl * This,
            /* [retval][out] */ BSTR *folderPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTreeControl )( 
            IXMiLFilesControl * This,
            /* [retval][out] */ IUITreeControl **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemFullPathName )( 
            IXMiLFilesControl * This,
            /* [in] */ DWORD item,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IXMiLFilesControlVtbl;

    interface IXMiLFilesControl
    {
        CONST_VTBL struct IXMiLFilesControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMiLFilesControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMiLFilesControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMiLFilesControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMiLFilesControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMiLFilesControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMiLFilesControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMiLFilesControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMiLFilesControl_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IXMiLFilesControl_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IXMiLFilesControl_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IXMiLFilesControl_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IXMiLFilesControl_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IXMiLFilesControl_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IXMiLFilesControl_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IXMiLFilesControl_SetFileSystemInterface(This,newVal)	\
    (This)->lpVtbl -> SetFileSystemInterface(This,newVal)

#define IXMiLFilesControl_SetRootFolderPath(This,folderPath)	\
    (This)->lpVtbl -> SetRootFolderPath(This,folderPath)

#define IXMiLFilesControl_GetRootFolderPath(This,folderPath)	\
    (This)->lpVtbl -> GetRootFolderPath(This,folderPath)

#define IXMiLFilesControl_GetTreeControl(This,pVal)	\
    (This)->lpVtbl -> GetTreeControl(This,pVal)

#define IXMiLFilesControl_GetItemFullPathName(This,item,pVal)	\
    (This)->lpVtbl -> GetItemFullPathName(This,item,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_put_BackColor_Proxy( 
    IXMiLFilesControl * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IXMiLFilesControl_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_get_BackColor_Proxy( 
    IXMiLFilesControl * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IXMiLFilesControl_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_putref_Font_Proxy( 
    IXMiLFilesControl * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IXMiLFilesControl_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_put_Font_Proxy( 
    IXMiLFilesControl * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IXMiLFilesControl_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_get_Font_Proxy( 
    IXMiLFilesControl * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IXMiLFilesControl_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_put_Enabled_Proxy( 
    IXMiLFilesControl * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IXMiLFilesControl_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_get_Enabled_Proxy( 
    IXMiLFilesControl * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IXMiLFilesControl_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_SetFileSystemInterface_Proxy( 
    IXMiLFilesControl * This,
    /* [in] */ IUnknown *newVal);


void __RPC_STUB IXMiLFilesControl_SetFileSystemInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_SetRootFolderPath_Proxy( 
    IXMiLFilesControl * This,
    /* [in] */ BSTR folderPath);


void __RPC_STUB IXMiLFilesControl_SetRootFolderPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_GetRootFolderPath_Proxy( 
    IXMiLFilesControl * This,
    /* [retval][out] */ BSTR *folderPath);


void __RPC_STUB IXMiLFilesControl_GetRootFolderPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_GetTreeControl_Proxy( 
    IXMiLFilesControl * This,
    /* [retval][out] */ IUITreeControl **pVal);


void __RPC_STUB IXMiLFilesControl_GetTreeControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMiLFilesControl_GetItemFullPathName_Proxy( 
    IXMiLFilesControl * This,
    /* [in] */ DWORD item,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IXMiLFilesControl_GetItemFullPathName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMiLFilesControl_INTERFACE_DEFINED__ */


#ifndef __IWorkgroupFilesView_INTERFACE_DEFINED__
#define __IWorkgroupFilesView_INTERFACE_DEFINED__

/* interface IWorkgroupFilesView */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWorkgroupFilesView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("31D66257-84E6-4B67-B37C-84AB5D833181")
    IWorkgroupFilesView : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IWorkgroupFilesViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWorkgroupFilesView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWorkgroupFilesView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWorkgroupFilesView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWorkgroupFilesView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWorkgroupFilesView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWorkgroupFilesView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWorkgroupFilesView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IWorkgroupFilesViewVtbl;

    interface IWorkgroupFilesView
    {
        CONST_VTBL struct IWorkgroupFilesViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWorkgroupFilesView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWorkgroupFilesView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWorkgroupFilesView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWorkgroupFilesView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWorkgroupFilesView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWorkgroupFilesView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWorkgroupFilesView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWorkgroupFilesView_INTERFACE_DEFINED__ */


#ifndef __IPointLightUI_INTERFACE_DEFINED__
#define __IPointLightUI_INTERFACE_DEFINED__

/* interface IPointLightUI */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPointLightUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82706ABA-B6F2-4139-80C6-5623877CD43B")
    IPointLightUI : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ForeColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long *phwnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetXYZ( 
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double z) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_x( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_y( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_z( 
            /* [retval][out] */ double *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointLightUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointLightUI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointLightUI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointLightUI * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPointLightUI * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPointLightUI * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPointLightUI * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPointLightUI * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IPointLightUI * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IPointLightUI * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForeColor )( 
            IPointLightUI * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForeColor )( 
            IPointLightUI * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IPointLightUI * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IPointLightUI * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IPointLightUI * This,
            /* [retval][out] */ long *phwnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetXYZ )( 
            IPointLightUI * This,
            /* [in] */ double x,
            /* [in] */ double y,
            /* [in] */ double z);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_x )( 
            IPointLightUI * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_y )( 
            IPointLightUI * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_z )( 
            IPointLightUI * This,
            /* [retval][out] */ double *pVal);
        
        END_INTERFACE
    } IPointLightUIVtbl;

    interface IPointLightUI
    {
        CONST_VTBL struct IPointLightUIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointLightUI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPointLightUI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPointLightUI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPointLightUI_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPointLightUI_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPointLightUI_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPointLightUI_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPointLightUI_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IPointLightUI_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IPointLightUI_put_ForeColor(This,clr)	\
    (This)->lpVtbl -> put_ForeColor(This,clr)

#define IPointLightUI_get_ForeColor(This,pclr)	\
    (This)->lpVtbl -> get_ForeColor(This,pclr)

#define IPointLightUI_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IPointLightUI_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IPointLightUI_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IPointLightUI_SetXYZ(This,x,y,z)	\
    (This)->lpVtbl -> SetXYZ(This,x,y,z)

#define IPointLightUI_get_x(This,pVal)	\
    (This)->lpVtbl -> get_x(This,pVal)

#define IPointLightUI_get_y(This,pVal)	\
    (This)->lpVtbl -> get_y(This,pVal)

#define IPointLightUI_get_z(This,pVal)	\
    (This)->lpVtbl -> get_z(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPointLightUI_put_BackColor_Proxy( 
    IPointLightUI * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IPointLightUI_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPointLightUI_get_BackColor_Proxy( 
    IPointLightUI * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IPointLightUI_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPointLightUI_put_ForeColor_Proxy( 
    IPointLightUI * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IPointLightUI_put_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPointLightUI_get_ForeColor_Proxy( 
    IPointLightUI * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IPointLightUI_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IPointLightUI_put_Enabled_Proxy( 
    IPointLightUI * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IPointLightUI_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPointLightUI_get_Enabled_Proxy( 
    IPointLightUI * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IPointLightUI_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPointLightUI_get_Window_Proxy( 
    IPointLightUI * This,
    /* [retval][out] */ long *phwnd);


void __RPC_STUB IPointLightUI_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPointLightUI_SetXYZ_Proxy( 
    IPointLightUI * This,
    /* [in] */ double x,
    /* [in] */ double y,
    /* [in] */ double z);


void __RPC_STUB IPointLightUI_SetXYZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPointLightUI_get_x_Proxy( 
    IPointLightUI * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IPointLightUI_get_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPointLightUI_get_y_Proxy( 
    IPointLightUI * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IPointLightUI_get_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPointLightUI_get_z_Proxy( 
    IPointLightUI * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IPointLightUI_get_z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPointLightUI_INTERFACE_DEFINED__ */



#ifndef __LXFRAMEWORKLib_LIBRARY_DEFINED__
#define __LXFRAMEWORKLib_LIBRARY_DEFINED__

/* library LXFRAMEWORKLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LXFRAMEWORKLib;

#ifndef ___ILXFrameworkAppEvents_DISPINTERFACE_DEFINED__
#define ___ILXFrameworkAppEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILXFrameworkAppEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILXFrameworkAppEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BC52EE2B-90B9-477E-9D39-240116B73C93")
    _ILXFrameworkAppEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILXFrameworkAppEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ILXFrameworkAppEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ILXFrameworkAppEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ILXFrameworkAppEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ILXFrameworkAppEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ILXFrameworkAppEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ILXFrameworkAppEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ILXFrameworkAppEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ILXFrameworkAppEventsVtbl;

    interface _ILXFrameworkAppEvents
    {
        CONST_VTBL struct _ILXFrameworkAppEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILXFrameworkAppEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ILXFrameworkAppEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ILXFrameworkAppEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ILXFrameworkAppEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ILXFrameworkAppEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ILXFrameworkAppEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ILXFrameworkAppEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILXFrameworkAppEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LXFrameworkApp;

#ifdef __cplusplus

class DECLSPEC_UUID("34DC5794-E465-4938-BD26-8216F92018C7")
LXFrameworkApp;
#endif

#ifndef ___ILXFrameworkFrameEvents_DISPINTERFACE_DEFINED__
#define ___ILXFrameworkFrameEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILXFrameworkFrameEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILXFrameworkFrameEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("64553DEE-887B-4D58-99F5-6CCA8E2A23FD")
    _ILXFrameworkFrameEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILXFrameworkFrameEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ILXFrameworkFrameEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ILXFrameworkFrameEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ILXFrameworkFrameEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ILXFrameworkFrameEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ILXFrameworkFrameEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ILXFrameworkFrameEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ILXFrameworkFrameEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ILXFrameworkFrameEventsVtbl;

    interface _ILXFrameworkFrameEvents
    {
        CONST_VTBL struct _ILXFrameworkFrameEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILXFrameworkFrameEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ILXFrameworkFrameEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ILXFrameworkFrameEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ILXFrameworkFrameEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ILXFrameworkFrameEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ILXFrameworkFrameEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ILXFrameworkFrameEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILXFrameworkFrameEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IWorkgroupDocumentEvents_DISPINTERFACE_DEFINED__
#define ___IWorkgroupDocumentEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWorkgroupDocumentEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWorkgroupDocumentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DAE58A71-2217-435E-BC17-3E256066A6A5")
    _IWorkgroupDocumentEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWorkgroupDocumentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWorkgroupDocumentEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWorkgroupDocumentEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWorkgroupDocumentEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWorkgroupDocumentEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWorkgroupDocumentEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWorkgroupDocumentEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWorkgroupDocumentEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWorkgroupDocumentEventsVtbl;

    interface _IWorkgroupDocumentEvents
    {
        CONST_VTBL struct _IWorkgroupDocumentEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWorkgroupDocumentEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWorkgroupDocumentEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWorkgroupDocumentEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWorkgroupDocumentEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWorkgroupDocumentEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWorkgroupDocumentEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWorkgroupDocumentEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWorkgroupDocumentEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WorkgroupDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("346A7612-0BC9-43B6-9D23-106D33A11080")
WorkgroupDocument;
#endif

#ifndef ___IXMiLFilesControlEvents_DISPINTERFACE_DEFINED__
#define ___IXMiLFilesControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IXMiLFilesControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IXMiLFilesControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("350C93F1-2F43-42B4-8FD7-1EF782183726")
    _IXMiLFilesControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IXMiLFilesControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IXMiLFilesControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IXMiLFilesControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IXMiLFilesControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IXMiLFilesControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IXMiLFilesControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IXMiLFilesControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IXMiLFilesControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IXMiLFilesControlEventsVtbl;

    interface _IXMiLFilesControlEvents
    {
        CONST_VTBL struct _IXMiLFilesControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IXMiLFilesControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IXMiLFilesControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IXMiLFilesControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IXMiLFilesControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IXMiLFilesControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IXMiLFilesControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IXMiLFilesControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IXMiLFilesControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_XMiLFilesControl;

#ifdef __cplusplus

class DECLSPEC_UUID("F26E7DD8-4A1D-4E50-A81F-A3195E2EB851")
XMiLFilesControl;
#endif

#ifndef ___IWorkgroupFilesViewEvents_DISPINTERFACE_DEFINED__
#define ___IWorkgroupFilesViewEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWorkgroupFilesViewEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWorkgroupFilesViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6B4020F1-F5A3-4994-B92F-FD0E3F5CC9E6")
    _IWorkgroupFilesViewEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWorkgroupFilesViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWorkgroupFilesViewEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWorkgroupFilesViewEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWorkgroupFilesViewEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWorkgroupFilesViewEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWorkgroupFilesViewEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWorkgroupFilesViewEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWorkgroupFilesViewEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWorkgroupFilesViewEventsVtbl;

    interface _IWorkgroupFilesViewEvents
    {
        CONST_VTBL struct _IWorkgroupFilesViewEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWorkgroupFilesViewEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWorkgroupFilesViewEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWorkgroupFilesViewEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWorkgroupFilesViewEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWorkgroupFilesViewEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWorkgroupFilesViewEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWorkgroupFilesViewEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWorkgroupFilesViewEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WorkgroupFilesView;

#ifdef __cplusplus

class DECLSPEC_UUID("944861A2-24A9-42FE-9733-B090759A042F")
WorkgroupFilesView;
#endif

#ifndef ___IPointLightUIEvents_DISPINTERFACE_DEFINED__
#define ___IPointLightUIEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPointLightUIEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPointLightUIEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9FEAE893-E44C-43E6-8D9A-66AE2D2C1E19")
    _IPointLightUIEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPointLightUIEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IPointLightUIEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IPointLightUIEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IPointLightUIEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IPointLightUIEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IPointLightUIEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IPointLightUIEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IPointLightUIEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IPointLightUIEventsVtbl;

    interface _IPointLightUIEvents
    {
        CONST_VTBL struct _IPointLightUIEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPointLightUIEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPointLightUIEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPointLightUIEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPointLightUIEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPointLightUIEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPointLightUIEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPointLightUIEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPointLightUIEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PointLightUI;

#ifdef __cplusplus

class DECLSPEC_UUID("6F022229-5559-4E74-9EFA-2872DF246C1B")
PointLightUI;
#endif

#ifndef __IEScoreDocument_INTERFACE_DEFINED__
#define __IEScoreDocument_INTERFACE_DEFINED__

/* interface IEScoreDocument */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEScoreDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1BF9EF42-BA1A-4472-B78A-E2DBD2E8D364")
    IEScoreDocument : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IEScoreDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEScoreDocument * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEScoreDocument * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEScoreDocument * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEScoreDocument * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEScoreDocument * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEScoreDocument * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEScoreDocument * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IEScoreDocumentVtbl;

    interface IEScoreDocument
    {
        CONST_VTBL struct IEScoreDocumentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEScoreDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEScoreDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEScoreDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEScoreDocument_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEScoreDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEScoreDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEScoreDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEScoreDocument_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EScoreDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("ED8070C7-1531-4061-9F44-E37C2053A969")
EScoreDocument;
#endif
#endif /* __LXFRAMEWORKLib_LIBRARY_DEFINED__ */

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


