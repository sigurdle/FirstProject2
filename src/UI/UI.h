

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Mar 16 03:50:01 2004
 */
/* Compiler settings for C:\MMStudio\Extras\UI\UI.idl:
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

#ifndef __UI_h__
#define __UI_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IUIScrollBar_FWD_DEFINED__
#define __IUIScrollBar_FWD_DEFINED__
typedef interface IUIScrollBar IUIScrollBar;
#endif 	/* __IUIScrollBar_FWD_DEFINED__ */


#ifndef __IUIListControl_FWD_DEFINED__
#define __IUIListControl_FWD_DEFINED__
typedef interface IUIListControl IUIListControl;
#endif 	/* __IUIListControl_FWD_DEFINED__ */


#ifndef __IUIAutoListWindow_FWD_DEFINED__
#define __IUIAutoListWindow_FWD_DEFINED__
typedef interface IUIAutoListWindow IUIAutoListWindow;
#endif 	/* __IUIAutoListWindow_FWD_DEFINED__ */


#ifndef __IUIEdit_FWD_DEFINED__
#define __IUIEdit_FWD_DEFINED__
typedef interface IUIEdit IUIEdit;
#endif 	/* __IUIEdit_FWD_DEFINED__ */


#ifndef __IUIColorSlider_FWD_DEFINED__
#define __IUIColorSlider_FWD_DEFINED__
typedef interface IUIColorSlider IUIColorSlider;
#endif 	/* __IUIColorSlider_FWD_DEFINED__ */


#ifndef __IUITreeControlSite_FWD_DEFINED__
#define __IUITreeControlSite_FWD_DEFINED__
typedef interface IUITreeControlSite IUITreeControlSite;
#endif 	/* __IUITreeControlSite_FWD_DEFINED__ */


#ifndef __IUITreeItem_FWD_DEFINED__
#define __IUITreeItem_FWD_DEFINED__
typedef interface IUITreeItem IUITreeItem;
#endif 	/* __IUITreeItem_FWD_DEFINED__ */


#ifndef __IUITreeControl_FWD_DEFINED__
#define __IUITreeControl_FWD_DEFINED__
typedef interface IUITreeControl IUITreeControl;
#endif 	/* __IUITreeControl_FWD_DEFINED__ */


#ifndef ___ITextDataEvents2_FWD_DEFINED__
#define ___ITextDataEvents2_FWD_DEFINED__
typedef interface _ITextDataEvents2 _ITextDataEvents2;
#endif 	/* ___ITextDataEvents2_FWD_DEFINED__ */


#ifndef ___IUIScrollBarEvents_FWD_DEFINED__
#define ___IUIScrollBarEvents_FWD_DEFINED__
typedef interface _IUIScrollBarEvents _IUIScrollBarEvents;
#endif 	/* ___IUIScrollBarEvents_FWD_DEFINED__ */


#ifndef __UIScrollBar_FWD_DEFINED__
#define __UIScrollBar_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIScrollBar UIScrollBar;
#else
typedef struct UIScrollBar UIScrollBar;
#endif /* __cplusplus */

#endif 	/* __UIScrollBar_FWD_DEFINED__ */


#ifndef ___IUIEditEvents_FWD_DEFINED__
#define ___IUIEditEvents_FWD_DEFINED__
typedef interface _IUIEditEvents _IUIEditEvents;
#endif 	/* ___IUIEditEvents_FWD_DEFINED__ */


#ifndef __UIEdit_FWD_DEFINED__
#define __UIEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIEdit UIEdit;
#else
typedef struct UIEdit UIEdit;
#endif /* __cplusplus */

#endif 	/* __UIEdit_FWD_DEFINED__ */


#ifndef ___IUIListControlEvents_FWD_DEFINED__
#define ___IUIListControlEvents_FWD_DEFINED__
typedef interface _IUIListControlEvents _IUIListControlEvents;
#endif 	/* ___IUIListControlEvents_FWD_DEFINED__ */


#ifndef __UIListControl_FWD_DEFINED__
#define __UIListControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIListControl UIListControl;
#else
typedef struct UIListControl UIListControl;
#endif /* __cplusplus */

#endif 	/* __UIListControl_FWD_DEFINED__ */


#ifndef ___IUIColorSliderEvents_FWD_DEFINED__
#define ___IUIColorSliderEvents_FWD_DEFINED__
typedef interface _IUIColorSliderEvents _IUIColorSliderEvents;
#endif 	/* ___IUIColorSliderEvents_FWD_DEFINED__ */


#ifndef __UIColorSlider_FWD_DEFINED__
#define __UIColorSlider_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIColorSlider UIColorSlider;
#else
typedef struct UIColorSlider UIColorSlider;
#endif /* __cplusplus */

#endif 	/* __UIColorSlider_FWD_DEFINED__ */


#ifndef ___IUITreeControlEvents_FWD_DEFINED__
#define ___IUITreeControlEvents_FWD_DEFINED__
typedef interface _IUITreeControlEvents _IUITreeControlEvents;
#endif 	/* ___IUITreeControlEvents_FWD_DEFINED__ */


#ifndef __IUIToolbarButtons_FWD_DEFINED__
#define __IUIToolbarButtons_FWD_DEFINED__
typedef interface IUIToolbarButtons IUIToolbarButtons;
#endif 	/* __IUIToolbarButtons_FWD_DEFINED__ */


#ifndef __UITreeControl_FWD_DEFINED__
#define __UITreeControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class UITreeControl UITreeControl;
#else
typedef struct UITreeControl UITreeControl;
#endif /* __cplusplus */

#endif 	/* __UITreeControl_FWD_DEFINED__ */


#ifndef ___IUIToolbarButtonsEvents_FWD_DEFINED__
#define ___IUIToolbarButtonsEvents_FWD_DEFINED__
typedef interface _IUIToolbarButtonsEvents _IUIToolbarButtonsEvents;
#endif 	/* ___IUIToolbarButtonsEvents_FWD_DEFINED__ */


#ifndef __IUIEditUnitValue_FWD_DEFINED__
#define __IUIEditUnitValue_FWD_DEFINED__
typedef interface IUIEditUnitValue IUIEditUnitValue;
#endif 	/* __IUIEditUnitValue_FWD_DEFINED__ */


#ifndef __UIToolbarButtons_FWD_DEFINED__
#define __UIToolbarButtons_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIToolbarButtons UIToolbarButtons;
#else
typedef struct UIToolbarButtons UIToolbarButtons;
#endif /* __cplusplus */

#endif 	/* __UIToolbarButtons_FWD_DEFINED__ */


#ifndef ___IUIEditUnitValueEvents_FWD_DEFINED__
#define ___IUIEditUnitValueEvents_FWD_DEFINED__
typedef interface _IUIEditUnitValueEvents _IUIEditUnitValueEvents;
#endif 	/* ___IUIEditUnitValueEvents_FWD_DEFINED__ */


#ifndef __IColorSpectrum_FWD_DEFINED__
#define __IColorSpectrum_FWD_DEFINED__
typedef interface IColorSpectrum IColorSpectrum;
#endif 	/* __IColorSpectrum_FWD_DEFINED__ */


#ifndef __UIEditUnitValue_FWD_DEFINED__
#define __UIEditUnitValue_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIEditUnitValue UIEditUnitValue;
#else
typedef struct UIEditUnitValue UIEditUnitValue;
#endif /* __cplusplus */

#endif 	/* __UIEditUnitValue_FWD_DEFINED__ */


#ifndef ___IColorSpectrumEvents_FWD_DEFINED__
#define ___IColorSpectrumEvents_FWD_DEFINED__
typedef interface _IColorSpectrumEvents _IColorSpectrumEvents;
#endif 	/* ___IColorSpectrumEvents_FWD_DEFINED__ */


#ifndef __IUISlider_FWD_DEFINED__
#define __IUISlider_FWD_DEFINED__
typedef interface IUISlider IUISlider;
#endif 	/* __IUISlider_FWD_DEFINED__ */


#ifndef __ColorSpectrum_FWD_DEFINED__
#define __ColorSpectrum_FWD_DEFINED__

#ifdef __cplusplus
typedef class ColorSpectrum ColorSpectrum;
#else
typedef struct ColorSpectrum ColorSpectrum;
#endif /* __cplusplus */

#endif 	/* __ColorSpectrum_FWD_DEFINED__ */


#ifndef ___IUISliderEvents_FWD_DEFINED__
#define ___IUISliderEvents_FWD_DEFINED__
typedef interface _IUISliderEvents _IUISliderEvents;
#endif 	/* ___IUISliderEvents_FWD_DEFINED__ */


#ifndef __IUIHSLColorWheel_FWD_DEFINED__
#define __IUIHSLColorWheel_FWD_DEFINED__
typedef interface IUIHSLColorWheel IUIHSLColorWheel;
#endif 	/* __IUIHSLColorWheel_FWD_DEFINED__ */


#ifndef __UISlider_FWD_DEFINED__
#define __UISlider_FWD_DEFINED__

#ifdef __cplusplus
typedef class UISlider UISlider;
#else
typedef struct UISlider UISlider;
#endif /* __cplusplus */

#endif 	/* __UISlider_FWD_DEFINED__ */


#ifndef ___IUIHSLColorWheelEvents_FWD_DEFINED__
#define ___IUIHSLColorWheelEvents_FWD_DEFINED__
typedef interface _IUIHSLColorWheelEvents _IUIHSLColorWheelEvents;
#endif 	/* ___IUIHSLColorWheelEvents_FWD_DEFINED__ */


#ifndef __IUIShellTree_FWD_DEFINED__
#define __IUIShellTree_FWD_DEFINED__
typedef interface IUIShellTree IUIShellTree;
#endif 	/* __IUIShellTree_FWD_DEFINED__ */


#ifndef __UIHSLColorWheel_FWD_DEFINED__
#define __UIHSLColorWheel_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIHSLColorWheel UIHSLColorWheel;
#else
typedef struct UIHSLColorWheel UIHSLColorWheel;
#endif /* __cplusplus */

#endif 	/* __UIHSLColorWheel_FWD_DEFINED__ */


#ifndef ___IUIShellTreeEvents_FWD_DEFINED__
#define ___IUIShellTreeEvents_FWD_DEFINED__
typedef interface _IUIShellTreeEvents _IUIShellTreeEvents;
#endif 	/* ___IUIShellTreeEvents_FWD_DEFINED__ */


#ifndef __UIShellTree_FWD_DEFINED__
#define __UIShellTree_FWD_DEFINED__

#ifdef __cplusplus
typedef class UIShellTree UIShellTree;
#else
typedef struct UIShellTree UIShellTree;
#endif /* __cplusplus */

#endif 	/* __UIShellTree_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_UI_0000 */
/* [local] */ 

typedef 
enum _TVExpandCode
    {	TV_COLLAPSE	= 1,
	TV_COLLAPSERESET	= 2,
	TV_EXPAND	= 3,
	TV_TOGGLE	= 4
    } 	TVExpandCode;



extern RPC_IF_HANDLE __MIDL_itf_UI_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_UI_0000_v0_0_s_ifspec;

#ifndef __IUIScrollBar_INTERFACE_DEFINED__
#define __IUIScrollBar_INTERFACE_DEFINED__

