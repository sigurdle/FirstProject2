#ifndef Web_HTMLGenericElement_h
#define Web_HTMLGenericElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLGenericElement : 

	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLGenericElement>,
//	public CLElementEditASImpl<HTMLGenericElement>,
	public ElementEditVALImpl<HTMLGenericElement>,
//	public ElementTimeContainerImpl,//<HTMLGenericElement>,
	public SMILAnimationTargetImpl<HTMLGenericElement>
{
public:
	CTOR HTMLGenericElement(StringIn qualifiedName);
	CTOR HTMLGenericElement(StringIn qualifiedName, NamedNodeMap* attributes);

	String get_timeContainer();
	void set_timeContainer(StringIn newVal);
};

}	// Web
}

#endif // Web_HTMLGenericElement_h
