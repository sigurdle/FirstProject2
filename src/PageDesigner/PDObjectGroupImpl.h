#pragma once

#include "PDObjectImpl.h"
#include "PDObjectTransformableImpl.h"

HRESULT GetTransformRectBoundingBox(IPDMatrix* mat, RectD* bounds, RectD* pVal);

template <class T, class IBase> class ATL_NO_VTABLE CPDObjectGroupImpl : 
	public CPDObjectImpl<IBase>
//	public CPDObjectTransformableImpl<T>
{
public:
	CPDObjectGroupImpl()
	{
		m_enableBackground = 0;	// accumulate
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CPDObjectImpl<IBase>::FinalConstruct();
		if (FAILED(hr)) return hr;

		return S_OK;
	}

	void FinalRelease()
	{
		CPDObjectImpl<IBase>::FinalRelease();
	}

	long m_enableBackground;

	STDMETHODIMP Move(double dx, double dy)
	{
		for (int i = 0; i < m_children->m_items.GetSize(); i++)
		{
			CComQIPtr<IPDObject> object = m_children->m_items[i];
			CComQIPtr<IPDObjectTransformable> objectTransformable = object;

			if (objectTransformable)
			{
				CComPtr<IPDMatrix> matrix;
				objectTransformable->get_transformMatrix(&matrix);

				CComPtr<IPDMatrix> imatrix;
				matrix->inverse(&imatrix);

				PointD pt0;
				pt0.x = 0;
				pt0.y = 0;

				PointD pt1;
				pt1.x = dx;
				pt1.y = dy;

				imatrix->transformPoint(&pt0, &pt0);
				imatrix->transformPoint(&pt1, &pt1);

				objectTransformable->Move(pt1.x-pt0.x, pt1.y-pt0.y);
			}
			else
				ATLASSERT(0);
		}

		return S_OK;
	}

	virtual void CalculateBounds()
	{
		{
			double minx = 9999999;
			double miny = 9999999;
			double maxx = -9999999;
			double maxy = -9999999;

			for (int i = 0; i < m_children->m_items.GetSize(); i++)
			{
				CComQIPtr<IPDObject> object = m_children->m_items[i];
				CComQIPtr<IPDObjectTransformable> transformable = object;
				if (transformable)
				{
					RectD xbounds;
					transformable->get_xbounds(&xbounds);

					minx = min(xbounds.X, minx);
					miny = min(xbounds.Y, miny);
					maxx = max(xbounds.X+xbounds.Width, maxx);
					maxy = max(xbounds.Y+xbounds.Height, maxy);
				}
			}

			static_cast<T*>(this)->m_bounds.X = minx;
			static_cast<T*>(this)->m_bounds.Y = miny;
			static_cast<T*>(this)->m_bounds.Width = maxx-minx;
			static_cast<T*>(this)->m_bounds.Height = maxy-miny;
		}

		{
			double minx = 9999999;
			double miny = 9999999;
			double maxx = -9999999;
			double maxy = -9999999;

			for (int i = 0; i < m_children->m_items.GetSize(); i++)
			{
				CComQIPtr<IPDObject> object = m_children->m_items[i];

				RectD objectExpandedRect;
				object->getExpandedBBox(&objectExpandedRect);

				CComQIPtr<IPDObjectTransformable> objectTransformable = object;
				ATLASSERT(objectTransformable != NULL);

				CComPtr<IPDMatrix> mat;
				objectTransformable->get_transformMatrix(&mat);

				RectD objectExpandedRectX;
				GetTransformRectBoundingBox(mat, &objectExpandedRect, &objectExpandedRectX);

				minx = min(objectExpandedRectX.X, minx);
				miny = min(objectExpandedRectX.Y, miny);
				maxx = max(objectExpandedRectX.X+objectExpandedRectX.Width, maxx);
				maxy = max(objectExpandedRectX.Y+objectExpandedRectX.Height, maxy);
			}

			m_filterRect.X = minx;
			m_filterRect.Y = miny;
			m_filterRect.Width = maxx-minx;
			m_filterRect.Height = maxy-miny;
		}

		GetTransformRectBoundingBox(m_matrix, &static_cast<T*>(this)->m_bounds, &static_cast<T*>(this)->m_xbounds);
	}

	HRESULT insertObject(IPDObject* object, IPDObject* before)
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

		object->put_parent(this);
		{
			CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);
			//pObject->m_parent = static_cast<CPDObjectUnknownImpl<IPDObjectUnknown>*>((IPDObjectUnknown*)this);//static_cast<CComObject<CPDGradient>*>(this);
			pObject->attachToSpread(pObject->m_parent);
		}

		{
			CComQIPtr<INotifySend> cp = object;
			DWORD cookie;
			cp->Advise(static_cast<T*>(this), &cookie);
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

		CalculateBounds();
		if (m_pDocument)
		{
			// TODO, check if this is necessary
		//	m_pDocument->DistributeStories();	// ???

			m_pDocument->FireOnChanged(NOTIFY_ADD, object, DISPID_UNKNOWN);
		}

		return S_OK;
	}

// IPDObjectGroupImpl
public:
	STDMETHOD(get_enableBackground)(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_enableBackground;
		return S_OK;
	}
	STDMETHOD(put_enableBackground)(/*[in]*/ long newVal)
	{
		m_enableBackground = newVal;
		// TODO, fire event
		return S_OK;
	}
	STDMETHOD(removeObject)(/*[in]*/ IPDObjectUnknown* object)
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
				object->put_parent(NULL);

				{
					CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);
					//pObject->m_parent = NULL;
					pObject->detachFromSpread();
				}

				m_children->m_items.RemoveAt(i);

				{
					CComQIPtr<INotifySend> cp = object;
					cp->Unadvise(static_cast<T*>(this));
				}

				static_cast<T*>(this)->FireOnChanged(NOTIFY_REMOVE, object, DISPID_UNKNOWN);

				CalculateBounds();

				int refcount = object->Release();

			// hm... ??
				/*
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

	STDMETHODIMP appendObject(IPDObject *object)
	{
		if (object == NULL) return E_POINTER;

		return insertObject(object, NULL);
	}

	STDMETHODIMP insertObjectBeforeObject(IPDObject *object, IPDObject *before)
	{
		if (object == NULL) return E_POINTER;
		if (before == NULL) return E_POINTER;
		
		return insertObject(object, before);
	}

// IObjectSerializable
	STDMETHODIMP Serialize(IArchive *ar, IArchiveElement* node)
	{
		CPDObjectImpl<IBase>::Serialize(ar, node);
//		CPDObjectTransformableImpl<T>::Serialize(ar, node);

		if (m_children)
		{
			node->putObjectMap(L"children", m_children);
		}

		return S_OK;
	}

	STDMETHODIMP Deserialize(IArchive *ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		CPDObjectImpl<IBase>::Deserialize(ar, node, pUnkExtra);
	//	CPDObjectTransformableImpl<T>::Deserialize(ar, node, pUnkExtra);

		CComObject<CObjectMap>* pMap;

		CComObject<CObjectMap>::CreateInstance(&pMap);
		if (pMap)
		{
			if (SUCCEEDED(node->getObjectMap(L"children", pMap, static_cast<IBase*>(this))))
			{
				for (int i = 0; i < pMap->m_items.GetSize(); i++)
				{
					IPDObject* object = static_cast<IPDObject*>(pMap->m_items[i]);
					appendObject(object);
				}
			}

			pMap->Release();
		}

		return S_OK;
	}
};
