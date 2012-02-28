#ifndef __DOMERROR_H__
#define __DOMERROR_H__

namespace System
{
namespace Web
{

class WEBEXT DOMError : public Object
{
public:
	CTOR DOMError()
	{
	}

	DOMErrorSeverity get_severity() const
	{
		return m_severity;
	}

	String get_message() const
	{
		return m_message;
	}

	IDOMLocator* get_location() const
	{
		return m_location;
	}

public:

	String m_message;
	IDOMLocator* m_location;
	DOMErrorSeverity m_severity;
};

}	// w3c
}

#endif	// __DOMERROR_H__
