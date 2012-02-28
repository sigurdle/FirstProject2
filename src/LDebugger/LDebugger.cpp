#include "stdafx.h"
#include "LDebugger.h"

#include <windows.h>
#include <objidl.h>

#include "LFC/Remoting.h"
#include "LFC/vc_typeinfo.h"

//using namespace System;

TestingRemote::TestingRemote()
{
}

namespace System
{
namespace UI
{
UIEXT extern int g_nWindows;
}
}

#if WIN32

/*
#define Array var
#include <windows.h>
#include <psapi.h>
#undef Array
*/
#endif

#include "../CodeComp/AOut.h"
#include "../Include/AmigaHunkParser.h"
#include "../Include/ArchFile.h"

typedef void (*dllentrypoint)();

namespace System
{

interface __declspec(uuid("C198D3E1-C9A9-43a1-A9A1-A307DD9C3EC2")) _AppDomain : public IUnknown
{
};

class AppDomain : public MarshalByRefObject, public _AppDomain
{
public:

	Object* CreateInstanceAndUnwrap(StringPtr appDomain, StringPtr type);

	virtual unsigned long STDMETHODCALLTYPE AddRef();
	virtual unsigned long STDMETHODCALLTYPE Release();
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(const ::IID & iid, void** pv);

	HANDLE m_hProcess;
	DWORD m_processId;

	Remoting::ServerInfo* m_server;
};

unsigned long AppDomain::AddRef()
{
	return 1;
}

unsigned long AppDomain::Release()
{
	return 1;
}

HRESULT AppDomain::QueryInterface(const ::IID & iid, void** pv)
{
	if (iid == __uuidof(IUnknown))
	{
		*pv = static_cast<IUnknown*>(this);
	}
	else if (iid == __uuidof(_AppDomain))
	{
		*pv = static_cast<_AppDomain*>(this);
	}
	else
		return E_NOINTERFACE;

	return S_OK;
}

LFCEXT rtti_object_locator* Build_rtti(ClassType* pType);
LFCEXT void** build_proxy_vtable(ClassType* pType);

Object* AppDomain::CreateInstanceAndUnwrap(StringPtr appDomain, StringPtr type)
{
	Type* pType = pD->LookupNamedType(type.m_str->ToStringA());

	ClassType* pClassType = dynamic_cast<ClassType*>(pType);

	void* serverObject = m_server->CreateObjectOnServer(pClassType);

	void** vtable = build_proxy_vtable(pClassType);
	vtable[-1] = Build_rtti(pClassType);

	uint8* object = (uint8*)allocate_object(pClassType->get_sizeof()+4);
	*(void**)(object) = vtable;
	*(void**)(object + pClassType->get_sizeof()) = serverObject;

	return (Object*)object;

#if 0
	rtti_object_locator* p3;
	{
		testrtti_derived1 obj;
		void* vtable = *(void**)&obj;
		p3 = ((rtti_object_locator**)vtable)[-1];
	}

	const type_info& ti2 = typeid(testrtti_derived1);

	ClassType* pType = (ClassType*)typeid(testrtti_derived1).GetType();

	void* vtable[1];
	rtti_object_locator* p4 = Build_rtti(pType);
	vtable[0] = p4;
	polymorphic_object object;
	object.vtable = &vtable[1];

	const type_info& ti = typeid(*(Object*)&object);

	testrtti_base3* testv = dynamic_cast<testrtti_base3*>((Object*)&object);
#endif

	return NULL;
}

AppDomain* CreateDomain()
{
	AppDomain* ad = new AppDomain;

	PROCESS_INFORMATION pi;

	LPWSTR lpApplicationName = L"C:\\mmstudio\\bin\\win32\\debug\\LDebugger.exe";

	STARTUPINFOW si = {0};
	si.cb = sizeof(&si);

	if (false)
	{
		CreateProcessW(

		lpApplicationName,
			L"remote",//  __in_out      LPTSTR lpCommandLine,
			NULL,//  __in          LPSECURITY_ATTRIBUTES lpProcessAttributes,
			NULL,//  __in          LPSECURITY_ATTRIBUTES lpThreadAttributes,
			TRUE,//  __in          BOOL bInheritHandles,
			0,//  __in          DWORD dwCreationFlags,
			NULL,//  __in          LPVOID lpEnvironment,
			NULL,//  __in          LPCTSTR lpCurrentDirectory,
			&si,//  __in          LPSTARTUPINFO lpStartupInfo,
			&pi//  __out         LPPROCESS_INFORMATION lpProcessInformation
			);

		ad->m_processId = pi.dwProcessId;
		ad->m_hProcess = pi.hProcess;

		Sleep(500);
	}

	ad->m_server = new Remoting::ServerInfo;

	ad->m_server->m_socket = new Remoting::WindowClientSocket;
	ad->m_server->m_socket->Socket();
	ad->m_server->m_socket->Connect("localhost", 500);

	return ad;
}

}	// System

int TestingRemote::TestMethod(System::StringW* param)
{
	MessageBoxW(NULL, param->c_str(), L"", MB_OK);

	return 4;
}

#if 0
#include <direct.h>
#endif

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#endif

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/CodeComp.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/CodeComp.lib")
#endif

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/javavm.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/javavm.lib")
#endif

#ifdef AMIGA
#define new DEBUG_NEW
#endif

//#include "resource.h"

#include "../LXUI/Screen.h"
//#include "../LXUI/UIFrameImpl.h"

#if __APPLE__
#define LDraw carbonLDraw
#include <Carbon/Carbon.h>
#undef LDraw

extern Boolean		gQuitFlag;	/* global */

//void DoEvent(EventRecord *event);
#endif

//#include "../LXUI/UIFrameImpl2.h"

extern int main(int argc, char* argv[]);

#if AMIGA

#include <stdio.h>

extern ULONG ret_pc;
extern uint16 sr;
ULONG nSig = 0;

FILE* fplog2;

void LOG2(const char* s)
{
	fprintf(fplog2, s);
	fflush(fplog2);
}

extern void check();

/////////////////////////////////////////////////////////////////////////////
// Standard Commands

// File commands
#define ID_FILE_NEW                     0xE100
#define ID_FILE_OPEN                    0xE101
#define ID_FILE_CLOSE                   0xE102
#define ID_FILE_SAVE                    0xE103
#define ID_FILE_SAVE_AS                 0xE104
#define ID_FILE_PAGE_SETUP              0xE105
#define ID_FILE_PRINT_SETUP             0xE106
#define ID_FILE_PRINT                   0xE107
#define ID_FILE_PRINT_DIRECT            0xE108
#define ID_FILE_PRINT_PREVIEW           0xE109
#define ID_FILE_UPDATE                  0xE10A
#define ID_FILE_SAVE_COPY_AS            0xE10B
#define ID_FILE_SEND_MAIL               0xE10C



