#ifndef Web_NodeList_h
#define Web_NodeList_h

namespace System
{
namespace Web
{

class WEBEXT NodeList : public Object
{
public:

	CTOR NodeList();
	~NodeList();

	unsigned int get_length() const;
	ChildNode* item(unsigned int index) const;

public:

	vector<ChildNode*> m_items;
};

}	// Web
}

#endif // Web_NodeList_h