/* interface IUIScrollBar */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIScrollBar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("580A9DFF-BC28-40BD-A809-4A87C9298879")
    IUIScrollBar : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_pos( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_pos( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_direction( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_direction( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_minv( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_maxv( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_visible( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInfo( 
            /* [in] */ long minv,
            /* [in] */ long maxv,
            /* [in] */ long visible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIScrollBarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIScrollBar * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIScrollBar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIScrollBar * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIScrollBar * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIScrollBar * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIScrollBar * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIScrollBar * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pos )( 
            IUIScrollBar * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_pos )( 
            IUIScrollBar * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_direction )( 
            IUIScrollBar * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_direction )( 
            IUIScrollBar * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_minv )( 
            IUIScrollBar * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_maxv )( 
            IUIScrollBar * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_visible )( 
            IUIScrollBar * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInfo )( 
            IUIScrollBar * This,
            /* [in] */ long minv,
            /* [in] */ long maxv,
            /* [in] */ long visible);
        
        END_INTERFACE
    } IUIScrollBarVtbl;

    interface IUIScrollBar
    {
        CONST_VTBL struct IUIScrollBarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIScrollBar_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIScrollBar_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIScrollBar_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIScrollBar_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIScrollBar_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIScrollBar_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIScrollBar_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIScrollBar_get_pos(This,pVal)	\
    (This)->lpVtbl -> get_pos(This,pVal)

#define IUIScrollBar_put_pos(This,newVal)	\
    (This)->lpVtbl -> put_pos(This,newVal)

#define IUIScrollBar_get_direction(This,pVal)	\
    (This)->lpVtbl -> get_direction(This,pVal)

#define IUIScrollBar_put_direction(This,newVal)	\
    (This)->lpVtbl -> put_direction(This,newVal)

#define IUIScrollBar_get_minv(This,pVal)	\
    (This)->lpVtbl -> get_minv(This,pVal)

#define IUIScrollBar_get_maxv(This,pVal)	\
    (This)->lpVtbl -> get_maxv(This,pVal)

#define IUIScrollBar_get_visible(This,pVal)	\
    (This)->lpVtbl -> get_visible(This,pVal)

#define IUIScrollBar_SetInfo(This,minv,maxv,visible)	\
    (This)->lpVtbl -> SetInfo(This,minv,maxv,visible)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_get_pos_Proxy( 
    IUIScrollBar * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIScrollBar_get_pos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_put_pos_Proxy( 
    IUIScrollBar * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIScrollBar_put_pos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_get_direction_Proxy( 
    IUIScrollBar * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIScrollBar_get_direction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_put_direction_Proxy( 
    IUIScrollBar * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIScrollBar_put_direction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_get_minv_Proxy( 
    IUIScrollBar * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIScrollBar_get_minv_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_get_maxv_Proxy( 
    IUIScrollBar * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIScrollBar_get_maxv_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_get_visible_Proxy( 
    IUIScrollBar * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIScrollBar_get_visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIScrollBar_SetInfo_Proxy( 
    IUIScrollBar * This,
    /* [in] */ long minv,
    /* [in] */ long maxv,
    /* [in] */ long visible);


void __RPC_STUB IUIScrollBar_SetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIScrollBar_INTERFACE_DEFINED__ */


#ifndef __IUIListControl_INTERFACE_DEFINED__
#define __IUIListControl_INTERFACE_DEFINED__

/* interface IUIListControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIListControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9DB1ED8-CE70-4514-AFCA-DD2E1CD21169")
    IUIListControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cursel( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_cursel( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddString( 
            /* [in] */ BSTR string,
            /* [retval][out] */ long *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetItemData( 
            /* [in] */ long index,
            /* [in] */ DWORD data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemData( 
            /* [in] */ long index,
            /* [retval][out] */ DWORD *data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetContent( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemText( 
            /* [in] */ unsigned long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CheckStyle( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CheckStyle( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCheck( 
            /* [in] */ long index,
            /* [in] */ DWORD check) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCheck( 
            /* [in] */ long index,
            /* [retval][out] */ DWORD *check) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_multipleSelect( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_multipleSelect( 
            /* [in] */ BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIListControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIListControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIListControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIListControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIListControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIListControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIListControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIListControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_cursel )( 
            IUIListControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_cursel )( 
            IUIListControl * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddString )( 
            IUIListControl * This,
            /* [in] */ BSTR string,
            /* [retval][out] */ long *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetItemData )( 
            IUIListControl * This,
            /* [in] */ long index,
            /* [in] */ DWORD data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemData )( 
            IUIListControl * This,
            /* [in] */ long index,
            /* [retval][out] */ DWORD *data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetContent )( 
            IUIListControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemText )( 
            IUIListControl * This,
            /* [in] */ unsigned long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CheckStyle )( 
            IUIListControl * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CheckStyle )( 
            IUIListControl * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCheck )( 
            IUIListControl * This,
            /* [in] */ long index,
            /* [in] */ DWORD check);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCheck )( 
            IUIListControl * This,
            /* [in] */ long index,
            /* [retval][out] */ DWORD *check);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_multipleSelect )( 
            IUIListControl * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_multipleSelect )( 
            IUIListControl * This,
            /* [in] */ BOOL newVal);
        
        END_INTERFACE
    } IUIListControlVtbl;

    interface IUIListControl
    {
        CONST_VTBL struct IUIListControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIListControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIListControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIListControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIListControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIListControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIListControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIListControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIListControl_get_cursel(This,pVal)	\
    (This)->lpVtbl -> get_cursel(This,pVal)

#define IUIListControl_put_cursel(This,newVal)	\
    (This)->lpVtbl -> put_cursel(This,newVal)

#define IUIListControl_AddString(This,string,index)	\
    (This)->lpVtbl -> AddString(This,string,index)

#define IUIListControl_SetItemData(This,index,data)	\
    (This)->lpVtbl -> SetItemData(This,index,data)

#define IUIListControl_GetItemData(This,index,data)	\
    (This)->lpVtbl -> GetItemData(This,index,data)

#define IUIListControl_ResetContent(This)	\
    (This)->lpVtbl -> ResetContent(This)

#define IUIListControl_GetItemText(This,index,pVal)	\
    (This)->lpVtbl -> GetItemText(This,index,pVal)

#define IUIListControl_get_CheckStyle(This,pVal)	\
    (This)->lpVtbl -> get_CheckStyle(This,pVal)

#define IUIListControl_put_CheckStyle(This,newVal)	\
    (This)->lpVtbl -> put_CheckStyle(This,newVal)

#define IUIListControl_SetCheck(This,index,check)	\
    (This)->lpVtbl -> SetCheck(This,index,check)

#define IUIListControl_GetCheck(This,index,check)	\
    (This)->lpVtbl -> GetCheck(This,index,check)

#define IUIListControl_get_multipleSelect(This,pVal)	\
    (This)->lpVtbl -> get_multipleSelect(This,pVal)

#define IUIListControl_put_multipleSelect(This,newVal)	\
    (This)->lpVtbl -> put_multipleSelect(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIListControl_get_cursel_Proxy( 
    IUIListControl * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIListControl_get_cursel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIListControl_put_cursel_Proxy( 
    IUIListControl * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIListControl_put_cursel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIListControl_AddString_Proxy( 
    IUIListControl * This,
    /* [in] */ BSTR string,
    /* [retval][out] */ long *index);


void __RPC_STUB IUIListControl_AddString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIListControl_SetItemData_Proxy( 
    IUIListControl * This,
    /* [in] */ long index,
    /* [in] */ DWORD data);


void __RPC_STUB IUIListControl_SetItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIListControl_GetItemData_Proxy( 
    IUIListControl * This,
    /* [in] */ long index,
    /* [retval][out] */ DWORD *data);


void __RPC_STUB IUIListControl_GetItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIListControl_ResetContent_Proxy( 
    IUIListControl * This);


void __RPC_STUB IUIListControl_ResetContent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIListControl_GetItemText_Proxy( 
    IUIListControl * This,
    /* [in] */ unsigned long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IUIListControl_GetItemText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIListControl_get_CheckStyle_Proxy( 
    IUIListControl * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUIListControl_get_CheckStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIListControl_put_CheckStyle_Proxy( 
    IUIListControl * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IUIListControl_put_CheckStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIListControl_SetCheck_Proxy( 
    IUIListControl * This,
    /* [in] */ long index,
    /* [in] */ DWORD check);


void __RPC_STUB IUIListControl_SetCheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIListControl_GetCheck_Proxy( 
    IUIListControl * This,
    /* [in] */ long index,
    /* [retval][out] */ DWORD *check);


void __RPC_STUB IUIListControl_GetCheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIListControl_get_multipleSelect_Proxy( 
    IUIListControl * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IUIListControl_get_multipleSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIListControl_put_multipleSelect_Proxy( 
    IUIListControl * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IUIListControl_put_multipleSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIListControl_INTERFACE_DEFINED__ */


#ifndef __IUIAutoListWindow_INTERFACE_DEFINED__
#define __IUIAutoListWindow_INTERFACE_DEFINED__

/* interface IUIAutoListWindow */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIAutoListWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("34D91B62-CDCE-453a-B0C2-80FB5A72A4F4")
    IUIAutoListWindow : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddString( 
            /* [in] */ long iImage,
            /* [in] */ BSTR string,
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIAutoListWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIAutoListWindow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIAutoListWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIAutoListWindow * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIAutoListWindow * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIAutoListWindow * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIAutoListWindow * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIAutoListWindow * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddString )( 
            IUIAutoListWindow * This,
            /* [in] */ long iImage,
            /* [in] */ BSTR string,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IUIAutoListWindowVtbl;

    interface IUIAutoListWindow
    {
        CONST_VTBL struct IUIAutoListWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIAutoListWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIAutoListWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIAutoListWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIAutoListWindow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIAutoListWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIAutoListWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIAutoListWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIAutoListWindow_AddString(This,iImage,string,pVal)	\
    (This)->lpVtbl -> AddString(This,iImage,string,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIAutoListWindow_AddString_Proxy( 
    IUIAutoListWindow * This,
    /* [in] */ long iImage,
    /* [in] */ BSTR string,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIAutoListWindow_AddString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIAutoListWindow_INTERFACE_DEFINED__ */


#ifndef __IUIEdit_INTERFACE_DEFINED__
#define __IUIEdit_INTERFACE_DEFINED__

/* interface IUIEdit */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("454511B5-17A1-447E-AFC1-86F2413E9FFF")
    IUIEdit : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_textDocument( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_textDocument( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vertScroll( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_vertScroll( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_horzScroll( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_horzScroll( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_undoManager( 
            /* [retval][out] */ IOleUndoManager **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_undoManager( 
            /* [in] */ IOleUndoManager *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_multiLine( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_multiLine( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_wordWrap( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_wordWrap( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lineNumbers( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lineNumbers( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cursorBox( 
            /* [retval][out] */ RECT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_font( 
            /* [retval][out] */ IFontDisp **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_font( 
            /* [in] */ IFontDisp *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LineHeight( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LineHeight( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tabSize( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_tabSize( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_viewWhitespace( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_viewWhitespace( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_viewTabs( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_viewTabs( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_viewSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_viewSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_viewEOLs( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_viewEOLs( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_line( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_column( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getCursorPosOffset( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setCursorPosOffset( 
            /* [in] */ long offset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetText( 
            /* [in] */ BSTR text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetText( 
            /* [retval][out] */ BSTR *text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FormatRange( 
            /* [in] */ long start,
            /* [in] */ long len,
            /* [in] */ long styleIndex,
            /* [in] */ long *styleElementIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearFormatting( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cut( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Copy( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Paste( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanPaste( 
            /* [in] */ unsigned long nFormat,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReplaceText( 
            /* [in] */ long offset,
            /* [in] */ long len,
            /* [in] */ BSTR data,
            /* [in] */ long datalen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSel( 
            /* [out] */ long *start,
            /* [out] */ long *end) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelText( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSel( 
            /* [in] */ long nStartChar,
            /* [in] */ long nEndChar,
            /* [in] */ VARIANT_BOOL bNoScroll) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReplaceSelText( 
            /* [in] */ BSTR data,
            /* [in] */ long len) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewStyle( 
            /* [retval][out] */ long *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStyle( 
            /* [in] */ long index,
            /* [in] */ DWORD fgColor,
            /* [in] */ DWORD bgColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoList( 
            /* [retval][out] */ IUIAutoListWindow **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoListPopup( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIEdit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIEdit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIEdit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIEdit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIEdit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIEdit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIEdit * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_textDocument )( 
            IUIEdit * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_textDocument )( 
            IUIEdit * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_vertScroll )( 
            IUIEdit * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_vertScroll )( 
            IUIEdit * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_horzScroll )( 
            IUIEdit * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_horzScroll )( 
            IUIEdit * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_undoManager )( 
            IUIEdit * This,
            /* [retval][out] */ IOleUndoManager **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_undoManager )( 
            IUIEdit * This,
            /* [in] */ IOleUndoManager *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_multiLine )( 
            IUIEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_multiLine )( 
            IUIEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_wordWrap )( 
            IUIEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_wordWrap )( 
            IUIEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lineNumbers )( 
            IUIEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_lineNumbers )( 
            IUIEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_cursorBox )( 
            IUIEdit * This,
            /* [retval][out] */ RECT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_font )( 
            IUIEdit * This,
            /* [retval][out] */ IFontDisp **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_font )( 
            IUIEdit * This,
            /* [in] */ IFontDisp *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineHeight )( 
            IUIEdit * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineHeight )( 
            IUIEdit * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_tabSize )( 
            IUIEdit * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_tabSize )( 
            IUIEdit * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_viewWhitespace )( 
            IUIEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_viewWhitespace )( 
            IUIEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_viewTabs )( 
            IUIEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_viewTabs )( 
            IUIEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_viewSpaces )( 
            IUIEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_viewSpaces )( 
            IUIEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_viewEOLs )( 
            IUIEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_viewEOLs )( 
            IUIEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_line )( 
            IUIEdit * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_column )( 
            IUIEdit * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getCursorPosOffset )( 
            IUIEdit * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setCursorPosOffset )( 
            IUIEdit * This,
            /* [in] */ long offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetText )( 
            IUIEdit * This,
            /* [in] */ BSTR text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IUIEdit * This,
            /* [retval][out] */ BSTR *text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FormatRange )( 
            IUIEdit * This,
            /* [in] */ long start,
            /* [in] */ long len,
            /* [in] */ long styleIndex,
            /* [in] */ long *styleElementIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearFormatting )( 
            IUIEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IUIEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cut )( 
            IUIEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Copy )( 
            IUIEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Paste )( 
            IUIEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CanPaste )( 
            IUIEdit * This,
            /* [in] */ unsigned long nFormat,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReplaceText )( 
            IUIEdit * This,
            /* [in] */ long offset,
            /* [in] */ long len,
            /* [in] */ BSTR data,
            /* [in] */ long datalen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSel )( 
            IUIEdit * This,
            /* [out] */ long *start,
            /* [out] */ long *end);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSelText )( 
            IUIEdit * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSel )( 
            IUIEdit * This,
            /* [in] */ long nStartChar,
            /* [in] */ long nEndChar,
            /* [in] */ VARIANT_BOOL bNoScroll);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReplaceSelText )( 
            IUIEdit * This,
            /* [in] */ BSTR data,
            /* [in] */ long len);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewStyle )( 
            IUIEdit * This,
            /* [retval][out] */ long *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetStyle )( 
            IUIEdit * This,
            /* [in] */ long index,
            /* [in] */ DWORD fgColor,
            /* [in] */ DWORD bgColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoList )( 
            IUIEdit * This,
            /* [retval][out] */ IUIAutoListWindow **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoListPopup )( 
            IUIEdit * This);
        
        END_INTERFACE
    } IUIEditVtbl;

    interface IUIEdit
    {
        CONST_VTBL struct IUIEditVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIEdit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIEdit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIEdit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIEdit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIEdit_get_textDocument(This,pVal)	\
    (This)->lpVtbl -> get_textDocument(This,pVal)

#define IUIEdit_put_textDocument(This,newVal)	\
    (This)->lpVtbl -> put_textDocument(This,newVal)

#define IUIEdit_get_vertScroll(This,pVal)	\
    (This)->lpVtbl -> get_vertScroll(This,pVal)

#define IUIEdit_put_vertScroll(This,newVal)	\
    (This)->lpVtbl -> put_vertScroll(This,newVal)

#define IUIEdit_get_horzScroll(This,pVal)	\
    (This)->lpVtbl -> get_horzScroll(This,pVal)

#define IUIEdit_put_horzScroll(This,newVal)	\
    (This)->lpVtbl -> put_horzScroll(This,newVal)

#define IUIEdit_get_undoManager(This,pVal)	\
    (This)->lpVtbl -> get_undoManager(This,pVal)

#define IUIEdit_put_undoManager(This,newVal)	\
    (This)->lpVtbl -> put_undoManager(This,newVal)

#define IUIEdit_get_multiLine(This,pVal)	\
    (This)->lpVtbl -> get_multiLine(This,pVal)

#define IUIEdit_put_multiLine(This,newVal)	\
    (This)->lpVtbl -> put_multiLine(This,newVal)

#define IUIEdit_get_wordWrap(This,pVal)	\
    (This)->lpVtbl -> get_wordWrap(This,pVal)

#define IUIEdit_put_wordWrap(This,newVal)	\
    (This)->lpVtbl -> put_wordWrap(This,newVal)

#define IUIEdit_get_lineNumbers(This,pVal)	\
    (This)->lpVtbl -> get_lineNumbers(This,pVal)

#define IUIEdit_put_lineNumbers(This,newVal)	\
    (This)->lpVtbl -> put_lineNumbers(This,newVal)

#define IUIEdit_get_cursorBox(This,pVal)	\
    (This)->lpVtbl -> get_cursorBox(This,pVal)

#define IUIEdit_get_font(This,pVal)	\
    (This)->lpVtbl -> get_font(This,pVal)

#define IUIEdit_put_font(This,newVal)	\
    (This)->lpVtbl -> put_font(This,newVal)

#define IUIEdit_get_LineHeight(This,pVal)	\
    (This)->lpVtbl -> get_LineHeight(This,pVal)

#define IUIEdit_put_LineHeight(This,newVal)	\
    (This)->lpVtbl -> put_LineHeight(This,newVal)

#define IUIEdit_get_tabSize(This,pVal)	\
    (This)->lpVtbl -> get_tabSize(This,pVal)

#define IUIEdit_put_tabSize(This,newVal)	\
    (This)->lpVtbl -> put_tabSize(This,newVal)

#define IUIEdit_get_viewWhitespace(This,pVal)	\
    (This)->lpVtbl -> get_viewWhitespace(This,pVal)

#define IUIEdit_put_viewWhitespace(This,newVal)	\
    (This)->lpVtbl -> put_viewWhitespace(This,newVal)

#define IUIEdit_get_viewTabs(This,pVal)	\
    (This)->lpVtbl -> get_viewTabs(This,pVal)

#define IUIEdit_put_viewTabs(This,newVal)	\
    (This)->lpVtbl -> put_viewTabs(This,newVal)

#define IUIEdit_get_viewSpaces(This,pVal)	\
    (This)->lpVtbl -> get_viewSpaces(This,pVal)

#define IUIEdit_put_viewSpaces(This,newVal)	\
    (This)->lpVtbl -> put_viewSpaces(This,newVal)

#define IUIEdit_get_viewEOLs(This,pVal)	\
    (This)->lpVtbl -> get_viewEOLs(This,pVal)

#define IUIEdit_put_viewEOLs(This,newVal)	\
    (This)->lpVtbl -> put_viewEOLs(This,newVal)

#define IUIEdit_get_line(This,pVal)	\
    (This)->lpVtbl -> get_line(This,pVal)

#define IUIEdit_get_column(This,pVal)	\
    (This)->lpVtbl -> get_column(This,pVal)

#define IUIEdit_getCursorPosOffset(This,pVal)	\
    (This)->lpVtbl -> getCursorPosOffset(This,pVal)

#define IUIEdit_setCursorPosOffset(This,offset)	\
    (This)->lpVtbl -> setCursorPosOffset(This,offset)

#define IUIEdit_SetText(This,text)	\
    (This)->lpVtbl -> SetText(This,text)

#define IUIEdit_GetText(This,text)	\
    (This)->lpVtbl -> GetText(This,text)

#define IUIEdit_FormatRange(This,start,len,styleIndex,styleElementIndex)	\
    (This)->lpVtbl -> FormatRange(This,start,len,styleIndex,styleElementIndex)

#define IUIEdit_ClearFormatting(This)	\
    (This)->lpVtbl -> ClearFormatting(This)

#define IUIEdit_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IUIEdit_Cut(This)	\
    (This)->lpVtbl -> Cut(This)

#define IUIEdit_Copy(This)	\
    (This)->lpVtbl -> Copy(This)

#define IUIEdit_Paste(This)	\
    (This)->lpVtbl -> Paste(This)

#define IUIEdit_CanPaste(This,nFormat,pVal)	\
    (This)->lpVtbl -> CanPaste(This,nFormat,pVal)

#define IUIEdit_ReplaceText(This,offset,len,data,datalen)	\
    (This)->lpVtbl -> ReplaceText(This,offset,len,data,datalen)

#define IUIEdit_GetSel(This,start,end)	\
    (This)->lpVtbl -> GetSel(This,start,end)

#define IUIEdit_GetSelText(This,pVal)	\
    (This)->lpVtbl -> GetSelText(This,pVal)

#define IUIEdit_SetSel(This,nStartChar,nEndChar,bNoScroll)	\
    (This)->lpVtbl -> SetSel(This,nStartChar,nEndChar,bNoScroll)

#define IUIEdit_ReplaceSelText(This,data,len)	\
    (This)->lpVtbl -> ReplaceSelText(This,data,len)

#define IUIEdit_NewStyle(This,index)	\
    (This)->lpVtbl -> NewStyle(This,index)

#define IUIEdit_SetStyle(This,index,fgColor,bgColor)	\
    (This)->lpVtbl -> SetStyle(This,index,fgColor,bgColor)

#define IUIEdit_AutoList(This,pVal)	\
    (This)->lpVtbl -> AutoList(This,pVal)

#define IUIEdit_AutoListPopup(This)	\
    (This)->lpVtbl -> AutoListPopup(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_textDocument_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB IUIEdit_get_textDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_textDocument_Proxy( 
    IUIEdit * This,
    /* [in] */ IDispatch *newVal);


void __RPC_STUB IUIEdit_put_textDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_vertScroll_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUIEdit_get_vertScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_vertScroll_Proxy( 
    IUIEdit * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IUIEdit_put_vertScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_horzScroll_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUIEdit_get_horzScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_horzScroll_Proxy( 
    IUIEdit * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IUIEdit_put_horzScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_undoManager_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ IOleUndoManager **pVal);


void __RPC_STUB IUIEdit_get_undoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_undoManager_Proxy( 
    IUIEdit * This,
    /* [in] */ IOleUndoManager *newVal);


void __RPC_STUB IUIEdit_put_undoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_multiLine_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_get_multiLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_multiLine_Proxy( 
    IUIEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUIEdit_put_multiLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_wordWrap_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_get_wordWrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_wordWrap_Proxy( 
    IUIEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUIEdit_put_wordWrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_lineNumbers_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_get_lineNumbers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_lineNumbers_Proxy( 
    IUIEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUIEdit_put_lineNumbers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_cursorBox_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ RECT *pVal);


void __RPC_STUB IUIEdit_get_cursorBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_font_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ IFontDisp **pVal);


void __RPC_STUB IUIEdit_get_font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_font_Proxy( 
    IUIEdit * This,
    /* [in] */ IFontDisp *newVal);


void __RPC_STUB IUIEdit_put_font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_LineHeight_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIEdit_get_LineHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_LineHeight_Proxy( 
    IUIEdit * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIEdit_put_LineHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_tabSize_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIEdit_get_tabSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_tabSize_Proxy( 
    IUIEdit * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIEdit_put_tabSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_viewWhitespace_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_get_viewWhitespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_viewWhitespace_Proxy( 
    IUIEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUIEdit_put_viewWhitespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_viewTabs_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_get_viewTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_viewTabs_Proxy( 
    IUIEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUIEdit_put_viewTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_viewSpaces_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_get_viewSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_viewSpaces_Proxy( 
    IUIEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUIEdit_put_viewSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_viewEOLs_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_get_viewEOLs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEdit_put_viewEOLs_Proxy( 
    IUIEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUIEdit_put_viewEOLs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_line_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIEdit_get_line_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEdit_get_column_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIEdit_get_column_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_getCursorPosOffset_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIEdit_getCursorPosOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_setCursorPosOffset_Proxy( 
    IUIEdit * This,
    /* [in] */ long offset);


void __RPC_STUB IUIEdit_setCursorPosOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_SetText_Proxy( 
    IUIEdit * This,
    /* [in] */ BSTR text);


void __RPC_STUB IUIEdit_SetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_GetText_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ BSTR *text);


void __RPC_STUB IUIEdit_GetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_FormatRange_Proxy( 
    IUIEdit * This,
    /* [in] */ long start,
    /* [in] */ long len,
    /* [in] */ long styleIndex,
    /* [in] */ long *styleElementIndex);


void __RPC_STUB IUIEdit_FormatRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_ClearFormatting_Proxy( 
    IUIEdit * This);


void __RPC_STUB IUIEdit_ClearFormatting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_Clear_Proxy( 
    IUIEdit * This);


void __RPC_STUB IUIEdit_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_Cut_Proxy( 
    IUIEdit * This);


void __RPC_STUB IUIEdit_Cut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_Copy_Proxy( 
    IUIEdit * This);


void __RPC_STUB IUIEdit_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_Paste_Proxy( 
    IUIEdit * This);


void __RPC_STUB IUIEdit_Paste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_CanPaste_Proxy( 
    IUIEdit * This,
    /* [in] */ unsigned long nFormat,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IUIEdit_CanPaste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_ReplaceText_Proxy( 
    IUIEdit * This,
    /* [in] */ long offset,
    /* [in] */ long len,
    /* [in] */ BSTR data,
    /* [in] */ long datalen);


void __RPC_STUB IUIEdit_ReplaceText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_GetSel_Proxy( 
    IUIEdit * This,
    /* [out] */ long *start,
    /* [out] */ long *end);


void __RPC_STUB IUIEdit_GetSel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_GetSelText_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IUIEdit_GetSelText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_SetSel_Proxy( 
    IUIEdit * This,
    /* [in] */ long nStartChar,
    /* [in] */ long nEndChar,
    /* [in] */ VARIANT_BOOL bNoScroll);


void __RPC_STUB IUIEdit_SetSel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_ReplaceSelText_Proxy( 
    IUIEdit * This,
    /* [in] */ BSTR data,
    /* [in] */ long len);


void __RPC_STUB IUIEdit_ReplaceSelText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_NewStyle_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ long *index);


void __RPC_STUB IUIEdit_NewStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_SetStyle_Proxy( 
    IUIEdit * This,
    /* [in] */ long index,
    /* [in] */ DWORD fgColor,
    /* [in] */ DWORD bgColor);


void __RPC_STUB IUIEdit_SetStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_AutoList_Proxy( 
    IUIEdit * This,
    /* [retval][out] */ IUIAutoListWindow **pVal);


void __RPC_STUB IUIEdit_AutoList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIEdit_AutoListPopup_Proxy( 
    IUIEdit * This);


void __RPC_STUB IUIEdit_AutoListPopup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIEdit_INTERFACE_DEFINED__ */


#ifndef __IUIColorSlider_INTERFACE_DEFINED__
#define __IUIColorSlider_INTERFACE_DEFINED__

/* interface IUIColorSlider */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIColorSlider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("58C0886F-EF22-434D-BF67-C7A311A8E434")
    IUIColorSlider : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_channel( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_channel( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rgb( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rgb( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_colorMode( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_colorMode( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fromValue( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fromValue( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_toValue( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_toValue( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_pos( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_pos( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIColorSliderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIColorSlider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIColorSlider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIColorSlider * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIColorSlider * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIColorSlider * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIColorSlider * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIColorSlider * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IUIColorSlider * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IUIColorSlider * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_channel )( 
            IUIColorSlider * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_channel )( 
            IUIColorSlider * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_rgb )( 
            IUIColorSlider * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_rgb )( 
            IUIColorSlider * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_colorMode )( 
            IUIColorSlider * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_colorMode )( 
            IUIColorSlider * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fromValue )( 
            IUIColorSlider * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fromValue )( 
            IUIColorSlider * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_toValue )( 
            IUIColorSlider * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_toValue )( 
            IUIColorSlider * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pos )( 
            IUIColorSlider * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_pos )( 
            IUIColorSlider * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IUIColorSliderVtbl;

    interface IUIColorSlider
    {
        CONST_VTBL struct IUIColorSliderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIColorSlider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIColorSlider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIColorSlider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIColorSlider_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIColorSlider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIColorSlider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIColorSlider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIColorSlider_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IUIColorSlider_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IUIColorSlider_get_channel(This,pVal)	\
    (This)->lpVtbl -> get_channel(This,pVal)

#define IUIColorSlider_put_channel(This,newVal)	\
    (This)->lpVtbl -> put_channel(This,newVal)

#define IUIColorSlider_get_rgb(This,pVal)	\
    (This)->lpVtbl -> get_rgb(This,pVal)

#define IUIColorSlider_put_rgb(This,newVal)	\
    (This)->lpVtbl -> put_rgb(This,newVal)

#define IUIColorSlider_get_colorMode(This,pVal)	\
    (This)->lpVtbl -> get_colorMode(This,pVal)

#define IUIColorSlider_put_colorMode(This,newVal)	\
    (This)->lpVtbl -> put_colorMode(This,newVal)

#define IUIColorSlider_get_fromValue(This,pVal)	\
    (This)->lpVtbl -> get_fromValue(This,pVal)

#define IUIColorSlider_put_fromValue(This,newVal)	\
    (This)->lpVtbl -> put_fromValue(This,newVal)

#define IUIColorSlider_get_toValue(This,pVal)	\
    (This)->lpVtbl -> get_toValue(This,pVal)

#define IUIColorSlider_put_toValue(This,newVal)	\
    (This)->lpVtbl -> put_toValue(This,newVal)

#define IUIColorSlider_get_pos(This,pVal)	\
    (This)->lpVtbl -> get_pos(This,pVal)

#define IUIColorSlider_put_pos(This,newVal)	\
    (This)->lpVtbl -> put_pos(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_put_Enabled_Proxy( 
    IUIColorSlider * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IUIColorSlider_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_get_Enabled_Proxy( 
    IUIColorSlider * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IUIColorSlider_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_get_channel_Proxy( 
    IUIColorSlider * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIColorSlider_get_channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_put_channel_Proxy( 
    IUIColorSlider * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIColorSlider_put_channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_get_rgb_Proxy( 
    IUIColorSlider * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUIColorSlider_get_rgb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_put_rgb_Proxy( 
    IUIColorSlider * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IUIColorSlider_put_rgb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_get_colorMode_Proxy( 
    IUIColorSlider * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIColorSlider_get_colorMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_put_colorMode_Proxy( 
    IUIColorSlider * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIColorSlider_put_colorMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_get_fromValue_Proxy( 
    IUIColorSlider * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUIColorSlider_get_fromValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_put_fromValue_Proxy( 
    IUIColorSlider * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IUIColorSlider_put_fromValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_get_toValue_Proxy( 
    IUIColorSlider * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUIColorSlider_get_toValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_put_toValue_Proxy( 
    IUIColorSlider * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IUIColorSlider_put_toValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_get_pos_Proxy( 
    IUIColorSlider * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIColorSlider_get_pos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIColorSlider_put_pos_Proxy( 
    IUIColorSlider * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIColorSlider_put_pos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIColorSlider_INTERFACE_DEFINED__ */


#ifndef __IUITreeControlSite_INTERFACE_DEFINED__
#define __IUITreeControlSite_INTERFACE_DEFINED__

/* interface IUITreeControlSite */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUITreeControlSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92072797-3CA4-418e-B74E-D9D9912337F8")
    IUITreeControlSite : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemText( 
            /* [in] */ DWORD itemData,
            /* [in] */ long column,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUITreeControlSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUITreeControlSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUITreeControlSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUITreeControlSite * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemText )( 
            IUITreeControlSite * This,
            /* [in] */ DWORD itemData,
            /* [in] */ long column,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IUITreeControlSiteVtbl;

    interface IUITreeControlSite
    {
        CONST_VTBL struct IUITreeControlSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUITreeControlSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUITreeControlSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUITreeControlSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUITreeControlSite_GetItemText(This,itemData,column,pVal)	\
    (This)->lpVtbl -> GetItemText(This,itemData,column,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControlSite_GetItemText_Proxy( 
    IUITreeControlSite * This,
    /* [in] */ DWORD itemData,
    /* [in] */ long column,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IUITreeControlSite_GetItemText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUITreeControlSite_INTERFACE_DEFINED__ */


#ifndef __IUITreeItem_INTERFACE_DEFINED__
#define __IUITreeItem_INTERFACE_DEFINED__

/* interface IUITreeItem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUITreeItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E1F3BB72-0912-465b-8682-8ACC21475DCA")
    IUITreeItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChildItem( 
            /* [in] */ long index,
            /* [retval][out] */ IUITreeItem **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppendItem( 
            /* [in] */ IUITreeItem *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetText( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUITreeItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUITreeItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUITreeItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUITreeItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUITreeItem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUITreeItem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUITreeItem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUITreeItem * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChildItem )( 
            IUITreeItem * This,
            /* [in] */ long index,
            /* [retval][out] */ IUITreeItem **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AppendItem )( 
            IUITreeItem * This,
            /* [in] */ IUITreeItem *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IUITreeItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IUITreeItemVtbl;

    interface IUITreeItem
    {
        CONST_VTBL struct IUITreeItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUITreeItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUITreeItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUITreeItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUITreeItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUITreeItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUITreeItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUITreeItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUITreeItem_ChildItem(This,index,pVal)	\
    (This)->lpVtbl -> ChildItem(This,index,pVal)

#define IUITreeItem_AppendItem(This,item)	\
    (This)->lpVtbl -> AppendItem(This,item)

#define IUITreeItem_GetText(This,pVal)	\
    (This)->lpVtbl -> GetText(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeItem_ChildItem_Proxy( 
    IUITreeItem * This,
    /* [in] */ long index,
    /* [retval][out] */ IUITreeItem **pVal);


void __RPC_STUB IUITreeItem_ChildItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeItem_AppendItem_Proxy( 
    IUITreeItem * This,
    /* [in] */ IUITreeItem *item);


void __RPC_STUB IUITreeItem_AppendItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeItem_GetText_Proxy( 
    IUITreeItem * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IUITreeItem_GetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUITreeItem_INTERFACE_DEFINED__ */


#ifndef __IUITreeControl_INTERFACE_DEFINED__
#define __IUITreeControl_INTERFACE_DEFINED__

/* interface IUITreeControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUITreeControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64211711-F30F-4FE5-8A88-A3D3DD978D1C")
    IUITreeControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hImageList( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hImageList( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Indentation( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Indentation( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ItemHeight( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ItemHeight( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertColumn( 
            /* [in] */ long index,
            /* [in] */ BSTR name,
            /* [in] */ long width,
            /* [in] */ BOOL bSizeable,
            /* [in] */ BOOL bVisible,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertItem( 
            /* [in] */ DWORD itemData,
            /* [in] */ IUITreeItem *parentItem,
            /* [in] */ IUITreeItem *beforeItem,
            /* [in] */ BSTR name,
            /* [in] */ long iIndex,
            /* [in] */ long cChildren,
            /* [retval][out] */ IUITreeItem **item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSite( 
            /* [in] */ IUITreeControlSite *pSite) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemInfo( 
            /* [in] */ IUITreeItem *item,
            /* [out] */ DWORD *itemdata,
            /* [out] */ long *iIndex,
            /* [out] */ long *cChildren) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParentItem( 
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pParent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetContent( 
            /* [in] */ IUITreeItem *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextSiblingItem( 
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPrevSiblingItem( 
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelectedItem( 
            /* [retval][out] */ IUITreeItem **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSelectedItem( 
            /* [in] */ IUITreeItem *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRootItem( 
            /* [retval][out] */ IUITreeItem **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstChildItem( 
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastChildItem( 
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemState( 
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetItemInfo( 
            /* [in] */ IUITreeItem *item,
            /* [in] */ DWORD itemdata,
            /* [in] */ long iIndex,
            /* [in] */ long cChildren) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRootItem( 
            /* [in] */ DWORD itemdata,
            /* [retval][out] */ IUITreeItem **pItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ IUITreeItem *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTest( 
            /* [in] */ POINT point,
            /* [out] */ DWORD *flags,
            /* [retval][out] */ IUITreeItem **pItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetItemState( 
            /* [in] */ IUITreeItem *item,
            /* [in] */ DWORD state) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEditControl( 
            /* [retval][out] */ IUIEdit **pEdit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetItemRect( 
            /* [in] */ IUITreeItem *item,
            /* [in] */ long pane,
            /* [in] */ VARIANT_BOOL bTextOnly,
            /* [retval][out] */ RECT *pRect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EditLabel( 
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUIEdit **ppEdit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Expand( 
            /* [in] */ IUITreeItem *item,
            /* [in] */ TVExpandCode code,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateItem( 
            /* [in] */ IUITreeItem *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ DWORD itemData,
            /* [in] */ BSTR name,
            /* [in] */ long iIndex,
            /* [in] */ long cChildren,
            /* [retval][out] */ IUITreeItem **item) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUITreeControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUITreeControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUITreeControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUITreeControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUITreeControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUITreeControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUITreeControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUITreeControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hImageList )( 
            IUITreeControl * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hImageList )( 
            IUITreeControl * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Indentation )( 
            IUITreeControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Indentation )( 
            IUITreeControl * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemHeight )( 
            IUITreeControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ItemHeight )( 
            IUITreeControl * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertColumn )( 
            IUITreeControl * This,
            /* [in] */ long index,
            /* [in] */ BSTR name,
            /* [in] */ long width,
            /* [in] */ BOOL bSizeable,
            /* [in] */ BOOL bVisible,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertItem )( 
            IUITreeControl * This,
            /* [in] */ DWORD itemData,
            /* [in] */ IUITreeItem *parentItem,
            /* [in] */ IUITreeItem *beforeItem,
            /* [in] */ BSTR name,
            /* [in] */ long iIndex,
            /* [in] */ long cChildren,
            /* [retval][out] */ IUITreeItem **item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSite )( 
            IUITreeControl * This,
            /* [in] */ IUITreeControlSite *pSite);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemInfo )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [out] */ DWORD *itemdata,
            /* [out] */ long *iIndex,
            /* [out] */ long *cChildren);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetParentItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pParent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetContent )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNextSiblingItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPrevSiblingItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSelectedItem )( 
            IUITreeControl * This,
            /* [retval][out] */ IUITreeItem **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSelectedItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRootItem )( 
            IUITreeControl * This,
            /* [retval][out] */ IUITreeItem **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFirstChildItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastChildItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUITreeItem **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemState )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetItemInfo )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [in] */ DWORD itemdata,
            /* [in] */ long iIndex,
            /* [in] */ long cChildren);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRootItem )( 
            IUITreeControl * This,
            /* [in] */ DWORD itemdata,
            /* [retval][out] */ IUITreeItem **pItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HitTest )( 
            IUITreeControl * This,
            /* [in] */ POINT point,
            /* [out] */ DWORD *flags,
            /* [retval][out] */ IUITreeItem **pItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetItemState )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [in] */ DWORD state);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEditControl )( 
            IUITreeControl * This,
            /* [retval][out] */ IUIEdit **pEdit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetItemRect )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [in] */ long pane,
            /* [in] */ VARIANT_BOOL bTextOnly,
            /* [retval][out] */ RECT *pRect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EditLabel )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [retval][out] */ IUIEdit **ppEdit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Expand )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item,
            /* [in] */ TVExpandCode code,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateItem )( 
            IUITreeControl * This,
            /* [in] */ IUITreeItem *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateItem )( 
            IUITreeControl * This,
            /* [in] */ DWORD itemData,
            /* [in] */ BSTR name,
            /* [in] */ long iIndex,
            /* [in] */ long cChildren,
            /* [retval][out] */ IUITreeItem **item);
        
        END_INTERFACE
    } IUITreeControlVtbl;

    interface IUITreeControl
    {
        CONST_VTBL struct IUITreeControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUITreeControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUITreeControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUITreeControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUITreeControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUITreeControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUITreeControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUITreeControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUITreeControl_get_hImageList(This,pVal)	\
    (This)->lpVtbl -> get_hImageList(This,pVal)

#define IUITreeControl_put_hImageList(This,newVal)	\
    (This)->lpVtbl -> put_hImageList(This,newVal)

#define IUITreeControl_get_Indentation(This,pVal)	\
    (This)->lpVtbl -> get_Indentation(This,pVal)

#define IUITreeControl_put_Indentation(This,newVal)	\
    (This)->lpVtbl -> put_Indentation(This,newVal)

#define IUITreeControl_get_ItemHeight(This,pVal)	\
    (This)->lpVtbl -> get_ItemHeight(This,pVal)

#define IUITreeControl_put_ItemHeight(This,newVal)	\
    (This)->lpVtbl -> put_ItemHeight(This,newVal)

#define IUITreeControl_InsertColumn(This,index,name,width,bSizeable,bVisible,pVal)	\
    (This)->lpVtbl -> InsertColumn(This,index,name,width,bSizeable,bVisible,pVal)

#define IUITreeControl_InsertItem(This,itemData,parentItem,beforeItem,name,iIndex,cChildren,item)	\
    (This)->lpVtbl -> InsertItem(This,itemData,parentItem,beforeItem,name,iIndex,cChildren,item)

#define IUITreeControl_SetSite(This,pSite)	\
    (This)->lpVtbl -> SetSite(This,pSite)

#define IUITreeControl_GetItemInfo(This,item,itemdata,iIndex,cChildren)	\
    (This)->lpVtbl -> GetItemInfo(This,item,itemdata,iIndex,cChildren)

#define IUITreeControl_GetParentItem(This,item,pParent)	\
    (This)->lpVtbl -> GetParentItem(This,item,pParent)

#define IUITreeControl_ResetContent(This,item)	\
    (This)->lpVtbl -> ResetContent(This,item)

#define IUITreeControl_GetNextSiblingItem(This,item,pVal)	\
    (This)->lpVtbl -> GetNextSiblingItem(This,item,pVal)

#define IUITreeControl_GetPrevSiblingItem(This,item,pVal)	\
    (This)->lpVtbl -> GetPrevSiblingItem(This,item,pVal)

#define IUITreeControl_GetSelectedItem(This,pVal)	\
    (This)->lpVtbl -> GetSelectedItem(This,pVal)

#define IUITreeControl_SetSelectedItem(This,item)	\
    (This)->lpVtbl -> SetSelectedItem(This,item)

#define IUITreeControl_GetRootItem(This,pVal)	\
    (This)->lpVtbl -> GetRootItem(This,pVal)

#define IUITreeControl_GetFirstChildItem(This,item,pVal)	\
    (This)->lpVtbl -> GetFirstChildItem(This,item,pVal)

#define IUITreeControl_GetLastChildItem(This,item,pVal)	\
    (This)->lpVtbl -> GetLastChildItem(This,item,pVal)

#define IUITreeControl_GetItemState(This,item,pVal)	\
    (This)->lpVtbl -> GetItemState(This,item,pVal)

#define IUITreeControl_SetItemInfo(This,item,itemdata,iIndex,cChildren)	\
    (This)->lpVtbl -> SetItemInfo(This,item,itemdata,iIndex,cChildren)

#define IUITreeControl_SetRootItem(This,itemdata,pItem)	\
    (This)->lpVtbl -> SetRootItem(This,itemdata,pItem)

#define IUITreeControl_DeleteItem(This,item)	\
    (This)->lpVtbl -> DeleteItem(This,item)

#define IUITreeControl_HitTest(This,point,flags,pItem)	\
    (This)->lpVtbl -> HitTest(This,point,flags,pItem)

#define IUITreeControl_SetItemState(This,item,state)	\
    (This)->lpVtbl -> SetItemState(This,item,state)

#define IUITreeControl_GetEditControl(This,pEdit)	\
    (This)->lpVtbl -> GetEditControl(This,pEdit)

#define IUITreeControl_GetItemRect(This,item,pane,bTextOnly,pRect)	\
    (This)->lpVtbl -> GetItemRect(This,item,pane,bTextOnly,pRect)

#define IUITreeControl_EditLabel(This,item,ppEdit)	\
    (This)->lpVtbl -> EditLabel(This,item,ppEdit)

#define IUITreeControl_Expand(This,item,code,pSuccess)	\
    (This)->lpVtbl -> Expand(This,item,code,pSuccess)

#define IUITreeControl_UpdateItem(This,item)	\
    (This)->lpVtbl -> UpdateItem(This,item)

#define IUITreeControl_CreateItem(This,itemData,name,iIndex,cChildren,item)	\
    (This)->lpVtbl -> CreateItem(This,itemData,name,iIndex,cChildren,item)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUITreeControl_get_hImageList_Proxy( 
    IUITreeControl * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUITreeControl_get_hImageList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUITreeControl_put_hImageList_Proxy( 
    IUITreeControl * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IUITreeControl_put_hImageList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUITreeControl_get_Indentation_Proxy( 
    IUITreeControl * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUITreeControl_get_Indentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUITreeControl_put_Indentation_Proxy( 
    IUITreeControl * This,
    /* [in] */ long newVal);


void __RPC_STUB IUITreeControl_put_Indentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUITreeControl_get_ItemHeight_Proxy( 
    IUITreeControl * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUITreeControl_get_ItemHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUITreeControl_put_ItemHeight_Proxy( 
    IUITreeControl * This,
    /* [in] */ long newVal);


void __RPC_STUB IUITreeControl_put_ItemHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_InsertColumn_Proxy( 
    IUITreeControl * This,
    /* [in] */ long index,
    /* [in] */ BSTR name,
    /* [in] */ long width,
    /* [in] */ BOOL bSizeable,
    /* [in] */ BOOL bVisible,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUITreeControl_InsertColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_InsertItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ DWORD itemData,
    /* [in] */ IUITreeItem *parentItem,
    /* [in] */ IUITreeItem *beforeItem,
    /* [in] */ BSTR name,
    /* [in] */ long iIndex,
    /* [in] */ long cChildren,
    /* [retval][out] */ IUITreeItem **item);


void __RPC_STUB IUITreeControl_InsertItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_SetSite_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeControlSite *pSite);


void __RPC_STUB IUITreeControl_SetSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetItemInfo_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [out] */ DWORD *itemdata,
    /* [out] */ long *iIndex,
    /* [out] */ long *cChildren);


void __RPC_STUB IUITreeControl_GetItemInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetParentItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [retval][out] */ IUITreeItem **pParent);


void __RPC_STUB IUITreeControl_GetParentItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_ResetContent_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item);


void __RPC_STUB IUITreeControl_ResetContent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetNextSiblingItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [retval][out] */ IUITreeItem **pVal);


void __RPC_STUB IUITreeControl_GetNextSiblingItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetPrevSiblingItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [retval][out] */ IUITreeItem **pVal);


void __RPC_STUB IUITreeControl_GetPrevSiblingItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetSelectedItem_Proxy( 
    IUITreeControl * This,
    /* [retval][out] */ IUITreeItem **pVal);


void __RPC_STUB IUITreeControl_GetSelectedItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_SetSelectedItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item);


void __RPC_STUB IUITreeControl_SetSelectedItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetRootItem_Proxy( 
    IUITreeControl * This,
    /* [retval][out] */ IUITreeItem **pVal);


void __RPC_STUB IUITreeControl_GetRootItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetFirstChildItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [retval][out] */ IUITreeItem **pVal);


void __RPC_STUB IUITreeControl_GetFirstChildItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetLastChildItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [retval][out] */ IUITreeItem **pVal);


void __RPC_STUB IUITreeControl_GetLastChildItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetItemState_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IUITreeControl_GetItemState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_SetItemInfo_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [in] */ DWORD itemdata,
    /* [in] */ long iIndex,
    /* [in] */ long cChildren);


void __RPC_STUB IUITreeControl_SetItemInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_SetRootItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ DWORD itemdata,
    /* [retval][out] */ IUITreeItem **pItem);


void __RPC_STUB IUITreeControl_SetRootItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_DeleteItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item);


void __RPC_STUB IUITreeControl_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_HitTest_Proxy( 
    IUITreeControl * This,
    /* [in] */ POINT point,
    /* [out] */ DWORD *flags,
    /* [retval][out] */ IUITreeItem **pItem);


void __RPC_STUB IUITreeControl_HitTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_SetItemState_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [in] */ DWORD state);


void __RPC_STUB IUITreeControl_SetItemState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetEditControl_Proxy( 
    IUITreeControl * This,
    /* [retval][out] */ IUIEdit **pEdit);


void __RPC_STUB IUITreeControl_GetEditControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_GetItemRect_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [in] */ long pane,
    /* [in] */ VARIANT_BOOL bTextOnly,
    /* [retval][out] */ RECT *pRect);


void __RPC_STUB IUITreeControl_GetItemRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_EditLabel_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [retval][out] */ IUIEdit **ppEdit);


void __RPC_STUB IUITreeControl_EditLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_Expand_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item,
    /* [in] */ TVExpandCode code,
    /* [retval][out] */ VARIANT_BOOL *pSuccess);


void __RPC_STUB IUITreeControl_Expand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_UpdateItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ IUITreeItem *item);


void __RPC_STUB IUITreeControl_UpdateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUITreeControl_CreateItem_Proxy( 
    IUITreeControl * This,
    /* [in] */ DWORD itemData,
    /* [in] */ BSTR name,
    /* [in] */ long iIndex,
    /* [in] */ long cChildren,
    /* [retval][out] */ IUITreeItem **item);


void __RPC_STUB IUITreeControl_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUITreeControl_INTERFACE_DEFINED__ */



#ifndef __UILib_LIBRARY_DEFINED__
#define __UILib_LIBRARY_DEFINED__

/* library UILib */
/* [helpstring][version][uuid] */ 




EXTERN_C const IID LIBID_UILib;

#ifndef ___ITextDataEvents2_DISPINTERFACE_DEFINED__
#define ___ITextDataEvents2_DISPINTERFACE_DEFINED__

/* dispinterface _ITextDataEvents2 */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITextDataEvents2;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C491D478-812D-4dd0-BB77-1FFCC8573CB8")
    _ITextDataEvents2 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITextDataEvents2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITextDataEvents2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITextDataEvents2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITextDataEvents2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITextDataEvents2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITextDataEvents2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITextDataEvents2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITextDataEvents2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITextDataEvents2Vtbl;

    interface _ITextDataEvents2
    {
        CONST_VTBL struct _ITextDataEvents2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITextDataEvents2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITextDataEvents2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITextDataEvents2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITextDataEvents2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITextDataEvents2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITextDataEvents2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITextDataEvents2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITextDataEvents2_DISPINTERFACE_DEFINED__ */


#ifndef ___IUIScrollBarEvents_DISPINTERFACE_DEFINED__
#define ___IUIScrollBarEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIScrollBarEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIScrollBarEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D81E77E5-6169-41E2-94AB-865DACA0C1D5")
    _IUIScrollBarEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIScrollBarEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIScrollBarEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIScrollBarEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIScrollBarEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIScrollBarEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIScrollBarEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIScrollBarEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIScrollBarEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIScrollBarEventsVtbl;

    interface _IUIScrollBarEvents
    {
        CONST_VTBL struct _IUIScrollBarEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIScrollBarEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIScrollBarEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIScrollBarEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIScrollBarEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIScrollBarEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIScrollBarEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIScrollBarEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIScrollBarEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIScrollBar;

#ifdef __cplusplus

class DECLSPEC_UUID("128E2E69-E10B-40CA-B55A-63A67EFA1E99")
UIScrollBar;
#endif

#ifndef ___IUIEditEvents_DISPINTERFACE_DEFINED__
#define ___IUIEditEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIEditEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIEditEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B8C3E236-95BE-49E7-B3D1-807B8769415E")
    _IUIEditEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIEditEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIEditEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIEditEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIEditEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIEditEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIEditEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIEditEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIEditEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIEditEventsVtbl;

    interface _IUIEditEvents
    {
        CONST_VTBL struct _IUIEditEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIEditEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIEditEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIEditEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIEditEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIEditEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIEditEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIEditEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIEditEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("94327EC1-8D79-4A8E-B9B7-ACCCE8C787EF")
UIEdit;
#endif

#ifndef ___IUIListControlEvents_DISPINTERFACE_DEFINED__
#define ___IUIListControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIListControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIListControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("FB6B2EF3-3E3E-47C4-94B9-E1479CC6B8F6")
    _IUIListControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIListControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIListControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIListControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIListControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIListControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIListControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIListControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIListControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIListControlEventsVtbl;

    interface _IUIListControlEvents
    {
        CONST_VTBL struct _IUIListControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIListControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIListControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIListControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIListControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIListControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIListControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIListControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIListControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIListControl;

#ifdef __cplusplus

class DECLSPEC_UUID("DF795E98-F397-4548-A56A-76A2B9AFF6CA")
UIListControl;
#endif

#ifndef ___IUIColorSliderEvents_DISPINTERFACE_DEFINED__
#define ___IUIColorSliderEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIColorSliderEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIColorSliderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6944F83F-D049-499C-9BE6-D58F26C841C6")
    _IUIColorSliderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIColorSliderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIColorSliderEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIColorSliderEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIColorSliderEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIColorSliderEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIColorSliderEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIColorSliderEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIColorSliderEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIColorSliderEventsVtbl;

    interface _IUIColorSliderEvents
    {
        CONST_VTBL struct _IUIColorSliderEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIColorSliderEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIColorSliderEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIColorSliderEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIColorSliderEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIColorSliderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIColorSliderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIColorSliderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIColorSliderEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIColorSlider;

#ifdef __cplusplus

class DECLSPEC_UUID("078A92DD-B19C-4B6B-A954-F596DA402DBE")
UIColorSlider;
#endif

#ifndef ___IUITreeControlEvents_DISPINTERFACE_DEFINED__
#define ___IUITreeControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUITreeControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUITreeControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CFEA71BE-9453-4903-8059-5807EEA3A34B")
    _IUITreeControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUITreeControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUITreeControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUITreeControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUITreeControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUITreeControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUITreeControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUITreeControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUITreeControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUITreeControlEventsVtbl;

    interface _IUITreeControlEvents
    {
        CONST_VTBL struct _IUITreeControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUITreeControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUITreeControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUITreeControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUITreeControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUITreeControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUITreeControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUITreeControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUITreeControlEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IUIToolbarButtons_INTERFACE_DEFINED__
#define __IUIToolbarButtons_INTERFACE_DEFINED__

/* interface IUIToolbarButtons */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIToolbarButtons;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6AAAD42E-F4B9-4E10-92A1-2B9138317527")
    IUIToolbarButtons : public IDispatch
    {
    public:
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
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long *phwnd) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderVisible( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderVisible( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Picture( 
            /* [in] */ IPictureDisp *pPicture) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Picture( 
            /* [in] */ IPictureDisp *pPicture) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ IPictureDisp **ppPicture) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBitmap( 
            /* [in] */ HBITMAP hBitmap,
            /* [in] */ long nWidth) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddButton( 
            /* [in] */ long buttonId,
            /* [in] */ long bmIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIToolbarButtonsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIToolbarButtons * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIToolbarButtons * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIToolbarButtons * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIToolbarButtons * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIToolbarButtons * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIToolbarButtons * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIToolbarButtons * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IUIToolbarButtons * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IUIToolbarButtons * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IUIToolbarButtons * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IUIToolbarButtons * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IUIToolbarButtons * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IUIToolbarButtons * This,
            /* [retval][out] */ long *phwnd);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderVisible )( 
            IUIToolbarButtons * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderVisible )( 
            IUIToolbarButtons * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Picture )( 
            IUIToolbarButtons * This,
            /* [in] */ IPictureDisp *pPicture);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Picture )( 
            IUIToolbarButtons * This,
            /* [in] */ IPictureDisp *pPicture);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Picture )( 
            IUIToolbarButtons * This,
            /* [retval][out] */ IPictureDisp **ppPicture);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBitmap )( 
            IUIToolbarButtons * This,
            /* [in] */ HBITMAP hBitmap,
            /* [in] */ long nWidth);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddButton )( 
            IUIToolbarButtons * This,
            /* [in] */ long buttonId,
            /* [in] */ long bmIndex);
        
        END_INTERFACE
    } IUIToolbarButtonsVtbl;

    interface IUIToolbarButtons
    {
        CONST_VTBL struct IUIToolbarButtonsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIToolbarButtons_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIToolbarButtons_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIToolbarButtons_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIToolbarButtons_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIToolbarButtons_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIToolbarButtons_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIToolbarButtons_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIToolbarButtons_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IUIToolbarButtons_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IUIToolbarButtons_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IUIToolbarButtons_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IUIToolbarButtons_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IUIToolbarButtons_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IUIToolbarButtons_put_BorderVisible(This,vbool)	\
    (This)->lpVtbl -> put_BorderVisible(This,vbool)

#define IUIToolbarButtons_get_BorderVisible(This,pbool)	\
    (This)->lpVtbl -> get_BorderVisible(This,pbool)

#define IUIToolbarButtons_putref_Picture(This,pPicture)	\
    (This)->lpVtbl -> putref_Picture(This,pPicture)

#define IUIToolbarButtons_put_Picture(This,pPicture)	\
    (This)->lpVtbl -> put_Picture(This,pPicture)

#define IUIToolbarButtons_get_Picture(This,ppPicture)	\
    (This)->lpVtbl -> get_Picture(This,ppPicture)

#define IUIToolbarButtons_SetBitmap(This,hBitmap,nWidth)	\
    (This)->lpVtbl -> SetBitmap(This,hBitmap,nWidth)

#define IUIToolbarButtons_AddButton(This,buttonId,bmIndex)	\
    (This)->lpVtbl -> AddButton(This,buttonId,bmIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propputref] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_putref_Font_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IUIToolbarButtons_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_put_Font_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IUIToolbarButtons_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_get_Font_Proxy( 
    IUIToolbarButtons * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IUIToolbarButtons_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_put_Enabled_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IUIToolbarButtons_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_get_Enabled_Proxy( 
    IUIToolbarButtons * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IUIToolbarButtons_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_get_Window_Proxy( 
    IUIToolbarButtons * This,
    /* [retval][out] */ long *phwnd);


void __RPC_STUB IUIToolbarButtons_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_put_BorderVisible_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IUIToolbarButtons_put_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_get_BorderVisible_Proxy( 
    IUIToolbarButtons * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IUIToolbarButtons_get_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_putref_Picture_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ IPictureDisp *pPicture);


void __RPC_STUB IUIToolbarButtons_putref_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_put_Picture_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ IPictureDisp *pPicture);


void __RPC_STUB IUIToolbarButtons_put_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_get_Picture_Proxy( 
    IUIToolbarButtons * This,
    /* [retval][out] */ IPictureDisp **ppPicture);


void __RPC_STUB IUIToolbarButtons_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_SetBitmap_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ HBITMAP hBitmap,
    /* [in] */ long nWidth);


void __RPC_STUB IUIToolbarButtons_SetBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIToolbarButtons_AddButton_Proxy( 
    IUIToolbarButtons * This,
    /* [in] */ long buttonId,
    /* [in] */ long bmIndex);


void __RPC_STUB IUIToolbarButtons_AddButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIToolbarButtons_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UITreeControl;

#ifdef __cplusplus

class DECLSPEC_UUID("80ECF3A6-4DCF-4FB6-8FFB-57319E15B658")
UITreeControl;
#endif

#ifndef ___IUIToolbarButtonsEvents_DISPINTERFACE_DEFINED__
#define ___IUIToolbarButtonsEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIToolbarButtonsEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIToolbarButtonsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("037538F4-E7CB-488B-B4B9-21406E6AEE98")
    _IUIToolbarButtonsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIToolbarButtonsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIToolbarButtonsEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIToolbarButtonsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIToolbarButtonsEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIToolbarButtonsEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIToolbarButtonsEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIToolbarButtonsEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIToolbarButtonsEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIToolbarButtonsEventsVtbl;

    interface _IUIToolbarButtonsEvents
    {
        CONST_VTBL struct _IUIToolbarButtonsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIToolbarButtonsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIToolbarButtonsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIToolbarButtonsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIToolbarButtonsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIToolbarButtonsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIToolbarButtonsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIToolbarButtonsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIToolbarButtonsEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IUIEditUnitValue_INTERFACE_DEFINED__
#define __IUIEditUnitValue_INTERFACE_DEFINED__

/* interface IUIEditUnitValue */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIEditUnitValue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45E01120-EE7E-11D5-95F0-0002E3045703")
    IUIEditUnitValue : public IDispatch
    {
    public:
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
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long *phwnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_value( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_value( 
            /* [in] */ double newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIEditUnitValueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIEditUnitValue * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIEditUnitValue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIEditUnitValue * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIEditUnitValue * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIEditUnitValue * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIEditUnitValue * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIEditUnitValue * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IUIEditUnitValue * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IUIEditUnitValue * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IUIEditUnitValue * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IUIEditUnitValue * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IUIEditUnitValue * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IUIEditUnitValue * This,
            /* [retval][out] */ long *phwnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_value )( 
            IUIEditUnitValue * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_value )( 
            IUIEditUnitValue * This,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } IUIEditUnitValueVtbl;

    interface IUIEditUnitValue
    {
        CONST_VTBL struct IUIEditUnitValueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIEditUnitValue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIEditUnitValue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIEditUnitValue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIEditUnitValue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIEditUnitValue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIEditUnitValue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIEditUnitValue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIEditUnitValue_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IUIEditUnitValue_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IUIEditUnitValue_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IUIEditUnitValue_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IUIEditUnitValue_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IUIEditUnitValue_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IUIEditUnitValue_get_value(This,pVal)	\
    (This)->lpVtbl -> get_value(This,pVal)

#define IUIEditUnitValue_put_value(This,newVal)	\
    (This)->lpVtbl -> put_value(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propputref] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_putref_Font_Proxy( 
    IUIEditUnitValue * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IUIEditUnitValue_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_put_Font_Proxy( 
    IUIEditUnitValue * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IUIEditUnitValue_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_get_Font_Proxy( 
    IUIEditUnitValue * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IUIEditUnitValue_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_put_Enabled_Proxy( 
    IUIEditUnitValue * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IUIEditUnitValue_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_get_Enabled_Proxy( 
    IUIEditUnitValue * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IUIEditUnitValue_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_get_Window_Proxy( 
    IUIEditUnitValue * This,
    /* [retval][out] */ long *phwnd);


void __RPC_STUB IUIEditUnitValue_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_get_value_Proxy( 
    IUIEditUnitValue * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IUIEditUnitValue_get_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIEditUnitValue_put_value_Proxy( 
    IUIEditUnitValue * This,
    /* [in] */ double newVal);


void __RPC_STUB IUIEditUnitValue_put_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIEditUnitValue_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIToolbarButtons;

#ifdef __cplusplus

class DECLSPEC_UUID("D432A4CD-BACF-4B9D-87DF-731A4F85FB9C")
UIToolbarButtons;
#endif

#ifndef ___IUIEditUnitValueEvents_DISPINTERFACE_DEFINED__
#define ___IUIEditUnitValueEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIEditUnitValueEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIEditUnitValueEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("45E01122-EE7E-11D5-95F0-0002E3045703")
    _IUIEditUnitValueEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIEditUnitValueEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIEditUnitValueEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIEditUnitValueEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIEditUnitValueEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIEditUnitValueEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIEditUnitValueEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIEditUnitValueEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIEditUnitValueEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIEditUnitValueEventsVtbl;

    interface _IUIEditUnitValueEvents
    {
        CONST_VTBL struct _IUIEditUnitValueEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIEditUnitValueEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIEditUnitValueEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIEditUnitValueEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIEditUnitValueEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIEditUnitValueEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIEditUnitValueEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIEditUnitValueEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIEditUnitValueEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IColorSpectrum_INTERFACE_DEFINED__
#define __IColorSpectrum_INTERFACE_DEFINED__

/* interface IColorSpectrum */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IColorSpectrum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4005B4FF-EA13-45F1-8AA6-E713E86A32B6")
    IColorSpectrum : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderWidth( 
            /* [in] */ long width) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderWidth( 
            /* [retval][out] */ long *width) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long *phwnd) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderVisible( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderVisible( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IColorSpectrumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IColorSpectrum * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IColorSpectrum * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IColorSpectrum * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IColorSpectrum * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IColorSpectrum * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IColorSpectrum * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IColorSpectrum * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderColor )( 
            IColorSpectrum * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderColor )( 
            IColorSpectrum * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderWidth )( 
            IColorSpectrum * This,
            /* [in] */ long width);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderWidth )( 
            IColorSpectrum * This,
            /* [retval][out] */ long *width);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IColorSpectrum * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IColorSpectrum * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IColorSpectrum * This,
            /* [retval][out] */ long *phwnd);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderVisible )( 
            IColorSpectrum * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderVisible )( 
            IColorSpectrum * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        END_INTERFACE
    } IColorSpectrumVtbl;

    interface IColorSpectrum
    {
        CONST_VTBL struct IColorSpectrumVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColorSpectrum_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IColorSpectrum_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IColorSpectrum_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IColorSpectrum_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IColorSpectrum_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IColorSpectrum_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IColorSpectrum_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IColorSpectrum_put_BorderColor(This,clr)	\
    (This)->lpVtbl -> put_BorderColor(This,clr)

#define IColorSpectrum_get_BorderColor(This,pclr)	\
    (This)->lpVtbl -> get_BorderColor(This,pclr)

#define IColorSpectrum_put_BorderWidth(This,width)	\
    (This)->lpVtbl -> put_BorderWidth(This,width)

#define IColorSpectrum_get_BorderWidth(This,width)	\
    (This)->lpVtbl -> get_BorderWidth(This,width)

#define IColorSpectrum_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IColorSpectrum_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IColorSpectrum_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IColorSpectrum_put_BorderVisible(This,vbool)	\
    (This)->lpVtbl -> put_BorderVisible(This,vbool)

#define IColorSpectrum_get_BorderVisible(This,pbool)	\
    (This)->lpVtbl -> get_BorderVisible(This,pbool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_put_BorderColor_Proxy( 
    IColorSpectrum * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IColorSpectrum_put_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_get_BorderColor_Proxy( 
    IColorSpectrum * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IColorSpectrum_get_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_put_BorderWidth_Proxy( 
    IColorSpectrum * This,
    /* [in] */ long width);


void __RPC_STUB IColorSpectrum_put_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_get_BorderWidth_Proxy( 
    IColorSpectrum * This,
    /* [retval][out] */ long *width);


void __RPC_STUB IColorSpectrum_get_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_put_Enabled_Proxy( 
    IColorSpectrum * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IColorSpectrum_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_get_Enabled_Proxy( 
    IColorSpectrum * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IColorSpectrum_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_get_Window_Proxy( 
    IColorSpectrum * This,
    /* [retval][out] */ long *phwnd);


void __RPC_STUB IColorSpectrum_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_put_BorderVisible_Proxy( 
    IColorSpectrum * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IColorSpectrum_put_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IColorSpectrum_get_BorderVisible_Proxy( 
    IColorSpectrum * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IColorSpectrum_get_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IColorSpectrum_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIEditUnitValue;

#ifdef __cplusplus

class DECLSPEC_UUID("45E01121-EE7E-11D5-95F0-0002E3045703")
UIEditUnitValue;
#endif

#ifndef ___IColorSpectrumEvents_DISPINTERFACE_DEFINED__
#define ___IColorSpectrumEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IColorSpectrumEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IColorSpectrumEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("14CC18D5-2A99-45C9-B68A-7FE78AF33709")
    _IColorSpectrumEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IColorSpectrumEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IColorSpectrumEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IColorSpectrumEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IColorSpectrumEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IColorSpectrumEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IColorSpectrumEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IColorSpectrumEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IColorSpectrumEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IColorSpectrumEventsVtbl;

    interface _IColorSpectrumEvents
    {
        CONST_VTBL struct _IColorSpectrumEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IColorSpectrumEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IColorSpectrumEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IColorSpectrumEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IColorSpectrumEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IColorSpectrumEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IColorSpectrumEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IColorSpectrumEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IColorSpectrumEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IUISlider_INTERFACE_DEFINED__
#define __IUISlider_INTERFACE_DEFINED__

/* interface IUISlider */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUISlider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5282E1A8-EC15-4198-B44F-A6849484E271")
    IUISlider : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_minValue( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_minValue( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_maxValue( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_maxValue( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_value( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_value( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUISliderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUISlider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUISlider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUISlider * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUISlider * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUISlider * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUISlider * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUISlider * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IUISlider * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IUISlider * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_minValue )( 
            IUISlider * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_minValue )( 
            IUISlider * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_maxValue )( 
            IUISlider * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_maxValue )( 
            IUISlider * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_value )( 
            IUISlider * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_value )( 
            IUISlider * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IUISliderVtbl;

    interface IUISlider
    {
        CONST_VTBL struct IUISliderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUISlider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUISlider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUISlider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUISlider_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUISlider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUISlider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUISlider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUISlider_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IUISlider_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IUISlider_get_minValue(This,pVal)	\
    (This)->lpVtbl -> get_minValue(This,pVal)

#define IUISlider_put_minValue(This,newVal)	\
    (This)->lpVtbl -> put_minValue(This,newVal)

#define IUISlider_get_maxValue(This,pVal)	\
    (This)->lpVtbl -> get_maxValue(This,pVal)

#define IUISlider_put_maxValue(This,newVal)	\
    (This)->lpVtbl -> put_maxValue(This,newVal)

#define IUISlider_get_value(This,pVal)	\
    (This)->lpVtbl -> get_value(This,pVal)

#define IUISlider_put_value(This,newVal)	\
    (This)->lpVtbl -> put_value(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUISlider_put_Enabled_Proxy( 
    IUISlider * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IUISlider_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUISlider_get_Enabled_Proxy( 
    IUISlider * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IUISlider_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUISlider_get_minValue_Proxy( 
    IUISlider * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUISlider_get_minValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUISlider_put_minValue_Proxy( 
    IUISlider * This,
    /* [in] */ long newVal);


void __RPC_STUB IUISlider_put_minValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUISlider_get_maxValue_Proxy( 
    IUISlider * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUISlider_get_maxValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUISlider_put_maxValue_Proxy( 
    IUISlider * This,
    /* [in] */ long newVal);


void __RPC_STUB IUISlider_put_maxValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUISlider_get_value_Proxy( 
    IUISlider * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUISlider_get_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUISlider_put_value_Proxy( 
    IUISlider * This,
    /* [in] */ long newVal);


void __RPC_STUB IUISlider_put_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUISlider_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ColorSpectrum;

#ifdef __cplusplus

class DECLSPEC_UUID("FFBA7B14-4B0C-4873-BDE9-E54854A3CBE2")
ColorSpectrum;
#endif

#ifndef ___IUISliderEvents_DISPINTERFACE_DEFINED__
#define ___IUISliderEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUISliderEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUISliderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("867184D3-8151-4B41-939D-08EFDC157700")
    _IUISliderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUISliderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUISliderEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUISliderEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUISliderEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUISliderEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUISliderEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUISliderEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUISliderEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUISliderEventsVtbl;

    interface _IUISliderEvents
    {
        CONST_VTBL struct _IUISliderEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUISliderEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUISliderEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUISliderEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUISliderEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUISliderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUISliderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUISliderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUISliderEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IUIHSLColorWheel_INTERFACE_DEFINED__
#define __IUIHSLColorWheel_INTERFACE_DEFINED__

/* interface IUIHSLColorWheel */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIHSLColorWheel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9F006C5-F2C9-4E53-B614-F835E24FF1A6")
    IUIHSLColorWheel : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hue( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hue( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sat( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sat( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lum( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lum( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIHSLColorWheelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIHSLColorWheel * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIHSLColorWheel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIHSLColorWheel * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIHSLColorWheel * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIHSLColorWheel * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIHSLColorWheel * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIHSLColorWheel * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IUIHSLColorWheel * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IUIHSLColorWheel * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hue )( 
            IUIHSLColorWheel * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hue )( 
            IUIHSLColorWheel * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sat )( 
            IUIHSLColorWheel * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_sat )( 
            IUIHSLColorWheel * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lum )( 
            IUIHSLColorWheel * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_lum )( 
            IUIHSLColorWheel * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IUIHSLColorWheelVtbl;

    interface IUIHSLColorWheel
    {
        CONST_VTBL struct IUIHSLColorWheelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIHSLColorWheel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIHSLColorWheel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIHSLColorWheel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIHSLColorWheel_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIHSLColorWheel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIHSLColorWheel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIHSLColorWheel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIHSLColorWheel_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IUIHSLColorWheel_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IUIHSLColorWheel_get_hue(This,pVal)	\
    (This)->lpVtbl -> get_hue(This,pVal)

#define IUIHSLColorWheel_put_hue(This,newVal)	\
    (This)->lpVtbl -> put_hue(This,newVal)

#define IUIHSLColorWheel_get_sat(This,pVal)	\
    (This)->lpVtbl -> get_sat(This,pVal)

#define IUIHSLColorWheel_put_sat(This,newVal)	\
    (This)->lpVtbl -> put_sat(This,newVal)

#define IUIHSLColorWheel_get_lum(This,pVal)	\
    (This)->lpVtbl -> get_lum(This,pVal)

#define IUIHSLColorWheel_put_lum(This,newVal)	\
    (This)->lpVtbl -> put_lum(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_put_Enabled_Proxy( 
    IUIHSLColorWheel * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IUIHSLColorWheel_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_get_Enabled_Proxy( 
    IUIHSLColorWheel * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IUIHSLColorWheel_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_get_hue_Proxy( 
    IUIHSLColorWheel * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIHSLColorWheel_get_hue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_put_hue_Proxy( 
    IUIHSLColorWheel * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIHSLColorWheel_put_hue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_get_sat_Proxy( 
    IUIHSLColorWheel * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIHSLColorWheel_get_sat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_put_sat_Proxy( 
    IUIHSLColorWheel * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIHSLColorWheel_put_sat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_get_lum_Proxy( 
    IUIHSLColorWheel * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IUIHSLColorWheel_get_lum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUIHSLColorWheel_put_lum_Proxy( 
    IUIHSLColorWheel * This,
    /* [in] */ long newVal);


void __RPC_STUB IUIHSLColorWheel_put_lum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIHSLColorWheel_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UISlider;

#ifdef __cplusplus

class DECLSPEC_UUID("3401C8E9-6245-4B10-9598-CB3DAA8C2537")
UISlider;
#endif

#ifndef ___IUIHSLColorWheelEvents_DISPINTERFACE_DEFINED__
#define ___IUIHSLColorWheelEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIHSLColorWheelEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIHSLColorWheelEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AC4671AB-07E9-49DD-90B6-2E3F75A5B212")
    _IUIHSLColorWheelEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIHSLColorWheelEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIHSLColorWheelEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIHSLColorWheelEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIHSLColorWheelEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIHSLColorWheelEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIHSLColorWheelEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIHSLColorWheelEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIHSLColorWheelEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIHSLColorWheelEventsVtbl;

    interface _IUIHSLColorWheelEvents
    {
        CONST_VTBL struct _IUIHSLColorWheelEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIHSLColorWheelEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIHSLColorWheelEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIHSLColorWheelEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIHSLColorWheelEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIHSLColorWheelEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIHSLColorWheelEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIHSLColorWheelEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIHSLColorWheelEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IUIShellTree_INTERFACE_DEFINED__
#define __IUIShellTree_INTERFACE_DEFINED__

/* interface IUIShellTree */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUIShellTree;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B468B8A7-8F6C-4F7A-BA89-7C4D708EE797")
    IUIShellTree : public IDispatch
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
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ long *phwnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PopulateTree( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUIShellTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUIShellTree * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUIShellTree * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUIShellTree * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUIShellTree * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUIShellTree * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUIShellTree * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUIShellTree * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IUIShellTree * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IUIShellTree * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IUIShellTree * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IUIShellTree * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IUIShellTree * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IUIShellTree * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IUIShellTree * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IUIShellTree * This,
            /* [retval][out] */ long *phwnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PopulateTree )( 
            IUIShellTree * This);
        
        END_INTERFACE
    } IUIShellTreeVtbl;

    interface IUIShellTree
    {
        CONST_VTBL struct IUIShellTreeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUIShellTree_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUIShellTree_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUIShellTree_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUIShellTree_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUIShellTree_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUIShellTree_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUIShellTree_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUIShellTree_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IUIShellTree_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IUIShellTree_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IUIShellTree_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IUIShellTree_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IUIShellTree_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IUIShellTree_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IUIShellTree_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IUIShellTree_PopulateTree(This)	\
    (This)->lpVtbl -> PopulateTree(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIShellTree_put_BackColor_Proxy( 
    IUIShellTree * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IUIShellTree_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIShellTree_get_BackColor_Proxy( 
    IUIShellTree * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IUIShellTree_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE IUIShellTree_putref_Font_Proxy( 
    IUIShellTree * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IUIShellTree_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIShellTree_put_Font_Proxy( 
    IUIShellTree * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IUIShellTree_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIShellTree_get_Font_Proxy( 
    IUIShellTree * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IUIShellTree_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IUIShellTree_put_Enabled_Proxy( 
    IUIShellTree * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IUIShellTree_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIShellTree_get_Enabled_Proxy( 
    IUIShellTree * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IUIShellTree_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IUIShellTree_get_Window_Proxy( 
    IUIShellTree * This,
    /* [retval][out] */ long *phwnd);


void __RPC_STUB IUIShellTree_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUIShellTree_PopulateTree_Proxy( 
    IUIShellTree * This);


void __RPC_STUB IUIShellTree_PopulateTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUIShellTree_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIHSLColorWheel;

#ifdef __cplusplus

class DECLSPEC_UUID("5C2E26BD-11F0-45A6-976E-18EC88213912")
UIHSLColorWheel;
#endif

#ifndef ___IUIShellTreeEvents_DISPINTERFACE_DEFINED__
#define ___IUIShellTreeEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUIShellTreeEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IUIShellTreeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F24B2EFF-9473-4FDC-BA0C-AA5CD096DE9E")
    _IUIShellTreeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUIShellTreeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUIShellTreeEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUIShellTreeEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUIShellTreeEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUIShellTreeEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUIShellTreeEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUIShellTreeEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUIShellTreeEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IUIShellTreeEventsVtbl;

    interface _IUIShellTreeEvents
    {
        CONST_VTBL struct _IUIShellTreeEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUIShellTreeEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUIShellTreeEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUIShellTreeEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUIShellTreeEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUIShellTreeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUIShellTreeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUIShellTreeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUIShellTreeEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UIShellTree;

#ifdef __cplusplus

class DECLSPEC_UUID("F9330907-42F9-4C6A-8F95-7C1E8B38F4BD")
UIShellTree;
#endif
#endif /* __UILib_LIBRARY_DEFINED__ */

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


