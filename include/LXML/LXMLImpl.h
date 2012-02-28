#ifndef __XMLIMPL_H__
#define __XMLIMPL_H__

namespace System
{
namespace Web
{

interface IXMLImplementation
{
	virtual Element* CreateElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes) = 0;
};

}	// Web
}

#endif
