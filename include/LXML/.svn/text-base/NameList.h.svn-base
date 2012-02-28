#ifndef w3c_NameList_h
#define w3c_NameList_h

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class WEBEXT NameList : public Object
{
public:
	CTOR NameList();

	class NameItem
	{
	public:
		CTOR NameItem(StringIn name, StringIn namespaceURI)
		{
			m_name = name;
			m_namespaceURI = namespaceURI;
		}

		String m_name;
		String m_namespaceURI;
	};

	unsigned int get_length() const;
	String getName(unsigned int index);
	String getNamespaceURI(unsigned int index);

protected:

	vector<NameItem> m_items;
};

}	// w3c
}

#endif // w3c_NameList_h
