// Archive.h : Declaration of the CArchive

#ifndef __ARCHIVE_H_
#define __ARCHIVE_H_

#include "resource.h"       // main symbols

class CArchive;

/////////////////////////////////////////////////////////////////////////////
// CArchiveElement

class ATL_NO_VTABLE CArchiveElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IArchiveElement, &IID_IArchiveElement, &LIBID_PAGEDESIGNERLib>
{
public:
	CArchiveElement()
	{
		m_pAr = NULL;
	}

	//void FinalRelease();

	CArchive* m_pAr;

	CComPtr<ILDOMNode> m_node;

//	HRESULT getObject(IDOMElement* element, IUnknown* pUnkExtra, IUnknown* *pVal);
	HRESULT deserializeObject(ILDOMElement* element, IUnknown *pUnk, IUnknown* pUnkExtra);

//DECLARE_REGISTRY_RESOURCEID(IDR_ARCHIVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CArchiveElement)
	COM_INTERFACE_ENTRY(IArchiveElement)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IArchiveElement
public:
	STDMETHOD(getObject)(/*[in]*/ IUnknown* pUnkExtra, /*[out,retval]*/ IUnknown* *pVal);
	STDMETHOD(serializeObjectMap)(/*[in]*/ IObjectMap* objectmap);
	STDMETHOD(deserializeObjectMap)(/*[in]*/ IObjectMap* objectmap, /*[in]*/ IUnknown* pUnkExtra);
	STDMETHOD(putObject)(IUnknown* pUnk);
	STDMETHOD(deserializeElement)(/*[in]*/ BSTR name, /*[in]*/ IUnknown* pUnk, IUnknown* pUnkExtra);
	STDMETHOD(serializeElement)(/*[in]*/ BSTR name, /*[in]*/ IUnknown* pUnk);
	STDMETHOD(getAttributeNode)(/*[in]*/ BSTR name, /*[out,retval]*/ IArchiveElement* *pVal);
	STDMETHOD(getData)(/*[out,retval]*/ VARIANT* pVal);
	STDMETHOD(getElement)(/*[in]*/ BSTR name, /*[in]*/ IUnknown* pUnkExtra, /*[out,retval]*/ IUnknown* *pVal);
	STDMETHOD(getObjectMap)(/*[in]*/ BSTR name, /*[in]*/ IObjectMap* objectmap, /*[in]*/ IUnknown* pUnkExtra);
	STDMETHOD(putObjectMap)(/*[in]*/ BSTR name, /*[in]*/ IObjectMap* objectmap);
	STDMETHOD(putData)(/*[in]*/ VARIANT value);
	STDMETHOD(putElement)(/*[in]*/ BSTR name,  /*[in]*/ IUnknown* pUnk);
	STDMETHOD(getAttribute)(/*[in]*/ BSTR name, /*[out,retval]*/ VARIANT* pVal);
	STDMETHOD(putAttribute)(/*[in]*/ BSTR name, /*[in]*/ VARIANT value);
};

bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

class CMappedObject
{
public:
//	IDOMElement* m_element;
	IUnknown* m_spUnknown;
//	long m_id;
};

/////////////////////////////////////////////////////////////////////////////
// CArchive
class ATL_NO_VTABLE CArchive : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CArchive, &CLSID_Archive>,
	public IDispatchImpl<IArchive, &IID_IArchive, &LIBID_PAGEDESIGNERLib>
{
public:
	CArchive()
	{
		m_dwMode = 0;
//		m_nextID = 0;
	}
/*
	class Class
	{
		CLSID m_clsid;
		_bstr_t m_name;
	};
*/


	void FinalRelease();

	DWORD m_dwMode;
	_bstr_t m_pathName;
	CComPtr<ILDOMDocument> m_xmldoc;

	//long m_nextID;

	CArray<CMappedObject,CMappedObject> m_writeTable;

//	void MapObject(IDOMElement* element, IUnknown* p);
	long LookupObject(IUnknown* p);
//	CMappedObject* LookupElement(IDOMElement* p);
	//int LookupObjectIndex(IUnknown* p);

DECLARE_REGISTRY_RESOURCEID(IDR_ARCHIVE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CArchive)
	COM_INTERFACE_ENTRY(IArchive)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IArchive
public:
	STDMETHOD(MapObject)(/*[in]*/ IUnknown* pUnk);
	STDMETHOD(Open)(/*[in]*/ BSTR pathName, /*[in]*/ DWORD dwMode, BSTR rootName, IArchiveElement** pVal);
};

#endif //__ARCHIVE_H_
