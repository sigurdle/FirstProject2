#ifndef Web_HTMLParamElement_h
#define Web_HTMLParamElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLParamElement : 
	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLParamElement>,
//	public CLElementEditASImpl<HTMLParamElement>,
	public ElementEditVALImpl<HTMLParamElement>
//	public IElementEditVAL	// ILNodeEditVAL
{
public:

	CTOR HTMLParamElement(NamedNodeMap* attributes);
	~HTMLParamElement();

	String get_name();
	void set_name(StringIn newVal);

	String get_type();
	void set_type(StringIn newVal);

	String get_value();
	void set_value(StringIn newVal);

	String get_valueType();
	void set_valueType(StringIn newVal);
};

}	// Web
}

#endif // Web_HTMLParamElement_h
