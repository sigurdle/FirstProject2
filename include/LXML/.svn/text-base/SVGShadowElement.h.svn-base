#ifndef __SVGSHADOWELEMENT_H__
#define __SVGSHADOWELEMENT_H__

//#include "resource.h"       // main symbols

//#include "DOMElement.h"
#include "ElementEditVALImpl.h"
//#include "LDOMEventTarget.h"
//#include "LElementEditASImpl.h"

namespace System
{
namespace Web
{

class WEBEXT SVGShadowElement : 

	public Element,
//	public CLElementEditASImpl<CLSVGShadowElement>,
	public ElementEditVALImpl<SVGShadowElement>,

//	public ILElementEditVAL, // ILNodeEditVAL

	protected CNotifyGetImpl<SVGShadowElement>,
	protected CNotifySendImpl<SVGShadowElement>
{
public:
	CTOR SVGShadowElement() : Element(NULL)
	{
		m_shadowOwnerElement = NULL;
	}

	Element* getElementById(StringIn elementId);

	Element* getShadowOwnerElement()
	{
		return m_shadowOwnerElement;
	}

	Element* m_shadowOwnerElement;

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
};

} // Web
}

#endif // __SVGShadowElement_H__
