#ifndef w3c_SVGForeignObjectElement_h
#define w3c_SVGForeignObjectElement_h

#include "PSVGForeignObjectElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGForeignObjectElement : 
	public SVGTransformableElement,
	//public SVGTransformableImpl<SVGForeignObjectElement>,
	public SVGStylableImpl<SVGForeignObjectElement>,
	public SVGLangSpaceImpl<SVGForeignObjectElement>,
//	public ElementEditASImpl<SVGForeignObjectElement>,
	public ElementEditVALImpl<SVGForeignObjectElement>,
//	public SMILAnimationTargetImpl<SVGForeignObjectElement>,
	public CSVGRenderElementImpl<SVGForeignObjectElement>

//	protected CNotifyGetImpl<SVGForeignObjectElement>,
//	protected CNotifySendImpl<SVGForeignObjectElement>
{
public:
	CTOR SVGForeignObjectElement(NamedNodeMap* attributes);

	SVGAnimatedLength* get_x();
	SVGAnimatedLength* get_y();
	SVGAnimatedLength* get_width();
	SVGAnimatedLength* get_height();

	inline PSVGForeignObjectElement* GetPElement()
	{
		return (PSVGForeignObjectElement*)m_pNode;
	}

protected:

	friend class PSVGForeignObjectElement;

	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;
	SVGAnimatedLength* m_width;
	SVGAnimatedLength* m_height;

	/*
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_x;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_y;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_width;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_height;
	*/

#if 0
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

	// TODO build animation list
		//BuildElementAnimationList(this, ILDOMElement* parent);
		DoAnimation(0,0);	// hm..
#if 0
		CalculateBounds();
#endif
		*/

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
#endif
};

}	// w3c
}

#endif // w3c_SVGForeignObjectElement_h