#endif

//#include "BrowserFrame.h"

/*
#if __APPLE__

void IdleTimer (
   EventLoopTimerRef inTimer,
   EventLoopIdleTimerMessage inState,
   void * inUserData
)
{
	pLayoutManager->MeasureAll();
	pLayoutManager->RenderAll();
}


#endif
*/

//int MessageLoop();

#include "LDebugger.h"

#include "TTDebuggerFrame.h"
//#include "P2PFrame.h"
//#include "MailReaderFrame.h"

#if 0//WIN32
#include "../LXMLEditor/LXMLEditor.h"
//#include "../LXMLEditor/LXMLEditor2.h"
#include "../LXMLEditor/LXMLEditorApp.h"
#include "../LXMLEditor/EXMLDocument.h"

#pragma comment(lib, "../LXMLEditor/Debug/LXMLEditor.lib")
#endif

#if WIN32

#include "../SWF/swfdecoder.h"
#pragma comment(lib, "../../lib/Win32/Debug/SWF.lib")

#endif

Module _Module;

namespace System
{

UI::MessageLoop messageLoop;

#if AMIGA

void _RunCommand(const char* name)
{
	BPTR out = dosOpen(DOSBase, "PIPE:test", MODE_NEWFILE);
	if (out)
	{
		BPTR seglist = NewLoadSegTags(name, (TAG_DONE));
		if (seglist)
		{
			struct ::Process* pr = CreateNewProcTags(
			//	(NP_Entry), (ULONG)testfunc,
				(NP_Seglist), seglist,
				(NP_Output), out,
				(NP_CloseOutput), TRUE,
			//	(NP_ExitCode), (ULONG)OnExit,
				(TAG_DONE));

			BPTR in = dosOpen(DOSBase, "PIPE:test", MODE_OLDFILE);
			if (in)
			{
				while (1)
				{
					char buffer[256];
					int nread = dosRead(DOSBase, in, buffer, 255);
					buffer[nread] = 0;

					printf("%s", buffer);

					if (nread < 255)
						break;
				}

				dosClose(DOSBase, in);
			}
			else
				printf("Failed to open input\n");
		}
		else
			printf("Failed to load command\n");

	//	dosClose(out);
	}
	else
		printf("Failed to open output\n");
}

#endif

#if AMIGA || __APPLE__

struct BITMAPFILEHEADER
{
	uint16    bfType;
	DWORD   bfSize;
	uint16    bfReserved1;
	uint16    bfReserved2;
	DWORD   bfOffBits;
};

#endif


#if WIN32

#if 0

#include "../PNG/PNGFormat.h"


#pragma comment(lib, "../PNG/Debug/PNG.lib")
#pragma comment(lib, "../LMedia/Debug/LMedia.lib")

#endif

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LXUI.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LXUI.lib")
#endif

using namespace IO;

//CServerAppModule _Module;

/*
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()
*/

/*
class RGBBitmapData
{
public:
	uint8* r_plane;
	uint8* g_plane;
	uint8* b_plane;
};
*/

#pragma pack(push, 1)

#pragma pack(pop)


#endif // WIN32

/*
template<class T> class ptr;

template<class T> class membuffer
{
public:
	T* m_p;
	ULONG m_nelts;

	ptr<T> operator + (ULONG offset)
	{
		ptr<T> p;
		p.m_membuffer = this;
		p.m_p = m_p + offset;
	}
};

template<class T> class ptr
{
public:
	T* m_p;
	membuffer<T>* m_membuffer;

	T& operator * ()
	{
		if (m_p < m_membuffer->m_p)
		{
			printf("Accessing Memory address before");
			exit(0);
		}
		if (m_p > m_membuffer->m_p + m_membuffer->m_nelts)
		{
			printf("Accessing Memory address before");
			exit(0);
		}
	}

	T& operator = (membuffer<T>& membuffer)
	{
		m_membuffer = membuffer;
		return *this;
	}

	T& operator = (T* 
};
*/

#if WIN32

// TODO, improve this interface
class IBitmapEncoder
{
public:
	virtual void SetFormat(int width, int height, int numcolors) = 0;
	virtual void SetPalette(uint8* red, int red_stride, uint8* green, int green_stride, uint8* blue, int blue_stride) = 0;
};

class BMPEncoder : public IBitmapEncoder
{
public:

	BMPEncoder(System::IO::ByteStreamWriter* stream)
	{
		m_bi = NULL;
		m_stream = stream;
	}

	~BMPEncoder()
	{
		delete m_bi;
	}

	void SetFormat(int width, int height, int numcolors)
	{
		m_bi = (MSWindows::BITMAPINFO*)new uint8[sizeof(MSWindows::BITMAPINFOHEADER) + sizeof(MSWindows::RGBQUAD)*numcolors];
		std::memset(m_bi, 0, sizeof(MSWindows::BITMAPINFOHEADER) + sizeof(MSWindows::RGBQUAD)*numcolors);

		m_bi->bmiHeader.biSize = sizeof(MSWindows::BITMAPINFOHEADER);
		m_bi->bmiHeader.biWidth = width;
		m_bi->bmiHeader.biHeight = height;
		m_bi->bmiHeader.biPlanes = 1;
		m_bi->bmiHeader.biBitCount = 8;
		m_bi->bmiHeader.biCompression = BI_RGB;
		m_bi->bmiHeader.biClrUsed = numcolors;
		m_bi->bmiHeader.biSizeImage = 0;
	}

	void SetPalette(uint8* red, int red_stride, uint8* green, int green_stride, uint8* blue, int blue_stride)
	{
		for (int i = 0; i < m_bi->bmiHeader.biClrUsed; i++)
		{
			m_bi->bmiColors[i].rgbRed = *red;
			m_bi->bmiColors[i].rgbGreen = *green;
			m_bi->bmiColors[i].rgbBlue = *blue;

			red += red_stride;
			green += green_stride;
			blue += blue_stride;
		}
	}

	void WriteHeader()
	{
		ASSERT(0);
#if 0
		// Make room for BITMAPFILEHEADER
		m_stream->Seek(sizeof(BITMAPFILEHEADER), System::IO::STREAM_SEEK_SET);

		ULONG headerSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*m_bi->bmiHeader.biClrUsed;
		if (m_stream->Write(m_bi, headerSize) != headerSize)
			throw -1;
#endif
	}

