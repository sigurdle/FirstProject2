

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon May 24 23:39:54 2004
 */
/* Compiler settings for C:\MMStudio\Extras\LMathML\LMathML.idl:
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

#ifndef __LMathML_h__
#define __LMathML_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILMathMLElement_FWD_DEFINED__
#define __ILMathMLElement_FWD_DEFINED__
typedef interface ILMathMLElement ILMathMLElement;
#endif 	/* __ILMathMLElement_FWD_DEFINED__ */


#ifndef __ILMathMLContainer_FWD_DEFINED__
#define __ILMathMLContainer_FWD_DEFINED__
typedef interface ILMathMLContainer ILMathMLContainer;
#endif 	/* __ILMathMLContainer_FWD_DEFINED__ */


#ifndef __ILMathMLPresentationElement_FWD_DEFINED__
#define __ILMathMLPresentationElement_FWD_DEFINED__
typedef interface ILMathMLPresentationElement ILMathMLPresentationElement;
#endif 	/* __ILMathMLPresentationElement_FWD_DEFINED__ */


#ifndef __ILMathMLPresentationContainer_FWD_DEFINED__
#define __ILMathMLPresentationContainer_FWD_DEFINED__
typedef interface ILMathMLPresentationContainer ILMathMLPresentationContainer;
#endif 	/* __ILMathMLPresentationContainer_FWD_DEFINED__ */


#ifndef __ILMathMLMathElement_FWD_DEFINED__
#define __ILMathMLMathElement_FWD_DEFINED__
typedef interface ILMathMLMathElement ILMathMLMathElement;
#endif 	/* __ILMathMLMathElement_FWD_DEFINED__ */


#ifndef __ILMathMLFencedElement_FWD_DEFINED__
#define __ILMathMLFencedElement_FWD_DEFINED__
typedef interface ILMathMLFencedElement ILMathMLFencedElement;
#endif 	/* __ILMathMLFencedElement_FWD_DEFINED__ */


#ifndef __LMathMLImplementation_FWD_DEFINED__
#define __LMathMLImplementation_FWD_DEFINED__

#ifdef __cplusplus
typedef class LMathMLImplementation LMathMLImplementation;
#else
typedef struct LMathMLImplementation LMathMLImplementation;
#endif /* __cplusplus */

#endif 	/* __LMathMLImplementation_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "LXML.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_LMathML_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_LMathML_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LMathML_0000_v0_0_s_ifspec;

#ifndef __ILMathMLElement_INTERFACE_DEFINED__
#define __ILMathMLElement_INTERFACE_DEFINED__

