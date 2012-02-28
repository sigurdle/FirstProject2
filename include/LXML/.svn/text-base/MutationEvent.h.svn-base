#ifndef w3c_MutationEvent_h
#define w3c_MutationEvent_h

namespace System
{
namespace Web
{

enum DOMAttrChangeType
{
	CHANGE_UNKNOWN = 0,
	CHANGE_MODIFICATION = 1,
	CHANGE_ADDITION = 2,
	CHANGE_REMOVAL = 3
};

class WEBEXT MutationEvent : public Event
{
public:
	CTOR MutationEvent();

	Node* get_relatedNode() const;
	String get_prevValue() const;
	String get_newValue() const;
	String get_attrName() const;
	DOMAttrChangeType get_attrChange() const;
	void initMutationEvent(StringIn typeArg, bool canBubbleArg, bool cancelableArg, Node* relatedNodeArg, StringIn prevValueArg, StringIn newValueArg, StringIn attrNameArg, DOMAttrChangeType attrChangeArg);

protected:

	String m_prevValue;
	String m_newValue;
	String m_attrName;
	Node* m_relatedNode;
	DOMAttrChangeType m_attrChange;
};

}	// w3c
}

#endif	// w3c_MutationEvent_h
