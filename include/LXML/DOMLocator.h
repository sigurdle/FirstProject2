#ifndef __DOMLOCATOR_H__
#define __DOMLOCATOR_H__

namespace System
{
namespace Web
{

class DOMLocator :
	public Object,
	public IDOMLocator
{
public:
	CTOR DOMLocator()
	{
		m_columnNumber = -1;
		m_lineNumber = -1;
		m_offset = -1;
		m_uri = nullptr;
	}

//	STDMETHOD(setOffset)(/*[in]*/ long newVal);
	long get_offset();
//	STDMETHOD(setLineColumn)(/*[in]*/ long lineNumber, /*[in]*/ long columnNumber);
	Node* getNode();
//	STDMETHOD(getSystemID)(/*[out,retval]*/ BSTR* pVal);
//	STDMETHOD(getPublicID)(/*[out,retval]*/ BSTR* pVal);
	int get_lineNumber();
	int get_columnNumber();
	String get_uri() const
	{
		return m_uri;
	}

public:

	String m_uri;
	int m_offset;
	int m_columnNumber;
	int m_lineNumber;
};

}	// w3c
}

#endif
