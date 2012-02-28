#ifndef Web_SVGFilterElement_h
#define Web_SVGFilterElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGFilterElement : 

	public SVGElement,
	public SVGStylableImpl<SVGFilterElement>,
	public SVGLangSpaceImpl<SVGFilterElement>,
//	public ElementEditASImpl<SVGFilterElement>,
	public ElementEditVALImpl<SVGFilterElement>,
//	public SMILAnimationTargetImpl<SVGFilterElement>

	protected AnimatedAttributeT<SVGAnimatedLength, 0>,
	protected AnimatedAttributeT<SVGAnimatedLength, 1>,
	protected AnimatedAttributeT<SVGAnimatedLength, 2>,
	protected AnimatedAttributeT<SVGAnimatedLength, 3>,
	protected AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 4>,
	protected AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 5>
{
public:

	CTOR SVGFilterElement(NamedNodeMap* attributes);

	/*
	double GetFilterX(CPSVGElement* pElement);
	double GetFilterY(CPSVGElement* pElement);
	double GetFilterWidth(CPSVGElement* pElement);
	double GetFilterHeight(CPSVGElement* pElement);
	*/

	AnimatedAttributeT<SVGAnimatedLength, 0>& x_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 0>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedLength, 1>& y_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 1>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedLength, 2>& width_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 2>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedLength, 3>& height_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedLength, 3>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 4>& filterUnits_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 4>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 5>& primitiveUnits_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 5>*>(this);
	}

	ISVGAnimatedEnumeration* get_filterUnits();
	ISVGAnimatedEnumeration* get_primitiveUnits();
	ISVGAnimatedLength* get_x();
	ISVGAnimatedLength* get_y();
	ISVGAnimatedLength* get_width();
	ISVGAnimatedLength* get_height();

	// SVG 1.2
	ImageData apply(ImageData* source);

protected:

	/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

	// TODO build animation list
//		DoAnimation(0,0);	// hm..

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/

	friend class PSVGFilterElement;
	friend class PSVGFEElement;

	inline PSVGFilterElement* GetPElement()
	{
		return (PSVGFilterElement*)m_pNode;
	}

//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_filterUnits;
//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_primitiveUnits;
	/*
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_x;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_y;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_width;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_height;
*/
	/*
	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;
	SVGAnimatedLength* m_width;
	SVGAnimatedLength* m_height;
	*/
};

}	// Web
}	// System

#endif // Web_SVGFilterElement_h
