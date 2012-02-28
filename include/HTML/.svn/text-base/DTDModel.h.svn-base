// DTDModel.h : Declaration of the CDTDModel

#ifndef __DTDMODEL_H_
#define __DTDMODEL_H_
#if 0

#include "resource.h"       // main symbols
#include "ASDTDModCP.h"
//#include "DOMCoreModCP.h"

class CDTDContentModel;
class CCPChoiceSeq;

class CDTDASNamedObjectMap :
	public CComObjectRootEx<CComSingleThreadModel>,

	public IDispatchImpl<DispIDTDASNamedObjectMap, &IID_DispIDTDASNamedObjectMap, &LIBID_ASDTDMODLib>,

	public IASNamedObjectMap
{
public:
	void FinalRelease()
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			m_items[i]->Release();
		}
	}

	CArray<IASObject*, IASObject*> m_items;

BEGIN_COM_MAP(CDTDASNamedObjectMap)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IASNamedObjectMap)
END_COM_MAP()

	STDMETHOD(get_length)(unsigned long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_items.GetSize();
		return S_OK;
	}

	STDMETHOD(getNamedItem)(BSTR name, IASObject** pVal)
	{
		if (pVal == NULL) return E_POINTER;

		for (int i = 0; i < m_items.GetSize(); i++)
		{
			BSTR bnodename;
			m_items[i]->get_nodeName(&bnodename);
			_bstr_t nodename = _bstr_t(bnodename);

			if (!wcscmp(name, nodename))
			{
				*pVal = m_items[i];
				(*pVal)->AddRef();
				return S_OK;
			}
		}

		*pVal = NULL;

		return S_OK;
	}

	STDMETHOD(getNamedItemNS)(BSTR namespaceURI, BSTR localName, IASObject** pVal)
	{
		if (pVal == NULL) return E_POINTER;

#if 0
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			BSTR nodename;
			m_items[i]->get_localName(&nodename);

			if (!wcscmp(name, nodename))
			{
				*pVal = m_items[i];
				(*pVal)->AddRef();
				return S_OK;
			}
		}
#endif

		*pVal = NULL;

		return S_OK;
	}

	STDMETHOD(item)(long index, IASObject** pVal)
	{
		if (pVal == NULL) return E_POINTER;

		if (index >= 0 && index < m_items.GetSize())
		{
			*pVal = m_items[index];
			(*pVal)->AddRef();
		}
		else
			*pVal = NULL;
		
		return S_OK;
	}

	STDMETHOD(setNamedItem)(IASObject* newASObject, IASObject** pVal)
	{
		if (newASObject == NULL) return E_POINTER;

		m_items.Add(newASObject);
		newASObject->AddRef();

		if (pVal)
		{
			*pVal = newASObject;
			(*pVal)->AddRef();
		}

		return S_OK;
	}

	STDMETHOD(setNamedItemNS)(IASObject* newASObject, IASObject** pVal)
	{
	// Same as above (?)
		if (newASObject == NULL) return E_POINTER;

		m_items.Add(newASObject);
		newASObject->AddRef();

		if (pVal)
		{
			*pVal = newASObject;
			(*pVal)->AddRef();
		}

		return S_OK;
	}
};

class CDTDASObjectList :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IASObjectList
{
public:
	void FinalRelease()
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			m_items[i]->Release();
		}
	}

	CArray<IASObject*, IASObject*> m_items;

BEGIN_COM_MAP(CDTDASObjectList)
	COM_INTERFACE_ENTRY(IASObjectList)
END_COM_MAP()

	STDMETHOD(item)(/*[in]*/ long index, /*[out,retval]*/ IASObject** pVal)
	{
		if (pVal == NULL) return E_POINTER;

		if (index >= 0 && index < m_items.GetSize())
		{
			*pVal = m_items[index];
			(*pVal)->AddRef();
		}
		else
			*pVal = NULL;

		return S_OK;
	}

	STDMETHOD(get_length)(/*[out, retval]*/ unsigned long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_items.GetSize();
		return S_OK;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CDTDModel
class CDTDModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDTDModel, &CLSID_DTDModel>,

	public IDispatchImpl<DispIDTDModel, &IID_DispIDTDModel, &LIBID_SVGLib>,

	public IDTDModel, //IASModel // IASObject

	public IConnectionPointContainerImpl<CDTDModel>,
	public CProxy_IDTDModelEvents< CDTDModel >
{
public:
	CDTDModel()
	{
		m_entityDeclarations = NULL;
		m_elementDeclarations = NULL;
		m_attributeDeclarations = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CComObject<CDTDContentModel>* BuildCM(CCPChoiceSeq* cp);

	CComQIPtr<IDOMErrorHandler> m_errorHandler;
	CComQIPtr<ITextData> m_textDoc;

DECLARE_REGISTRY_RESOURCEID(IDR_DTDMODEL)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDTDModel)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IDTDModel)
	COM_INTERFACE_ENTRY(IASObject)
	COM_INTERFACE_ENTRY(IASModel)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDTDModel)
