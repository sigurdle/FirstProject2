#pragma once

class CPDObjectGroup;
class CPDLayer;

//class CObjectMap;

#include "ObjectMap.h"

template<class T> class CPDSpreadImpl;

//#include "PDSpreadImpl.h"

#include "PDObjectUnknownImpl.h"

#include "PDMatrix.h"

//#include "PDObjectChildImpl.h"
#include "PDObjectWithChildrenImpl.h"

class CPDRenderer;

class ATL_NO_VTABLE CPDObject
{
public:
	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY) = 0;
	virtual void CalculateBounds() = 0;
	virtual Gdiplus::RectF GetBounds()
	{
		return Gdiplus::RectF(0,0,0,0);
	}
	/*
	virtual void Render2(Gdiplus::Graphics* graphics)
	{
	}
	*/
};

template <class IBase> class ATL_NO_VTABLE CPDObjectImpl :
	public CPDObject,
	public CPDObjectUnknownImpl<IBase>,
	public CPDObjectWithChildrenImpl<CPDObjectImpl<IBase> >,
	public IObjectSerializable
{
public:
	CPDObjectImpl()
	{
		m_children = NULL;
		m_matrix = NULL;

	// Rendering stuff (uninitialized)
		m_backgroundBitmap = NULL;

		m_expandedBBox.X = 0xacacacac;
		m_expandedBBox.Y = 0xacacacac;
		m_expandedBBox.Width = 0xacacacac;
		m_expandedBBox.Height = 0xacacacac;

		m_scaleX = 0;
		m_scaleY = 0;
	//
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CComObject<CObjectMap>::CreateInstance(&m_children);
		if (FAILED(hr)) return hr;
		m_children->AddRef();

		hr = CComObject<CPDMatrix>::CreateInstance(&m_matrix);
		if (FAILED(hr)) return hr;
		m_matrix->AddRef();

		return S_OK;
	}

	void FinalRelease()
	{
		if (m_children)
		{
			m_children->Release();
			m_children = NULL;
		}

		if (m_matrix)
		{
			m_matrix->Release();
			m_matrix = NULL;
		}

		/*
		m_expandedBBox.X = 0xacacacac;
		m_expandedBBox.Y = 0xacacacac;
		m_expandedBBox.Width = 0xacacacac;
		m_expandedBBox.Height = 0xacacacac;

		m_scaleX = 0;
		m_scaleY = 0;
		*/
	}

	CComObject<CPDMatrix>* m_matrix;

	CComObject<CObjectMap>* m_children;

	RectD m_filterRect;
	RectD m_expandedBBox;
	double m_scaleX;
	double m_scaleY;

	Gdiplus::Bitmap* m_backgroundBitmap;

	void CalculateScale(RectD& expandedRect, IPDMatrix* objectCtm)
	{
		PointD ptxy;
		ptxy.x = expandedRect.X;
		ptxy.y = expandedRect.Y;

		PointD ptx;
		ptx.x = expandedRect.X+expandedRect.Width;
		ptx.y = expandedRect.Y;

		PointD pty;
		pty.x = expandedRect.X;
		pty.y = expandedRect.Y+expandedRect.Height;

		objectCtm->transformPoint(&ptxy, &ptxy);
		objectCtm->transformPoint(&ptx, &ptx);
		objectCtm->transformPoint(&pty, &pty);

		double dx, dy;

		dx = ptx.x-ptxy.x;
		dy = ptx.y-ptxy.y;
		m_scaleX = sqrt(dx*dx + dy*dy) / expandedRect.Width;

		dx = pty.x-ptxy.x;
		dy = pty.y-ptxy.y;
		m_scaleY = sqrt(dx*dx + dy*dy) / expandedRect.Height;
	}

	void attachToSpread(IPDObjectUnknown* parent)
	{
		CComPtr<IPDSpread> spread;
		parent->get_spread(&spread);

		CComPtr<IPDLayer> layer;
		parent->get_layer(&layer);

		CComPtr<IPDDocument> document;
		parent->get_document(&document);

		m_spread = spread;
		m_layer = static_cast<CPDLayer*>(layer.p);
		m_pDocument = static_cast<CPDDocument*>(document.p);

		if (m_children)
		{
			for (int i = 0; i < m_children->m_items.GetSize(); i++)
			{
				CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_children->m_items[i]);
				pObject->attachToSpread(this);
			}
		}
	}

	void detachFromSpread()
	{
		m_layer = NULL;
		m_spread = NULL;

		if (m_children)
		{
			for (int i = 0; i < m_children->m_items.GetSize(); i++)
			{
				CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_children->m_items[i]);
				pObject->detachFromSpread();
			}
		}
	}

