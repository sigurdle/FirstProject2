#ifndef Web_SVGGenericElement_h
#define Web_SVGGenericElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGGenericElement : 

	public SVGElement,
	public ElementEditVALImpl<SVGGenericElement>,
	public SVGStylableImpl<SVGGenericElement>
//	public CLElementEditASImpl<SVGGenericElement>,
//	public SMILAnimationTargetImpl<SVGGenericElement>,

//	protected CNotifyGetImpl<SVGGenericElement>,
//	protected CNotifySendImpl<SVGGenericElement>
{
public:
	CTOR SVGGenericElement(StringIn qualifiedName);
	CTOR SVGGenericElement(StringIn qualifiedName, NamedNodeMap* attributes);

};

}	// Web
}

#endif // Web_SVGGenericElement_h
