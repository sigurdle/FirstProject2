#ifndef __LSMILROOTLAYOUTELEMENT_H_
#define __LSMILROOTLAYOUTELEMENT_H_

namespace System
{
namespace Web
{

class HTMLEXT SMILRootLayoutElement : 

	public SMILElement,
	public SMILElementLayoutImpl<SMILRootLayoutElement>,
	public SMILAnimationTargetImpl<SMILRootLayoutElement>,

	protected CNotifyGetImpl<SMILRootLayoutElement>,
	protected CNotifySendImpl<SMILRootLayoutElement>
{
public:
	CTOR SMILRootLayoutElement(NamedNodeMap* attributes);

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

public:

	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CColorValue> > > >, CValueTypeWrapper<CreateInstanceT<CColorValue> > >* m_backgroundColor;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<LongValue> > > >, CValueTypeWrapper<CreateInstanceT<LongValue> > >* m_width;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<LongValue> > > >, CValueTypeWrapper<CreateInstanceT<LongValue> > >* m_height;
};

}	// Web
}

#endif //__LSMILROOTLAYOUTELEMENT_H_
