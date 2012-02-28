#ifndef w3c_SVGTransformableImpl_h
#define w3c_SVGTransformableImpl_h

#include "SVGLocatableImpl.h"

#include "SVGTransformList.h"
#include "SVGAnimatedTransformList.h"

namespace System
{
namespace Web
{

template <class T> class SVGTransformableImpl :
	public SVGLocatableImpl<T>,
	public ISingleObjectListener
{
public:

#if 0
	/*template<class T>*/ static void transformBaseValChanged(Object* obj)
	{
		SVGTransformableImpl<T>* e = (SVGTransformableImpl<T>*)obj;
		ASSERT(0);
	}
#endif

	CTOR SVGTransformableImpl()
	{
	//	static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_transform, NULL, WSTR("transform")));
	//	m_transform->m_baseVal->m_pListener = this;
	}

	~SVGTransformableImpl()
	{
		/*
		if (m_transform)
		{
			m_transform->m_baseVal->m_pListener = NULL;

			m_transform = NULL;
		}
		ASSERT(m_transform == NULL);
		*/
	}

#if 0
	virtual void OnChanged(CSingleObject* pObject)
	{
		// ??
		ASSERT(0);
		//m_transform->m_animated->m_pAttr->OnBaseValChanged();
	}
#endif

// ISVGLocatable
#if 0
	STDMETHOD(getCTM)(/*[out,retval]*/ ILSVGMatrix** pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		CComObject<SVGMatrix>* pMatrix = static_cast<T*>(this)->m_transform->m_animated->m_animVal->m_value->consolidate();	// This AddRefs
		*pVal = pMatrix;

		return S_OK;
	}
#endif

	SVGMatrix* getTransformMatrix()
	{
		VERIFY(0);
		return NULL;
#if 0
		CComObject<SVGMatrix>* pMatrix;
		CComObject<SVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->m_matrix = static_cast<T*>(this)->m_transform->m_animated->m_animVal->m_value->consolidate();
		}
		*pVal = pMatrix;

		return S_OK;
#endif
	}

// ISVGTransformable
	SVGAnimatedTransformList* get_transform()
	{
		return m_transform;
	}

	Attr* m_transformAttr;
	SVGAnimatedTransformList* m_transform;
};

}	// w3c
}

#endif // w3c_SVGTransformableImpl_h