	void WriteBitmap(LDraw::BitmapData* bitmapData)
	{
		ASSERT(0);
#if 0
		BITMAPFILEHEADER bfh;
		bfh.bfType = 0x4d42;
		bfh.bfReserved1 = 0;
		bfh.bfReserved2 = 0;
		bfh.bfOffBits = m_stream->Seek(0, System::IO::STREAM_SEEK_CUR);

		DWORD rowbytes = ROWBYTES_DWORD(m_bi->bmiHeader.biWidth, m_bi->bmiHeader.biBitCount);

		if (rowbytes > bitmapData->Stride)
			THROW(-1);

		for (int y = m_bi->bmiHeader.biHeight-1; y >= 0; y--)
		{
			uint8* src = bitmapData->Scan0 + y*bitmapData->Stride;

			if (m_stream->Write(src, rowbytes) != rowbytes)
				THROW(-1);
		}

		// Write BITMAPFILEHEADER
		bfh.bfSize = m_stream->Seek(0, System::IO::STREAM_SEEK_CUR);
		m_stream->Seek(0, System::IO::STREAM_SEEK_SET);
		if (m_stream->Write(&bfh, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
			THROW(-1);
#endif
	}

protected:

	MSWindows::BITMAPINFO* m_bi;
	ByteStreamWriter* m_stream;
};

void WriteStreamToFile(ISequentialByteStream* stream, const char* filename)
{
	HANDLE hFile = MSWindows::CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == MSWindows::Invalid_Handle_Value)
		throw -1;

	uint8 buffer[256];

	while (1)
	{
		ULONG nRead = stream->Read(buffer, 256);
		MSWindows::DWORD nWritten;
		MSWindows::WriteFile(hFile, buffer, nRead, &nWritten, NULL);
		if (nWritten < nRead)
			throw -1;

		if (nRead < 256)
			break;
	}

	MSWindows::CloseHandle(hFile);
}

//#define CAB_SIGNATURE        ENDIANLONG ('MSCF')
#define CAB_SIGNATURE        ('FCSM')

#define CAB_FLAG_HASPREV     0x0001
#define CAB_FLAG_HASNEXT     0x0002
#define CAB_FLAG_RESERVE     0x0004

#define CAB_ATTRIB_READONLY  0x0001
#define CAB_ATTRIB_HIDDEN    0x0002
#define CAB_ATTRIB_SYSTEM    0x0004
#define CAB_ATTRIB_VOLUME    0x0008
#define CAB_ATTRIB_DIRECTORY 0x0010
#define CAB_ATTRIB_ARCHIVE   0x0020

#define CAB_FILE_FIRST       0x0000
#define CAB_FILE_NEXT        0x0001
#define CAB_FILE_SPLIT       0xFFFE
#define CAB_FILE_CONTINUED   0xFFFD

struct CFHEADER
{
	uint32 sig;              // file signature 'MSCF' (CAB_SIGNATURE)
	uint32 csumHeader;       // header checksum (0 if not used)
	uint32 cbCabinet;        // cabinet file size
	uint32 csumFolders;      // folders checksum (0 if not used)
	uint32 coffFiles;        // offset of first CAB_ENTRY
	uint32 csumFiles;        // files checksum (0 if not used)
	uint8  versionMinor;     // cabinet version (3)
	uint8 versionMajor;	// cabinet version (1)
	uint16 cFolders;         // number of folders
	uint16 cFiles;           // number of files
	uint16 flags;            // cabinet flags (CAB_FLAG_*)
	uint16 setID;            // cabinet set id
	uint16 iCabinet;         // zero-based cabinet number
};

struct CFFOLDER
{
    uint32  coffCabStart;	/* offset of the first CFDATA block in this folder */
    uint16  cCFData;	/* number of CFDATA blocks in this folder */
    uint16  typeCompress;	/* compression type indicator */
//    u1  abReserve[];	/* (optional) per-folder reserved area */
};

struct CFFILE
{
	uint32  cbFile;	/* uncompressed size of this file in bytes */
	uint32  uoffFolderStart;	/* uncompressed offset of this file in the folder */
	uint16  iFolder;	/* index into the CFFOLDER area */
	uint16  date;	/* date stamp for this file */
	uint16  time;	/* time stamp for this file */
	uint16  attribs;	/* attribute flags for this file */
//	uint8  szName[];	/* name of this file */
};

#define tcompMASK_TYPE          0x000F  // Mask for compression type
#define tcompTYPE_NONE          0x0000  // No compression
#define tcompTYPE_MSZIP         0x0001  // MSZIP
#define tcompTYPE_QUANTUM       0x0002  // Quantum
#define tcompTYPE_LZX           0x0003  // LZX
#define tcompBAD                0x000F  // Unspecified compression type

void ReadCAB(ISequentialByteStream* stream)
{
	CFHEADER hdr;
	if (stream->Read(&hdr, sizeof(hdr)) != sizeof(hdr))
		throw -1;

	hdr.sig = LittleEndian32(hdr.sig);
	if (hdr.sig != CAB_SIGNATURE)
		throw -1;

	if (hdr.versionMajor > 1)
		throw -1;

	uint16 cbCFHeader;
	uint8 cbCFFolder;
	uint8 cbCFData;
	if (hdr.flags & CAB_FLAG_RESERVE)
	{
		stream->Read(&cbCFHeader, 2);

		stream->Read(&cbCFFolder, 1);
		stream->Read(&cbCFData, 1);
	}
	else
	{
		cbCFHeader = 0;
		cbCFFolder = 0;
		cbCFData = 0;
	}

//	ASNTag tag;
//	ReadTag(stream, &tag);

	stream->Seek(cbCFHeader, System::IO::STREAM_SEEK_CUR);

	for (int i = 0; i < hdr.cFolders; i++)
	{
		CFFOLDER folder;
		stream->Read(&folder, sizeof(CFFOLDER));

		uint8 type = folder.typeCompress & tcompMASK_TYPE;

		stream->Seek(cbCFFolder, System::IO::STREAM_SEEK_CUR);
	}

	stream->Seek(hdr.coffFiles, System::IO::STREAM_SEEK_SET);

	for (int i = 0; i < hdr.cFiles; i++)
	{
		CFFILE file;
		stream->Read(&file, sizeof(CFFILE));

		StringA filename;

		while (1)
		{
			char c; 
			stream->Read(&c, 1);
			if (c == 0)
				break;

			ASSERT(0);
#if 0
			filename += c;
#endif
		}

		TRACE("%s\n", filename.c_str());
	}
}

#endif

LFCEXT void InitTypes();

class WindowClientSocket : public AsyncSocket
{
public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	UI::UIElement* m_pElement;
};

void WindowClientSocket::OnReceive(int nErrorCode)
{
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

		LDraw::RectI rect(30, 30, 60, 30);
		Send(&rect, sizeof(rect));
	}
}

void WindowClientSocket::OnConnect(int nErrorCode)
{
	TRACE("WindowClientSocket::OnConnect\n");
}

void WindowClientSocket::OnClose(int nErrorCode)
{
	TRACE("WindowClientSocket::OnClose\n");
}

//int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
int Run()
{
//	printf("Hello\n");
//	return 0;

	LDraw::Init();

#if 0
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);
#endif

#if 0
	_Module.Lock();
#endif

#if 0
	ReadCAB(new FileByteStream("C:/downloads/swflash.cab"));
#endif

#if 0
	ReadCertificate(new FileByteStream("C:/test"));

