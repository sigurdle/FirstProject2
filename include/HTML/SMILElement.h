#ifndef Web_SMILElement_h
#define Web_SMILElement_h

namespace System
{
namespace Web
{

class HTMLEXT SMILElement : public Element
{
public:
	CTOR SMILElement(PElementBase* pelement, NamedNodeMap* attributes) : Element(pelement, attributes)
	{
	}
};

}	// Web
}

#endif // Web_SMILElement_h
