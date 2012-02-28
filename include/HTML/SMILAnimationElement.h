#ifndef w3c_SMILAnimationElement_h
#define w3c_SMILAnimationElement_h

namespace System
{
namespace Web
{

class HTMLEXT SMILAnimationElement : public SMILElement
{
public:
	CTOR SMILAnimationElement(PElementBase* pelement, NamedNodeMap* attributes) : SMILElement(pelement, attributes)
	{
		m_animateImpl = new ElementAnimate(this);
	}

	ElementAnimate* m_animateImpl;
};

}	// Web
}

#endif // w3c_SMILAnimationElement_h
