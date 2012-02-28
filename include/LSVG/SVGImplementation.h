#ifndef Web_SVGImplementation_h
#define Web_SVGImplementation_h

namespace System
{
namespace Web
{

class SVGImplementation : 
	public Object,
	public IXMLImplementation
{
public:
	CTOR SVGImplementation();

	Element* createSVGElement(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);
	Element* createSVGElementShapes(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);
	Element* createSVGElementFilters(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);
	Element* createSVGElementTextFonts(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);
	Element* createSVGElementAnimation(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);

// IXMLImplementation
public:
	Element* CreateElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);
};

}	// Web
}

#endif // Web_SVGImplementation_h
