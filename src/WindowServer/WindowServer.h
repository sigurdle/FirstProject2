#include "../LXUI/Socket.h"

namespace System
{
namespace WindowServer
{

class ClientSocket : public AsyncSocket
{
public:

	UI::CUIFrameImpl* m_frame;
	UI::WindowBase2* m_pElement;

	virtual void OnReceive(int nErrorCode);
};

class ListenerSocket : public AsyncSocket
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

}	// WindowServer
}
