/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Apr 28 07:30:06 2002
 */
/* Compiler settings for C:\MMStudio\Extras\LSVG\LSVG.idl:
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

#ifndef __LSVG_h__
#define __LSVG_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILSVGDocument_FWD_DEFINED__
#define __ILSVGDocument_FWD_DEFINED__
typedef interface ILSVGDocument ILSVGDocument;
#endif 	/* __ILSVGDocument_FWD_DEFINED__ */


#ifndef __ILSVGElement_FWD_DEFINED__
#define __ILSVGElement_FWD_DEFINED__
typedef interface ILSVGElement ILSVGElement;
#endif 	/* __ILSVGElement_FWD_DEFINED__ */


#ifndef __ILSVGSVGElement_FWD_DEFINED__
#define __ILSVGSVGElement_FWD_DEFINED__
typedef interface ILSVGSVGElement ILSVGSVGElement;
#endif 	/* __ILSVGSVGElement_FWD_DEFINED__ */


#ifndef __LSVGDocument_FWD_DEFINED__
#define __LSVGDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class LSVGDocument LSVGDocument;
#else
typedef struct LSVGDocument LSVGDocument;
#endif /* __cplusplus */

#endif 	/* __LSVGDocument_FWD_DEFINED__ */


#ifndef __LSVGElement_FWD_DEFINED__
#define __LSVGElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class LSVGElement LSVGElement;
#else
typedef struct LSVGElement LSVGElement;
#endif /* __cplusplus */

#endif 	/* __LSVGElement_FWD_DEFINED__ */


#ifndef __LSVGSVGElement_FWD_DEFINED__
#define __LSVGSVGElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class LSVGSVGElement LSVGSVGElement;
#else
typedef struct LSVGSVGElement LSVGSVGElement;
#endif /* __cplusplus */

#endif 	/* __LSVGSVGElement_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LDOM.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_LSVG_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_LSVG_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LSVG_0000_v0_0_s_ifspec;

#ifndef __ILSVGDocument_INTERFACE_DEFINED__
#define __ILSVGDocument_INTERFACE_DEFINED__

