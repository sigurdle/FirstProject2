#ifndef __SOCKET_H__
#define __SOCKET_H__

//#if AMIGA

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
 */

/*
 * Protocols
 */
#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_IGMP            2               /* group management protocol */
#define IPPROTO_GGP             3               /* gateway^2 (deprecated) */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_PUP             12              /* pup */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */

#define IPPROTO_RAW             255             /* raw IP packet */
#define IPPROTO_MAX             256

/*
 * Types
 */
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */

//#endif

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

/*
 * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
 *
 *
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
#define IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
                                        /* 0x20000000 distinguishes new &
                                           old ioctl's */
#define _IO(x,y)        (IOC_VOID|((x)<<8)|(y))

#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONREAD    _IOR('f', 127, u_long) /* get # bytes to read */
#define FIONBIO     _IOW('f', 126, u_long) /* set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, u_long) /* set/clear async i/o */

namespace System
{
namespace Net
{

/*
 * Basic system type definitions, taken from the BSD file sys/types.h.
 */
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

	typedef UINT_PTR SOCKET;

/*
 * Internet address (old style... should be updated)
 */
struct in_addr {
        union {
                struct { unsigned char s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { unsigned short s_w1,s_w2; } S_un_w;
                unsigned long S_addr;
        } S_un;
};

/*
 * Structure used by kernel to store most
 * addresses.
 */
struct SOCKADDR {
        unsigned short sa_family;              /* address family */
        char    sa_data[14];            /* up to 14 bytes of direct address */
};

/*
 * Socket address, internet style.
 */
struct SOCKADDR_IN {
        short   sin_family;
        unsigned short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};

class NETEXT AsyncSocket : public Object
{
public:
	CTOR AsyncSocket();
	virtual ~AsyncSocket();

	bool Create(UINT nSocketPort = 0, int nSocketType = SOCK_STREAM, const char* lpszSocketAddress = NULL);
//	bool CreateBlocking(int nSocketType = SOCK_STREAM, int protocol = IPPROTO_TCP);

	bool Socket(int nSocketType = SOCK_STREAM, int protocol = IPPROTO_TCP);

	bool Bind(UINT nSocketPort, const char* lpszSocketAddress = NULL);
	bool Bind(const SOCKADDR* lpSockAddr, int nSockAddrLen);

	void Close();

	bool Accept(AsyncSocket* pSocket);

	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	int IOCtl(long lCommand, ULONG* lpArgument);

	virtual int Send(const void* pv, int size, int nFlags = 0);
	virtual int Receive(void* pv, int size, int nFlags = 0);
	virtual int ReceiveFrom(void* pv, int size, SOCKADDR* lpSockAddr, int* lpSockAddrLen);

	int Listen(int nConnectionBacklog = 5);
	bool Connect(ULONG address, int port);
	bool Connect(const char* server, int port);
	bool Connect(StringIn server, int port)
	{
		return Connect(CString(server), port);
	}

	bool GetPeerName(SOCKADDR* lpSockAddr, int* lpSockAddrLen);
	bool GetPeerName(StringVariant& rPeerAddress, UINT& rPeerPort);

	bool GetSockName(StringVariant& rSocketAddress, UINT& rSocketPort);

	int Read(void* pv, int size);	// TODO remove ??
	int Write(const void* pv, int size);// TODO remove ??

#if _WIN32
	class SocketWindow : public MSWindows::WindowImpl//<SocketWindow>
	{
	public:
		typedef MSWindows::WindowImpl/*<SocketWindow>*/ windowBase;

		void Create();

		typedef map<SOCKET,AsyncSocket*, less<SOCKET>, __gc_allocator> tysocketmap;
		tysocketmap m_sockets;

		virtual bool ProcessWindowMessage( MSWindows::Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ );

		LRESULT OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	};

	SocketWindow* pSocketWindow;
#endif

	SOCKET m_socket;
};

}	// Net
}	// System

#endif // __SOCKET_H__
