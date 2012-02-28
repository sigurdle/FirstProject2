#pragma once

#include "PDObjectWithAppearanceImpl.h"

template <class T> class ATL_NO_VTABLE CPDObjectWithAppearanceAndStrokeFillImpl :
	public CPDObjectWithAppearanceImpl<T, IPDObjectWithAppearanceAndStrokeFill>
{
public:
	CPDObjectWithAppearanceAndStrokeFillImpl()
	{
		m_subObjects = NULL;
		m_activeStroke = NULL;
		m_activeFill = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CPDObjectWithAppearanceImpl<T, IPDObjectWithAppearanceAndStrokeFill>::FinalConstruct();
		if (FAILED(hr)) return hr;

		hr = CComObject<CObjectMap>::CreateInstance(&m_subObjects);
		if (FAILED(hr)) return hr;
		m_subObjects->AddRef();

		return S_OK;
	}

	void FinalRelease()
	{
		CPDObjectWithAppearanceImpl<T, IPDObjectWithAppearanceAndStrokeFill>::FinalRelease();

		if (m_subObjects)
		{
			RemoveAllSubObjects();

			m_subObjects->Release();
			m_subObjects = NULL;
		}
	}

	void RemoveAllSubObjects()
	{
		for (int i = 0; i < m_subObjects->m_items.GetSize(); i++)
		{
			CComQIPtr<INotifySend> cp = m_subObjects->m_items[i];
			CComQIPtr<INotifyGet> get = static_cast<T*>(this)->GetUnknown();
			if (get) cp->Unadvise(get);
		}
		m_subObjects->m_items.RemoveAll();
	}

	CComObject<CObjectMap>* m_subObjects;
	IPDObjectStroke* m_activeStroke;
	IPDObjectFill* m_activeFill;

	STDMETHODIMP removeSubObjects()
	{
		RemoveAllSubObjects();
		return S_OK;
	}

	STDMETHOD(get_subObjects)(/*[out, retval]*/ IObjectMap* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_subObjects;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHODIMP get_activeStroke(IPDObjectStroke **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_activeStroke;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP put_activeStroke(IPDObjectStroke *newVal)
	{
		m_activeStroke = newVal;
		return S_OK;
	}

	STDMETHODIMP get_activeFill(IPDObjectFill **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_activeFill;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP put_activeFill(IPDObjectFill *newVal)
	{
		m_activeFill = newVal;
		return S_OK;
	}

	STDMETHODIMP appendSubObject(IPDObjectWithBrush *object)
	{
		if (object == NULL) return E_INVALIDARG;

	// TODO, remove from previous parent (if any)

		object->AddRef();

//		CComQIPtr<IPDObject> o = object;
//		o->put_parent(this);
//		o->put_document(m_pDocument);

		/*
		{
			CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(o.p);
			pObject->CalculateBounds();
		}
		*/
		CComQIPtr<INotifyGet> get = static_cast<T*>(this)->GetUnknown();
		if (get)
		{
			CComQIPtr<INotifySend> cp = object;
			DWORD cookie;
			cp->Advise(get, &cookie);
		}

		m_subObjects->m_items.Add(object);

		static_cast<T*>(this)->FireOnChanged(NOTIFY_ADD, object, DISPID_UNKNOWN);

		return S_OK;
	}

	STDMETHODIMP removeSubObject(IPDObjectWithBrush *object)
	{
		// TODO: Add your implementation code here

		return S_OK;
	}

	STDMETHODIMP copyAppearanceFrom(VARIANT_BOOL newArtHasBasicAppearance, IPDObjectWithAppearanceAndStrokeFill *other)
	{
//		VARIANT_BOOL newArtHasBasicAppearance;
//		gIApp->get_newArtHasBasicAppearance(&newArtHasBasicAppearance);

		RemoveAllSubObjects();

		CComPtr<IPDObjectFill> activefill;
		other->get_activeFill(&activefill);

		CComPtr<IPDObjectStroke> activestroke;
		other->get_activeStroke(&activestroke);

		if (newArtHasBasicAppearance)
		{
			// Fill
			{
				CComPtr<IPDObjectFill> clonefill;
				activefill->clone((IPDObject**)&clonefill);

				m_activeFill = clonefill;
				appendSubObject(clonefill);
			}

			// Stroke
			{
				CComPtr<IPDObjectStroke> clonestroke;
				activestroke->clone((IPDObject**)&clonestroke);

				m_activeStroke = clonestroke;
				appendSubObject(clonestroke);
			}
		}
		else
		{
			CComPtr<IObjectMap> subObjects;
			other->get_subObjects(&subObjects);

			long nsubObjects;
			subObjects->get_length(&nsubObjects);

			for (int i = 0; i < nsubObjects; i++)
			{
				CComPtr<IPDObjectWithBrush> object;
				subObjects->item(i, (IUnknown**)&object);

				CComPtr<IPDObjectWithBrush> clone;
				object->clone((IPDObject**)&clone);
				if (clone)
				{
					if (object == activestroke)
						m_activeStroke = (IPDObjectStroke*)clone.p;
					else if (object == activefill)
						m_activeFill = (IPDObjectFill*)clone.p;

					appendSubObject(clone);
				}
			}
		}

		return S_OK;
	}
};
