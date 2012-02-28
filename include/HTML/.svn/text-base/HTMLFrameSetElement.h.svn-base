#ifndef Web_HTMLFrameSetElement_h
#define Web_HTMLFrameSetElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLFrameSetElement : 
	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLFrameSetElement>,
//	public CLElementEditASImpl<CLHTMLFrameSetElement>,
	public ElementEditVALImpl<HTMLFrameSetElement>
{
public:
	CTOR HTMLFrameSetElement(NamedNodeMap* attributes);
	~HTMLFrameSetElement();

	String get_rows();
	void set_rows(StringIn newVal);

	String get_cols();
	void set_cols(StringIn newVal);

	Graphics::Color get_borderColorRGBValue();
	void set_borderColorRGBValue(Graphics::Color newVal);

	inline PHTMLFrameSetElement* GetPElement()
	{
		return (PHTMLFrameSetElement*)m_pNode;
	}
};

}	// Web
}

#endif // Web_HTMLFrameSetElement_h
