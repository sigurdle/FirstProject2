#ifndef Web_Entity_h
#define Web_Entity_h

namespace System
{
namespace Web
{

class CEntity;

class WEBEXT Entity : public ChildNode
{
public:
	CTOR Entity(StringIn name, StringIn notationName);

	String get_notationName();
	//void set_notationName(StringIn notationName);	// TODO readonly
	String get_publicId();
	String get_systemId();

	virtual String get_nodeName() const override;
	virtual NodeType get_nodeType() const override;
	virtual Node* cloneNode(bool deep) const override;

public:

	String m_name;
	String m_notationName;
	String m_value;

	CEntity* m_pDTDEntity;
};

}	//Web
}

#endif // Web_Entity_h
