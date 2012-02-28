

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Fri May 20 20:32:34 2005
 */
/* Compiler settings for C:\MMStudio\Extras\FTPMod\FTPMod.idl:
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

#ifndef __FTPMod_h__
#define __FTPMod_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFTPBrowser_FWD_DEFINED__
#define __IFTPBrowser_FWD_DEFINED__
typedef interface IFTPBrowser IFTPBrowser;
#endif 	/* __IFTPBrowser_FWD_DEFINED__ */


#ifndef __IWebDAVBrowser_FWD_DEFINED__
#define __IWebDAVBrowser_FWD_DEFINED__
typedef interface IWebDAVBrowser IWebDAVBrowser;
#endif 	/* __IWebDAVBrowser_FWD_DEFINED__ */


#ifndef ___IFTPBrowserEvents_FWD_DEFINED__
#define ___IFTPBrowserEvents_FWD_DEFINED__
typedef interface _IFTPBrowserEvents _IFTPBrowserEvents;
#endif 	/* ___IFTPBrowserEvents_FWD_DEFINED__ */


#ifndef __FTPBrowser_FWD_DEFINED__
#define __FTPBrowser_FWD_DEFINED__

#ifdef __cplusplus
typedef class FTPBrowser FTPBrowser;
#else
typedef struct FTPBrowser FTPBrowser;
#endif /* __cplusplus */

#endif 	/* __FTPBrowser_FWD_DEFINED__ */


#ifndef ___IWebDAVBrowserEvents_FWD_DEFINED__
#define ___IWebDAVBrowserEvents_FWD_DEFINED__
typedef interface _IWebDAVBrowserEvents _IWebDAVBrowserEvents;
#endif 	/* ___IWebDAVBrowserEvents_FWD_DEFINED__ */


#ifndef __WebDAVBrowser_FWD_DEFINED__
#define __WebDAVBrowser_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebDAVBrowser WebDAVBrowser;
#else
typedef struct WebDAVBrowser WebDAVBrowser;
#endif /* __cplusplus */

#endif 	/* __WebDAVBrowser_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dispex.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IFTPBrowser_INTERFACE_DEFINED__
#define __IFTPBrowser_INTERFACE_DEFINED__

