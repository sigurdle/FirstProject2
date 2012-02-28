#include "stdafx.h"
#include "LFC.h"

namespace System
{

Guid::Guid(StringIn str)
{
	if (UuidFromString((RPC_WSTR)str.c_strw(), &m_guid) != RPC_S_OK)
	{
		raise(SystemException("UuidFromString failed"));
	}
}

String Guid::ToString()
{
	WCHAR* p;
	UuidToStringW(&m_guid, &p);
	String s(p);
	RpcStringFree(&p);
	return s;
}

uint32 Guid::GetHashCode()
{
	ASSERT(0);
	return 0;
}

// static
Guid Guid::Parse(StringIn str)
{
	GUID guid;
	if (UuidFromString((RPC_WSTR)str.c_strw(), &guid) != RPC_S_OK)
	{
		raise(SystemException("UuidFromString failed"));
	}
	return guid;
}

// static
Guid Guid::NewGuid()
{
	GUID guid;
	ThrowHr hr = CoCreateGuid(&guid);
	return guid;
}

}	// System
