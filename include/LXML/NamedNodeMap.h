#ifndef Web_NamedNodeMap_h
#define Web_NamedNodeMap_h

namespace System
{
namespace Web
{

interface INamedNodeMapListener
{
	virtual void OnAddedNode(NamedNodeMap* nodemap, Node* node) = 0;
	virtual void OnRemoveNode(NamedNodeMap* nodemap, Node* node) = 0;
};

class WEBEXT NamedNodeMap : public Object
{
public:

	CTOR NamedNodeMap();
	~NamedNodeMap();

	unsigned int get_length() const throw();
	Node* item(unsigned int index) const throw(ArgumentOutOfRangeException);
	Node* getNamedItem(StringIn name) const;
	Node* getNamedItemNS(StringIn namespaceURI, StringIn localName) const;
	Node* setNamedItem(Node* node);
	Node* setNamedItemNS(Node* node);
	Node* removeNamedItem(StringIn name);
	Node* removeNamedItemNS(StringIn namespaceURI, StringIn localName);

public:

	INamedNodeMapListener* m_pListener;
	vector<Node*> m_items;
};

}	// Web
}

#endif // Web_NamedNodeMap_h
