#ifndef Web_HTMLCanvasElement_h
#define Web_HTMLCanvasElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLCanvasElement :
	public HTMLElement,
	public IWebCanvas,
	public IImageProviderElement,
	public ElementCSSInlineStyleImpl<HTMLCanvasElement>
{
public:
	CTOR HTMLCanvasElement(NamedNodeMap* attributes);
	~HTMLCanvasElement();

	unsigned int get_width();
	unsigned int get_height();

	String toDataURL();
	String toDataURL(StringIn type/*, [Variadic] in any args*/);

	virtual Object* getContext(StringIn contextId);
	virtual Object* getContext(StringIn contextId, Object* contextAttributes);

	virtual gm::Sizei GetImageSize() override;

private:

	ICanvasRenderingContext* m_currentContext;

	WebGLRenderingContext* m_webglContext;
	CanvasRenderingContext2D* m_context2d;
};

}	// Web
}

#endif // w3c_HTMLCanvasElement_h
