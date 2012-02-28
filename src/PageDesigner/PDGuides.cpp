#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "ObjectMap.h"
#include "PDGuides.h"
#include "PDGuide.h"
#include "PDLayer.h"

/////////////////////////
// CPDGuides

int CPDGuides::FinalConstruct()
{
	CComObject<CObjectMap>::CreateInstance(&m_children);
	m_children->AddRef();

	CoCreateGuid(&m_uniqId);

	return S_OK;
}

void CPDGuides::FinalRelease()
{
	if (m_children)
	{
		m_children->Release();
		m_children = NULL;
	}
}

STDMETHODIMP CPDGuides::createGuide(long direction, IPDGuide **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDGuide>* pGuide;
	CComObject<CPDGuide>::CreateInstance(&pGuide);
	if (pGuide)
	{
		pGuide->m_direction = direction;

		*pVal = pGuide;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDGuides::appendGuide(IPDGuide *guide)
{
	return insertObject(guide, NULL);

#if 0
	if (guide == NULL) return E_POINTER;

	CComObject<CPDGuide>* pGuide = static_cast<CComObject<CPDGuide>*>(guide);
	pGuide->m_layer = m_layer;
	guide->AddRef();

	m_children->m_items.Add(guide/*static_cast<CComObject<CPDGuide>*>(guide)*/);
	return S_OK;
#endif
}

STDMETHODIMP CPDGuides::get_length(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_children->m_items.GetSize();
	return S_OK;
}

STDMETHODIMP CPDGuides::item(long index, IPDGuide **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (index >= 0 && index < m_children->m_items.GetSize())
	{
		*pVal = (IPDGuide*)m_children->m_items[index];
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDGuides::getGuideUnderPoint(double x, double y, double tolerance, IPDGuide **pVal)
{
	if (pVal == NULL) return E_POINTER;

	for (int i = 0; i < m_children->m_items.GetSize(); i++)
	{
		CComObject<CPDGuide>* pGuide = static_cast<CComObject<CPDGuide>*>((IPDGuide*)m_children->m_items[i]);

		if (pGuide->m_direction == 0)	// Horizontal
		{
			if (fabs(pGuide->m_position-y) < tolerance)
			{
				*pVal = pGuide;
				(*pVal)->AddRef();

				return S_OK;
			}
		}
		else
		{
			if (fabs(pGuide->m_position-x) < tolerance)
			{
				*pVal = pGuide;
				(*pVal)->AddRef();

				return S_OK;
			}
		}
	}

	*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDGuides::deleteAllGuides()
{
	for (int i = 0; i < m_children->m_items.GetSize(); i++)
	{
		m_children->m_items[i]->Release();
	}
	m_children->m_items.RemoveAll();

// TODO: notify

	return S_OK;
}

HRESULT CPDGuides::insertObject(IPDGuide* object, IPDGuide* before)
{
//	CPDGuide* pBefore = static_cast<CPDGuide*>(before);

	object->AddRef();

	/*
	ATLASSERT(pObject->m_pDocument == m_pDocument);
	if (pObject->m_pDocument != m_pDocument)
	{
		MessageBox(NULL, "Cannot insert object across documents", "", MB_OK);
		return E_FAIL;
	}
	*/

// First remove it from previous parent
	CComPtr<IPDObjectUnknown> parent;
	object->get_parent(&parent);

// First remove it from previous parent
	if (parent)
	{
		parent->removeObject(object);
	}

	CComPtr<IPDObjectUnknown> after;

	if (before)
		before->get_previousSibling(&after);
	else
		get_lastChild(&after);

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

	{
		CPDGuide* pObject = static_cast<CPDGuide*>(object);
		pObject->m_layer = m_layer;
		pObject->m_parent = static_cast<CPDObjectUnknownImpl<IPDObjectUnknown>*>((IPDObjectUnknown*)this);
	//	pObject->attachToSpread(pObject->m_parent);
	}

	if (before)
	{
		for (int i = 0; i < m_children->m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_children->m_items[i], before))
			{
				m_children->m_items.InsertAt(i, object);
				break;
			}
		}
	}
	else
	{
		m_children->m_items.Add(object);
	}
/*
	CalculateBounds();
	if (m_pDocument)
	{
		m_pDocument->DistributeStories();

		m_pDocument->FireOnChanged(NOTIFY_ADD, object, IID_IPDObject, DISPID_UNKNOWN);
	}
*/
	return S_OK;
}

STDMETHODIMP CPDGuides::removeObject(IPDObjectUnknown *object)
{
	if (object == NULL)
	{
		ATLASSERT(0);
		return E_POINTER;
	}

	for (int i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_children->m_items[i], object))
		{
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
			{
				CPDGuide* pObject = static_cast<CPDGuide*>(object);
				//pObject->detachFromSpread();
			}

			object->Release();

			m_children->m_items.RemoveAt(i);

			/*
			CalculateBounds();
			if (m_pDocument)
			{
				m_pDocument->DistributeStories();
			}
			*/

			return S_OK;
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}