	Crypt::MD5 md5;
	md5.m_stream = new MemoryByteStream("message digest", 14);
	md5.process();
	uint8 digest[16];
	md5.GetDigest((DWORD*)digest);

	{
		StringA str;

		for (int i = 0; i < 16; i++)
		{
			char buf[3];
			sprintf(buf, "%2.2x", digest[i]);
			str += buf;
		}

		ATLTRACE("%s\n", str.c_str());
	}
#endif

#if 0
	ZIPFormat zip;
	zip.Open("C:/fileformatspecs/ISO_IEC_14496-5_2001_Amd_2_2003_PDF_version_(en)_036355_.zip");
#endif

#if 0
	LZIP::Archive* zip = new LZIP::Archive;
	zip->Open(new FileByteStream("D:\\Program Files\\Java\\jre1.5.0_02\\lib\\javaws.jar"));

	LZIP::File* file = zip->OpenFile("META-INF/MANIFEST.MF");
	bool okay = zip->Check();
//	LMedia::ISequentialByteStream* stream = file->GetStream();

//	WriteStreamToFile(stream, "C:/MANIFEST.MF");
#endif

#if 0
	LSWF::Encoder encoder;
	encoder.m_stream = new ByteStreamWriter("C:/test.swf");

	encoder.WriteHeader();
	encoder.WriteMovieHeader(swf->m_movie);

	LSWF::ShapeCharacter* shape = swf->m_movie->CreateShape();
	shape->MoveTo(10*20, 10*20);
	shape->LineTo(40*20, 50*20);

	swf->m_movie->DefineShape(shape);

	swf->m_movie->Close();

	{
		LSWF::Decoder decoder(new LSWF::FormatStream(new FileByteStream("C:/test.swf")));
		LSWF::Movie movie;
		decoder.m_stream->ReadHeader();
		decoder.ReadMovieHeader(&movie);
	}
#endif

#if 0
	LMedia::JNGFormat* jng = new LMedia::JNGFormat();
	jng->SetStream(new FileByteStream("C:/files/jng/TCPN0L.jng"));
//	jng->SetStream(new FileByteStream("C:/files/jng/TCBN0S.jng"));
	jng->ReadSignature();
	jng->ReadHeader();
	LMedia::DATStream* stream = new LMedia::DATStream(CK_JDAT, jng->GetStream());

	WriteStreamToFile(stream, "C:/test.jpg");
#endif

//	MailReaderFrame* wndMain = new MailReaderFrame;
//	wndMain->Show();

	/*
	{
		BrowserFrame* wndMain = new BrowserFrame;
		wndMain->Show();
	}
	*/

//	uint8 buf[512];
//	ptr<uint8> pointer = mem(buf);

	if (false)
	{
		TTDebuggerFrame* wndMain2 = new TTDebuggerFrame;
		wndMain2->Show();
	}

//	P2PFrame* wndMain = new P2PFrame;
//	wndMain->Show();

#if 0
	if (false)
	{
		FullscreenWindow* full = new FullscreenWindow;
		full->CreateFull();

		Screen2* pScreen = new Screen2;
		//screen->m_y = 40;
		pScreen->m_pOwnerFullscreen = full;
		pScreen->Create();
		full->m_surfaceList.push_back(pScreen);

		DebuggerFrame* wndMain = new DebuggerFrame;
		WindowBase2* pBase2 = new WindowBase2;
		pBase2->set_VisualTree(wndMain);

		WindowHost* site = pScreen->OpenWindow();
		site->SetClient(pBase2);
		site->Show();

		pScreen->Render();
	}
//	else
#endif

	{
		int size0 = sizeof(LDraw::RectF);
		int size1 = typeid(LDraw::RectF).GetType()->get_sizeof();
		VERIFY(size0 == size1);
	}

	VERIFY(sizeof(stack<LDraw::RectF>) == typeid(stack<LDraw::RectF>).GetType()->get_sizeof());
	{
		int size0 = sizeof(LDraw::GraphicsO);
		int size1 = typeid(LDraw::GraphicsO).GetType()->get_sizeof();


		int offset0 = offsetof(LDraw::GraphicsO, m_p);
		int offset_0 = offsetof(LDraw::GraphicsO, m_clipRect);
	//	int offset1 = typeid(LDraw::GraphicsO).GetType()->GetClass()->m_pScope->GetDeclarator(NULL)->m_offset;

		VERIFY(size0 == size1);
	//	VERIFY(offset0 == offset1);
	}

	VERIFY(sizeof(LDraw::LinearGradientBrush) == typeid(LDraw::LinearGradientBrush).GetType()->get_sizeof());
	VERIFY(sizeof(Object) == typeid(Object).GetType()->get_sizeof());
	VERIFY(sizeof(StringA) == typeid(StringA).GetType()->get_sizeof());
	VERIFY(sizeof(StringW) == typeid(StringW).GetType()->get_sizeof());
	VERIFY(sizeof(Type) == typeid(Type).GetType()->get_sizeof());
	VERIFY(sizeof(EnumType) == typeid(EnumType).GetType()->get_sizeof());
	VERIFY(sizeof(Typedef) == typeid(Typedef).GetType()->get_sizeof());
	VERIFY(sizeof(NamedType) == typeid(NamedType).GetType()->get_sizeof());
	VERIFY(sizeof(NamespaceType) == typeid(NamespaceType).GetType()->get_sizeof());
	{
		int size0 = sizeof(ClassType);
		int size1 = typeid(ClassType).GetType()->get_sizeof(); 
		VERIFY(size0 == size1);
	}
	VERIFY(sizeof(TemplatedClassArgs) == typeid(TemplatedClassArgs).GetType()->get_sizeof());

	{
		int size0 = sizeof(UI::DependencyObject);
		int size1 = typeid(UI::DependencyObject).GetType()->get_sizeof();

		VERIFY(size0 == size1);
	}

	{
		int size0 = sizeof(UI::Visual);
		int size1 = typeid(UI::Visual).GetType()->get_sizeof();
		VERIFY(size0 == size1);
	}

	{
		int size0 = sizeof(UI::UIElement);
		int size1 = typeid(UI::UIElement).GetType()->get_sizeof();
		VERIFY(size0 == size1);
	}

