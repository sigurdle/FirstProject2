#ifndef Web_SVGPathElement_h
#define Web_SVGPathElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGPathElement : 

	public SVGTransformableElement,
	public SVGAnimatedPathDataImpl<SVGPathElement>,
	//public SVGTransformableImpl<SVGPathElement>,
	public SVGStylableImpl<SVGPathElement>,
	public SVGLangSpaceImpl<SVGPathElement>,
	public SVGTestsImpl<SVGPathElement>,
	public ElementEditVALImpl<SVGPathElement>,
//	public SMILAnimationTargetImpl<SVGPathElement>,
	public CSVGRenderElementImpl<SVGPathElement>

//	protected CNotifyGetImpl<SVGPathElement>,
//	protected CNotifySendImpl<SVGPathElement>
{
public:
	CTOR SVGPathElement();

#if 0
	STDMETHOD(createSVGPathSegCurvetoQuadraticSmoothRel)(/*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegCurvetoQuadraticSmoothRel** pVal);
	STDMETHOD(createSVGPathSegCurvetoQuadraticSmoothAbs)(/*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegCurvetoQuadraticSmoothAbs** pVal);
	STDMETHOD(createSVGPathSegCurvetoCubicSmoothRel)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x2, /*[in]*/ double y2, /*[out,retval]*/ ILSVGPathSegCurvetoCubicSmoothRel** pVal);
	STDMETHOD(createSVGPathSegCurvetoCubicSmoothAbs)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x2, /*[in]*/ double y2, /*[out,retval]*/ ILSVGPathSegCurvetoCubicSmoothAbs** pVal);
	STDMETHOD(createSVGPathSegLinetoVerticalRel)(/*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegLinetoVerticalRel** pVal);
	STDMETHOD(createSVGPathSegLinetoVerticalAbs)(/*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegLinetoVerticalAbs** pVal);
	STDMETHOD(createSVGPathSegLinetoHorizontalRel)(/*[in]*/ double x, /*[out,retval]*/ ILSVGPathSegLinetoHorizontalRel** pVal);
	STDMETHOD(createSVGPathSegLinetoHorizontalAbs)(/*[in]*/ double x, /*[out,retval]*/ ILSVGPathSegLinetoHorizontalAbs** pVal);
	STDMETHOD(createSVGPathSegCurvetoQuadraticRel)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[out,retval]*/ ILSVGPathSegCurvetoQuadraticRel** pVal);
	STDMETHOD(createSVGPathSegCurvetoQuadraticAbs)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[out,retval]*/ ILSVGPathSegCurvetoQuadraticAbs** pVal);
	STDMETHOD(createSVGPathSegCurvetoCubicRel)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2, /*[out,retval]*/ ILSVGPathSegCurvetoCubicRel** ppResult);
	STDMETHOD(createSVGPathSegCurvetoCubicAbs)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2, /*[out,retval]*/ ILSVGPathSegCurvetoCubicAbs** ppResult);
	STDMETHOD(createSVGPathSegLinetoRel)(/*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegLinetoRel** ppResult);
	STDMETHOD(createSVGPathSegLinetoAbs)(/*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegLinetoAbs** ppResult);
	STDMETHOD(createSVGPathSegMovetoRel)(/*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegMovetoRel** ppResult);
	STDMETHOD(createSVGPathSegMovetoAbs)(/*[in]*/ double x, /*[in]*/ double y, /*[out,retval]*/ ILSVGPathSegMovetoAbs** ppResult);
	STDMETHOD(createSVGPathSegClosePath)(/*[out,retval]*/ ILSVGPathSegClosePath** ppResult);
	STDMETHOD(get_pathSegList)(ILSVGPathSegList* *pVal)
	{
		return CLSVGAnimatedPathDataImpl<SVGPathElement>::get_pathSegList(pVal);
	}
	STDMETHOD(get_normalizedPathSegList)(ILSVGPathSegList* *pVal)
	{
		return CLSVGAnimatedPathDataImpl<SVGPathElement>::get_normalizedPathSegList(pVal);
	}
	STDMETHOD(get_animatedPathSegList)(ILSVGPathSegList* *pVal)
	{
		return CLSVGAnimatedPathDataImpl<SVGPathElement>::get_animatedPathSegList(pVal);
	}
	STDMETHOD(get_animatedNormalizedPathSegList)(ILSVGPathSegList* *pVal)
	{
		return CLSVGAnimatedPathDataImpl<SVGPathElement>::get_animatedNormalizedPathSegList(pVal);
	}
#endif

protected:

#if 0
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
#if 0
		if (IsUnknownEqualUnknown(targetObject, m_d->m_animated->m_baseVal->m_seglist->GetUnknown()))
		{
		//	SetAttribute(L"", L"d");
			m_d->SetAttribute(this);
		}
		else if (IsUnknownEqualUnknown(targetObject, m_d->m_animated->m_baseVal->m_normalizedseglist->GetUnknown()))
		{
			_bstr_t d =  m_d->m_animated->m_baseVal->m_normalizedseglist->StringFromPathSegList();
			m_d->m_animated->m_baseVal->m_seglist->ParsePathData(d);//this, , (BSTR)d);

			m_d->SetAttribute(this);
		}

	// TODO build animation list
		//BuildElementAnimationList(this, ILDOMElement* parent);
		DoAnimation(0,0);	// hm..

		{
			for (int i = 0; i < m_pElements.GetSize(); i++)
			{
				CPSVGElementImpl* pElement = (CPSVGElementImpl*)m_pElements[i];
				pElement->CalculateBounds();
			}
		}
#endif
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
#endif

	friend class PSVGPathElement;
};

}	// Web
}	// System

#endif // w3c_SVGPathElement_h
