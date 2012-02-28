#ifndef __SVGEXTENSIONDEFSELEMENT_H__
#define __SVGEXTENSIONDEFSELEMENT_H__

//#include "resource.h"       // main symbols

//#include "LSVGExtensionDefsElement.h"

namespace System
{
namespace Web
{

class SVGElementDefElement;

class SVGEXT SVGExtensionDefsElement : 

	public SVGElement,
	public SVGStylableImpl<SVGExtensionDefsElement>,
//	public ElementEditASImpl<SVGExtensionDefsElement>,
	public ElementEditVALImpl<SVGExtensionDefsElement>,
	public SMILAnimationTargetImpl<SVGExtensionDefsElement>,

	public IElementEditVAL,	// INodeEditVAL

	protected CNotifyGetImpl<SVGExtensionDefsElement>,
	protected CNotifySendImpl<SVGExtensionDefsElement>
{
public:
	CTOR SVGExtensionDefsElement() : SVGElement(new PElementBase(this))
	{
		m_hrefDocument = NULL;
		SetAllValues(this);	// ???
	}

	Document* m_hrefDocument;
#if 0
	CComPtr<CLSVGExtensionDefsElement> m_extensionDefsElement;
#endif

//	LXML::ILElementBehaviorFactory* m_factory;

	SVGElementDefElement* GetElementDef(StringIn namespaceURI, StringIn name);

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
};

}	// Web
}

#endif // __SVGExtensionDefsElement_H__
