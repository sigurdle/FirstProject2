#ifndef Web_SVGPolygonElement_h
#define Web_SVGPolygonElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGPolygonElement : 
	public SVGPolygonalShapeElement,
	//public SVGAnimatedPointsImpl<SVGPolygonElement>,
	//public SVGTransformableImpl<SVGPolygonElement>,
	public SVGStylableImpl<SVGPolygonElement>,
	public SVGLangSpaceImpl<SVGPolygonElement>,
//	public ElementEditASImpl<SVGPolygonElement>,
	public ElementEditVALImpl<SVGPolygonElement>,
//	public SMILAnimationTargetImpl<SVGPolygonElement>,
	public CSVGRenderElementImpl<SVGPolygonElement>

//	protected CNotifyGetImpl<SVGPolygonElement>,
//	protected CNotifySendImpl<SVGPolygonElement>
{
public:

	CTOR SVGPolygonElement(NamedNodeMap* attributes);

	PSVGPolygonElement* GetPElement() const
	{
		return (PSVGPolygonElement*)m_pNode;
	}

protected:

#if 0
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

	/*
		if (IsUnknownEqualUnknown(targetObject, m_pcx->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"cx");
		}
		else if (IsUnknownEqualUnknown(targetObject, m_pcy->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"cy");
		}
		else if (IsUnknownEqualUnknown(targetObject, m_prx->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"rx");
		}
		else if (IsUnknownEqualUnknown(targetObject, m_pry->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"ry");
		}
		*/

	// TODO build animation list
		//BuildElementAnimationList(this, ILDOMElement* parent);
#if 0
		DoAnimation(0,0);	// hm..
		CalculateBounds();
#endif

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
#endif

	/*
#ifndef __LERSTAD__
	AttrCallbacks(SVGPolygonElement, points)
#endif
	*/

	friend class PSVGPolygonElement;
//	PSVGPolygonElement* m_pElement;
};

}	// w3c
}

#endif // Web_SVGPolygonElement_h
