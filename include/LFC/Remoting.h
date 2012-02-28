#error "not yet"

#include "Socket.h"

namespace System
{
namespace Remoting
{

class ObjectServerList
{
public:
	uint32 m_serverID;
	uint32 m_objectID;
	ObjectServerList* next;
};

class PerObject : public Object
{
public:
	CTOR PerObject();

	list<PerObject*>::iterator m_writeUnlockNode;

	ObjectServerList* m_serverList;

	uint32 m_lockedServerID;	// The server that holds the write lock

	uint32 m_changed;
	int m_writeLock;
};

class LFCEXT UpdateLock
{
public:
	CTOR UpdateLock(Object* obj);
	~UpdateLock();

	PerObject* m_perobject;
};

class LFCEXT Stream
{
public:

	CTOR Stream()
	{
		m_id = 0;
	}

	Stream& operator >> (int32& ref)
	{
		Read(&ref, 4);
		return *this;
	}

	Stream& operator << (int32 value)
	{
		Write(&value, 4);
		return *this;
	}

	ULONG Read(void* pv, ULONG cb)
	{
		return m_stream->Read(pv, cb);
	}

	ULONG Write(const void* pv, ULONG cb)
	{
		return m_stream->Write(pv, cb);
	}

	void* ReadObject();
	void ReadClass(uint8* object, ClassType* pType);
	void ReadMember(uint8* object, Type* pType);
	void ReadMembers(uint8* object, ClassType* pType);

	void WriteObject(const void* object);
	void WriteClass(const uint8* object, ClassType* pType);
	void WriteMembers(const uint8* object, ClassType* pType);
	void WriteMember(const uint8* object, Type* pType);

public:

	map<const void*, uint32> m_objectmapSave;
	map<uint32, void*> m_objectmapLoad;

	IO::ISequentialByteStream* m_stream;

	uint32 m_id;
};

class LFCEXT ClientSocket : public AsyncSocket, public IO::ISequentialByteStream
{
public:
	CTOR ClientSocket()
	{
		m_id = 0;
		m_stream.m_stream = this;
	}

	virtual void OnReceive(int nErrorCode);

	virtual ULONG Read(void* pv, ULONG cb)
	{
		return AsyncSocket::Read(pv, cb);
	}
	virtual ULONG Write(const void* pv, ULONG cb)
	{
		return AsyncSocket::Write(pv, cb);
	}
	virtual LONGLONG Seek(LONGLONG move, IO::SeekOrigin origin)
	{
		ASSERT(0);
		return 0;
	}
	virtual LONGLONG GetSize()
	{
		return -1;
	}
//	virtual LONGLONG GetSize() const = 0;
	virtual IO::ISequentialByteStream* Clone() const
	{
		ASSERT(0);
		return NULL;
	}

public:

	Stream m_stream;

//	map<const void*, uint32> m_objectmap;	// the objects that are on the client and their IDs

	uint32 m_id;
};

class LFCEXT ListenerSocket : public AsyncSocket
{
public:

	virtual void OnAccept(int nErrorCode);

	/*
	virtual void OnRead()
	{
		TRACE("OnRead\n");

		char buf[512];
		int nRead = Receive(buf, 512);

	//	::MessageBox(NULL, buf, NULL, MB_OK);
	}
	*/
};

class LFCEXT WindowClientSocket : public AsyncSocket, public IO::ISequentialByteStream
{
public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	virtual ULONG Read(void* pv, ULONG cb)
	{
		return AsyncSocket::Read(pv, cb);
	}
	virtual ULONG Write(const void* pv, ULONG cb)
	{
		return AsyncSocket::Write(pv, cb);
	}
	virtual LONGLONG Seek(LONGLONG move, IO::SeekOrigin origin);
	virtual LONGLONG GetSize();
	virtual IO::ISequentialByteStream* Clone() const
	{
		ASSERT(0);
		return NULL;
	}
};

class LFCEXT ServerInfo
{
public:
	CTOR ServerInfo();
	virtual ~ServerInfo();

	ClassType* GetClass(StringIn classname);
	Object* CreateObject(ClassType* pType);

	void* CreateObjectOnServer(ClassType* pType);

//	void InvokeMethod_void(void* object, int methodID, uint8* args, int argssize);
	int InvokeMethod_int32(void* object, int methodID, uint8* args, int argssize);
//	double InvokeMethod_double(void* object, int methodID, uint8* args, int argssize);

//	Object* ReadObject(IO::ISequentialByteStream* stream);

	Stream m_stream;

	WindowClientSocket* m_socket;
	uint32 m_serverID;
};

}
}
