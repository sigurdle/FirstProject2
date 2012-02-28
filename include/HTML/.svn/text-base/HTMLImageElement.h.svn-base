#ifndef Web_HTMLImageElement_h
#define Web_HTMLImageElement_h

namespace System
{
namespace Web
{

//class CImage;

class HTMLEXT HTMLImageElement : 
	public HTMLElement,
	public IImageProviderElement,
	public ElementCSSInlineStyleImpl<HTMLImageElement>,
//	public ElementEditASImpl<HTMLImageElement>,
	public ElementEditVALImpl<HTMLImageElement>

//	public IElementCSSInlineStyle,
//	public IElementEditVAL,	// INodeEditVAL
{
public:
	CTOR HTMLImageElement(NamedNodeMap* attributes);
	~HTMLImageElement();

	int get_width();
	void set_width(int newVal);
	int get_height();
	void set_height(int newVal);
	String get_src();
	void set_src(StringIn newVal);

	Attr* get_widthAttr()
	{
		return m_widthAttr;
	}

	Attr* get_heightAttr()
	{
		return m_heightAttr;
	}

	Attr* get_srcAttr()
	{
		return m_srcAttr;
	}

	virtual gm::Sizei GetImageSize() override;
	CImage* GetImage();

protected:

	friend DWORD WINAPI ThreadFunc(void* lpParameter);

	int ReadJPEG(IO::Stream* stream);
	int ReadPNG(IO::Stream* stream);
	int ReadGIF(IO::Stream* stream);

	Attr* m_widthAttr;
	Attr* m_heightAttr;
	Attr* m_srcAttr;

	CImage* m_pImage;
};

}	// Web
}

#endif // Web_HTMLImageElement_h
