#ifndef w3c_SVGLocatableImpl_h
#define w3c_SVGLocatableImpl_h

#include "SVGTransformList.h"
#include "SVGAnimatedTransformList.h"

#include "PSVGElement.h"	// ??

namespace System
{
namespace Web
{

//class SVGElement;

class SVGEXT SVGLocatableImplImpl
{
public:
//	HRESULT getRBBox(CLDOMElementImplImpl* pElement, /*[out,retval]*/ ILSVGRect** pVal);
	virtual ISVGRect* getBBox();
};

template <class T/*, class IBase*/> class SVGLocatableImpl : 
//	public IBase,
	public SVGLocatableImplImpl
{
public:
	CTOR SVGLocatableImpl()
	{
	}

	SVGMatrix* getTransformToElement(SVGElement* element)
	{
		// TODO
		ASSERT(0);
		return NULL;
	}
	SVGMatrix* getScreenCTM()
	{
		VERIFY(0);
		return NULL;
#if 0
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		if (static_cast<T*>(this)->m_pNodes.GetSize() > 0)
		{
			CComObject<SVGMatrix>* p;
			HRESULT hr = CComObject<SVGMatrix>::CreateInstance(&p);
			if (FAILED(hr)) return hr;
			(*pVal = p)->AddRef();
			p->m_matrix = ((CPSVGElementImpl*)static_cast<T*>(this)->m_pNodes[0])->GetScreenCTM();
		}
#endif

		return 0;
#if 0
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		CComQIPtr<ILSVGLocatable> parent = static_cast<T*>(this)->m_parentNode;
		if (parent)
		{
			CComPtr<ILSVGMatrix> parentctm;
			parent->getScreenCTM(&parentctm);

			CComPtr<ILSVGMatrix> ctm;
			getCTM(&ctm);

			ctm->multiply(parentctm, pVal);
		}
		else
		{
			getCTM(pVal);
		}
#endif

		return 0;
	}

	SVGMatrix* getTransformMatrix()
	{
		ASSERT(0);
#if 0
		if (pVal == NULL) return E_POINTER;

		CComObject<SVGMatrix>* pMatrix;
		CComObject<SVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->AddRef();

			*pVal = pMatrix;
		}
#endif

		return NULL;
	}

	SVGMatrix* getCTM()
	{
		ASSERT(0);
		return NULL;
#if 0
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
	
		*pVal = NULL;

		CComObject<SVGMatrix>* pMatrix;
		CComObject<SVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->AddRef();

			CComPtr<ILDOMNode> node = static_cast<T*>(this);
			while (node)
			{
				CComQIPtr<ILSVGTransformable> transformable = node;
				if (transformable)
				{
					CComPtr<ILSVGAnimatedTransformList> atransformlist;
					transformable->get_transform(&atransformlist);

					CComPtr<ILSVGTransformList> transformlist;
					atransformlist->get_animVal(&transformlist);

					gmMatrix3 matrix2 = static_cast<CLSVGTransformList*>(transformlist.p)->consolidate();
	
					pMatrix->m_matrix *= matrix2;

					//pMatrix2->Release();
				}

				CComPtr<ILDOMNode> parentNode;
				node->get_parentNode(&parentNode);

				CComQIPtr<ILSVGFitToViewBox> viewbox = parentNode;
				if (viewbox != NULL)
				{
					// ???
					pMatrix->m_matrix *= ((CPSVGElement*)CComQIPtr<CLDOMElementImplImpl>(parentNode)->m_pNodes[0])->GetViewBoxMatrix();
					break;
				}

				node = parentNode;
			}

			*pVal = pMatrix;
		}
#endif
		return NULL;
	}

#if 0
	STDMETHOD(getRBBox)(/*[out,retval]*/ ILSVGRect* *pVal)
	{
		return SVGLocatableImplImpl::getRBBox(static_cast<T*>(this), pVal);
	}
#endif
	ISVGRect* getBBox()
	{
		ASSERT(0);
		return NULL;//SVGLocatableImplImpl::getBBox(static_cast<T*>(this), pVal);
	}
	SVGElement* get_farthestViewportElement()
	{
		ASSERT(0);
		return NULL;
	}
	SVGElement* get_nearestViewportElement()
	{
		ASSERT(0);
		return 0;
		//return ((ILSVGElement*)static_cast<T*>(this))->get_viewportElement(pVal);
	}

	SVGPoint* convertClientXY(/*[in]*/ int clientXArg, /*[in]*/ int clientYArg)
	{
		VERIFY(0);
		return NULL;
	}
};

}	// w3c
}

#endif // w3c_SVGLocatableImpl_h
