#ifndef w3c_SVGPolylineElement_h
#define w3c_SVGPolylineElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGPolylineElement : 
	public SVGPolygonalShapeElement,
//	public SVGAnimatedPointsImpl<SVGPolylineElement>,
	//public SVGTransformableImpl<SVGPolylineElement>,
	public SVGStylableImpl<SVGPolylineElement>,
	public SVGLangSpaceImpl<SVGPolylineElement>,
//	public ElementEditASImpl<SVGPolylineElement>,
	public ElementEditVALImpl<SVGPolylineElement>,
//	public SMILAnimationTargetImpl<SVGPolylineElement>,
	public CSVGRenderElementImpl<SVGPolylineElement>

//	protected CNotifyGetImpl<SVGPolylineElement>,
//	protected CNotifySendImpl<SVGPolylineElement>
{
public:
	CTOR SVGPolylineElement(NamedNodeMap* attributes);

	PSVGPolylineElement* GetPElement() const
	{
		return (PSVGPolylineElement*)m_pNode;
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

	friend class PSVGPolylineElement;
};

}	// w3c
}

#endif // w3c_SVGPolylineElement_h
