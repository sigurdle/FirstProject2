#ifndef Web_HTMLFormElement_h
#define Web_HTMLFormElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLFormElement : 
	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLFormElement>,
//	public CLElementEditASImpl<HTMLFormElement>,
	public ElementEditVALImpl<HTMLFormElement>

//	public IElementCSSInlineStyle,
//	public IElementEditVAL,	// ILNodeEditVAL
{
public:

	CTOR HTMLFormElement(NamedNodeMap* attributes);
	~HTMLFormElement();

	void submit();
	void reset();

	System::StringW* get_action();
	void set_action(System::StringW* newVal);

	System::StringW* get_name();
	void set_name(System::StringW* newVal);

	System::StringW* get_method();
	void set_method(System::StringW* newVal);

	System::StringW* get_target();
	void set_target(System::StringW* newVal);
};

}	// Web
}

#endif // Web_HTMLFormElement_h
