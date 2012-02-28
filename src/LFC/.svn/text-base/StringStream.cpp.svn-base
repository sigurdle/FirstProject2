#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

	/*
StringStream::StringStream(const StringBuilder& builder)
{
	if (m_streamObject != other.m_streamObject)
	{
		if (other.m_streamObject) other.m_streamObject->IncRef();
		if (m_streamObject) m_streamObject->DecRef();
		m_streamObject = other.m_streamObject;
	}
	return *this;
}
*/

StringWriter& StringWriter::operator = (const StringWriter& other)
{
	/*
	if (m_streamObject != other.m_streamObject)
	{
		if (other.m_streamObject) other.m_streamObject->IncRef();
		if (m_streamObject) m_streamObject->DecRef();
		m_streamObject = other.m_streamObject;
	}
	*/
	m_str = other.m_str;
	return *this;
}

}	// IO
}	// System
