#pragma once

class CObjectMap;
class CPDGuides;
class CPDDocument;
class CPDObjectGroup;
class CPDObjectLayerGroup;

#include "PDGuides.h"
#include "PDObjectImpl.h"
#include "PDPage.h"

//#include "ObjectMap.h"

bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

template<class IBase> class ATL_NO_VTABLE CPDSpreadImpl :
	public IBase,
	public IObjectSerializable
{
public:
	CPDSpreadImpl()
	{
		m_pages = NULL;
		m_layergroups = NULL;
		m_pDocument = NULL;

		m_spine = 0;
	}

	HRESULT FinalConstruct()
	{
		HRESULT hr;

		hr = ::CoCreateGuid(&m_uniqId);
		if (FAILED(hr)) return hr;

		hr = CComObject<CObjectMap>::CreateInstance(&m_pages);
		if (FAILED(hr)) return hr;
		m_pages->AddRef();

		hr = CComObject<CObjectMap>::CreateInstance(&m_layergroups);
		if (FAILED(hr)) return hr;
		m_layergroups->AddRef();

		m_firstChild = NULL;
		m_lastChild = NULL;

		return S_OK;
	}

	void FinalRelease()
	{
		if (m_pages)
		{
			m_pages->Release();
			m_pages = NULL;
		}

		if (m_layergroups)
		{
			m_layergroups->Release();
			m_layergroups = NULL;
		}
	}

	CPDDocument* m_pDocument;
	GUID m_uniqId;

	CComObject<CObjectMap>* m_pages;
	CComObject<CObjectMap>*	m_layergroups;

	IPDObjectUnknown* m_firstChild;	// first LayerGroup
	IPDObjectUnknown* m_lastChild;		// last layerGroup

//	CComObject<CPDObjectGroup>*	m_layergroups;
	long m_spine;

	HRESULT insertLayerGroup(IPDObjectLayerGroup* object, IPDObjectLayerGroup* before)
	{
		object->AddRef();

		/*
		ATLASSERT(pObject->m_pDocument == m_pDocument);
		if (pObject->m_pDocument != m_pDocument)
		{
			MessageBox(NULL, "Cannot insert object across documents", "", MB_OK);
			return E_FAIL;
		}
		*/

		CComPtr<IPDSpread> spread;
		object->get_spread(&spread);

	// First remove it from previous parent
		if (spread)
		{
			spread->removeLayerGroup(object);
		}

		CComPtr<IPDObjectUnknown> after;

		if (before)
			before->get_previousSibling(&after);
		else
			get_lastLayerGroup(&after);

		object->put_nextSibling(before);
		object->put_previousSibling(after);

		if (after == NULL)
			m_firstChild = object;
		else
			after->put_nextSibling(object);

		if (before == NULL)
			m_lastChild = object;
		else
			before->put_previousSibling(object);

		//pObject->m_parent = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)this);//static_cast<CComObject<CPDGradient>*>(this);
		object->put_spread(this);

		if (before)
		{
			for (int i = 0; i < m_layergroups->m_items.GetSize(); i++)
			{
				if (IsUnknownEqualUnknown(m_layergroups->m_items[i], before))
				{
					m_layergroups->m_items.InsertAt(i, object);
					break;
				}
			}
		}
		else
		{
			m_layergroups->m_items.Add(object);
		}

		if (m_pDocument)	// TODO, confirm that this is correct
		{
			m_pDocument->DistributeStories();
		}

		return S_OK;
	}

	HRESULT removePage(IPDPage* page)
	{
		for (int i = 0; i < m_pages->m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(page, m_pages->m_items[i]))
			{
				page->Release();
				m_pages->m_items.RemoveAt(i);
				return S_OK;
			}
		}

		return E_FAIL;
	}

