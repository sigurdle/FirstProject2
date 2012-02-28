#ifndef w3c_EntityReference_h
#define w3c_EntityReference_h

namespace System
{
namespace Web
{

class WEBEXT EntityReference : 
	public ChildNode,
	public EventTarget,
	protected CNotifySendImpl<EntityReference>
{
public:
	CTOR EntityReference();
	~EntityReference();

	String get_nodeName();
	NodeType get_nodeType() const
	{
		return NODE_ENTITY_REFERENCE;
	}

//	STDMETHOD(get_textContent)(/*[out, retval]*/ BSTR *pVal);

	Node* cloneNodeExport(Document* ownerDocument, bool deep) const
	{
		ASSERT(0);
		return NULL;
	}

	String m_notationName;
	String m_value;

	Entity* m_entity;
};

}	// w3c
}

#endif // w3c_EntityReference_h
