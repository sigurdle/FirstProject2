#ifndef Web_SVGSwitchElement_h
#define Web_SVGSwitchElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGSwitchElement : 

	public SVGTransformableElement,
	//public SVGTransformableImpl<SVGSwitchElement>,
	public SVGStylableImpl<SVGSwitchElement>,
	public SVGTestsImpl<SVGSwitchElement>,
	public SVGLangSpaceImpl<SVGSwitchElement>,
//	public SMILAnimationTargetImpl<SVGSwitchElement>,
	public CSVGRenderElementImpl<SVGSwitchElement>,
	public ElementEditVALImpl<SVGSwitchElement>

//	protected CNotifyGetImpl<SVGSwitchElement>,
//	protected CNotifySendImpl<SVGSwitchElement>
{
public:

	CTOR SVGSwitchElement(NamedNodeMap* attributes);

	Element* SelectElement();
	void UpdateSelectedElement();

	Element* getSelectedElement();

	Element* m_selectedElement;

protected:

	/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		UpdateSelectedElement();

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/
};

}	// Web
}

#endif // Web_SVGSwitchElement_h