// IPDSpread
public:
	STDMETHOD(get_uniqId)(/*[out, retval]*/ GUID *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_uniqId;
		return S_OK;
	}
	STDMETHOD(get_ownerDocument)(/*[out, retval]*/ IPDDocument* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_pDocument;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_spine)(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_spine;
		return S_OK;
	}
	STDMETHOD(put_spine)(/*[in]*/ long newVal)
	{
		m_spine = newVal;
		ATLASSERT(m_spine <= m_pages->m_items.GetSize());
		return S_OK;
	}
	STDMETHODIMP get_pages(IObjectMap **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_pages;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHODIMP get_layergroups(/*[out, retval]*/ IObjectMap* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_layergroups;//->m_children;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHODIMP getLayerGroupFromLayer(IPDLayer *layer, IPDObjectLayerGroup **pVal)
	{
		if (pVal == NULL) return E_POINTER;

		for (int i = 0; i < m_layergroups->/*m_children->*/m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(static_cast<IPDLayer*>(static_cast<CPDObjectLayerGroup*>((IPDObjectLayerGroup*)(m_layergroups->/*m_children->*/m_items[i]))->m_layer), layer))
			{
				*pVal = static_cast<IPDObjectLayerGroup*>(m_layergroups->/*m_children->*/m_items[i]);
				(*pVal)->AddRef();
				return S_OK;
			}
		}

		*pVal = NULL;

		return E_FAIL;
	}
	STDMETHODIMP removeLayerGroup(/*[in]*/ IPDObjectLayerGroup* object)
	{
		if (object == NULL)
		{
			ATLASSERT(0);
			return E_POINTER;
		}

		//CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);

		for (int i = 0; i < m_layergroups->m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_layergroups->m_items[i], object))
			{
				/*
				if (pObject->m_previousSibling != NULL)
					pObject->m_previousSibling->m_nextSibling = pObject->m_nextSibling;
				else
					m_firstChild = pObject->m_nextSibling;

				if (pObject->m_nextSibling != NULL)
					pObject->m_nextSibling->m_previousSibling = pObject->m_previousSibling;
				else
					m_lastChild = pObject->m_previousSibling;

				pObject->m_previousSibling = NULL;
				pObject->m_nextSibling = NULL;
				*/

				CComPtr<IPDObjectUnknown> previousSibling;
				object->get_previousSibling(&previousSibling);

				CComPtr<IPDObjectUnknown> nextSibling;
				object->get_nextSibling(&nextSibling);

				if (previousSibling != NULL)
					previousSibling->put_nextSibling(nextSibling);
				else
					m_firstChild = nextSibling;

				if (nextSibling != NULL)
					nextSibling->put_previousSibling(previousSibling);
				else
					m_lastChild = previousSibling;

				object->put_previousSibling(NULL);
				object->put_nextSibling(NULL);

			//	pObject->m_parent = NULL;
			//	pObject->detachFromSpread();

			// Fire event ??

				object->Release();

				m_layergroups->m_items.RemoveAt(i);

				if (m_pDocument)	// TODO, confirm that this is correct
				{
					m_pDocument->DistributeStories();
				}

				return S_OK;
			}
		}

		return E_FAIL;
	}

	STDMETHOD(get_lastLayerGroup)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_lastChild;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_firstLayerGroup)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_firstChild;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(getObjectByUniqId)(/*[in]*/ GUID guid, /*[out,retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;

		//*pVal = m_layergroups->getObjectByUniqId(guid);

		for (int i = 0; i < m_layergroups->m_items.GetSize(); i++)
		{
			*pVal = static_cast<CPDObjectLayerGroup*>((IPDObjectLayerGroup*)m_layergroups->m_items[i])->getObjectByUniqId(guid);
			if (*pVal)
			{
				(*pVal)->AddRef();
				return S_OK;
			}
		}

		if (*pVal) (*pVal)->AddRef();
		//*pVal = NULL;

		return S_OK;
	}
#if 0
	STDMETHOD(saveAsXML)(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node)
	{
		return S_OK;
		return E_FAIL;
	}
#endif

// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		node->putObjectMap(L"pages", m_pages);
		node->putObjectMap(L"layergroups", m_layergroups);

		return S_OK;
	}
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		CComQIPtr<IPDDocument> document = pUnkExtra;
		m_pDocument = static_cast<CPDDocument*>((IPDDocument*)document.p);

		if (SUCCEEDED(node->getObjectMap(L"pages", m_pages, static_cast<IBase*>(this))))
		{
			/*
			for (int i = 0; i < m_pages->m_items.GetSize(); i++)
			{
				CPDPage* pPage = static_cast<CPDPage*>((IPDPage*)m_pages->m_items[i]);
			//	pPage->m_pDocument = m_pDocument;	// hm.. not set
			//	pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>(static_cast<IPDSpread*>(this));
			}
			*/
		}

		CComObject<CObjectMap>* pMap;
		CComObject<CObjectMap>::CreateInstance(&pMap);
		if (pMap)
		{
			if (SUCCEEDED(node->getObjectMap(L"layergroups", pMap, static_cast<IBase*>(this))))
			{
				for (int i = 0; i < pMap->m_items.GetSize(); i++)
				{
					IPDObjectLayerGroup* pLayerGroup = static_cast<IPDObjectLayerGroup*>(pMap->m_items[i]);
					insertLayerGroup(pLayerGroup, NULL);
				}
			}
			pMap->Release();
		}

		return S_OK;
	}
};