/* interface IFTPBrowser */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFTPBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92534163-5CB0-4A09-8D54-16DAF35CC128")
    IFTPBrowser : public IDispatch
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
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long *phwnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServerName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Password( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Directory( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Directory( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFTPBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFTPBrowser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFTPBrowser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFTPBrowser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFTPBrowser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFTPBrowser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFTPBrowser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFTPBrowser * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IFTPBrowser * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IFTPBrowser * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IFTPBrowser * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IFTPBrowser * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IFTPBrowser * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IFTPBrowser * This,
            /* [retval][out] */ long *phwnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerName )( 
            IFTPBrowser * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServerName )( 
            IFTPBrowser * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserName )( 
            IFTPBrowser * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UserName )( 
            IFTPBrowser * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Password )( 
            IFTPBrowser * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Password )( 
            IFTPBrowser * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Directory )( 
            IFTPBrowser * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Directory )( 
            IFTPBrowser * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IFTPBrowser * This,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IFTPBrowser * This);
        
        END_INTERFACE
    } IFTPBrowserVtbl;

    interface IFTPBrowser
    {
        CONST_VTBL struct IFTPBrowserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFTPBrowser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFTPBrowser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFTPBrowser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFTPBrowser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFTPBrowser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFTPBrowser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFTPBrowser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFTPBrowser_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IFTPBrowser_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IFTPBrowser_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IFTPBrowser_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IFTPBrowser_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IFTPBrowser_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IFTPBrowser_get_ServerName(This,pVal)	\
    (This)->lpVtbl -> get_ServerName(This,pVal)

#define IFTPBrowser_put_ServerName(This,newVal)	\
    (This)->lpVtbl -> put_ServerName(This,newVal)

#define IFTPBrowser_get_UserName(This,pVal)	\
    (This)->lpVtbl -> get_UserName(This,pVal)

#define IFTPBrowser_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IFTPBrowser_get_Password(This,pVal)	\
    (This)->lpVtbl -> get_Password(This,pVal)

#define IFTPBrowser_put_Password(This,newVal)	\
    (This)->lpVtbl -> put_Password(This,newVal)

#define IFTPBrowser_get_Directory(This,pVal)	\
    (This)->lpVtbl -> get_Directory(This,pVal)

#define IFTPBrowser_put_Directory(This,newVal)	\
    (This)->lpVtbl -> put_Directory(This,newVal)

#define IFTPBrowser_Connect(This,pSuccess)	\
    (This)->lpVtbl -> Connect(This,pSuccess)

#define IFTPBrowser_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_put_BackColor_Proxy( 
    IFTPBrowser * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IFTPBrowser_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_get_BackColor_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IFTPBrowser_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_putref_Font_Proxy( 
    IFTPBrowser * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IFTPBrowser_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_put_Font_Proxy( 
    IFTPBrowser * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IFTPBrowser_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_get_Font_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IFTPBrowser_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_get_Window_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ long *phwnd);


void __RPC_STUB IFTPBrowser_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_get_ServerName_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IFTPBrowser_get_ServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_put_ServerName_Proxy( 
    IFTPBrowser * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFTPBrowser_put_ServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_get_UserName_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IFTPBrowser_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_put_UserName_Proxy( 
    IFTPBrowser * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFTPBrowser_put_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_get_Password_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IFTPBrowser_get_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_put_Password_Proxy( 
    IFTPBrowser * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFTPBrowser_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_get_Directory_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IFTPBrowser_get_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_put_Directory_Proxy( 
    IFTPBrowser * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFTPBrowser_put_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_Connect_Proxy( 
    IFTPBrowser * This,
    /* [retval][out] */ VARIANT_BOOL *pSuccess);


void __RPC_STUB IFTPBrowser_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFTPBrowser_Disconnect_Proxy( 
    IFTPBrowser * This);


void __RPC_STUB IFTPBrowser_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFTPBrowser_INTERFACE_DEFINED__ */


#ifndef __IWebDAVBrowser_INTERFACE_DEFINED__
#define __IWebDAVBrowser_INTERFACE_DEFINED__

/* interface IWebDAVBrowser */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebDAVBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B777E903-8C1B-482F-9B18-44F0062965A7")
    IWebDAVBrowser : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Directory( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Directory( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebDAVBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebDAVBrowser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebDAVBrowser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebDAVBrowser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebDAVBrowser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebDAVBrowser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebDAVBrowser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebDAVBrowser * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Directory )( 
            IWebDAVBrowser * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Directory )( 
            IWebDAVBrowser * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IWebDAVBrowser * This,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IWebDAVBrowser * This);
        
        END_INTERFACE
    } IWebDAVBrowserVtbl;

    interface IWebDAVBrowser
    {
        CONST_VTBL struct IWebDAVBrowserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebDAVBrowser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebDAVBrowser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebDAVBrowser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebDAVBrowser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebDAVBrowser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebDAVBrowser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebDAVBrowser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebDAVBrowser_get_Directory(This,pVal)	\
    (This)->lpVtbl -> get_Directory(This,pVal)

#define IWebDAVBrowser_put_Directory(This,newVal)	\
    (This)->lpVtbl -> put_Directory(This,newVal)

#define IWebDAVBrowser_Connect(This,pSuccess)	\
    (This)->lpVtbl -> Connect(This,pSuccess)

#define IWebDAVBrowser_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebDAVBrowser_get_Directory_Proxy( 
    IWebDAVBrowser * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWebDAVBrowser_get_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebDAVBrowser_put_Directory_Proxy( 
    IWebDAVBrowser * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebDAVBrowser_put_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebDAVBrowser_Connect_Proxy( 
    IWebDAVBrowser * This,
    /* [retval][out] */ VARIANT_BOOL *pSuccess);


void __RPC_STUB IWebDAVBrowser_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebDAVBrowser_Disconnect_Proxy( 
    IWebDAVBrowser * This);


void __RPC_STUB IWebDAVBrowser_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebDAVBrowser_INTERFACE_DEFINED__ */



#ifndef __FTPMODLib_LIBRARY_DEFINED__
#define __FTPMODLib_LIBRARY_DEFINED__

/* library FTPMODLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FTPMODLib;

#ifndef ___IFTPBrowserEvents_DISPINTERFACE_DEFINED__
#define ___IFTPBrowserEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IFTPBrowserEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IFTPBrowserEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("91918FD6-2F3B-49AC-9319-C6A337A1BA77")
    _IFTPBrowserEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IFTPBrowserEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IFTPBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IFTPBrowserEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IFTPBrowserEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IFTPBrowserEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IFTPBrowserEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IFTPBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IFTPBrowserEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IFTPBrowserEventsVtbl;

    interface _IFTPBrowserEvents
    {
        CONST_VTBL struct _IFTPBrowserEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IFTPBrowserEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IFTPBrowserEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IFTPBrowserEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IFTPBrowserEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IFTPBrowserEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IFTPBrowserEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IFTPBrowserEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IFTPBrowserEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_FTPBrowser;

#ifdef __cplusplus

class DECLSPEC_UUID("6107A6C8-CC8F-431D-A6B8-8B487710652C")
FTPBrowser;
#endif

#ifndef ___IWebDAVBrowserEvents_DISPINTERFACE_DEFINED__
#define ___IWebDAVBrowserEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWebDAVBrowserEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWebDAVBrowserEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F92D2AB5-0C2A-49B0-A86F-3FB7500B7323")
    _IWebDAVBrowserEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWebDAVBrowserEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWebDAVBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWebDAVBrowserEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWebDAVBrowserEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWebDAVBrowserEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWebDAVBrowserEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWebDAVBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWebDAVBrowserEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWebDAVBrowserEventsVtbl;

    interface _IWebDAVBrowserEvents
    {
        CONST_VTBL struct _IWebDAVBrowserEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWebDAVBrowserEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWebDAVBrowserEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWebDAVBrowserEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWebDAVBrowserEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWebDAVBrowserEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWebDAVBrowserEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWebDAVBrowserEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWebDAVBrowserEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebDAVBrowser;

#ifdef __cplusplus

class DECLSPEC_UUID("A1FEFD08-969F-45B4-8C70-DFD7FB8F93A4")
WebDAVBrowser;
#endif
#endif /* __FTPMODLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