/* interface ILMathMLElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILMathMLElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("871E30A0-5B55-46fa-8546-3D5E58A82918")
    ILMathMLElement : public ILDOMElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_className( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_className( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mathElementStyle( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_mathElementStyle( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__id( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put__id( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_xref( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_xref( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_href( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_href( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ownerMathElement( 
            /* [retval][out] */ ILMathMLMathElement **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMathMLElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILMathMLElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILMathMLElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILMathMLElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeType )( 
            ILMathMLElement * This,
            /* [retval][out] */ LDOMNodeType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeName )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeValue )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_nodeValue )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_parentNode )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_firstChild )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lastChild )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nextSibling )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_previousSibling )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerDocument )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMDocument **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_attributes )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMNamedNodeMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_childNodes )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *appendChild )( 
            ILMathMLElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [retval][out] */ ILDOMNode **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *insertBefore )( 
            ILMathMLElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ VARIANT refChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeChild )( 
            ILMathMLElement * This,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *replaceChild )( 
            ILMathMLElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasChildNodes )( 
            ILMathMLElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasAttributes )( 
            ILMathMLElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *cloneNode )( 
            ILMathMLElement * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isSupported )( 
            ILMathMLElement * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *normalize )( 
            ILMathMLElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_namespaceURI )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_namespaceURI )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_prefix )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_prefix )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_localName )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_localName )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_textContent )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_textContent )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupPrefix )( 
            ILMathMLElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupNamespaceURI )( 
            ILMathMLElement * This,
            /* [in] */ BSTR prefix,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setUserData )( 
            ILMathMLElement * This,
            /* [in] */ BSTR key,
            /* [in] */ LDOMUserData data,
            /* [in] */ ILDOMUserDataHandler *handler,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getUserData )( 
            ILMathMLElement * This,
            /* [in] */ BSTR key,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeChildren )( 
            ILMathMLElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uniqID )( 
            ILMathMLElement * This,
            /* [retval][out] */ GUID *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_uniqID )( 
            ILMathMLElement * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTextOffset )( 
            ILMathMLElement * This,
            /* [in] */ long which,
            /* [retval][out] */ long *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setTextOffset )( 
            ILMathMLElement * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_tagName )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttribute )( 
            ILMathMLElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttribute )( 
            ILMathMLElement * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttribute )( 
            ILMathMLElement * This,
            /* [in] */ BSTR name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNode )( 
            ILMathMLElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNode )( 
            ILMathMLElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNode )( 
            ILMathMLElement * This,
            /* [in] */ ILDOMAttr *oldAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttribute )( 
            ILMathMLElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNS )( 
            ILMathMLElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNS )( 
            ILMathMLElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNS )( 
            ILMathMLElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNodeNS )( 
            ILMathMLElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNodeNS )( 
            ILMathMLElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttributeNS )( 
            ILMathMLElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagName )( 
            ILMathMLElement * This,
            /* [in] */ BSTR tagname,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagNameNS )( 
            ILMathMLElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_markupContent )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_markupContent )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *addBehavior )( 
            ILMathMLElement * This,
            /* [in] */ BSTR bstrUrl,
            /* [in] */ VARIANT *pvarFactory,
            /* [retval][out] */ long *pCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setActive )( 
            ILMathMLElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_className )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_className )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mathElementStyle )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mathElementStyle )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__id )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put__id )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_xref )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_xref )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_href )( 
            ILMathMLElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_href )( 
            ILMathMLElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerMathElement )( 
            ILMathMLElement * This,
            /* [retval][out] */ ILMathMLMathElement **pVal);
        
        END_INTERFACE
    } ILMathMLElementVtbl;

    interface ILMathMLElement
    {
        CONST_VTBL struct ILMathMLElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMathMLElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMathMLElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMathMLElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMathMLElement_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILMathMLElement_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILMathMLElement_get_nodeValue(This,pVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pVal)

#define ILMathMLElement_put_nodeValue(This,newVal)	\
    (This)->lpVtbl -> put_nodeValue(This,newVal)

#define ILMathMLElement_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILMathMLElement_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILMathMLElement_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILMathMLElement_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILMathMLElement_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILMathMLElement_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILMathMLElement_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILMathMLElement_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILMathMLElement_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILMathMLElement_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILMathMLElement_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILMathMLElement_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILMathMLElement_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILMathMLElement_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILMathMLElement_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILMathMLElement_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILMathMLElement_normalize(This)	\
    (This)->lpVtbl -> normalize(This)

#define ILMathMLElement_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILMathMLElement_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILMathMLElement_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILMathMLElement_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILMathMLElement_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILMathMLElement_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILMathMLElement_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILMathMLElement_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)

#define ILMathMLElement_lookupPrefix(This,namespaceURI,pVal)	\
    (This)->lpVtbl -> lookupPrefix(This,namespaceURI,pVal)

#define ILMathMLElement_lookupNamespaceURI(This,prefix,pVal)	\
    (This)->lpVtbl -> lookupNamespaceURI(This,prefix,pVal)

#define ILMathMLElement_setUserData(This,key,data,handler,pVal)	\
    (This)->lpVtbl -> setUserData(This,key,data,handler,pVal)

#define ILMathMLElement_getUserData(This,key,pVal)	\
    (This)->lpVtbl -> getUserData(This,key,pVal)

#define ILMathMLElement_removeChildren(This)	\
    (This)->lpVtbl -> removeChildren(This)

#define ILMathMLElement_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILMathMLElement_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILMathMLElement_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILMathMLElement_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)


#define ILMathMLElement_get_tagName(This,pVal)	\
    (This)->lpVtbl -> get_tagName(This,pVal)

#define ILMathMLElement_getAttribute(This,name,pVal)	\
    (This)->lpVtbl -> getAttribute(This,name,pVal)

#define ILMathMLElement_setAttribute(This,name,value)	\
    (This)->lpVtbl -> setAttribute(This,name,value)

#define ILMathMLElement_removeAttribute(This,name)	\
    (This)->lpVtbl -> removeAttribute(This,name)

#define ILMathMLElement_getAttributeNode(This,name,pVal)	\
    (This)->lpVtbl -> getAttributeNode(This,name,pVal)

#define ILMathMLElement_setAttributeNode(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNode(This,newAttr,pVal)

#define ILMathMLElement_removeAttributeNode(This,oldAttr,pVal)	\
    (This)->lpVtbl -> removeAttributeNode(This,oldAttr,pVal)

#define ILMathMLElement_hasAttribute(This,name,pVal)	\
    (This)->lpVtbl -> hasAttribute(This,name,pVal)

#define ILMathMLElement_getAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLElement_setAttributeNS(This,namespaceURI,qualifiedName,value)	\
    (This)->lpVtbl -> setAttributeNS(This,namespaceURI,qualifiedName,value)

#define ILMathMLElement_removeAttributeNS(This,namespaceURI,localName)	\
    (This)->lpVtbl -> removeAttributeNS(This,namespaceURI,localName)

#define ILMathMLElement_getAttributeNodeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNodeNS(This,namespaceURI,localName,pVal)

#define ILMathMLElement_setAttributeNodeNS(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNodeNS(This,newAttr,pVal)

#define ILMathMLElement_hasAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> hasAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLElement_getElementsByTagName(This,tagname,pVal)	\
    (This)->lpVtbl -> getElementsByTagName(This,tagname,pVal)

#define ILMathMLElement_getElementsByTagNameNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getElementsByTagNameNS(This,namespaceURI,localName,pVal)

#define ILMathMLElement_get_markupContent(This,pVal)	\
    (This)->lpVtbl -> get_markupContent(This,pVal)

#define ILMathMLElement_put_markupContent(This,newVal)	\
    (This)->lpVtbl -> put_markupContent(This,newVal)

#define ILMathMLElement_addBehavior(This,bstrUrl,pvarFactory,pCookie)	\
    (This)->lpVtbl -> addBehavior(This,bstrUrl,pvarFactory,pCookie)

#define ILMathMLElement_setActive(This)	\
    (This)->lpVtbl -> setActive(This)


#define ILMathMLElement_get_className(This,pVal)	\
    (This)->lpVtbl -> get_className(This,pVal)

#define ILMathMLElement_put_className(This,newVal)	\
    (This)->lpVtbl -> put_className(This,newVal)

#define ILMathMLElement_get_mathElementStyle(This,pVal)	\
    (This)->lpVtbl -> get_mathElementStyle(This,pVal)

#define ILMathMLElement_put_mathElementStyle(This,newVal)	\
    (This)->lpVtbl -> put_mathElementStyle(This,newVal)

#define ILMathMLElement_get__id(This,pVal)	\
    (This)->lpVtbl -> get__id(This,pVal)

#define ILMathMLElement_put__id(This,newVal)	\
    (This)->lpVtbl -> put__id(This,newVal)

#define ILMathMLElement_get_xref(This,pVal)	\
    (This)->lpVtbl -> get_xref(This,pVal)

#define ILMathMLElement_put_xref(This,newVal)	\
    (This)->lpVtbl -> put_xref(This,newVal)

#define ILMathMLElement_get_href(This,pVal)	\
    (This)->lpVtbl -> get_href(This,pVal)

#define ILMathMLElement_put_href(This,newVal)	\
    (This)->lpVtbl -> put_href(This,newVal)

#define ILMathMLElement_get_ownerMathElement(This,pVal)	\
    (This)->lpVtbl -> get_ownerMathElement(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_get_className_Proxy( 
    ILMathMLElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLElement_get_className_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_put_className_Proxy( 
    ILMathMLElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLElement_put_className_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_get_mathElementStyle_Proxy( 
    ILMathMLElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLElement_get_mathElementStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_put_mathElementStyle_Proxy( 
    ILMathMLElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLElement_put_mathElementStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_get__id_Proxy( 
    ILMathMLElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLElement_get__id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_put__id_Proxy( 
    ILMathMLElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLElement_put__id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_get_xref_Proxy( 
    ILMathMLElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLElement_get_xref_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_put_xref_Proxy( 
    ILMathMLElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLElement_put_xref_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_get_href_Proxy( 
    ILMathMLElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLElement_get_href_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_put_href_Proxy( 
    ILMathMLElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLElement_put_href_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLElement_get_ownerMathElement_Proxy( 
    ILMathMLElement * This,
    /* [retval][out] */ ILMathMLMathElement **pVal);


void __RPC_STUB ILMathMLElement_get_ownerMathElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMathMLElement_INTERFACE_DEFINED__ */


#ifndef __ILMathMLContainer_INTERFACE_DEFINED__
#define __ILMathMLContainer_INTERFACE_DEFINED__

/* interface ILMathMLContainer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILMathMLContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7FA1701A-09F8-4125-B900-6E51B5AF7C35")
    ILMathMLContainer : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILMathMLContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILMathMLContainer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILMathMLContainer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILMathMLContainer * This);
        
        END_INTERFACE
    } ILMathMLContainerVtbl;

    interface ILMathMLContainer
    {
        CONST_VTBL struct ILMathMLContainerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMathMLContainer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMathMLContainer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMathMLContainer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILMathMLContainer_INTERFACE_DEFINED__ */


#ifndef __ILMathMLPresentationElement_INTERFACE_DEFINED__
#define __ILMathMLPresentationElement_INTERFACE_DEFINED__

/* interface ILMathMLPresentationElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILMathMLPresentationElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57A48D44-93F2-402d-9B91-2CB174DA15F3")
    ILMathMLPresentationElement : public ILMathMLElement
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILMathMLPresentationElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILMathMLPresentationElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILMathMLPresentationElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILMathMLPresentationElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeType )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ LDOMNodeType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeName )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeValue )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_nodeValue )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_parentNode )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_firstChild )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lastChild )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nextSibling )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_previousSibling )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerDocument )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMDocument **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_attributes )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMNamedNodeMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_childNodes )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *appendChild )( 
            ILMathMLPresentationElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [retval][out] */ ILDOMNode **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *insertBefore )( 
            ILMathMLPresentationElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ VARIANT refChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeChild )( 
            ILMathMLPresentationElement * This,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *replaceChild )( 
            ILMathMLPresentationElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasChildNodes )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasAttributes )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *cloneNode )( 
            ILMathMLPresentationElement * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isSupported )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *normalize )( 
            ILMathMLPresentationElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_namespaceURI )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_namespaceURI )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_prefix )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_prefix )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_localName )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_localName )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_textContent )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_textContent )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupPrefix )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupNamespaceURI )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR prefix,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setUserData )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR key,
            /* [in] */ LDOMUserData data,
            /* [in] */ ILDOMUserDataHandler *handler,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getUserData )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR key,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeChildren )( 
            ILMathMLPresentationElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uniqID )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ GUID *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_uniqID )( 
            ILMathMLPresentationElement * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTextOffset )( 
            ILMathMLPresentationElement * This,
            /* [in] */ long which,
            /* [retval][out] */ long *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setTextOffset )( 
            ILMathMLPresentationElement * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_tagName )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttribute )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttribute )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttribute )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNode )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNode )( 
            ILMathMLPresentationElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNode )( 
            ILMathMLPresentationElement * This,
            /* [in] */ ILDOMAttr *oldAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttribute )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNS )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNS )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNS )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNodeNS )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNodeNS )( 
            ILMathMLPresentationElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttributeNS )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagName )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR tagname,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagNameNS )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_markupContent )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_markupContent )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *addBehavior )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR bstrUrl,
            /* [in] */ VARIANT *pvarFactory,
            /* [retval][out] */ long *pCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setActive )( 
            ILMathMLPresentationElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_className )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_className )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mathElementStyle )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mathElementStyle )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__id )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put__id )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_xref )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_xref )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_href )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_href )( 
            ILMathMLPresentationElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerMathElement )( 
            ILMathMLPresentationElement * This,
            /* [retval][out] */ ILMathMLMathElement **pVal);
        
        END_INTERFACE
    } ILMathMLPresentationElementVtbl;

    interface ILMathMLPresentationElement
    {
        CONST_VTBL struct ILMathMLPresentationElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMathMLPresentationElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMathMLPresentationElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMathMLPresentationElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMathMLPresentationElement_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILMathMLPresentationElement_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILMathMLPresentationElement_get_nodeValue(This,pVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pVal)

#define ILMathMLPresentationElement_put_nodeValue(This,newVal)	\
    (This)->lpVtbl -> put_nodeValue(This,newVal)

#define ILMathMLPresentationElement_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILMathMLPresentationElement_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILMathMLPresentationElement_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILMathMLPresentationElement_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILMathMLPresentationElement_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILMathMLPresentationElement_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILMathMLPresentationElement_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILMathMLPresentationElement_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILMathMLPresentationElement_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILMathMLPresentationElement_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILMathMLPresentationElement_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILMathMLPresentationElement_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILMathMLPresentationElement_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILMathMLPresentationElement_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILMathMLPresentationElement_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILMathMLPresentationElement_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILMathMLPresentationElement_normalize(This)	\
    (This)->lpVtbl -> normalize(This)

#define ILMathMLPresentationElement_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILMathMLPresentationElement_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILMathMLPresentationElement_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILMathMLPresentationElement_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILMathMLPresentationElement_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILMathMLPresentationElement_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILMathMLPresentationElement_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILMathMLPresentationElement_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)

#define ILMathMLPresentationElement_lookupPrefix(This,namespaceURI,pVal)	\
    (This)->lpVtbl -> lookupPrefix(This,namespaceURI,pVal)

#define ILMathMLPresentationElement_lookupNamespaceURI(This,prefix,pVal)	\
    (This)->lpVtbl -> lookupNamespaceURI(This,prefix,pVal)

#define ILMathMLPresentationElement_setUserData(This,key,data,handler,pVal)	\
    (This)->lpVtbl -> setUserData(This,key,data,handler,pVal)

#define ILMathMLPresentationElement_getUserData(This,key,pVal)	\
    (This)->lpVtbl -> getUserData(This,key,pVal)

#define ILMathMLPresentationElement_removeChildren(This)	\
    (This)->lpVtbl -> removeChildren(This)

#define ILMathMLPresentationElement_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILMathMLPresentationElement_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILMathMLPresentationElement_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILMathMLPresentationElement_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)


#define ILMathMLPresentationElement_get_tagName(This,pVal)	\
    (This)->lpVtbl -> get_tagName(This,pVal)

#define ILMathMLPresentationElement_getAttribute(This,name,pVal)	\
    (This)->lpVtbl -> getAttribute(This,name,pVal)

#define ILMathMLPresentationElement_setAttribute(This,name,value)	\
    (This)->lpVtbl -> setAttribute(This,name,value)

#define ILMathMLPresentationElement_removeAttribute(This,name)	\
    (This)->lpVtbl -> removeAttribute(This,name)

#define ILMathMLPresentationElement_getAttributeNode(This,name,pVal)	\
    (This)->lpVtbl -> getAttributeNode(This,name,pVal)

#define ILMathMLPresentationElement_setAttributeNode(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNode(This,newAttr,pVal)

#define ILMathMLPresentationElement_removeAttributeNode(This,oldAttr,pVal)	\
    (This)->lpVtbl -> removeAttributeNode(This,oldAttr,pVal)

#define ILMathMLPresentationElement_hasAttribute(This,name,pVal)	\
    (This)->lpVtbl -> hasAttribute(This,name,pVal)

#define ILMathMLPresentationElement_getAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationElement_setAttributeNS(This,namespaceURI,qualifiedName,value)	\
    (This)->lpVtbl -> setAttributeNS(This,namespaceURI,qualifiedName,value)

#define ILMathMLPresentationElement_removeAttributeNS(This,namespaceURI,localName)	\
    (This)->lpVtbl -> removeAttributeNS(This,namespaceURI,localName)

#define ILMathMLPresentationElement_getAttributeNodeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNodeNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationElement_setAttributeNodeNS(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNodeNS(This,newAttr,pVal)

#define ILMathMLPresentationElement_hasAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> hasAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationElement_getElementsByTagName(This,tagname,pVal)	\
    (This)->lpVtbl -> getElementsByTagName(This,tagname,pVal)

#define ILMathMLPresentationElement_getElementsByTagNameNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getElementsByTagNameNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationElement_get_markupContent(This,pVal)	\
    (This)->lpVtbl -> get_markupContent(This,pVal)

#define ILMathMLPresentationElement_put_markupContent(This,newVal)	\
    (This)->lpVtbl -> put_markupContent(This,newVal)

#define ILMathMLPresentationElement_addBehavior(This,bstrUrl,pvarFactory,pCookie)	\
    (This)->lpVtbl -> addBehavior(This,bstrUrl,pvarFactory,pCookie)

#define ILMathMLPresentationElement_setActive(This)	\
    (This)->lpVtbl -> setActive(This)


#define ILMathMLPresentationElement_get_className(This,pVal)	\
    (This)->lpVtbl -> get_className(This,pVal)

#define ILMathMLPresentationElement_put_className(This,newVal)	\
    (This)->lpVtbl -> put_className(This,newVal)

#define ILMathMLPresentationElement_get_mathElementStyle(This,pVal)	\
    (This)->lpVtbl -> get_mathElementStyle(This,pVal)

#define ILMathMLPresentationElement_put_mathElementStyle(This,newVal)	\
    (This)->lpVtbl -> put_mathElementStyle(This,newVal)

#define ILMathMLPresentationElement_get__id(This,pVal)	\
    (This)->lpVtbl -> get__id(This,pVal)

#define ILMathMLPresentationElement_put__id(This,newVal)	\
    (This)->lpVtbl -> put__id(This,newVal)

#define ILMathMLPresentationElement_get_xref(This,pVal)	\
    (This)->lpVtbl -> get_xref(This,pVal)

#define ILMathMLPresentationElement_put_xref(This,newVal)	\
    (This)->lpVtbl -> put_xref(This,newVal)

#define ILMathMLPresentationElement_get_href(This,pVal)	\
    (This)->lpVtbl -> get_href(This,pVal)

#define ILMathMLPresentationElement_put_href(This,newVal)	\
    (This)->lpVtbl -> put_href(This,newVal)

#define ILMathMLPresentationElement_get_ownerMathElement(This,pVal)	\
    (This)->lpVtbl -> get_ownerMathElement(This,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILMathMLPresentationElement_INTERFACE_DEFINED__ */


#ifndef __ILMathMLPresentationContainer_INTERFACE_DEFINED__
#define __ILMathMLPresentationContainer_INTERFACE_DEFINED__

/* interface ILMathMLPresentationContainer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILMathMLPresentationContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5C9D0D22-CD53-4f77-9B30-F39EBB2FAFDB")
    ILMathMLPresentationContainer : public ILMathMLPresentationElement
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILMathMLPresentationContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILMathMLPresentationContainer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILMathMLPresentationContainer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeType )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ LDOMNodeType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeName )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeValue )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_nodeValue )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_parentNode )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_firstChild )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lastChild )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nextSibling )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_previousSibling )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerDocument )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMDocument **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_attributes )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMNamedNodeMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_childNodes )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *appendChild )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ ILDOMNode *newChild,
            /* [retval][out] */ ILDOMNode **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *insertBefore )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ VARIANT refChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeChild )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *replaceChild )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasChildNodes )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasAttributes )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *cloneNode )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isSupported )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *normalize )( 
            ILMathMLPresentationContainer * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_namespaceURI )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_namespaceURI )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_prefix )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_prefix )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_localName )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_localName )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_textContent )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_textContent )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupPrefix )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR namespaceURI,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupNamespaceURI )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR prefix,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setUserData )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR key,
            /* [in] */ LDOMUserData data,
            /* [in] */ ILDOMUserDataHandler *handler,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getUserData )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR key,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeChildren )( 
            ILMathMLPresentationContainer * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uniqID )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ GUID *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_uniqID )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTextOffset )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ long which,
            /* [retval][out] */ long *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setTextOffset )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_tagName )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttribute )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttribute )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttribute )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNode )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNode )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNode )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ ILDOMAttr *oldAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttribute )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNS )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNS )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNS )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNodeNS )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNodeNS )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttributeNS )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagName )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR tagname,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagNameNS )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_markupContent )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_markupContent )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *addBehavior )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR bstrUrl,
            /* [in] */ VARIANT *pvarFactory,
            /* [retval][out] */ long *pCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setActive )( 
            ILMathMLPresentationContainer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_className )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_className )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mathElementStyle )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mathElementStyle )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__id )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put__id )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_xref )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_xref )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_href )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_href )( 
            ILMathMLPresentationContainer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerMathElement )( 
            ILMathMLPresentationContainer * This,
            /* [retval][out] */ ILMathMLMathElement **pVal);
        
        END_INTERFACE
    } ILMathMLPresentationContainerVtbl;

    interface ILMathMLPresentationContainer
    {
        CONST_VTBL struct ILMathMLPresentationContainerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMathMLPresentationContainer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMathMLPresentationContainer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMathMLPresentationContainer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMathMLPresentationContainer_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILMathMLPresentationContainer_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILMathMLPresentationContainer_get_nodeValue(This,pVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pVal)

#define ILMathMLPresentationContainer_put_nodeValue(This,newVal)	\
    (This)->lpVtbl -> put_nodeValue(This,newVal)

#define ILMathMLPresentationContainer_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILMathMLPresentationContainer_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILMathMLPresentationContainer_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILMathMLPresentationContainer_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILMathMLPresentationContainer_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILMathMLPresentationContainer_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILMathMLPresentationContainer_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILMathMLPresentationContainer_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILMathMLPresentationContainer_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILMathMLPresentationContainer_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILMathMLPresentationContainer_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILMathMLPresentationContainer_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILMathMLPresentationContainer_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILMathMLPresentationContainer_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILMathMLPresentationContainer_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILMathMLPresentationContainer_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILMathMLPresentationContainer_normalize(This)	\
    (This)->lpVtbl -> normalize(This)

#define ILMathMLPresentationContainer_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILMathMLPresentationContainer_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILMathMLPresentationContainer_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILMathMLPresentationContainer_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILMathMLPresentationContainer_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILMathMLPresentationContainer_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILMathMLPresentationContainer_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILMathMLPresentationContainer_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)

#define ILMathMLPresentationContainer_lookupPrefix(This,namespaceURI,pVal)	\
    (This)->lpVtbl -> lookupPrefix(This,namespaceURI,pVal)

#define ILMathMLPresentationContainer_lookupNamespaceURI(This,prefix,pVal)	\
    (This)->lpVtbl -> lookupNamespaceURI(This,prefix,pVal)

#define ILMathMLPresentationContainer_setUserData(This,key,data,handler,pVal)	\
    (This)->lpVtbl -> setUserData(This,key,data,handler,pVal)

#define ILMathMLPresentationContainer_getUserData(This,key,pVal)	\
    (This)->lpVtbl -> getUserData(This,key,pVal)

#define ILMathMLPresentationContainer_removeChildren(This)	\
    (This)->lpVtbl -> removeChildren(This)

#define ILMathMLPresentationContainer_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILMathMLPresentationContainer_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILMathMLPresentationContainer_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILMathMLPresentationContainer_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)


#define ILMathMLPresentationContainer_get_tagName(This,pVal)	\
    (This)->lpVtbl -> get_tagName(This,pVal)

#define ILMathMLPresentationContainer_getAttribute(This,name,pVal)	\
    (This)->lpVtbl -> getAttribute(This,name,pVal)

#define ILMathMLPresentationContainer_setAttribute(This,name,value)	\
    (This)->lpVtbl -> setAttribute(This,name,value)

#define ILMathMLPresentationContainer_removeAttribute(This,name)	\
    (This)->lpVtbl -> removeAttribute(This,name)

#define ILMathMLPresentationContainer_getAttributeNode(This,name,pVal)	\
    (This)->lpVtbl -> getAttributeNode(This,name,pVal)

#define ILMathMLPresentationContainer_setAttributeNode(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNode(This,newAttr,pVal)

#define ILMathMLPresentationContainer_removeAttributeNode(This,oldAttr,pVal)	\
    (This)->lpVtbl -> removeAttributeNode(This,oldAttr,pVal)

#define ILMathMLPresentationContainer_hasAttribute(This,name,pVal)	\
    (This)->lpVtbl -> hasAttribute(This,name,pVal)

#define ILMathMLPresentationContainer_getAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationContainer_setAttributeNS(This,namespaceURI,qualifiedName,value)	\
    (This)->lpVtbl -> setAttributeNS(This,namespaceURI,qualifiedName,value)

#define ILMathMLPresentationContainer_removeAttributeNS(This,namespaceURI,localName)	\
    (This)->lpVtbl -> removeAttributeNS(This,namespaceURI,localName)

#define ILMathMLPresentationContainer_getAttributeNodeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNodeNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationContainer_setAttributeNodeNS(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNodeNS(This,newAttr,pVal)

#define ILMathMLPresentationContainer_hasAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> hasAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationContainer_getElementsByTagName(This,tagname,pVal)	\
    (This)->lpVtbl -> getElementsByTagName(This,tagname,pVal)

#define ILMathMLPresentationContainer_getElementsByTagNameNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getElementsByTagNameNS(This,namespaceURI,localName,pVal)

#define ILMathMLPresentationContainer_get_markupContent(This,pVal)	\
    (This)->lpVtbl -> get_markupContent(This,pVal)

#define ILMathMLPresentationContainer_put_markupContent(This,newVal)	\
    (This)->lpVtbl -> put_markupContent(This,newVal)

#define ILMathMLPresentationContainer_addBehavior(This,bstrUrl,pvarFactory,pCookie)	\
    (This)->lpVtbl -> addBehavior(This,bstrUrl,pvarFactory,pCookie)

#define ILMathMLPresentationContainer_setActive(This)	\
    (This)->lpVtbl -> setActive(This)


#define ILMathMLPresentationContainer_get_className(This,pVal)	\
    (This)->lpVtbl -> get_className(This,pVal)

#define ILMathMLPresentationContainer_put_className(This,newVal)	\
    (This)->lpVtbl -> put_className(This,newVal)

#define ILMathMLPresentationContainer_get_mathElementStyle(This,pVal)	\
    (This)->lpVtbl -> get_mathElementStyle(This,pVal)

#define ILMathMLPresentationContainer_put_mathElementStyle(This,newVal)	\
    (This)->lpVtbl -> put_mathElementStyle(This,newVal)

#define ILMathMLPresentationContainer_get__id(This,pVal)	\
    (This)->lpVtbl -> get__id(This,pVal)

#define ILMathMLPresentationContainer_put__id(This,newVal)	\
    (This)->lpVtbl -> put__id(This,newVal)

#define ILMathMLPresentationContainer_get_xref(This,pVal)	\
    (This)->lpVtbl -> get_xref(This,pVal)

#define ILMathMLPresentationContainer_put_xref(This,newVal)	\
    (This)->lpVtbl -> put_xref(This,newVal)

#define ILMathMLPresentationContainer_get_href(This,pVal)	\
    (This)->lpVtbl -> get_href(This,pVal)

#define ILMathMLPresentationContainer_put_href(This,newVal)	\
    (This)->lpVtbl -> put_href(This,newVal)

#define ILMathMLPresentationContainer_get_ownerMathElement(This,pVal)	\
    (This)->lpVtbl -> get_ownerMathElement(This,pVal)



#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILMathMLPresentationContainer_INTERFACE_DEFINED__ */


#ifndef __ILMathMLMathElement_INTERFACE_DEFINED__
#define __ILMathMLMathElement_INTERFACE_DEFINED__

/* interface ILMathMLMathElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILMathMLMathElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("272291ED-532D-4f7a-B0F0-BFFC3682E1B9")
    ILMathMLMathElement : public ILMathMLElement
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_macros( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_macros( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_display( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_display( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMathMLMathElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILMathMLMathElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILMathMLMathElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILMathMLMathElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeType )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ LDOMNodeType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeName )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeValue )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_nodeValue )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_parentNode )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_firstChild )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lastChild )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nextSibling )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_previousSibling )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerDocument )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMDocument **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_attributes )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMNamedNodeMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_childNodes )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *appendChild )( 
            ILMathMLMathElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [retval][out] */ ILDOMNode **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *insertBefore )( 
            ILMathMLMathElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ VARIANT refChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeChild )( 
            ILMathMLMathElement * This,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *replaceChild )( 
            ILMathMLMathElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasChildNodes )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasAttributes )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *cloneNode )( 
            ILMathMLMathElement * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isSupported )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *normalize )( 
            ILMathMLMathElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_namespaceURI )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_namespaceURI )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_prefix )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_prefix )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_localName )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_localName )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_textContent )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_textContent )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupPrefix )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupNamespaceURI )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR prefix,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setUserData )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR key,
            /* [in] */ LDOMUserData data,
            /* [in] */ ILDOMUserDataHandler *handler,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getUserData )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR key,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeChildren )( 
            ILMathMLMathElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uniqID )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ GUID *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_uniqID )( 
            ILMathMLMathElement * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTextOffset )( 
            ILMathMLMathElement * This,
            /* [in] */ long which,
            /* [retval][out] */ long *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setTextOffset )( 
            ILMathMLMathElement * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_tagName )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttribute )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttribute )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttribute )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNode )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNode )( 
            ILMathMLMathElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNode )( 
            ILMathMLMathElement * This,
            /* [in] */ ILDOMAttr *oldAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttribute )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNS )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNS )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNS )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNodeNS )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNodeNS )( 
            ILMathMLMathElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttributeNS )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagName )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR tagname,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagNameNS )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_markupContent )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_markupContent )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *addBehavior )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR bstrUrl,
            /* [in] */ VARIANT *pvarFactory,
            /* [retval][out] */ long *pCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setActive )( 
            ILMathMLMathElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_className )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_className )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mathElementStyle )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mathElementStyle )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__id )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put__id )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_xref )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_xref )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_href )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_href )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerMathElement )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ ILMathMLMathElement **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_macros )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_macros )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_display )( 
            ILMathMLMathElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_display )( 
            ILMathMLMathElement * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ILMathMLMathElementVtbl;

    interface ILMathMLMathElement
    {
        CONST_VTBL struct ILMathMLMathElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMathMLMathElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMathMLMathElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMathMLMathElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMathMLMathElement_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILMathMLMathElement_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILMathMLMathElement_get_nodeValue(This,pVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pVal)

#define ILMathMLMathElement_put_nodeValue(This,newVal)	\
    (This)->lpVtbl -> put_nodeValue(This,newVal)

#define ILMathMLMathElement_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILMathMLMathElement_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILMathMLMathElement_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILMathMLMathElement_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILMathMLMathElement_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILMathMLMathElement_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILMathMLMathElement_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILMathMLMathElement_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILMathMLMathElement_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILMathMLMathElement_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILMathMLMathElement_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILMathMLMathElement_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILMathMLMathElement_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILMathMLMathElement_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILMathMLMathElement_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILMathMLMathElement_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILMathMLMathElement_normalize(This)	\
    (This)->lpVtbl -> normalize(This)

#define ILMathMLMathElement_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILMathMLMathElement_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILMathMLMathElement_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILMathMLMathElement_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILMathMLMathElement_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILMathMLMathElement_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILMathMLMathElement_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILMathMLMathElement_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)

#define ILMathMLMathElement_lookupPrefix(This,namespaceURI,pVal)	\
    (This)->lpVtbl -> lookupPrefix(This,namespaceURI,pVal)

#define ILMathMLMathElement_lookupNamespaceURI(This,prefix,pVal)	\
    (This)->lpVtbl -> lookupNamespaceURI(This,prefix,pVal)

#define ILMathMLMathElement_setUserData(This,key,data,handler,pVal)	\
    (This)->lpVtbl -> setUserData(This,key,data,handler,pVal)

#define ILMathMLMathElement_getUserData(This,key,pVal)	\
    (This)->lpVtbl -> getUserData(This,key,pVal)

#define ILMathMLMathElement_removeChildren(This)	\
    (This)->lpVtbl -> removeChildren(This)

#define ILMathMLMathElement_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILMathMLMathElement_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILMathMLMathElement_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILMathMLMathElement_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)


#define ILMathMLMathElement_get_tagName(This,pVal)	\
    (This)->lpVtbl -> get_tagName(This,pVal)

#define ILMathMLMathElement_getAttribute(This,name,pVal)	\
    (This)->lpVtbl -> getAttribute(This,name,pVal)

#define ILMathMLMathElement_setAttribute(This,name,value)	\
    (This)->lpVtbl -> setAttribute(This,name,value)

#define ILMathMLMathElement_removeAttribute(This,name)	\
    (This)->lpVtbl -> removeAttribute(This,name)

#define ILMathMLMathElement_getAttributeNode(This,name,pVal)	\
    (This)->lpVtbl -> getAttributeNode(This,name,pVal)

#define ILMathMLMathElement_setAttributeNode(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNode(This,newAttr,pVal)

#define ILMathMLMathElement_removeAttributeNode(This,oldAttr,pVal)	\
    (This)->lpVtbl -> removeAttributeNode(This,oldAttr,pVal)

#define ILMathMLMathElement_hasAttribute(This,name,pVal)	\
    (This)->lpVtbl -> hasAttribute(This,name,pVal)

#define ILMathMLMathElement_getAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLMathElement_setAttributeNS(This,namespaceURI,qualifiedName,value)	\
    (This)->lpVtbl -> setAttributeNS(This,namespaceURI,qualifiedName,value)

#define ILMathMLMathElement_removeAttributeNS(This,namespaceURI,localName)	\
    (This)->lpVtbl -> removeAttributeNS(This,namespaceURI,localName)

#define ILMathMLMathElement_getAttributeNodeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNodeNS(This,namespaceURI,localName,pVal)

#define ILMathMLMathElement_setAttributeNodeNS(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNodeNS(This,newAttr,pVal)

#define ILMathMLMathElement_hasAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> hasAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLMathElement_getElementsByTagName(This,tagname,pVal)	\
    (This)->lpVtbl -> getElementsByTagName(This,tagname,pVal)

#define ILMathMLMathElement_getElementsByTagNameNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getElementsByTagNameNS(This,namespaceURI,localName,pVal)

#define ILMathMLMathElement_get_markupContent(This,pVal)	\
    (This)->lpVtbl -> get_markupContent(This,pVal)

#define ILMathMLMathElement_put_markupContent(This,newVal)	\
    (This)->lpVtbl -> put_markupContent(This,newVal)

#define ILMathMLMathElement_addBehavior(This,bstrUrl,pvarFactory,pCookie)	\
    (This)->lpVtbl -> addBehavior(This,bstrUrl,pvarFactory,pCookie)

#define ILMathMLMathElement_setActive(This)	\
    (This)->lpVtbl -> setActive(This)


#define ILMathMLMathElement_get_className(This,pVal)	\
    (This)->lpVtbl -> get_className(This,pVal)

#define ILMathMLMathElement_put_className(This,newVal)	\
    (This)->lpVtbl -> put_className(This,newVal)

#define ILMathMLMathElement_get_mathElementStyle(This,pVal)	\
    (This)->lpVtbl -> get_mathElementStyle(This,pVal)

#define ILMathMLMathElement_put_mathElementStyle(This,newVal)	\
    (This)->lpVtbl -> put_mathElementStyle(This,newVal)

#define ILMathMLMathElement_get__id(This,pVal)	\
    (This)->lpVtbl -> get__id(This,pVal)

#define ILMathMLMathElement_put__id(This,newVal)	\
    (This)->lpVtbl -> put__id(This,newVal)

#define ILMathMLMathElement_get_xref(This,pVal)	\
    (This)->lpVtbl -> get_xref(This,pVal)

#define ILMathMLMathElement_put_xref(This,newVal)	\
    (This)->lpVtbl -> put_xref(This,newVal)

#define ILMathMLMathElement_get_href(This,pVal)	\
    (This)->lpVtbl -> get_href(This,pVal)

#define ILMathMLMathElement_put_href(This,newVal)	\
    (This)->lpVtbl -> put_href(This,newVal)

#define ILMathMLMathElement_get_ownerMathElement(This,pVal)	\
    (This)->lpVtbl -> get_ownerMathElement(This,pVal)


#define ILMathMLMathElement_get_macros(This,pVal)	\
    (This)->lpVtbl -> get_macros(This,pVal)

#define ILMathMLMathElement_put_macros(This,newVal)	\
    (This)->lpVtbl -> put_macros(This,newVal)

#define ILMathMLMathElement_get_display(This,pVal)	\
    (This)->lpVtbl -> get_display(This,pVal)

#define ILMathMLMathElement_put_display(This,newVal)	\
    (This)->lpVtbl -> put_display(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLMathElement_get_macros_Proxy( 
    ILMathMLMathElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLMathElement_get_macros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLMathElement_put_macros_Proxy( 
    ILMathMLMathElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLMathElement_put_macros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLMathElement_get_display_Proxy( 
    ILMathMLMathElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLMathElement_get_display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLMathElement_put_display_Proxy( 
    ILMathMLMathElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLMathElement_put_display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMathMLMathElement_INTERFACE_DEFINED__ */


#ifndef __ILMathMLFencedElement_INTERFACE_DEFINED__
#define __ILMathMLFencedElement_INTERFACE_DEFINED__

/* interface ILMathMLFencedElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILMathMLFencedElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6AB965E-62A8-4c12-9EE2-81035F5DB857")
    ILMathMLFencedElement : public ILMathMLPresentationContainer
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_open( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_open( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_close( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_close( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_separators( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_separators( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMathMLFencedElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILMathMLFencedElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILMathMLFencedElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILMathMLFencedElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeType )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ LDOMNodeType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeName )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nodeValue )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_nodeValue )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_parentNode )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_firstChild )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lastChild )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nextSibling )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_previousSibling )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMNode **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerDocument )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMDocument **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_attributes )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMNamedNodeMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_childNodes )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *appendChild )( 
            ILMathMLFencedElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [retval][out] */ ILDOMNode **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *insertBefore )( 
            ILMathMLFencedElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ VARIANT refChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeChild )( 
            ILMathMLFencedElement * This,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *replaceChild )( 
            ILMathMLFencedElement * This,
            /* [in] */ ILDOMNode *newChild,
            /* [in] */ ILDOMNode *oldChild,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasChildNodes )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hasAttributes )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *cloneNode )( 
            ILMathMLFencedElement * This,
            /* [in] */ VARIANT_BOOL deep,
            /* [retval][out] */ ILDOMNode **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isSupported )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR feature,
            /* [in] */ BSTR version,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *normalize )( 
            ILMathMLFencedElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_namespaceURI )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_namespaceURI )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_prefix )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_prefix )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_localName )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_localName )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_textContent )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_textContent )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupPrefix )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *lookupNamespaceURI )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR prefix,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setUserData )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR key,
            /* [in] */ LDOMUserData data,
            /* [in] */ ILDOMUserDataHandler *handler,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getUserData )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR key,
            /* [retval][out] */ LDOMUserData *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeChildren )( 
            ILMathMLFencedElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uniqID )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ GUID *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_uniqID )( 
            ILMathMLFencedElement * This,
            /* [in] */ GUID newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTextOffset )( 
            ILMathMLFencedElement * This,
            /* [in] */ long which,
            /* [retval][out] */ long *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setTextOffset )( 
            ILMathMLFencedElement * This,
            /* [in] */ long which,
            /* [in] */ long offset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_tagName )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttribute )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttribute )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttribute )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNode )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNode )( 
            ILMathMLFencedElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNode )( 
            ILMathMLFencedElement * This,
            /* [in] */ ILDOMAttr *oldAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttribute )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNS )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNS )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR qualifiedName,
            /* [in] */ BSTR value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *removeAttributeNS )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getAttributeNodeNS )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setAttributeNodeNS )( 
            ILMathMLFencedElement * This,
            /* [in] */ ILDOMAttr *newAttr,
            /* [retval][out] */ ILDOMAttr **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hasAttributeNS )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagName )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR tagname,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *getElementsByTagNameNS )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR namespaceURI,
            /* [in] */ BSTR localName,
            /* [retval][out] */ ILDOMNodeList **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_markupContent )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_markupContent )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *addBehavior )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR bstrUrl,
            /* [in] */ VARIANT *pvarFactory,
            /* [retval][out] */ long *pCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *setActive )( 
            ILMathMLFencedElement * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_className )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_className )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mathElementStyle )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mathElementStyle )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__id )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put__id )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_xref )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_xref )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_href )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_href )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ownerMathElement )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ ILMathMLMathElement **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_open )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_open )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_close )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_close )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_separators )( 
            ILMathMLFencedElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_separators )( 
            ILMathMLFencedElement * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ILMathMLFencedElementVtbl;

    interface ILMathMLFencedElement
    {
        CONST_VTBL struct ILMathMLFencedElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMathMLFencedElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMathMLFencedElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMathMLFencedElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMathMLFencedElement_get_nodeType(This,pVal)	\
    (This)->lpVtbl -> get_nodeType(This,pVal)

#define ILMathMLFencedElement_get_nodeName(This,pVal)	\
    (This)->lpVtbl -> get_nodeName(This,pVal)

#define ILMathMLFencedElement_get_nodeValue(This,pVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pVal)

#define ILMathMLFencedElement_put_nodeValue(This,newVal)	\
    (This)->lpVtbl -> put_nodeValue(This,newVal)

#define ILMathMLFencedElement_get_parentNode(This,pVal)	\
    (This)->lpVtbl -> get_parentNode(This,pVal)

#define ILMathMLFencedElement_get_firstChild(This,pVal)	\
    (This)->lpVtbl -> get_firstChild(This,pVal)

#define ILMathMLFencedElement_get_lastChild(This,pVal)	\
    (This)->lpVtbl -> get_lastChild(This,pVal)

#define ILMathMLFencedElement_get_nextSibling(This,pVal)	\
    (This)->lpVtbl -> get_nextSibling(This,pVal)

#define ILMathMLFencedElement_get_previousSibling(This,pVal)	\
    (This)->lpVtbl -> get_previousSibling(This,pVal)

#define ILMathMLFencedElement_get_ownerDocument(This,pVal)	\
    (This)->lpVtbl -> get_ownerDocument(This,pVal)

#define ILMathMLFencedElement_get_attributes(This,pVal)	\
    (This)->lpVtbl -> get_attributes(This,pVal)

#define ILMathMLFencedElement_get_childNodes(This,pVal)	\
    (This)->lpVtbl -> get_childNodes(This,pVal)

#define ILMathMLFencedElement_appendChild(This,newChild,result)	\
    (This)->lpVtbl -> appendChild(This,newChild,result)

#define ILMathMLFencedElement_insertBefore(This,newChild,refChild,ppResult)	\
    (This)->lpVtbl -> insertBefore(This,newChild,refChild,ppResult)

#define ILMathMLFencedElement_removeChild(This,oldChild,ppResult)	\
    (This)->lpVtbl -> removeChild(This,oldChild,ppResult)

#define ILMathMLFencedElement_replaceChild(This,newChild,oldChild,ppResult)	\
    (This)->lpVtbl -> replaceChild(This,newChild,oldChild,ppResult)

#define ILMathMLFencedElement_hasChildNodes(This,pVal)	\
    (This)->lpVtbl -> hasChildNodes(This,pVal)

#define ILMathMLFencedElement_hasAttributes(This,pVal)	\
    (This)->lpVtbl -> hasAttributes(This,pVal)

#define ILMathMLFencedElement_cloneNode(This,deep,ppResult)	\
    (This)->lpVtbl -> cloneNode(This,deep,ppResult)

#define ILMathMLFencedElement_isSupported(This,feature,version,pVal)	\
    (This)->lpVtbl -> isSupported(This,feature,version,pVal)

#define ILMathMLFencedElement_normalize(This)	\
    (This)->lpVtbl -> normalize(This)

#define ILMathMLFencedElement_get_namespaceURI(This,pVal)	\
    (This)->lpVtbl -> get_namespaceURI(This,pVal)

#define ILMathMLFencedElement_put_namespaceURI(This,newVal)	\
    (This)->lpVtbl -> put_namespaceURI(This,newVal)

#define ILMathMLFencedElement_get_prefix(This,pVal)	\
    (This)->lpVtbl -> get_prefix(This,pVal)

#define ILMathMLFencedElement_put_prefix(This,newVal)	\
    (This)->lpVtbl -> put_prefix(This,newVal)

#define ILMathMLFencedElement_get_localName(This,pVal)	\
    (This)->lpVtbl -> get_localName(This,pVal)

#define ILMathMLFencedElement_put_localName(This,newVal)	\
    (This)->lpVtbl -> put_localName(This,newVal)

#define ILMathMLFencedElement_get_textContent(This,pVal)	\
    (This)->lpVtbl -> get_textContent(This,pVal)

#define ILMathMLFencedElement_put_textContent(This,newVal)	\
    (This)->lpVtbl -> put_textContent(This,newVal)

#define ILMathMLFencedElement_lookupPrefix(This,namespaceURI,pVal)	\
    (This)->lpVtbl -> lookupPrefix(This,namespaceURI,pVal)

#define ILMathMLFencedElement_lookupNamespaceURI(This,prefix,pVal)	\
    (This)->lpVtbl -> lookupNamespaceURI(This,prefix,pVal)

#define ILMathMLFencedElement_setUserData(This,key,data,handler,pVal)	\
    (This)->lpVtbl -> setUserData(This,key,data,handler,pVal)

#define ILMathMLFencedElement_getUserData(This,key,pVal)	\
    (This)->lpVtbl -> getUserData(This,key,pVal)

#define ILMathMLFencedElement_removeChildren(This)	\
    (This)->lpVtbl -> removeChildren(This)

#define ILMathMLFencedElement_get_uniqID(This,pVal)	\
    (This)->lpVtbl -> get_uniqID(This,pVal)

#define ILMathMLFencedElement_put_uniqID(This,newVal)	\
    (This)->lpVtbl -> put_uniqID(This,newVal)

#define ILMathMLFencedElement_getTextOffset(This,which,offset)	\
    (This)->lpVtbl -> getTextOffset(This,which,offset)

#define ILMathMLFencedElement_setTextOffset(This,which,offset)	\
    (This)->lpVtbl -> setTextOffset(This,which,offset)


#define ILMathMLFencedElement_get_tagName(This,pVal)	\
    (This)->lpVtbl -> get_tagName(This,pVal)

#define ILMathMLFencedElement_getAttribute(This,name,pVal)	\
    (This)->lpVtbl -> getAttribute(This,name,pVal)

#define ILMathMLFencedElement_setAttribute(This,name,value)	\
    (This)->lpVtbl -> setAttribute(This,name,value)

#define ILMathMLFencedElement_removeAttribute(This,name)	\
    (This)->lpVtbl -> removeAttribute(This,name)

#define ILMathMLFencedElement_getAttributeNode(This,name,pVal)	\
    (This)->lpVtbl -> getAttributeNode(This,name,pVal)

#define ILMathMLFencedElement_setAttributeNode(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNode(This,newAttr,pVal)

#define ILMathMLFencedElement_removeAttributeNode(This,oldAttr,pVal)	\
    (This)->lpVtbl -> removeAttributeNode(This,oldAttr,pVal)

#define ILMathMLFencedElement_hasAttribute(This,name,pVal)	\
    (This)->lpVtbl -> hasAttribute(This,name,pVal)

#define ILMathMLFencedElement_getAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLFencedElement_setAttributeNS(This,namespaceURI,qualifiedName,value)	\
    (This)->lpVtbl -> setAttributeNS(This,namespaceURI,qualifiedName,value)

#define ILMathMLFencedElement_removeAttributeNS(This,namespaceURI,localName)	\
    (This)->lpVtbl -> removeAttributeNS(This,namespaceURI,localName)

#define ILMathMLFencedElement_getAttributeNodeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getAttributeNodeNS(This,namespaceURI,localName,pVal)

#define ILMathMLFencedElement_setAttributeNodeNS(This,newAttr,pVal)	\
    (This)->lpVtbl -> setAttributeNodeNS(This,newAttr,pVal)

#define ILMathMLFencedElement_hasAttributeNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> hasAttributeNS(This,namespaceURI,localName,pVal)

#define ILMathMLFencedElement_getElementsByTagName(This,tagname,pVal)	\
    (This)->lpVtbl -> getElementsByTagName(This,tagname,pVal)

#define ILMathMLFencedElement_getElementsByTagNameNS(This,namespaceURI,localName,pVal)	\
    (This)->lpVtbl -> getElementsByTagNameNS(This,namespaceURI,localName,pVal)

#define ILMathMLFencedElement_get_markupContent(This,pVal)	\
    (This)->lpVtbl -> get_markupContent(This,pVal)

#define ILMathMLFencedElement_put_markupContent(This,newVal)	\
    (This)->lpVtbl -> put_markupContent(This,newVal)

#define ILMathMLFencedElement_addBehavior(This,bstrUrl,pvarFactory,pCookie)	\
    (This)->lpVtbl -> addBehavior(This,bstrUrl,pvarFactory,pCookie)

#define ILMathMLFencedElement_setActive(This)	\
    (This)->lpVtbl -> setActive(This)


#define ILMathMLFencedElement_get_className(This,pVal)	\
    (This)->lpVtbl -> get_className(This,pVal)

#define ILMathMLFencedElement_put_className(This,newVal)	\
    (This)->lpVtbl -> put_className(This,newVal)

#define ILMathMLFencedElement_get_mathElementStyle(This,pVal)	\
    (This)->lpVtbl -> get_mathElementStyle(This,pVal)

#define ILMathMLFencedElement_put_mathElementStyle(This,newVal)	\
    (This)->lpVtbl -> put_mathElementStyle(This,newVal)

#define ILMathMLFencedElement_get__id(This,pVal)	\
    (This)->lpVtbl -> get__id(This,pVal)

#define ILMathMLFencedElement_put__id(This,newVal)	\
    (This)->lpVtbl -> put__id(This,newVal)

#define ILMathMLFencedElement_get_xref(This,pVal)	\
    (This)->lpVtbl -> get_xref(This,pVal)

#define ILMathMLFencedElement_put_xref(This,newVal)	\
    (This)->lpVtbl -> put_xref(This,newVal)

#define ILMathMLFencedElement_get_href(This,pVal)	\
    (This)->lpVtbl -> get_href(This,pVal)

#define ILMathMLFencedElement_put_href(This,newVal)	\
    (This)->lpVtbl -> put_href(This,newVal)

#define ILMathMLFencedElement_get_ownerMathElement(This,pVal)	\
    (This)->lpVtbl -> get_ownerMathElement(This,pVal)




#define ILMathMLFencedElement_get_open(This,pVal)	\
    (This)->lpVtbl -> get_open(This,pVal)

#define ILMathMLFencedElement_put_open(This,newVal)	\
    (This)->lpVtbl -> put_open(This,newVal)

#define ILMathMLFencedElement_get_close(This,pVal)	\
    (This)->lpVtbl -> get_close(This,pVal)

#define ILMathMLFencedElement_put_close(This,newVal)	\
    (This)->lpVtbl -> put_close(This,newVal)

#define ILMathMLFencedElement_get_separators(This,pVal)	\
    (This)->lpVtbl -> get_separators(This,pVal)

#define ILMathMLFencedElement_put_separators(This,newVal)	\
    (This)->lpVtbl -> put_separators(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLFencedElement_get_open_Proxy( 
    ILMathMLFencedElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLFencedElement_get_open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLFencedElement_put_open_Proxy( 
    ILMathMLFencedElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLFencedElement_put_open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLFencedElement_get_close_Proxy( 
    ILMathMLFencedElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLFencedElement_get_close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLFencedElement_put_close_Proxy( 
    ILMathMLFencedElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLFencedElement_put_close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILMathMLFencedElement_get_separators_Proxy( 
    ILMathMLFencedElement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ILMathMLFencedElement_get_separators_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILMathMLFencedElement_put_separators_Proxy( 
    ILMathMLFencedElement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILMathMLFencedElement_put_separators_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMathMLFencedElement_INTERFACE_DEFINED__ */



#ifndef __LMATHMLLib_LIBRARY_DEFINED__
#define __LMATHMLLib_LIBRARY_DEFINED__

/* library LMATHMLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LMATHMLLib;

EXTERN_C const CLSID CLSID_LMathMLImplementation;

#ifdef __cplusplus

class DECLSPEC_UUID("E3AE652E-1E81-4299-8D29-E83290433C49")
LMathMLImplementation;
#endif
#endif /* __LMATHMLLib_LIBRARY_DEFINED__ */

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