	VERIFY(sizeof(LDraw::GraphicsO) == typeid(LDraw::GraphicsO).GetType()->get_sizeof());
	VERIFY(sizeof(LDraw::GraphicsMetafile) == typeid(LDraw::GraphicsMetafile).GetType()->get_sizeof());
	VERIFY(sizeof(LDraw::Direct3D9_I) == typeid(LDraw::Direct3D9_I).GetType()->get_sizeof());

	VERIFY(sizeof(UI::EventManager::PerClass) == typeid(UI::EventManager::PerClass).GetType()->get_sizeof());

	VERIFY(sizeof(UI::Control) == typeid(UI::Control).GetType()->get_sizeof());
	VERIFY(sizeof(UI::SolidColorBrush) == typeid(UI::SolidColorBrush).GetType()->get_sizeof());
	VERIFY(sizeof(UI::LinearGradientBrush) == typeid(UI::LinearGradientBrush).GetType()->get_sizeof());
	VERIFY(sizeof(UI::BaseWindow) == typeid(UI::BaseWindow).GetType()->get_sizeof());
	VERIFY(sizeof(UI::Window) == typeid(UI::Window).GetType()->get_sizeof());
	VERIFY(sizeof(UI::ChildWindow) == typeid(UI::ChildWindow).GetType()->get_sizeof());
	VERIFY(sizeof(UI::Popup) == typeid(UI::Popup).GetType()->get_sizeof());
	VERIFY(sizeof(UI::Style) == typeid(UI::Style).GetType()->get_sizeof());
	VERIFY(sizeof(UI::Button) == typeid(UI::Button).GetType()->get_sizeof());
	VERIFY(sizeof(UI::Trigger) == typeid(UI::Trigger).GetType()->get_sizeof());
	VERIFY(sizeof(UI::ScrollBar) == typeid(UI::ScrollBar).GetType()->get_sizeof());
	VERIFY(sizeof(UI::ScrollViewer) == typeid(UI::ScrollViewer).GetType()->get_sizeof());
	VERIFY(sizeof(UI::Track) == typeid(UI::Track).GetType()->get_sizeof());
	VERIFY(sizeof(UI::MouseButtonEventArgs) == typeid(UI::MouseButtonEventArgs).GetType()->get_sizeof());
	VERIFY(sizeof(Debugger::DebuggerFrame) == typeid(Debugger::DebuggerFrame).GetType()->get_sizeof());

	{
		int size0 = sizeof(System::mem_fun_t<System::UI::UIElement,System::UI::CanExecuteRoutedEventArgs *>);
		int size1 = typeid(System::mem_fun_t<System::UI::UIElement,System::UI::CanExecuteRoutedEventArgs *>).GetType()->get_sizeof();

		VERIFY(size0 == size1);
	}

	{
		int size0 = sizeof(System::stub2<System::mem_fun_t<System::UI::UIElement,System::UI::CanExecuteRoutedEventArgs *>,void,System::Object *,System::UI::CanExecuteRoutedEventArgs *>);
		int size1 = typeid(System::stub2<System::mem_fun_t<System::UI::UIElement,System::UI::CanExecuteRoutedEventArgs *>,void,System::Object *,System::UI::CanExecuteRoutedEventArgs *>).GetType()->get_sizeof();

		VERIFY(size0 == size1);
	}

	__live_object_ptr<Debugger::DebuggerFrame> wndMain = NULL;

	if (true)
	{
	//	UI::DesktopScreen* pScreen = new UI::DesktopScreen;

		wndMain = new Debugger::DebuggerFrame;

	#if 0
		LXmlEdit::CLXMLEditorApp* wndMain = new LXmlEdit::CLXMLEditorApp;
	//	wndMain->Show();
		LXmlEdit::CEXMLDocument* pDocument = new LXmlEdit::CEXMLDocument;
		pDocument->m_app = wndMain;
		pDocument->Load(WSTR("C:/mmstudio/help/filtest.html"));
		pDocument->ShowViews(NULL);
	#endif

	//	BrowserFrame* wndMain = new BrowserFrame;
	//	MailReaderFrame* wndMain = new MailReaderFrame;
	//	TTDebuggerFrame* wndMain = new TTDebuggerFrame;

		if (true)
		{
			wndMain->Show();
#if 0
			UI::WindowBase2* pBase2 = new UI::WindowBase2;
			pBase2->set_VisualTree(wndMain);

		//	pBase2->set_VisualTree(wndMain);

			UI::WindowHost* site = pScreen->OpenWindow();
			site->SetClient(pBase2);
			site->Show();
#endif
		}
		else
		{
		//

			WindowClientSocket* socket = new WindowClientSocket;
			socket->Socket();
			socket->Connect("localhost", 500);
			//socket->Connect("www.w3.org", 500);

			uint16 cmd = 1;
			int sent = socket->Send(&cmd, 2);
			ASSERT(sent == 2);
		}
	}

	/*
	{
		ArchFile arch;
#if WIN32
		FileByteStream file("C:/AmigaDebugger/liball.a");
#else
		FileByteStream file("WinHD_C:AmigaDebugger/liball.a");
#endif
		arch.Read(&file);
	}
	*/

#if 0
	{
#if 0
		_chdir("c:/mingw");

		char* argv[] =
		{
			NULL,
			"bin/main.o",
			"lib/gcc-lib/mingw32/3.2.3/libgcc.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libnix\\libnixmain.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libnix\\libnix.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\gcc-lib\\m68k-amigaos\\2.95.3\\libb\\libgcc.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libamiga.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libstdc++.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libnix\\libstubs.a",
		};
#endif

		char* argv[] =
		{
			NULL,
			"C:\\AmigaDebugger\\ncrt0.o",
			"C:\\AmigaDebugger\\main.o",
		//	"C:\\mmstudio\\extras\\Browser\\Browser.o",
//			"C:\\mmstudio\\extras\\Browser\\BrowserFrame.o",
//			"C:\\mmstudio\\extras\\LFC\\Object.o",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libstdc++.a",
			"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libnix\\libnixmain.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libnix\\libnix.a",
			"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\libnix\\libstubs.a",
		//	"C:\\Program Files\\Cloanto\\Amiga Forever\\Emulation\\shared\\dir\\Work\\devkits\\compilers\\gcc\\classic\\stable\\lib\\gcc-lib\\m68k-amigaos\\2.95.3\\libgcc.a",
		};

		main(sizeof(argv) / sizeof(char*), argv);
		return 0;
	}
#endif

#if AMIGA

//	_RunCommand("c:list");

	if (wndMain)
	{
		messageLoop.AddSignalHandler(1<<nSig, wndMain);
	}
#endif

//	UI::g_nWindows++;
	int nRet = messageLoop.Run();

//	delete wndMain;

//	_Module.RemoveMessageLoop();
	return nRet;
}

}	// System

