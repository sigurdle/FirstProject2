#ifndef Web_HTMLSelectElement_h
#define Web_HTMLSelectElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLSelectElement : 

	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLSelectElement>,
//	public CLElementEditASImpl<HTMLSelectElement>,
	public ElementEditVALImpl<HTMLSelectElement>,

//	public ILElementCSSInlineStyle,
//	public ILElementEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<HTMLSelectElement>,
	public CNotifySendImpl<HTMLSelectElement>
{
public:

	CTOR HTMLSelectElement(NamedNodeMap* attributes);
	~HTMLSelectElement();

	System::StringW* get_type();
	int get_selectedIndex();
	void set_selectedIndex(int newVal);
	System::StringW* get_value();
	void set_value(System::StringW* newVal);
	bool get_multiple();
	void set_multiple(bool newVal);
	int get_length() const;
	void set_length(int newVal);
	int get_size();
	void set_size(int newVal);
	void remove(int index);

protected:

	int m_selectedIndex;
};

}	// Web
}

#endif // Web_HTMLSelectElement_h
