#ifndef Web_SVGUseElement_h
#define Web_SVGUseElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGUseElement : 

	public SVGTransformableElement,
	public SVGURIReferenceImpl<SVGUseElement>,
//	public SVGTransformableImpl<SVGUseElement>,
	public SVGStylableImpl<SVGUseElement>,
//	public ElementEditASImpl<SVGUseElement>,
	public ElementEditVALImpl<SVGUseElement>,
	public SMILAnimationTargetImpl<SVGUseElement>,
	public CSVGRenderElementImpl<SVGUseElement>,

//	public ISVGTransformable,	// ??
//	public IElementEditVAL,	// INodeEditVAL

	protected CNotifyGetImpl<SVGUseElement>,
	protected CNotifySendImpl<SVGUseElement>
{
public:
	CTOR SVGUseElement(NamedNodeMap* attributes);
	~SVGUseElement();

	SVGElementInstance* GetInstanceRoot();
	SVGElementInstance* GetAnimatedInstanceRoot();

	SVGAnimatedLength* get_x();
	SVGAnimatedLength* get_y();
	SVGAnimatedLength* get_width();
	SVGAnimatedLength* get_height();
	SVGElementInstance* get_instanceRoot();
	SVGElementInstance* get_animatedInstanceRoot();

	/*
// ISVGLocatable
	SVGElement* get_nearestViewportElement();
	SVGElement* get_farthestViewportElement();
	ISVGRect* getBBox();
	SVGMatrix* getCTM();
	SVGMatrix* getScreenCTM();
	SVGMatrix* getTransformToElement(SVGElement* element);
	SVGMatrix* getTransformMatrix();
	*/

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
// TODO, test all these in a generic way in CAnimationTarget
	/*
		if (IsUnknownEqualUnknown(targetObject, m_px->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"x");
		}
		else if (IsUnknownEqualUnknown(targetObject, m_py->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"y");
		}
		else if (IsUnknownEqualUnknown(targetObject, m_pwidth->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"width");
		}
		else if (IsUnknownEqualUnknown(targetObject, m_pheight->m_baseVal.m_length->GetUnknown()))
		{
			SetAttribute(L"", L"height");
		}
		*/

	// TODO build animation list
		//BuildElementAnimationList(this, ILDOMElement* parent);
	/*
		DoAnimation(0,0);	// hm..

		{
			for (int i = 0; i < m_pElements.GetSize(); i++)
			{
				CPSVGElement* pElement = (CPSVGElement*)m_pElements[i];
				pElement->CalculateBounds();
			}
		}
*/
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

	SVGElementInstance* m_instanceRoot;
	SVGElementInstance* m_animatedInstanceRoot;

	friend class PSVGUseElement;

	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;
	SVGAnimatedLength* m_width;
	SVGAnimatedLength* m_height;
};

}	// Web
}

#endif // Web_SVGUseElement_h