#if WIN32

using namespace System;

//int WINAPI _tWinMain(MSWindows::HINSTANCE hInstance, MSWindows::HINSTANCE /*hPrevInstance*/, const char* /*LPTSTR*/ lpstrCmdLine, int nCmdShow)
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*LPTSTR*/ lpstrCmdLine, int nCmdShow)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPWSTR /*LPTSTR*/ lpstrCmdLine, int nCmdShow)
//int WINAPI wWinMainCRTStartup(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPWSTR lpstrCmdLine, int nCmdShow)
{
	LoadTypes(hInstance);

#if 0
	HRESULT hRes = ::OleInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ASSERT(SUCCEEDED(hRes));

#if 0
#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_BAR_CLASSES;	// change to support other controls
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ASSERT(bRet);
#else
	::InitCommonControls();
#endif
#endif
#endif

	_Module.m_hInstance = hInstance;
//	hRes = _Module.Init(ObjectMap, hInstance);
	//ATLASSERT(SUCCEEDED(hRes));

#if 0
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
#endif

	int nRet = 0;
	char szTokens[] = ("-/");
	bool bRun = true;
	bool bAutomation = false;

#if 0
	LPCTSTR lpszToken = _Module.FindOneOf(::GetCommandLine(), szTokens);
	while(lpszToken != NULL)
	{
		if(lstrcmpi(lpszToken, _T("UnregServer")) == 0)
		{
			nRet = _Module.UnregisterServer();
			bRun = false;
			break;
		}
		else if(lstrcmpi(lpszToken, _T("RegServer")) == 0)
		{
			nRet = _Module.RegisterServer();
			bRun = false;
			break;
		}
		else if((lstrcmpi(lpszToken, _T("Automation")) == 0) ||
			(lstrcmpi(lpszToken, _T("Embedding")) == 0))
		{
			bAutomation = true;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}
#endif

	if (false)
	{
		LPCWSTR cmdline = ::GetCommandLineW();

	//	::MessageBoxW(NULL, cmdline, L"", MB_OK);

		if (wcsstr(cmdline, L"remote"))
		{
			MessageBoxW(NULL, L"remote", L"", MB_OK);

			InitTypes();

		//	LDraw::Init();

		//	InitTypes();

			Remoting::ListenerSocket* pSocket = new Remoting::ListenerSocket;
			pSocket->Create(500);
			pSocket->Listen();

			UI::g_nWindows++;

			UI::MessageLoop loop;

			loop.Run();

			return 0;
		}
		else
		{
			System::InitTypes();

			AppDomain* ad = CreateDomain();

			TestingRemote* obj = static_cast<TestingRemote*>(ad->CreateInstanceAndUnwrap(NULL, WSTR("TestingRemote")));

			obj->TestMethod(NULL);

			return 0;
		}
	}

	if(bRun)
	{
#if 0
		_Module.StartMonitor();
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
		ASSERT(SUCCEEDED(hRes));
		hRes = ::CoResumeClassObjects();
		ASSERT(SUCCEEDED(hRes));

		if(bAutomation)
		{
			CMessageLoop theLoop;
			nRet = theLoop.Run();
		}
		else
#endif
		{
			try
			{
				System::InitTypes();
				nRet = System::Run(/*lpstrCmdLine, nCmdShow*/);
			}
			catch(Exception* e)
			{
				MessageBoxW(NULL, e->get_Reason()->c_str(), L"Exception", MB_OK);
			}
		}

#if 0
		_Module.RevokeClassObjects();
		::Sleep(_Module.m_dwPause);
#endif
	}

#if 0
	_Module.Term();
#endif

#if 0
	::OleUninitialize();
#endif

#if 0
	checkleaks();
#endif

	return nRet;
}

#endif

#if AMIGA

//#include "../CodeComp/debug.h"

//#include "DisassemblyWnd.h"
//#include "CallStackWnd.h"

struct GfxBase* GfxBase;
struct IntuitionBase* IntuitionBase;
struct Library* P96Base;

#if 0
long OnCommand(long nCommand)
{
	switch (nCommand)
	{
	case ID_FILE_OPEN:
		{
			OnFileOpen(nCommand);
		}
		break;

	case ID_DEBUG_GO:
		{
			sr &= ~(1<<15);	// clear trace bit
			Signal(task, 1<<nDebugeeSig);
		}
		break;

	case ID_DEBUG_STEPINTO:
		{
			sr |= 1<<15;	// set trace bit
			Signal(task, 1<<nDebugeeSig);
		}
		break;
	}
}
#endif

namespace System
{

//struct Window* pWindow;
//struct Menu* pMenu;

#if 0
////////////////////////////////////////////////////////////////////////////
// WindowBase

WindowBase::WindowBase()
{
	m_pWindow = NULL;
	m_pMenu = NULL;
}

WindowBase::~WindowBase()
{
	if (m_pWindow)
	{
		SetMenuStrip(m_pWindow, NULL);
		CloseWindow(m_pWindow);
		m_pWindow = NULL;
	}

	if (m_pMenu)
	{
		FreeMenus(m_pMenu);
		m_pMenu = NULL;
	}
}

void WindowBase::SetMenu(struct Menu* pMenu)
{
	if (m_pWindow)
	{
		SetMenuStrip(m_pWindow, pMenu);

		if (m_pMenu)
			FreeMenus(m_pMenu);

		m_pMenu = pMenu;
	}
	else
	{
		if (m_pMenu)
			FreeMenus(m_pMenu);

		m_pMenu = pMenu;
	}
}

//extern struct MsgPort* pUserPort;

void WindowBase::Show()
{
	if (m_pWindow == NULL)
	{
		m_pWindow = OpenWindowTags(NULL,
			(WA_Title), (ULONG)"Disassembly",
			(WA_Activate), TRUE,
			(WA_Width), 400,
			(WA_Height), 400,
			(WA_NewLookMenus), TRUE,
			(WA_Flags), WFLG_SIMPLE_REFRESH | WFLG_GIMMEZEROZERO | WFLG_DRAGBAR | WFLG_SIZEGADGET | WFLG_CLOSEGADGET | WFLG_DEPTHGADGET,
			(WA_IDCMP), 0,
			(WA_MinWidth), 64,
			(WA_MinHeight), 24,
			(WA_MaxWidth), ~0,
			(WA_MaxHeight), ~0,
			(TAG_DONE));
		if (m_pWindow)
		{
			m_pWindow->UserData = reinterpret_cast<uint8*>(static_cast<WindowBase*>(this));

			m_pWindow->UserPort = pUserPort;
			ModifyIDCMP(m_pWindow, IDCMP_NEWSIZE | IDCMP_REFRESHWINDOW | IDCMP_MENUPICK | IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY);

			if (m_pMenu)
			{
				SetMenuStrip(m_pWindow, m_pMenu);
			}
		}
	}
	else
	{
		ActivateWindow(m_pWindow);
	}
}

void WindowBase::Invalidate()
{
	// hm..
	OnPaint();
}

int WindowBase::HandleIntuiMessage(struct IntuiMessage* pMsg)
{
	ULONG Class = pMsg->Class;
	UWORD Code = pMsg->Code;
	
	switch (Class)
	{
	case IDCMP_NEWSIZE:
		{
			OnSize(m_pWindow->Width, m_pWindow->Height);
		}
		break;

	case IDCMP_REFRESHWINDOW:
		{

			BeginRefresh(pMsg->IDCMPWindow);
			OnPaint();
			EndRefresh(pMsg->IDCMPWindow, TRUE);
		}
		break;

	case IDCMP_MENUPICK:
		{

		//	printf("%d -> %d -> %d\n", MENUNUM(Code), ITEMNUM(Code), SUBNUM(Code));
		//	bContinue = FALSE;

			int menunum = MENUNUM(Code);
			struct Menu* m = m_pMenu;
			while (menunum > 0)
			{
				m = m->NextMenu;
				menunum--;
			}
			int itemnum = ITEMNUM(Code);
			struct MenuItem* mi = m->FirstItem;
			while (itemnum)
			{
				mi = mi->NextItem;
				itemnum--;
			}
			
			ULONG nCommand = (ULONG)GTMENUITEM_USERDATA(mi);

			OnCommand(nCommand);
		}
		break;

	case IDCMP_VANILLAKEY:
		{
			::OnCommand(ID_DEBUG_STEPINTO);
		}
		break;
		
	case IDCMP_CLOSEWINDOW:
		{
			return 1;	// TODO
		}
		break;
	}

	return 0;
}
#endif

//#include "mainfrm.h"

#if 0
void mainloop()
{
	/*
	DesktopScreen* pScreen = new DesktopScreen;
	DebuggerFrame* wndMain = new DebuggerFrame;
	pScreen->OpenWindow(wndMain);
	*/

	DesktopScreen* pScreen = new DesktopScreen;

	DebuggerFrame* wndMain = new DebuggerFrame;
	WindowBase2* pBase2 = new WindowBase2;
	pBase2->put_VisualTree(wndMain);

	WindowHost* site = pScreen->OpenWindow();
	site->SetClient(pBase2);
	site->Show();

	int nRet = MessageLoop();

//	BrowserFrame* wndMain = new BrowserFrame;

#if 0
	g_nWindows++;

	CUIFrameImpl* frame = new CUIFrameImpl;

	DebuggerFrame* wndMain = new DebuggerFrame;
	frame->m_pClient = wndMain;
	wndMain->m_pSite = frame;
	frame->Show();

//	wndMain->OpenFile("test.cpp");

	int nRet = MessageLoop();

	/*
	wndMain->OnFileOpenProgram();

	wndMain->OnDebugGo();
	*/

//	OpenProgram("test.exe");
//	pDisasmWnd->SetActive((ULONG)ret_pc);

	wndMain->m_pSite->Close();

//	delete wndMain;
#endif
}
#endif

}

#include "../LFC/Linker.h"

extern System::Linker* plinker;

struct Task* pMonitorTask;

extern "C" void VTrap0();
extern "C" void VTrace();

struct Screen* g_Screen;

namespace System
{
	extern void load_t2();
}

using namespace System;

int main(int argc, char* argv[])
{
	printf("%d\n", plinker);

	ASSERT(pD == NULL);
	pD = new CVR;

	{
		gsymmap_t::iterator it = plinker->m_globsyms.begin();

		while (it != plinker->m_globsyms.end())
		{
			GlobalSymbol* psym = (*it).second;

			if (strstr(psym->m_name->c_str(), "9IAddChild"))
			{
				printf("symbol %s\n", psym->m_name->c_str());
			}

		//	if (psym->m_syms.size())
			{
				if (psym->setResolvedValue)
				{
					pD->m_symbols.insert(multimap<StringA*, ULONG_PTR, Ref_Less<StringA>, __gc_allocator>::value_type(psym->m_name, psym->setResolvedValue));
				}
			}

			++it;
		}
	}

	//printf("addr: %p\n", typeid(IAddChild));

	System::load_t2();

	printf("sizeof(UI::DependencyObject) actual: %d, calced: %d\n", sizeof(UI::DependencyObject), typeid(UI::DependencyObject).GetType()->get_sizeof());
	printf("sizeof(UI::Animatable) actual: %d, calced: %d\n", sizeof(UI::Animatable), typeid(UI::Animatable).GetType()->get_sizeof());
	printf("sizeof(UI::Visual) actual: %d, calced: %d\n", sizeof(UI::Visual), typeid(UI::Visual).GetType()->get_sizeof());
	printf("sizeof(UI::UIElement) actual: %d, calced: %d\n", sizeof(UI::UIElement), typeid(UI::UIElement).GetType()->get_sizeof());
	printf("sizeof(UI::Shape) actual: %d, calced: %d\n", sizeof(UI::Shape), typeid(UI::Shape).GetType()->get_sizeof());
	printf("sizeof(LDraw::RectD) actual: %d, calced: %d\n", sizeof(LDraw::RectD), typeid(LDraw::RectD).GetType()->get_sizeof());

	printf("offsetof(Animatable, m_baseValues), actual: %d, calced: %d\n", offsetof(UI::Animatable, m_baseValues), typeid(UI::Animatable).GetType()->GetClass()->GetDeclarator(new StringA("m_baseValues"))->m_offset);

	printf("offsetof(Visual, m_userdata), actual: %d, calced: %d\n", offsetof(UI::Visual, m_userdata), typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_userdata"))->m_offset);
	printf("offsetof(Visual, m_expandedBBox), actual: %d, calced: %d\n", offsetof(UI::Visual, m_expandedBBox), typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_expandedBBox"))->m_offset);
	printf("offsetof(Visual, m_expandedBBoxParent), actual: %d, calced: %d\n", offsetof(UI::Visual, m_expandedBBoxParent), typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_expandedBBoxParent"))->m_offset);
	printf("offsetof(Visual, m_LayoutTransform), actual: %d, calced: %d\n", offsetof(UI::Visual, m_LayoutTransform), typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_LayoutTransform"))->m_offset);
	printf("offsetof(Visual, m_pDrawCommands), actual: %d, calced: %d\n", offsetof(UI::Visual, m_pDrawCommands), typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_pDrawCommands"))->m_offset);

	printf("offsetof(UIElement, m_pDockParent), actual: %d, calced: %d\n", offsetof(UI::UIElement, m_pDockParent), typeid(UI::UIElement).GetType()->GetClass()->GetDeclarator(new StringA("m_pDockParent"))->m_offset);
	printf("offsetof(UIElement, m_redrawNext), actual: %d, calced: %d\n", offsetof(UI::UIElement, m_redrawNext), typeid(UI::UIElement).GetType()->GetClass()->GetDeclarator(new StringA("m_redrawNext"))->m_offset);

	ASSERT(sizeof(UI::Animatable) == typeid(UI::Animatable).GetType()->get_sizeof());
	ASSERT(sizeof(UI::UIElement) == typeid(UI::UIElement).GetType()->get_sizeof());
	ASSERT(sizeof(UI::Shape) == typeid(UI::Shape).GetType()->get_sizeof());
	ASSERT(sizeof(UI::Polyline) == typeid(UI::Polyline).GetType()->get_sizeof());
	ASSERT(sizeof(UI::Button) == typeid(UI::Button).GetType()->get_sizeof());
	ASSERT(sizeof(UI::ChildWindow) == typeid(UI::ChildWindow).GetType()->get_sizeof());
	ASSERT(sizeof(UI::ChildWindowContainer) == typeid(UI::ChildWindowContainer).GetType()->get_sizeof());

	ASSERT(offsetof(UI::Visual, m_userdata) == typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_userdata"))->m_offset);
	ASSERT(offsetof(UI::Visual, m_expandedBBox) == typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_expandedBBox"))->m_offset);
	ASSERT(offsetof(UI::Visual, m_expandedBBoxParent) == typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_expandedBBoxParent"))->m_offset);
	ASSERT(offsetof(UI::Visual, m_LayoutTransform) == typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_LayoutTransform"))->m_offset);
	ASSERT(offsetof(UI::Visual, m_pDrawCommands) == typeid(UI::Visual).GetType()->GetClass()->GetDeclarator(new StringA("m_pDrawCommands"))->m_offset);

	ASSERT(offsetof(UI::UIElement, m_pDockParent) == typeid(UI::UIElement).GetType()->GetClass()->GetDeclarator(new StringA("m_pDockParent"))->m_offset);
	ASSERT(offsetof(UI::UIElement, m_redrawNext) == typeid(UI::UIElement).GetType()->GetClass()->GetDeclarator(new StringA("m_redrawNext"))->m_offset);

	ASSERT(sizeof(DebuggerFrame) == typeid(DebuggerFrame).GetType()->get_sizeof());

//	printf("Hello\n");
//	return 0;

	ASSERT(IntuitionBase == NULL);
	IntuitionBase = (struct IntuitionBase*)execOpenLibrary(SysBase, "intuition.library", 39);
	if (IntuitionBase == NULL)
	{
		printf("Requires v39\n");
		return 10;
	}
	GfxBase = (struct GfxBase*)execOpenLibrary(SysBase, "graphics.library", 39);
	P96Base = (struct Library*)execOpenLibrary(SysBase, "Picasso96API.library", 2);
	KeymapBase = execOpenLibrary(SysBase, "keymap.library", 0);

	fplog2 = fopen("WinHD_C:alog.txt", "w");

	pMonitorTask = FindTask(NULL);
	nSig = AllocSignal(-1);

//	addr = (ULONG)0;
//	ret_pc = addr;

	UI::pUserPort = CreateMsgPort();

#if 0
	struct NewMenu nm[] =
	{
		NM_TITLE, (STRPTR)"Project", NULL, 0/*flags*/, 0, NULL,
			NM_ITEM, (STRPTR)"Open...", NULL, 0/*flags*/, 0, (APTR)ID_FILE_OPEN,
			NM_ITEM, (STRPTR)"Save As...", NULL, 0/*flags*/, 0, NULL,
			NM_ITEM, (STRPTR)"Exit", NULL, 0/*flags*/, 0, NULL,
		NM_TITLE, (STRPTR)"Edit", NULL, 0/*flags*/, 0, NULL,
			NM_ITEM, (STRPTR)"Cut", (STRPTR)"X", NM_COMMANDSTRING/*flags*/, 0, NULL,
			NM_ITEM, (STRPTR)"Copy", (STRPTR)"C", NM_COMMANDSTRING/*flags*/, 0, NULL,
			NM_ITEM, (STRPTR)"Paste", (STRPTR)"V", NM_COMMANDSTRING/*flags*/, 0, NULL,
		NM_TITLE, (STRPTR)"Debug", NULL, 0/*flags*/, 0, NULL,
			NM_ITEM, (STRPTR)"Go", (STRPTR)NULL, 0/*flags*/, 0, (APTR)ID_DEBUG_GO,
			NM_ITEM, (STRPTR)"Step Into", (STRPTR)NULL, 0/*flags*/, 0, (APTR)ID_DEBUG_STEPINTO,
		NM_END
	};
#endif

	g_Screen = LockPubScreen(NULL);

	APTR vi = GetVisualInfoA(g_Screen, NULL);

//	pDisasmWnd = new CDisassemblyWnd;

#if 0
	struct Menu* pMenu = CreateMenusA(nm, NULL);
	LayoutMenus(pMenu, vi, (GTMN_NewLookMenus), TRUE, (TAG_DONE));
#endif

#if 0
	pDisasmWnd->SetMenu(pMenu);
	pDisasmWnd->Show();
#endif

	ULONG OldTrap[2];

	OldTrap[0] = *(ULONG*)0x24;
	OldTrap[1] = *(ULONG*)0x80;

	*(ULONG*)0x24 = (ULONG)VTrace;
	*(ULONG*)0x80 = (ULONG)VTrap0;

	/*
	char* buffer = (char*)AllocMem(8, 0);
	buffer[9] = 2;

	FreeMem(buffer, 8);
	*/

	//mainloop();

	Run();

//	char* data = new char[64];
//	data[0] = 3;
//	data[64] = 6;
//	delete data;

//	check();

//	CloseWindow(pWindow);
//	delete pDisasmWnd;

	FreeSignal(nSig);

	FreeVisualInfo(vi);
	UnlockPubScreen(NULL, g_Screen);

//	DeleteMsgPort(pUserPort);

	*(ULONG*)0x24 = OldTrap[0];
	*(ULONG*)0x80 = OldTrap[1];

//	printf("Done\n");

	fclose(fplog2);

	execCloseLibrary(SysBase, (struct Library*)IntuitionBase);
	IntuitionBase = NULL;

	execCloseLibrary(SysBase, (struct Library*)GfxBase);
	GfxBase = NULL;

	execCloseLibrary(SysBase, (struct Library*)P96Base);
	P96Base = NULL;

	execCloseLibrary(SysBase, (struct Library*)KeymapBase);
	KeymapBase = NULL;

	return 0;
}

#endif
