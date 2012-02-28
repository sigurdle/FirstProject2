

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Oct 04 01:03:25 2004
 */
/* Compiler settings for C:\MMStudio\Extras\TextDataMod\TextDataMod.idl:
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

#ifndef __TextDataMod_h__
#define __TextDataMod_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITextData_FWD_DEFINED__
#define __ITextData_FWD_DEFINED__
typedef interface ITextData ITextData;
#endif 	/* __ITextData_FWD_DEFINED__ */


#ifndef ___ITextDataEvents_FWD_DEFINED__
#define ___ITextDataEvents_FWD_DEFINED__
typedef interface _ITextDataEvents _ITextDataEvents;
#endif 	/* ___ITextDataEvents_FWD_DEFINED__ */


#ifndef __TextData_FWD_DEFINED__
#define __TextData_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextData TextData;
#else
typedef struct TextData TextData;
#endif /* __cplusplus */

#endif 	/* __TextData_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ITextData_INTERFACE_DEFINED__
#define __ITextData_INTERFACE_DEFINED__

/* interface ITextData */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("73026767-140F-11D5-95EF-444553540000")
    ITextData : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_data( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_data( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_len( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_url( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_url( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE load( 
            /* [in] */ BSTR pathName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE insertText( 
            /* [in] */ long offset,
            /* [in] */ BSTR data,
            /* [in] */ long len) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE deleteText( 
            /* [in] */ long offset,
            /* [in] */ long len) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE replaceText( 
            /* [in] */ long offset,
            /* [in] */ long deletelen,
            /* [in] */ BSTR data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE lockData( 
            /* [retval][out] */ long *lockcount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE unlockData( 
            /* [retval][out] */ long *lockcount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadByteArray( 
            /* [in] */ SAFEARRAY * dataArray,
            /* [retval][out] */ VARIANT_BOOL *success) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setData( 
            /* [in] */ BSTR data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE save( 
            /* [in] */ BSTR pathName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_data )( 
            ITextData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_data )( 
            ITextData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_len )( 
            ITextData * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_url )( 
            ITextData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_url )( 
            ITextData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *load )( 
            ITextData * This,
            /* [in] */ BSTR pathName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *insertText )( 
            ITextData * This,
            /* [in] */ long offset,
            /* [in] */ BSTR data,
            /* [in] */ long len);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *deleteText )( 
            ITextData * This,
            /* [in] */ long offset,
            /* [in] */ long len);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *replaceText )( 
            ITextData * This,
            /* [in] */ long offset,
            /* [in] */ long deletelen,
            /* [in] */ BSTR data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *lockData )( 
            ITextData * This,
            /* [retval][out] */ long *lockcount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *unlockData )( 
            ITextData * This,
            /* [retval][out] */ long *lockcount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *loadByteArray )( 
            ITextData * This,
            /* [in] */ SAFEARRAY * dataArray,
            /* [retval][out] */ VARIANT_BOOL *success);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setData )( 
            ITextData * This,
            /* [in] */ BSTR data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *save )( 
            ITextData * This,
            /* [in] */ BSTR pathName);
        
        END_INTERFACE
    } ITextDataVtbl;

    interface ITextData
    {
        CONST_VTBL struct ITextDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextData_get_data(This,pVal)	\
    (This)->lpVtbl -> get_data(This,pVal)

#define ITextData_put_data(This,newVal)	\
    (This)->lpVtbl -> put_data(This,newVal)

#define ITextData_get_len(This,pVal)	\
    (This)->lpVtbl -> get_len(This,pVal)

#define ITextData_get_url(This,pVal)	\
    (This)->lpVtbl -> get_url(This,pVal)

#define ITextData_put_url(This,newVal)	\
    (This)->lpVtbl -> put_url(This,newVal)

#define ITextData_load(This,pathName)	\
    (This)->lpVtbl -> load(This,pathName)

#define ITextData_insertText(This,offset,data,len)	\
    (This)->lpVtbl -> insertText(This,offset,data,len)

#define ITextData_deleteText(This,offset,len)	\
    (This)->lpVtbl -> deleteText(This,offset,len)

#define ITextData_replaceText(This,offset,deletelen,data)	\
    (This)->lpVtbl -> replaceText(This,offset,deletelen,data)

#define ITextData_lockData(This,lockcount)	\
    (This)->lpVtbl -> lockData(This,lockcount)

#define ITextData_unlockData(This,lockcount)	\
    (This)->lpVtbl -> unlockData(This,lockcount)

#define ITextData_loadByteArray(This,dataArray,success)	\
    (This)->lpVtbl -> loadByteArray(This,dataArray,success)

#define ITextData_setData(This,data)	\
    (This)->lpVtbl -> setData(This,data)

#define ITextData_save(This,pathName)	\
    (This)->lpVtbl -> save(This,pathName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextData_get_data_Proxy( 
    ITextData * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITextData_get_data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextData_put_data_Proxy( 
    ITextData * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITextData_put_data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextData_get_len_Proxy( 
    ITextData * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITextData_get_len_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextData_get_url_Proxy( 
    ITextData * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITextData_get_url_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextData_put_url_Proxy( 
    ITextData * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITextData_put_url_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_load_Proxy( 
    ITextData * This,
    /* [in] */ BSTR pathName);


void __RPC_STUB ITextData_load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_insertText_Proxy( 
    ITextData * This,
    /* [in] */ long offset,
    /* [in] */ BSTR data,
    /* [in] */ long len);


void __RPC_STUB ITextData_insertText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_deleteText_Proxy( 
    ITextData * This,
    /* [in] */ long offset,
    /* [in] */ long len);


void __RPC_STUB ITextData_deleteText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_replaceText_Proxy( 
    ITextData * This,
    /* [in] */ long offset,
    /* [in] */ long deletelen,
    /* [in] */ BSTR data);


void __RPC_STUB ITextData_replaceText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_lockData_Proxy( 
    ITextData * This,
    /* [retval][out] */ long *lockcount);


void __RPC_STUB ITextData_lockData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_unlockData_Proxy( 
    ITextData * This,
    /* [retval][out] */ long *lockcount);


void __RPC_STUB ITextData_unlockData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_loadByteArray_Proxy( 
    ITextData * This,
    /* [in] */ SAFEARRAY * dataArray,
    /* [retval][out] */ VARIANT_BOOL *success);


void __RPC_STUB ITextData_loadByteArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_setData_Proxy( 
    ITextData * This,
    /* [in] */ BSTR data);


void __RPC_STUB ITextData_setData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextData_save_Proxy( 
    ITextData * This,
    /* [in] */ BSTR pathName);


void __RPC_STUB ITextData_save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextData_INTERFACE_DEFINED__ */



#ifndef __TEXTDATAMODLib_LIBRARY_DEFINED__
#define __TEXTDATAMODLib_LIBRARY_DEFINED__

/* library TEXTDATAMODLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TEXTDATAMODLib;

#ifndef ___ITextDataEvents_DISPINTERFACE_DEFINED__
#define ___ITextDataEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITextDataEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITextDataEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C491D478-812D-4dd0-BB77-1FFCC8573CB8")
    _ITextDataEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITextDataEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITextDataEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITextDataEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITextDataEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITextDataEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITextDataEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITextDataEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITextDataEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITextDataEventsVtbl;

    interface _ITextDataEvents
    {
        CONST_VTBL struct _ITextDataEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITextDataEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITextDataEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITextDataEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITextDataEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITextDataEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITextDataEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITextDataEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITextDataEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TextData;

#ifdef __cplusplus

class DECLSPEC_UUID("73026768-140F-11D5-95EF-444553540000")
TextData;
#endif
#endif /* __TEXTDATAMODLib_LIBRARY_DEFINED__ */

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