/* interface ILSVGDocument */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILSVGDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FE525497-831B-425A-BC84-5FE2133C5EDA")
    ILSVGDocument : public ILDOMDocument
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILSVGDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILSVGDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILSVGDocument __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeType )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ LDOMNodeType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parentNode )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parentNode )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendChild )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *result);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerDocument )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ownerDocument )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMDocument __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertBefore )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [in] */ ILDOMNode __RPC_FAR *refChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeChild )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *oldChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replaceChild )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [in] */ ILDOMNode __RPC_FAR *oldChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *hasChildNodes )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *cloneNode )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *hasAttributes )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isSupported )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMNamedNodeMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_attributes )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNamedNodeMap __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeName )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeName )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_namespaceURI )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_namespaceURI )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_prefix )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_prefix )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_localName )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_localName )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_childNodes )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMNodeList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNProp )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ DWORD dwdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNProp )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ DWORD __RPC_FAR *dwdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTextOffset )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ long which,
            /* [retval][out] */ long __RPC_FAR *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTextOffset )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setWhiteSpace )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ long which,
            /* [in] */ BSTR whitespace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getWhiteSpace )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ long which,
            /* [retval][out] */ BSTR __RPC_FAR *whitespace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqID )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_uniqID )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_textContent )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_textContent )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_documentElement )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMElement __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_documentElement )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMElement __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_url )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_url )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_async )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_async )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_implementation )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMImplementation __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_implementation )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMImplementation __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_encoding )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_encoding )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_actualEncoding )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_actualEncoding )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_standalone )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_standalone )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Version )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_doctype )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMDocumentType __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_doctype )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMDocumentType __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createElement )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR tagName,
            /* [retval][out] */ ILDOMElement __RPC_FAR *__RPC_FAR *ppElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createElementNS )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [retval][out] */ ILDOMElement __RPC_FAR *__RPC_FAR *ppElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createAttribute )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr __RPC_FAR *__RPC_FAR *ppAttr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createAttributeNS )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [retval][out] */ ILDOMAttr __RPC_FAR *__RPC_FAR *ppAttr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createTextNode )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR data,
            /* [retval][out] */ ILDOMText __RPC_FAR *__RPC_FAR *ppText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createComment )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR data,
            /* [retval][out] */ ILDOMComment __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createCDATASection )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR data,
            /* [retval][out] */ ILDOMCDATASection __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createDocumentFragment )( 
            ILSVGDocument __RPC_FAR * This,
            /* [retval][out] */ ILDOMDocumentFragment __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getElementById )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR elementId,
            /* [retval][out] */ ILDOMElement __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *load )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR url,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *save )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR url,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadXML )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ BSTR data,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *success);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *saveXML )( 
            ILSVGDocument __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *node,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } ILSVGDocumentVtbl;

    interface ILSVGDocument
    {
        CONST_VTBL struct ILSVGDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILSVGDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILSVGDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILSVGDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILSVGDocument_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILSVGDocument_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILSVGDocument_put_parentNode(This,pVal)	\
    (This)->lpVtbl -> put_parentNode(This,pVal)

#define ILSVGDocument_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILSVGDocument_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILSVGDocument_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILSVGDocument_put_nextSibling(This,pVal)	\
    (This)->lpVtbl -> put_nextSibling(This,pVal)

#define ILSVGDocument_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILSVGDocument_put_previousSibling(This,pVal)	\
    (This)->lpVtbl -> put_previousSibling(This,pVal)

#define ILSVGDocument_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILSVGDocument_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILSVGDocument_put_ownerDocument(This,newVal)	\
    (This)->lpVtbl -> put_ownerDocument(This,newVal)

#define ILSVGDocument_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILSVGDocument_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILSVGDocument_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILSVGDocument_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILSVGDocument_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILSVGDocument_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILSVGDocument_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILSVGDocument_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILSVGDocument_put_attributes(This,newVal)	\
    (This)->lpVtbl -> put_attributes(This,newVal)

#define ILSVGDocument_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILSVGDocument_put_nodeName(This,newVal)	\
    (This)->lpVtbl -> put_nodeName(This,newVal)

#define ILSVGDocument_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILSVGDocument_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILSVGDocument_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILSVGDocument_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILSVGDocument_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILSVGDocument_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILSVGDocument_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILSVGDocument_SetNProp(This,name,dwdata)	\
    (This)->lpVtbl -> SetNProp(This,name,dwdata)

#define ILSVGDocument_GetNProp(This,name,dwdata)	\
    (This)->lpVtbl -> GetNProp(This,name,dwdata)

#define ILSVGDocument_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILSVGDocument_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)

#define ILSVGDocument_setWhiteSpace(This,which,whitespace)	\
    (This)->lpVtbl -> setWhiteSpace(This,which,whitespace)

#define ILSVGDocument_getWhiteSpace(This,which,whitespace)	\
    (This)->lpVtbl -> getWhiteSpace(This,which,whitespace)

#define ILSVGDocument_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILSVGDocument_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILSVGDocument_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILSVGDocument_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)


#define ILSVGDocument_get_documentElement(This,pVal)	\
    (This)->lpVtbl -> get_documentElement(This,pVal)

#define ILSVGDocument_put_documentElement(This,newVal)	\
    (This)->lpVtbl -> put_documentElement(This,newVal)

#define ILSVGDocument_get_url(This,pVal)	\
    (This)->lpVtbl -> get_url(This,pVal)

#define ILSVGDocument_put_url(This,newVal)	\
    (This)->lpVtbl -> put_url(This,newVal)

#define ILSVGDocument_get_async(This,pVal)	\
    (This)->lpVtbl -> get_async(This,pVal)

#define ILSVGDocument_put_async(This,newVal)	\
    (This)->lpVtbl -> put_async(This,newVal)

#define ILSVGDocument_get_implementation(This,pVal)	\
    (This)->lpVtbl -> get_implementation(This,pVal)

#define ILSVGDocument_put_implementation(This,newVal)	\
    (This)->lpVtbl -> put_implementation(This,newVal)

#define ILSVGDocument_get_encoding(This,pVal)	\
    (This)->lpVtbl -> get_encoding(This,pVal)

#define ILSVGDocument_put_encoding(This,newVal)	\
    (This)->lpVtbl -> put_encoding(This,newVal)

#define ILSVGDocument_get_actualEncoding(This,pVal)	\
    (This)->lpVtbl -> get_actualEncoding(This,pVal)

#define ILSVGDocument_put_actualEncoding(This,newVal)	\
    (This)->lpVtbl -> put_actualEncoding(This,newVal)

#define ILSVGDocument_get_standalone(This,pVal)	\
    (This)->lpVtbl -> get_standalone(This,pVal)

#define ILSVGDocument_put_standalone(This,newVal)	\
    (This)->lpVtbl -> put_standalone(This,newVal)

#define ILSVGDocument_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ILSVGDocument_put_Version(This,newVal)	\
    (This)->lpVtbl -> put_Version(This,newVal)

#define ILSVGDocument_get_doctype(This,pVal)	\
    (This)->lpVtbl -> get_doctype(This,pVal)

#define ILSVGDocument_put_doctype(This,newVal)	\
    (This)->lpVtbl -> put_doctype(This,newVal)

#define ILSVGDocument_createElement(This,tagName,ppElement)	\
    (This)->lpVtbl -> createElement(This,tagName,ppElement)

#define ILSVGDocument_createElementNS(This,namespaceURI,qualifiedName,ppElement)	\
    (This)->lpVtbl -> createElementNS(This,namespaceURI,qualifiedName,ppElement)

#define ILSVGDocument_createAttribute(This,name,ppAttr)	\
    (This)->lpVtbl -> createAttribute(This,name,ppAttr)

#define ILSVGDocument_createAttributeNS(This,namespaceURI,qualifiedName,ppAttr)	\
    (This)->lpVtbl -> createAttributeNS(This,namespaceURI,qualifiedName,ppAttr)

#define ILSVGDocument_createTextNode(This,data,ppText)	\
    (This)->lpVtbl -> createTextNode(This,data,ppText)

#define ILSVGDocument_createComment(This,data,pVal)	\
    (This)->lpVtbl -> createComment(This,data,pVal)

#define ILSVGDocument_createCDATASection(This,data,pVal)	\
    (This)->lpVtbl -> createCDATASection(This,data,pVal)

#define ILSVGDocument_createDocumentFragment(This,pVal)	\
    (This)->lpVtbl -> createDocumentFragment(This,pVal)

#define ILSVGDocument_getElementById(This,elementId,pVal)	\
    (This)->lpVtbl -> getElementById(This,elementId,pVal)

#define ILSVGDocument_load(This,url,success)	\
    (This)->lpVtbl -> load(This,url,success)

#define ILSVGDocument_save(This,url,success)	\
    (This)->lpVtbl -> save(This,url,success)

#define ILSVGDocument_loadXML(This,data,success)	\
    (This)->lpVtbl -> loadXML(This,data,success)

#define ILSVGDocument_saveXML(This,node,pVal)	\
    (This)->lpVtbl -> saveXML(This,node,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILSVGDocument_INTERFACE_DEFINED__ */


#ifndef __ILSVGElement_INTERFACE_DEFINED__
#define __ILSVGElement_INTERFACE_DEFINED__

/* interface ILSVGElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILSVGElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6FB104F8-6C42-4CA9-A0C4-89CA85E92EF4")
    ILSVGElement : public ILDOMElement
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ownerSVGElement( 
            /* [retval][out] */ ILSVGSVGElement __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_viewportElement( 
            /* [retval][out] */ ILSVGElement __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILSVGElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILSVGElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILSVGElement __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeType )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ LDOMNodeType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parentNode )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parentNode )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendChild )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *result);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerDocument )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ownerDocument )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMDocument __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertBefore )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [in] */ ILDOMNode __RPC_FAR *refChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeChild )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *oldChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replaceChild )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [in] */ ILDOMNode __RPC_FAR *oldChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *hasChildNodes )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *cloneNode )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *hasAttributes )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isSupported )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNamedNodeMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_attributes )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNamedNodeMap __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeName )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeName )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_namespaceURI )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_namespaceURI )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_prefix )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_prefix )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_localName )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_localName )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_childNodes )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNodeList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNProp )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ DWORD dwdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNProp )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ DWORD __RPC_FAR *dwdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTextOffset )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [retval][out] */ long __RPC_FAR *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTextOffset )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setWhiteSpace )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [in] */ BSTR whitespace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getWhiteSpace )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [retval][out] */ BSTR __RPC_FAR *whitespace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqID )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_uniqID )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_textContent )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_textContent )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tagName )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_tagName )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttributeNode )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMAttr __RPC_FAR *newAttr,
            /* [retval][out] */ ILDOMAttr __RPC_FAR *__RPC_FAR *ppAttr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttributeNode )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *pValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttributeNS )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttributeNS )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [in] */ BSTR value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            ILSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerSVGElement )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILSVGSVGElement __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_viewportElement )( 
            ILSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILSVGElement __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } ILSVGElementVtbl;

    interface ILSVGElement
    {
        CONST_VTBL struct ILSVGElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILSVGElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILSVGElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILSVGElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILSVGElement_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILSVGElement_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILSVGElement_put_parentNode(This,pVal)	\
    (This)->lpVtbl -> put_parentNode(This,pVal)

#define ILSVGElement_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILSVGElement_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILSVGElement_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILSVGElement_put_nextSibling(This,pVal)	\
    (This)->lpVtbl -> put_nextSibling(This,pVal)

#define ILSVGElement_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILSVGElement_put_previousSibling(This,pVal)	\
    (This)->lpVtbl -> put_previousSibling(This,pVal)

#define ILSVGElement_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILSVGElement_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILSVGElement_put_ownerDocument(This,newVal)	\
    (This)->lpVtbl -> put_ownerDocument(This,newVal)

#define ILSVGElement_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILSVGElement_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILSVGElement_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILSVGElement_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILSVGElement_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILSVGElement_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILSVGElement_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILSVGElement_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILSVGElement_put_attributes(This,newVal)	\
    (This)->lpVtbl -> put_attributes(This,newVal)

#define ILSVGElement_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILSVGElement_put_nodeName(This,newVal)	\
    (This)->lpVtbl -> put_nodeName(This,newVal)

#define ILSVGElement_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILSVGElement_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILSVGElement_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILSVGElement_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILSVGElement_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILSVGElement_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILSVGElement_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILSVGElement_SetNProp(This,name,dwdata)	\
    (This)->lpVtbl -> SetNProp(This,name,dwdata)

#define ILSVGElement_GetNProp(This,name,dwdata)	\
    (This)->lpVtbl -> GetNProp(This,name,dwdata)

#define ILSVGElement_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILSVGElement_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)

#define ILSVGElement_setWhiteSpace(This,which,whitespace)	\
    (This)->lpVtbl -> setWhiteSpace(This,which,whitespace)

#define ILSVGElement_getWhiteSpace(This,which,whitespace)	\
    (This)->lpVtbl -> getWhiteSpace(This,which,whitespace)

#define ILSVGElement_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILSVGElement_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILSVGElement_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILSVGElement_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)


#define ILSVGElement_get_tagName(This,pVal)	\
    (This)->lpVtbl -> get_tagName(This,pVal)

#define ILSVGElement_put_tagName(This,newVal)	\
    (This)->lpVtbl -> put_tagName(This,newVal)

#define ILSVGElement_setAttributeNode(This,newAttr,ppAttr)	\
    (This)->lpVtbl -> setAttributeNode(This,newAttr,ppAttr)

#define ILSVGElement_getAttributeNode(This,name,ppResult)	\
    (This)->lpVtbl -> getAttributeNode(This,name,ppResult)

#define ILSVGElement_getAttribute(This,name,pValue)	\
    (This)->lpVtbl -> getAttribute(This,name,pValue)

#define ILSVGElement_setAttribute(This,name,value)	\
    (This)->lpVtbl -> setAttribute(This,name,value)

#define ILSVGElement_getAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNS(This,namespaceURI,localName,pVal)

#define ILSVGElement_setAttributeNS(This,namespaceURI,qualifiedName,value)	\
    (This)->lpVtbl -> setAttributeNS(This,namespaceURI,qualifiedName,value)

#define ILSVGElement_removeAttribute(This,name)	\
    (This)->lpVtbl -> removeAttribute(This,name)


#define ILSVGElement_get_ownerSVGElement(This,pVal)	\
    (This)->lpVtbl -> get_ownerSVGElement(This,pVal)

#define ILSVGElement_get_viewportElement(This,pVal)	\
    (This)->lpVtbl -> get_viewportElement(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILSVGElement_get_ownerSVGElement_Proxy( 
    ILSVGElement __RPC_FAR * This,
    /* [retval][out] */ ILSVGSVGElement __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ILSVGElement_get_ownerSVGElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILSVGElement_get_viewportElement_Proxy( 
    ILSVGElement __RPC_FAR * This,
    /* [retval][out] */ ILSVGElement __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ILSVGElement_get_viewportElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILSVGElement_INTERFACE_DEFINED__ */


#ifndef __ILSVGSVGElement_INTERFACE_DEFINED__
#define __ILSVGSVGElement_INTERFACE_DEFINED__

/* interface ILSVGSVGElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILSVGSVGElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("501F1F85-7CF8-487D-B474-7370EAE55521")
    ILSVGSVGElement : public ILSVGElement
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILSVGSVGElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILSVGSVGElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILSVGSVGElement __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeType )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ LDOMNodeType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parentNode )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_parentNode )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_firstChild )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastChild )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nextSibling )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nextSibling )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_previousSibling )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_previousSibling )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *appendChild )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *result);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerDocument )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMDocument __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ownerDocument )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMDocument __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertBefore )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [in] */ ILDOMNode __RPC_FAR *refChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeChild )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *oldChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replaceChild )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNode __RPC_FAR *newChild,
            /* [in] */ ILDOMNode __RPC_FAR *oldChild,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *hasChildNodes )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *cloneNode )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *hasAttributes )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isSupported )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNamedNodeMap __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_attributes )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMNamedNodeMap __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeName )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeName )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_namespaceURI )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_namespaceURI )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_prefix )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_prefix )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_localName )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_localName )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_childNodes )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILDOMNodeList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNProp )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ DWORD dwdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNProp )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ DWORD __RPC_FAR *dwdata);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTextOffset )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [retval][out] */ long __RPC_FAR *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTextOffset )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setWhiteSpace )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [in] */ BSTR whitespace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getWhiteSpace )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ long which,
            /* [retval][out] */ BSTR __RPC_FAR *whitespace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_uniqID )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_uniqID )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_textContent )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_textContent )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tagName )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_tagName )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttributeNode )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ ILDOMAttr __RPC_FAR *newAttr,
            /* [retval][out] */ ILDOMAttr __RPC_FAR *__RPC_FAR *ppAttr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttributeNode )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr __RPC_FAR *__RPC_FAR *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *pValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttributeNS )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttributeNS )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [in] */ BSTR value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ownerSVGElement )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILSVGSVGElement __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_viewportElement )( 
            ILSVGSVGElement __RPC_FAR * This,
            /* [retval][out] */ ILSVGElement __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } ILSVGSVGElementVtbl;

    interface ILSVGSVGElement
    {
        CONST_VTBL struct ILSVGSVGElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILSVGSVGElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILSVGSVGElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILSVGSVGElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILSVGSVGElement_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILSVGSVGElement_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILSVGSVGElement_put_parentNode(This,pVal)	\
    (This)->lpVtbl -> put_parentNode(This,pVal)

#define ILSVGSVGElement_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILSVGSVGElement_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILSVGSVGElement_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILSVGSVGElement_put_nextSibling(This,pVal)	\
    (This)->lpVtbl -> put_nextSibling(This,pVal)

#define ILSVGSVGElement_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILSVGSVGElement_put_previousSibling(This,pVal)	\
    (This)->lpVtbl -> put_previousSibling(This,pVal)

#define ILSVGSVGElement_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILSVGSVGElement_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILSVGSVGElement_put_ownerDocument(This,newVal)	\
    (This)->lpVtbl -> put_ownerDocument(This,newVal)

#define ILSVGSVGElement_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILSVGSVGElement_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILSVGSVGElement_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILSVGSVGElement_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILSVGSVGElement_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILSVGSVGElement_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILSVGSVGElement_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILSVGSVGElement_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILSVGSVGElement_put_attributes(This,newVal)	\
    (This)->lpVtbl -> put_attributes(This,newVal)

#define ILSVGSVGElement_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILSVGSVGElement_put_nodeName(This,newVal)	\
    (This)->lpVtbl -> put_nodeName(This,newVal)

#define ILSVGSVGElement_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILSVGSVGElement_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILSVGSVGElement_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILSVGSVGElement_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILSVGSVGElement_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILSVGSVGElement_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILSVGSVGElement_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILSVGSVGElement_SetNProp(This,name,dwdata)	\
    (This)->lpVtbl -> SetNProp(This,name,dwdata)

#define ILSVGSVGElement_GetNProp(This,name,dwdata)	\
    (This)->lpVtbl -> GetNProp(This,name,dwdata)

#define ILSVGSVGElement_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILSVGSVGElement_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)

#define ILSVGSVGElement_setWhiteSpace(This,which,whitespace)	\
    (This)->lpVtbl -> setWhiteSpace(This,which,whitespace)

#define ILSVGSVGElement_getWhiteSpace(This,which,whitespace)	\
    (This)->lpVtbl -> getWhiteSpace(This,which,whitespace)

#define ILSVGSVGElement_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILSVGSVGElement_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILSVGSVGElement_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILSVGSVGElement_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)


#define ILSVGSVGElement_get_tagName(This,pVal)	\
    (This)->lpVtbl -> get_tagName(This,pVal)

#define ILSVGSVGElement_put_tagName(This,newVal)	\
    (This)->lpVtbl -> put_tagName(This,newVal)

#define ILSVGSVGElement_setAttributeNode(This,newAttr,ppAttr)	\
    (This)->lpVtbl -> setAttributeNode(This,newAttr,ppAttr)

#define ILSVGSVGElement_getAttributeNode(This,name,ppResult)	\
    (This)->lpVtbl -> getAttributeNode(This,name,ppResult)

#define ILSVGSVGElement_getAttribute(This,name,pValue)	\
    (This)->lpVtbl -> getAttribute(This,name,pValue)

#define ILSVGSVGElement_setAttribute(This,name,value)	\
    (This)->lpVtbl -> setAttribute(This,name,value)

#define ILSVGSVGElement_getAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNS(This,namespaceURI,localName,pVal)

#define ILSVGSVGElement_setAttributeNS(This,namespaceURI,qualifiedName,value)	\
    (This)->lpVtbl -> setAttributeNS(This,namespaceURI,qualifiedName,value)

#define ILSVGSVGElement_removeAttribute(This,name)	\
    (This)->lpVtbl -> removeAttribute(This,name)


#define ILSVGSVGElement_get_ownerSVGElement(This,pVal)	\
    (This)->lpVtbl -> get_ownerSVGElement(This,pVal)

#define ILSVGSVGElement_get_viewportElement(This,pVal)	\
    (This)->lpVtbl -> get_viewportElement(This,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILSVGSVGElement_INTERFACE_DEFINED__ */



#ifndef __LSVGLib_LIBRARY_DEFINED__
#define __LSVGLib_LIBRARY_DEFINED__

/* library LSVGLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LSVGLib;

EXTERN_C const CLSID CLSID_LSVGDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("2221506D-8EDA-4E2E-990B-1F09730105DE")
LSVGDocument;
#endif

EXTERN_C const CLSID CLSID_LSVGElement;

#ifdef __cplusplus

class DECLSPEC_UUID("3804E6CA-F5DE-4150-A5E6-BFFCB1063BDF")
LSVGElement;
#endif

EXTERN_C const CLSID CLSID_LSVGSVGElement;

#ifdef __cplusplus

class DECLSPEC_UUID("2BDD6556-EA30-48FC-AB51-703262FBDBB7")
LSVGSVGElement;
#endif
#endif /* __LSVGLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
