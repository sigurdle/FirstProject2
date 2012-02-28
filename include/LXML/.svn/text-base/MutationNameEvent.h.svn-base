#ifndef w3c_MutationNameEvent_h
#define w3c_MutationNameEvent_h

namespace System
{
namespace Web
{

class WEBEXT MutationNameEvent : public MutationEvent
{
public:
	CTOR MutationNameEvent();

	String get_prevNamespaceURI() const;

	String get_prevNodeName() const;

	void initMutationNameEventNS(
		StringIn namespaceURI,
		StringIn typeArg,
		bool canBubbleArg,
		bool cancelableArg,
		Node* relatedNodeArg,
		StringIn prevNamespaceURI,
		StringIn prevNodeName);

protected:

	String m_prevNamespaceURI;
	String m_prevNodeName;
};

}	// w3c
}

#endif // w3c_MutationNameEvent_h