CONNECTION_POINT_ENTRY(DIID__IDTDModelEvents)
END_CONNECTION_POINT_MAP()

// IDTDModel
public:
	STDMETHOD(FireModelChanged)();
	STDMETHOD(saveAsText)(/*[out,retval]*/ BSTR* pVal);
	STDMETHOD(parse)(/*[out,retval]*/ bool* pSuccess);
	STDMETHOD(get_sourceTextDoc)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(set_sourceTextDoc)(/*[in]*/ IUnknown* newVal);
	STDMETHOD(get_errorHandler)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(set_errorHandler)(/*[in]*/ IUnknown* newVal);
	STDMETHOD(load)(/*[in]*/ BSTR pathName, /*[out,retval]*/ bool* pSuccess);

/*
	CComQIPtr<ITextDocument> m_textDoc;


	int m_line;
	int m_column;
	unsigned long m_fpos;

	int m_efpos;
	CDTDEntity* m_pInsideEntity;

	CArray<CEntity*,CEntity*> m_entityList;
	CArray<CElement*,CElement*> m_elementList;
	CArray<CAttlist*,CAttlist*> m_attlistList;
*/

	CComObject<CDTDASNamedObjectMap>* m_entityDeclarations;
	CComObject<CDTDASNamedObjectMap>* m_elementDeclarations;
	CComObject<CDTDASNamedObjectMap>* m_attributeDeclarations;
/*
	void LoadDocument(BSTR pathName);
	void Parse();

	BOOL eof();
	int _getc();
	int getc();
	void ungetc();
	_bstr_t GetID();
	void GetNSID(_bstr_t& ns, _bstr_t& id);
	void SkipSpaces();
	_bstr_t GetString();
	void EatChar(int c);

	CDTDEntity* GetEntityByName(BSTR name);
	CDTDElement* GetElementByName(BSTR ns, BSTR name);
	CDTDAttlist* GetAttlistByName(BSTR ns, BSTR name);

	void ParseCommentNode();

	void ParseElementContentSpec(CDTDElement* pElement);
	CDTDCPChoiceSeq* ParseChoiceSeq();
	CDTDCP* ParseCP();

	void ParseEntity(CDTDEntity* pEntity);
	void ParseElement(CDTDElement* pElement);
	void ParseAttlist(CDTDAttlist* pAttlist);
*/

// IASObject
	STDMETHOD(get_ownerASModel)(/*[out, retval]*/ IASModel* *pVal)
	{
		return E_FAIL;
	}

	STDMETHOD(put_ownerASModel)(/*[in]*/ IASModel* newVal)
	{
		return E_FAIL;
	}

	STDMETHOD(cloneASObject)(/*[in]*/ bool deep, /*[out,retval]*/ IASObject** pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(put_localName)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(put_prefix)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(put_nodeName)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_asNodeType)(/*[out, retval]*/ ASObjectType *pVal)
	{
		*pVal = AS_MODEL;
		return S_OK;
	}

// IASModel
	STDMETHOD(createASContentModel)(/*[in]*/ unsigned long minOccurs, /*[in]*/ unsigned long maxOccurs, /*[in]*/ ASContentModelTypeOp Operator, /*[out,retval]*/ IASContentModel** pVal);
	STDMETHOD(createASEntityDeclaration)(/*[in]*/ BSTR name, /*[out,retval]*/ IASEntityDeclaration** pVal);
	STDMETHOD(createASNotationDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[in]*/ BSTR systemId, /*[in]*/ BSTR publicId, /*[out,retval]*/ IASNotationDeclaration** pVal);
	STDMETHOD(createASAttributeDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASAttributeDeclaration** pVal);
	STDMETHOD(createASElementDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASElementDeclaration** pVal);
	STDMETHOD(get_contentModelDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal);
	STDMETHOD(get_entityDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal);
	STDMETHOD(get_notationDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal);
	STDMETHOD(get_attributeDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal);
	STDMETHOD(get_elementDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal);
	STDMETHOD(get_isNamespaceAware)(/*[out, retval]*/ bool *pVal);
};

#endif //__DTDMODEL_H_
#endif