public:
	STDMETHOD(getExpandedBBox)(/*[out,retval]*/ RectD* pVal)
	{
		*pVal = m_expandedBBox;
		return S_OK;
	}
	STDMETHOD(get_children)(/*[out, retval]*/ IObjectMap* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_children;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_lastChild)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
//		m_lastChild->QueryInterface(IID_IPDObject, (void**)pVal);
		*pVal = m_lastChild;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_firstChild)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
//		m_firstChild->QueryInterface(IID_IPDObject, (void**)pVal);
		*pVal = m_firstChild;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
#if 0
	STDMETHODIMP saveAsXML(IDOMDocument *document, IDOMNode *node, BOOL saveId)
	{
		CComQIPtr<IDOMElement> element = node;
		if (element)
		{
			if (saveId)
			{
				LPOLESTR guidstr;
				StringFromCLSID(m_uniqId, &guidstr);
				element->setAttribute(L"guid", guidstr);
				CoTaskMemFree(guidstr);
			}

			CComPtr<IDOMNamedNodeMap> attributes;
			element->get_attributes(&attributes);

			ATLASSERT(0);
			/*
			if (m_matrix)
			{
				CComPtr<IDOMAttr> attnode;
				document->createAttribute(L"transform", &attnode);
				m_matrix->saveAsXML(document, attnode, TRUE);
				attributes->setNamedItem(attnode, NULL);
			}
			*/

			return S_OK;
		}
		else
			return E_FAIL;
	}

	STDMETHODIMP loadXML(/*[in]*/ IDOMNode* node)
	{
		CComQIPtr<IDOMElement> element = node;
		if (element)
		{
			BSTR bstrguid;
			element->getAttribute(L"guid", &bstrguid);
			if (bstrguid)
			{
				HRESULT hr = CLSIDFromString(bstrguid, &m_uniqId);
				SysFreeString(bstrguid);

				if (FAILED(hr)) return hr;
			}
			else
			{
				HRESULT hr = ::CoCreateGuid(&m_uniqId);

				if (FAILED(hr)) return hr;
			}

			CComPtr<IDOMNamedNodeMap> attributes;
			element->get_attributes(&attributes);

			ATLASSERT(0);
			/*
			if (m_matrix)
			{
				CComPtr<IDOMAttr> attnode;
				attributes->getNamedItem(L"transform", (IDOMNode**)&attnode);

				m_matrix->loadXML(attnode);
			}
			*/

			return S_OK;
		}
		else
			return E_FAIL;
	}
#endif
	STDMETHOD(getScreenCTM)(/*[out,retval]*/ IPDMatrix* *pVal)
	{
		if (pVal == NULL) return E_POINTER;

		if (m_parent)
		{
			CComPtr<IPDMatrix> parentctm;
			CComQIPtr<IPDObject> parent = m_parent;
			parent->getScreenCTM(&parentctm);

		//	parentctm->multiply(m_matrix, pVal);	// TODO other way around?
			m_matrix->multiply(parentctm, pVal);	// TODO other way around?
		}
		else
		{
			ATLASSERT(m_matrix);

			*pVal = m_matrix;
			(*pVal)->AddRef();
		}

		return S_OK;
	}
//
	STDMETHODIMP clone(/*[out,retval]*/IPDObject* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;

		// Serialize
		{
			CComPtr<IArchive> ar;
			ar.CoCreateInstance(CLSID_Archive);

			CComPtr<IArchiveElement> node;
			if (SUCCEEDED(ar->Open(L"c:\\clone", 1, NULL, &node)))
			{
				node->putObject(static_cast<IBase*>(this));
			}
		}

		//Deserialize
		{
			CComPtr<IArchive> ar;
			ar.CoCreateInstance(CLSID_Archive);

			CComPtr<IArchiveElement> node;
			if (SUCCEEDED(ar->Open(L"c:\\clone", 2, NULL, &node)))
			{
				node->getObject(NULL, (IUnknown**)pVal);
			}
		}

		return S_OK;
	}

// IObjectSerializable
	STDMETHODIMP Serialize(IArchive *ar, IArchiveElement* node)
	{
		return S_OK;
	}

	STDMETHODIMP Deserialize(IArchive *ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		return S_OK;
	}
};
