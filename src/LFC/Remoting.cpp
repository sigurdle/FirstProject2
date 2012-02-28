#include "stdafx.h"
#include "LFC.h"
#include "Remoting.h"

namespace System
{
namespace Remoting
{

uint32 this_serverID;
map<const void*, PerObject*> perobject;
list<PerObject*> m_writeUnlockObjects;

	/*

  Two models

  1:
  all clients have a list to all the other clients

  2: A client only knows about one server, that server knows about all the clients

	*/

class Server
{
public:
	//Socket* socket;

	map<void*, uint32> m_objectmap;	// The objects that are on the server and their ID on that server

	uint32 m_serverID;
};

/*
class ServerObject
{
public:
	uint32 m_ID;	// The id of 
};
*/

PerObject* GetPerObject(const void* obj)
{
	map<const void*, PerObject*>::iterator it = perobject.find(obj);
	if (it == perobject.end())	// No per object data, it's writable
	{
		return NULL;
	}
	else
	{
		return (*it).second;
	}
}

class IPerObjectData
{
public:
	virtual PerObject* GetPerObjectData() const = 0;
};

//void WriteObject(const void* object, IO::ISequentialByteStream* stream);
//void WriteMembers(const uint8* object, ClassType* pType, IO::ISequentialByteStream* stream);

void Stream::WriteMember(const uint8* object, Type* pType)
{
	Type_type kind = pType->get_Kind();

	if (kind == type_class)
	{
		WriteMembers(object, static_cast<ClassType*>(pType));
	}
	else if (kind == type_pointer)
	{
		Type* pPointerTo = pType->GetPointerTo()->GetStripped();
		/*
		if (pType->GetPointerTo()->get_Kind() == type_pointer)
		{
			WriteObject(*(void**)object, stream);
		}
		else
		*/
		if (pPointerTo->get_Kind() == type_class)
		{
			WriteObject(*(void**)object);
		}
		else
		{
			// TODO

		//	If it's on the heap, then we can get its size, if not, we fail

			ASSERT(0);
		}
	}
	else
	{
		ASSERT(0);
	//	Write(object, pType->get_sizeof());
	}
}

void Stream::WriteMembers(const uint8* object, ClassType* pType)
{
	for (uint i = 0; i < pType->m_pScope->m_orderedDecls.size(); i++)
	{
		Declarator* decl = pType->m_pScope->m_orderedDecls[i];

		if (!decl->get_IsStatic() && !decl->get_IsTypedef())
		{
			Type* pType = decl->m_pType->GetStripped();
			Type_type kind = pType->get_Kind();

			if (kind == type_array)
			{
				ArrayType* array = static_cast<ArrayType*>(pType);

				size_t count = array->get_ElemCount();

				for (size_t i = 0; i < count; ++i)
				{
					WriteMember(object + decl->m_offset + i*array->get_ElemType()->get_sizeof(), array->get_ElemType());
				}
			}
			else if (kind != type_function)
			{
				WriteMember(object + decl->m_offset, pType);
				/*
				switch (kind)
				{
				case type_int:
				case type_long:
				case type_unsigned_int:
				case type_unsigned_long:
				case type_float:

				case type_double:
				case type_long_long:
				}
				*/
			}
		}
	}
}

void Stream::WriteClass(const uint8* object, ClassType* pType)
{
	for (unsigned int i = 0; i < pType->m_bases.size(); i++)
	{
		WriteClass(object + pType->m_bases[i]->m_offset, pType->m_bases[i]->m_pClass->GetClass());
	}

	WriteMembers(object, pType);
}

void Stream::WriteObject(const void* object)
{
	if (object == NULL)
	{
		uint32 id = 0;
		Write(&id, 4);
		return;
	}

	map<const void*, uint32>::iterator it = m_objectmapSave.find(object);

	PerObject* perobject = GetPerObject(object);

	if (it != m_objectmapSave.end())
	{
		uint32 id = (*it).second;
		Write(&id, 4);
	}
	else
	{
		ClassType* pType = System::GetType(object);

		uint32 id = ++m_id;
		Write(&id, 4);

		m_objectmapSave.insert(map<const void*, uint32>::value_type(object, id));

		char classname[256] = {0};
		std::memcpy(classname, pType->get_QName().GetData8(), pType->get_QName().GetLength());
		Write(classname, 256);

		WriteClass((uint8*)object, pType);
	}
}

void Stream::ReadMember(uint8* object, Type* pType)
{
	Type_type kind = pType->get_Kind();

	if (kind == type_class)
	{
		ReadMembers(object, static_cast<ClassType*>(pType));
	}
	else if (kind == type_pointer)
	{
		Type* pPointerTo = pType->GetPointerTo()->GetStripped();

		if (pPointerTo->get_Kind() == type_class)
		{
			*(void**)object = ReadObject();
		}
		else
		{
			ASSERT(0);
		}
	}
	else
	{
		Read(object, pType->get_sizeof());
	}
}

void Stream::ReadMembers(uint8* object, ClassType* pType)
{
	for (uint i = 0; i < pType->m_pScope->m_orderedDecls.size(); i++)
	{
		Declarator* decl = pType->m_pScope->m_orderedDecls[i];

		if (!decl->get_IsStatic() && !decl->get_IsTypedef())
		{
			Type* pType = decl->m_pType->GetStripped();
			Type_type kind = pType->get_Kind();

			if (kind == type_array)
			{
				ASSERT(0);
				/*
				ArrayType* array = static_cast<ArrayType*>(decl->m_pType);

				uint count = array->get_ElemCount();

				for (uint i = 0; i < count; i++)
				{
					WriteMember(object + decl->m_offset + i*array->get_ElemType()->get_sizeof(), array->get_ElemType(), stream);
				}
				*/
			}
			else if (kind != type_function)
			{
				ReadMember(object + decl->m_offset, pType);
			}
		}
	}
}

void Stream::ReadClass(uint8* object, ClassType* pType)
{
	for (unsigned int i = 0; i < pType->m_bases.size(); i++)
	{
		ReadClass(object + pType->m_bases[i]->m_offset, pType->m_bases[i]->m_pClass->GetClass());
	}

	ReadMembers(object, pType);
}

void* Stream::ReadObject()
{
	uint32 id;
	Read(&id, 4);
	if (id == 0)
	{
		return NULL;
	}

	map<uint32, void*>::iterator it = m_objectmapLoad.find(id);

	if (it != m_objectmapLoad.end())
	{
		return (*it).second;
	}
	else
	{
		// We don't call any constructors.. hmm.

		char classname[256] = {0};
		Read(classname, 256);

		ClassType* pType = (ClassType*)pD->LookupNamedType(classname);
		ASSERT(pType);

		uint8* object = new /*(pHeap)*/ uint8[pType->get_sizeof()];

		ReadClass(object, pType);

		return object;
	}

	return NULL;
}

LONGLONG WindowClientSocket::Seek(LONGLONG move, IO::SeekOrigin origin)
{
	ASSERT(0);
	return 0;
}

LONGLONG WindowClientSocket::GetSize()
{
	return -1;
}

ServerInfo::ServerInfo()
{
	m_socket = NULL;
	m_serverID = 0;
}

ServerInfo::~ServerInfo()
{
}

Object* ServerInfo::CreateObject(ClassType* pType)
{
	uint16 cmd = 1;	// CreateObjectByVal
	char classname[256] = {0};
	std::memcpy(classname, pType->get_QName().GetData8(), pType->get_QName().GetLength());
	m_socket->Write(&cmd, 2);
	m_socket->Write(classname, 256);

	m_stream.m_stream = m_socket;
	void* object = m_stream.ReadObject();

	return (Object*)object;
}

void* ServerInfo::CreateObjectOnServer(ClassType* pType)
{
	uint16 cmd = 2;	// CreateObjectByRef
	char classname[256] = {0};
	std::memcpy(classname, pType->get_QName().GetData8(), pType->get_QName().GetLength());
	m_socket->Write(&cmd, 2);
	m_socket->Write(classname, 256);

	m_stream.m_stream = m_socket;
	int32 object;
	m_stream >> object;

	return (void*)object;
}

int ServerInfo::InvokeMethod_int32(void* object, int methodID, uint8* args, int argssize)
{
	uint16 cmd = 3;
	m_socket->Write(&cmd, 2);
	m_socket->Write(&object, sizeof(void*));
	m_socket->Write(&methodID, 4);

	m_stream.m_stream = m_socket;
	int result;
	m_stream >> result;

	return result;
}

ClassType* ServerInfo::GetClass(StringIn classname)
{
	uint32 len = classname.GetLength32();
	m_socket->Send(&len, 4);
	m_socket->Send(classname.GetData8(), len);

	m_stream.m_stream = m_socket;
	Object* obj = (Object*)m_stream.ReadObject();

	return dynamic_cast<ClassType*>(obj);
}

void WindowClientSocket::OnReceive(int nErrorCode)
{
	TRACE("WindowClientSocket::OnReceive\n");
	/*
	uint8 msgid;

	int nread = Read(&msgid, 1);
	ASSERT(nread == 1);

	if (msgid == 1)	// left buttondown
	{
		int x;
		int y;

		Read(&x, 4);
		Read(&y, 4);
	}
	else if (msgid == 2)	// left buttonup
	{
		int x;
		int y;

		Read(&x, 4);
		Read(&y, 4);
	}
	else if (msgid == 3)	// mousemove
	{
		int x;
		int y;

		Read(&x, 4);
		Read(&y, 4);
	}
	else if (msgid == 4)	// render
	{
		uint16 id = 6;
		Send(&id, 2);

		gm::RectI rect(30, 30, 60, 30);
		Send(&rect, sizeof(rect));
	}
	*/
}

void WindowClientSocket::OnConnect(int nErrorCode)
{
	TRACE("WindowClientSocket::OnConnect\n");
}

void WindowClientSocket::OnClose(int nErrorCode)
{
	TRACE("WindowClientSocket::OnClose\n");
}

void ClientSocket::OnReceive(int nErrorCode)
{
	uint16 cmd;
	int nread = Read(&cmd, 2);

	TRACE("ClientSocket::OnReceive(cmd=%d)\n", cmd);

	if (cmd == 1)	// CreateObjectByVal
	{
		char classname[256];
		Read(classname, 256);

		NamedType* pType = pD->LookupNamedType(classname);

		Object* obj = newobj(static_cast<ClassType*>(pType));

		m_stream.WriteObject(obj);
	}
	else if (cmd == 2)	// CreateObjectByRef
	{
		char classname[256];
		Read(classname, 256);

		NamedType* pType = pD->LookupNamedType(classname);

		Object* obj = newobj(static_cast<ClassType*>(pType));

		m_stream.Write(&obj, sizeof(void*));
	}
	else if (cmd == 3)	// InvokeMethod
	{
		int32 ob;
		m_stream >> ob;

		int32 methodID;
		m_stream >> methodID;

		Object* obj = (Object*)ob;

		int result = 9;
		m_stream << result;
	}
	else
		ASSERT(0);
}

void ListenerSocket::OnAccept(int nErrorCode)
{
	ClientSocket* pSocket = new ClientSocket;
	Accept(pSocket);
	if (pSocket->m_socket != INVALID_SOCKET)
	{
	}
	else
		delete pSocket;

	TRACE("OnAccept %d\n", (int)pSocket->m_socket);
}

PerObject::PerObject()
{
	m_lockedServerID = 0;
	m_writeUnlockNode = m_writeUnlockObjects.end();
}

UpdateLock::UpdateLock(Object* obj)
{
	map<const void*, PerObject*>::iterator it = perobject.find(obj);
	if (it == perobject.end())	// No per object data, it's writable
	{
		m_perobject = NULL;
	}
	else
	{
		m_perobject = (*it).second;

		if (m_perobject->m_writeLock)
		{
			// Write to server holding the write lock and tell it we want a write lock

			ASSERT(0);
		}

		++m_perobject->m_changed;
		++m_perobject->m_writeLock;
	}
}

UpdateLock::~UpdateLock()
{
	if (m_perobject)
	{
		--m_perobject->m_writeLock;

		if (m_perobject->m_writeLock == 0)
		{
			// Delay unlock
			if (m_perobject->m_writeUnlockNode == m_writeUnlockObjects.end())
			{
				m_perobject->m_writeUnlockNode = m_writeUnlockObjects.insert(m_writeUnlockObjects.end(), m_perobject);
			}
		}
		//ObjectServerList*
	}
}

/*
void WriteLock(Object* obj)
{
	map<Object*, PerObject*>::iterator it = perobject.find(obj);
	if (it == perobject.end())	// No per object data, it's writable
		return;

	(*it).second->m_writeLock++;
}

void WriteUnlock(Object* obj)
{
	map<Object*, PerObject*>::iterator it = perobject.find(obj);
	if (it == perobject.end())	// No per object data, it's writable
		return;

	(*it).second->m_writeLock--;
}
*/

/*
CreateServer()
{
	WindowServer::ListenerSocket* pSocket = new WindowServer::ListenerSocket;
	pSocket->Create(500);
	pSocket->Listen();
}
*/

}	// Remoting
}	// System
