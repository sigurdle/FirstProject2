#ifndef Web_HTMLBodyElement_h
#define Web_HTMLBodyElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLBodyElement : 

	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLBodyElement>,
//	public CLElementEditASImpl<HTMLBodyElement>,
	public ElementEditVALImpl<HTMLBodyElement>
//	public ElementTimeContainerImpl,//<HTMLBodyElement>,
//	public SMILAnimationTargetImpl<HTMLBodyElement>

//	public IElementEditVAL,	// ILNodeEditVAL
//	public IElementTimeContainer,	// ILElementTime
{
public:
	CTOR HTMLBodyElement(NamedNodeMap* attributes);

	virtual double GetImplicitDuration()
	{
		return INDEFINITE;
	}

	String get_timeContainer()
	{
		return WSTR("par");
		/*
		getAttribute(L"timeContainer", pVal);
		if (*pVal == NULL) *pVal = SysAllocString(L"none");
		*/
	}
	void set_timeContainer(StringIn newVal)
	{
		setAttribute(WSTR("timeContainer"), newVal);
	}
};

}	// Web
}

#endif // Web_HTMLBodyElement_h
