#ifndef Web_HTMLAnchorElement_h
#define Web_HTMLAnchorElement_h

//#include "resource.h"       // main symbols

//#include "HTMLElement.h"
//#include "LElementEditASImpl.h"

namespace System
{
namespace Web
{

class HTMLEXT HTMLAnchorElement : 

	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLAnchorElement>,
//	public CLElementEditASImpl<CLHTMLAnchorElement>,
	public ElementEditVALImpl<HTMLAnchorElement>,

	//public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<HTMLAnchorElement>,
	protected CNotifySendImpl<HTMLAnchorElement>
{
public:
	CTOR HTMLAnchorElement(NamedNodeMap* attributes);
	~HTMLAnchorElement();

	String get_accessKey();
	void set_accessKey(StringIn newVal);
	String get_charset();
	void set_charset(StringIn newVal);
	String get_coords();
	void set_coords(StringIn newVal);
	String get_href();
	void set_href(StringIn newVal);
	String get_hreflang();
	void set_hreflang(StringIn newVal);
//	[propget, helpstring("property name")] HRESULT name([out, retval] BSTR *pVal);
//	[propput, helpstring("property name")] HRESULT name([in] BSTR newVal);
	String get_rel();
	void set_rel(StringIn newVal);
	String get_rev();
	void set_rev(StringIn newVal);
	String get_shape();
	void set_shape(StringIn newVal);
	String get_tabIndex();
	void set_tabIndex(StringIn newVal);
	String get_target();
	void set_target(StringIn newVal);
	String get_type();
	void set_type(StringIn newVal);

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

	static ImmutableString<WCHAR> href_str;
};

}	// Web
}

#endif // Web_HTMLAnchorElement_h
