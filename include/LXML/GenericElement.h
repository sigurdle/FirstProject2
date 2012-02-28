#ifndef w3c_GenericElement_h
#define w3c_GenericElement_h

namespace System
{
namespace Web
{

class WEBEXT GenericElement : 
	public Element,
//	public CLElementEditASImpl<GenericElement>,
	public ElementEditVALImpl<GenericElement>
//	public CLSVGShadowableImpl,
{
public:
	CTOR GenericElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName);
	CTOR GenericElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes);

	virtual String get_namespaceURI() const override;

	//PElement* m_pElement;
};

}	// w3c
}

#endif // w3c_GenericElement_h
