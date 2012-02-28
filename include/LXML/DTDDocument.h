#ifndef __DTDDOCUMENT_H
#define __DTDDOCUMENT_H

//#include "resource.h"       // main symbols

#include "LDTDNodeImpl.h"

namespace System
{
namespace Web
{

class CLDTDElement;
class CLDOMEntity;
class CDTDParser;
class CCPChoiceSeq;

class WEBEXT CEntity : public CDTDObjectImpl
//	public EventTarget
{
public:
	CTOR CEntity()
	{
		m_pDTDDocument = NULL;

		m_domEntity = NULL;
	}

	CDTDParser* m_pDTDDocument;

	CLDOMEntity* m_domEntity;

	int m_c;	// '%' for parameter entity
	String m_name;

	String m_value;
	String m_system;
	String m_public;

public:
	String get_value() const;
	void set_value(StringIn newVal);
	String get_name() const;
	void set_name(StringIn newVal);
	//STDMETHOD(get_nodeType)(/*[out, retval]*/ LDOMNodeType *pVal);
#if 0
	STDMETHOD(get_entity)(/*[out, retval]*/ CLDOMEntity* *pVal);
#endif
	/*
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_domEntity;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	*/
};

class WEBEXT CNotation : public CDTDObjectImpl
//	public EventTarget
{
public:
	CTOR CNotation()
	{
		m_pDTDDocument = NULL;
	}

	NodeType get_nodeType();

	CDTDParser* m_pDTDDocument;
};

class WEBEXT CAttribute
{
public:
	String m_name;
	vector<String> m_enums;
//	CArray<_bstr_t, _bstr_t> m_enums;

	ASValueConstraint m_defaultType;
	String m_value;
};

class WEBEXT CAttlist : public CDTDObjectImpl
//	public EventTarget
{
public:
	CTOR CAttlist()
	{
		m_pDTDDocument = NULL;
	}

	~CAttlist()
	{
		for (unsigned int i = 0; i < m_attributes.GetSize(); i++)
		{
			delete m_attributes[i];
		}
	}

	String get_name() const;
	void set_name(StringIn newVal);
	//STDMETHOD(get_nodeType)(/*[out, retval]*/ LDOMNodeType *pVal);

public:

	CDTDParser* m_pDTDDocument;

	String m_ns;
	String m_name;
	vector<CAttribute*> m_attributes;
};

#if 0
class CASDTDModel;

class WEBEXT CDTDDocument :
//	public CDTDObjectImpl<ILDTDDocument>
	public Document,
	public EventTarget,
	public CLDOMDocumentViewImpl<CDTDDocument>,
	public DocumentEvent,
	public CLDOMDocumentRangeImpl<CDTDDocument>,
	public CLDOMDocumentTraversalImpl<CDTDDocument>,
	public CLDocumentCSSImpl<CDTDDocument>,
	public ILDTDDocument,

	public CNotifyGetImpl<CDTDDocument>,
	public CNotifySendImpl<CDTDDocument>
{
public:
	typedef CDTDDocument T;

	CTOR CDTDDocument()
	{
		m_pASModel = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	ILDOMErrorHandler* m_errorHandler;

	CComBSTR m_url;

	CComObject<CASDTDModel>* m_pASModel;

	CArray<ILDOMNode*,ILDOMNode*> m_items;

	CArray<CEntity*,CEntity*> m_entityList;
	CArray<CLDTDElement*,CLDTDElement*> m_elementList;
	CArray<CAttlist*,CAttlist*> m_attlistList;

	CEntity* GetEntityByName(BSTR name);
	CLDTDElement* GetElementByName(BSTR ns, BSTR name);
//	CAttlist* GetAttlistByName(BSTR ns, BSTR name);

	void LoadDocument(BSTR pathName);

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_LDTDDOCUMENT)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDTDDocument)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMDocument)
	COM_INTERFACE_ENTRY(ILDTDDocument)
	COM_INTERFACE_ENTRY(ILDOMEventTarget)
	COM_INTERFACE_ENTRY(ILDocumentStyle)
	COM_INTERFACE_ENTRY(ILDocumentCSS)
	COM_INTERFACE_ENTRY(ILDOMDocumentView)
	COM_INTERFACE_ENTRY(ILDOMDocumentEvent)
	COM_INTERFACE_ENTRY(ILDOMDocumentRange)
	COM_INTERFACE_ENTRY(ILDOMDocumentTraversal)

	COM_INTERFACE_ENTRY(CLDOMNodeImplImpl)
	COM_INTERFACE_ENTRY(CLDOMDocumentImplImpl)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()
*/

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

public:

	STDMETHOD(get_asModel)(/*[out, retval]*/ IASModel* *pVal);
#if 0
	STDMETHOD(parseTextData)(/*[in]*/ ITextData* textData, /*[out,retval]*/ VARIANT_BOOL* pVal);
#endif
//	STDMETHOD(get_nodeType)(/*[out, retval]*/ LDOMNodeType *pVal);
//	STDMETHOD(get_length)(/*[out, retval]*/ long *pVal);
//	STDMETHOD(item)(/*[in]*/ long index, /*[out,retval]*/ ILDOMNode* *pVal);
	STDMETHOD(get_errorHandler)(/*[out, retval]*/ ILDOMErrorHandler* *pVal);
	STDMETHOD(set_errorHandler)(/*[in]*/ ILDOMErrorHandler* newVal);
};

#endif

class WEBEXT DTDDocument
{
public:
	CTOR DTDDocument();
	~DTDDocument();

	vector<CEntity*> m_entityList;
	vector<CLDTDElement*> m_elementList;
	vector<CAttlist*> m_attlistList;

	void Load(StringIn url);

	CEntity* GetEntityByName(StringIn name);
	CLDTDElement* GetElementByName(StringIn ns, StringIn name);
};

}	// Web
}

#endif
