#ifndef SVGURIReferenceImpl_h
#define SVGURIReferenceImpl_h

namespace System
{
namespace Web
{

extern ImmutableString<WCHAR> xlinkNamespaceURI;

template <class T> class SVGURIReferenceImpl :
	public ISVGURIReference,
//	public SVGURIReferenceImplImpl,
	public AnimatedAttributeT<SVGAnimatedString>
{
public:
	CTOR SVGURIReferenceImpl() :
		AnimatedAttributeT<SVGAnimatedString>(static_cast<T*>(this), &xlinkNamespaceURI, WSTR("href"))
	{
	//	static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_href, xlinkNamespaceURI, WSTR("href")));
	}

	AnimatedAttributeT<SVGAnimatedString>& href_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedString>*>(this);
	}

	ISVGAnimatedString* get_href()
	{
		return href_attr();
	}
};

}	// Web
}	// System

#endif // SVGURIReferenceImpl_h
