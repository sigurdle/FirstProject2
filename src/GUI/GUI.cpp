#include "stdafx.h"
#include "GUI2.h"

#include "physics.h"
#include <pxdefaulterrorcallback.h>
#include <pxdefaultallocator.h>

#pragma comment(lib, "LFC")
#pragma comment(lib, "Networking")
#pragma comment(lib, "Graphics")
#pragma comment(lib, "DShowPlayer")
#pragma comment(lib, "CSS")
#pragma comment(lib, "Expressive")

#if defined(PX_PHYSICS_NXPHYSICS_API)
#ifdef _M_IX86
#ifdef _DEBUG
#pragma comment(lib, "PhysX3_x86")
#pragma comment(lib, "PhysX3Common_x86")
#pragma comment(lib, "PhysX3Extensions")
#else
#pragma comment(lib, "PhysX3_x86")
#pragma comment(lib, "PhysX3Common_x86")
#pragma comment(lib, "PhysX3Extensions")

#endif
#else
#pragma comment(lib, "PhysX3_x64")
#pragma comment(lib, "PhysX3Common_x64")
#endif
#endif

#pragma comment(lib, "dwmapi")

#pragma comment(lib, "Uiautomationcore")

// Direct3D 10
//#pragma comment(lib, "d3d10_1")

/*
#ifdef _DEBUG
#pragma comment(lib, "d3dx10d")
#else
#pragma comment(lib, "d3dx10")
#endif
*/

//#pragma comment(lib, "dxgi")

/*
// Direct3D 9
#ifdef _DEBUG
#pragma comment( lib, "d3dx9d")
#else
#pragma comment(lib, "d3dx9")
#endif
*/

/*
// Direct2D / DirectWrite
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
*/

// DirectX Audio
#ifdef _DEBUG
#pragma comment(lib, "xapobased")
#else
#pragma comment(lib, "xapobase")
#endif

#pragma comment(lib, "xapofx")
#pragma comment(lib, "x3daudio")

// OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

// DShow
#pragma comment(lib, "Strmiids")
#pragma comment(lib, "Quartz")

namespace System
{

GUIEXT void Show(Graphics::Bitmap* bitmap)
{
	Gui::DrawBitmapVisual* v = new Gui::DrawBitmapVisual(bitmap);

	Gui::Window* win = new Gui::Window(v/*, LDraw::SizeF(600, 500)*/);
	win->set_Width(600);
	win->set_Height(500);

	AddView(bitmap, win);

	win->Show();
}

GUIEXT Gui::Window* Edit(Gui::Vector2_F* vec)
{
	Gui::GraphAxisVisual* ed = new Gui::GraphAxisVisual;
	ed->set_Width(800);
	ed->set_Height(700);

	ed->m_points.push_back(vec);
	ed->m_colors.push_back(new Gui::Color(1,0,0));

	Gui::Window* win = new Gui::Window(ed, gm::SizeF(600.0f, 500.0f));
	win->Show();

	return win;
}

namespace Gui
{

IMP_DEPENDENCY_PROPERTY(int, Date, Year, 0)
IMP_DEPENDENCY_PROPERTY(int, Date, DayOfWeek, 0)
IMP_DEPENDENCY_PROPERTY(int, Date, HourOfDay, 0)
IMP_DEPENDENCY_PROPERTY(int, Date, Second, 0)
IMP_DEPENDENCY_PROPERTY(int, Date, Minute, 0)
IMP_DEPENDENCY_PROPERTY(int, Date, Milliseconds, 0)

DependencyClass* Date::get_Class()
{
	static DependencyClass depclass(typeid(Date), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_YearProperty(),
		get_DayOfWeekProperty(),
		get_HourOfDayProperty(),
		get_SecondProperty(),
		get_MinuteProperty(),
		get_MillisecondsProperty(),
	};

	return &depclass;
}

DependencyClass* Date::pClass(get_Class());

Date::Date() : DependencyObject(get_Class())
{
}

Date* Date::get_CurrentDate()
{
	static Date date;
//	static __live_object_ptr<Date> date(new Date);

	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);

	date.set_Year(systemtime.wYear);
	date.set_DayOfWeek(systemtime.wDayOfWeek);
	date.set_HourOfDay(systemtime.wHour);
	date.set_Second(systemtime.wSecond);
	date.set_Minute(systemtime.wMinute);

	return &date;
}

GUIEXT void MakeScrollable(UIElement* element)
{
	ScrollViewer* scrollviewer = new ScrollViewer;
	UIElement* parent = element->get_LogicalParent();
	parent->ReplaceChild(0, scrollviewer);
	scrollviewer->set_Content(element);
}

GUIEXT String DefaultPrinter()
{
	WCHAR buffer[512];
	DWORD cb = _countof(buffer);
	if (!GetDefaultPrinter(buffer, &cb))
	{
		switch (GetLastError())
		{
		case ERROR_FILE_NOT_FOUND:
			raise(SystemException(L"There is no default printer"));
		}
	}

	return String(string_copy(buffer));
}

GUIEXT bool Print(Visual* visual)
{
//	Clipboard::get_Current();
	HWND hWnd = MessageWindow::GetHwnd();

	DOCINFO docInfo;
	ZeroMemory(&docInfo, sizeof(docInfo));
	docInfo.cbSize = sizeof(docInfo);
	docInfo.lpszDocName = L"Print Job";

	HDC hdcPrint;

	if (true)
	{
		PRINTPAGERANGE* pPageRanges = new PRINTPAGERANGE[1];

		PRINTDLGEX printDlg;
		ZeroMemory(&printDlg, sizeof(printDlg));
		printDlg.lStructSize = sizeof(printDlg);
		printDlg.hwndOwner = hWnd;
	//	printDlg.Flags = PD_RETURNDC;
	//	printDlg.hInstance = NULL;//_Module.GetInstance();
		printDlg.hDevMode = NULL;
		printDlg.hDevNames = NULL;
		printDlg.hDC = NULL;
		printDlg.Flags = PD_RETURNDC | PD_COLLATE;
		printDlg.Flags2 = 0;
		printDlg.ExclusionFlags = 0;
		printDlg.nPageRanges = 0;
		printDlg.nMaxPageRanges = 10;
		printDlg.lpPageRanges = pPageRanges;
		printDlg.nMinPage = 1;
		printDlg.nMaxPage = 2;
		printDlg.nCopies = 1;
		printDlg.hInstance = NULL;
		printDlg.lpPrintTemplateName = NULL;
		printDlg.lpCallback = NULL;
		printDlg.nPropertyPages = 0;
		printDlg.lphPropertyPages = NULL;
		printDlg.nStartPage = START_PAGE_GENERAL;
		printDlg.dwResultAction = 0;

		HRESULT hr = PrintDlgEx(&printDlg);
		if (FAILED(hr))
		{
			return false;
		}

		hdcPrint = printDlg.hDC;

		if (printDlg.dwResultAction != PD_RESULT_PRINT)
			return false;
	}
	else
	{
	//	hdcPrint = CreateDC(NULL, buffer, NULL, NULL);
	}

	if (!(GetDeviceCaps(hdcPrint, RASTERCAPS) & RC_STRETCHDIB)) 
	{ 
		DeleteDC(hdcPrint);

		MessageBox(hWnd,
			L"Printer does not support StretchDIBits",
			L"Device Error",
			MB_OK | MB_ICONINFORMATION);

		return false;
	}

// Retrieve the number of pixels-per-logical-inch in the 
    // horizontal and vertical directions for the display upon which 
    // the bitmap was created. These are likely the same as for 
    // the present display, so we use those values here. 
 
//    hWinDC = GetDC(hWnd);
  //  float fLogPelsX1 = (float)GetDeviceCaps(hWinDC, LOGPIXELSX); 
//    float fLogPelsY1 = (float)GetDeviceCaps(hWinDC, LOGPIXELSY); 
	float fLogPelsX1 = (float)96;
	float fLogPelsY1 = (float)96;

	// Retrieve the number of pixels-per-logical-inch in the 
	// horizontal and vertical directions for the printer upon which 
	// the bitmap will be printed. 

	float fLogPelsX2 = (float)GetDeviceCaps(hdcPrint, LOGPIXELSX); 
	float fLogPelsY2 = (float)GetDeviceCaps(hdcPrint, LOGPIXELSY); 

	int cWidthPels = GetDeviceCaps(hdcPrint, HORZRES); 
	int cHeightPels = GetDeviceCaps(hdcPrint, VERTRES); 

    // Determine the scaling factors required to print the bitmap and 
    // retain its original proportions. 
 
	float scaleX, scaleY;

    if (fLogPelsX1 > fLogPelsX2) 
        scaleX = (fLogPelsX1 / fLogPelsX2); 
    else
		scaleX = (fLogPelsX2 / fLogPelsX1); 
 
    if (fLogPelsY1 > fLogPelsY2) 
        scaleY = (fLogPelsY1 / fLogPelsY2); 
    else
		scaleY = (fLogPelsY2 / fLogPelsY1); 

	StartDoc(hdcPrint, &docInfo);

	StartPage(hdcPrint);

	int bitmapWidth = 800;
	int bitmapHeight = 800;

	Graphics::Bitmap* bitmap = visual->GetBitmap(NULL, bitmapWidth, bitmapHeight, scaleX, scaleY);

	Graphics::Bitmap* bitmap2 = new Graphics::Bitmap(Graphics::Direct10::get_D3DDevice(), Graphics::D3D10Texture2D(Graphics::Direct10::get_D3DDevice(), bitmapWidth, bitmapHeight, DXGI_FORMAT_R8G8B8A8_UNORM, D3D10_USAGE_STAGING));
	Graphics::Direct10::get_D3DDevice()->CopyResource(bitmap2->m_d3d10_texture, bitmap->m_d3d10_texture);

	BITMAPV4HEADER bh = {0};
	bh.bV4Size = sizeof(BITMAPINFOHEADER);
	bh.bV4Width = bitmapWidth;
	bh.bV4Height = -bitmapHeight;
	bh.bV4Planes = 1;
	bh.bV4BitCount = 32;
	bh.bV4V4Compression = BI_RGB;
	bh.bV4SizeImage = 0;

	ASSERT(0);
#if 0
	Graphics::MAPPED_TEXTURE2D mapped;
	bitmap2->Map(D3D10_MAP_READ, &mapped);
	for (int y = 0; y < bitmapHeight; ++y)
	{
		ubyte* p = (byte*)mapped.pData + mapped.RowPitch * y;
		for (int x = 0; x < bitmapWidth; ++x)
		{
			ubyte add = 255 * (255-p[3]) / 255;
			p[0] = (int)p[0] * p[3] / 255 + add;
			p[1] = (int)p[1] * p[3] / 255 + add;
			p[2] = (int)p[2] * p[3] / 255 + add;

			p += 4;
		}
	}

	int destX = 0;
	int destY = 0;

	int scanlines = StretchDIBits(hdcPrint,
		destX, destY, bitmapWidth, bitmapHeight,
		0, 0, bitmapWidth, bitmapHeight,
		mapped.pData, (BITMAPINFO*)&bh,
		DIB_RGB_COLORS, SRCCOPY);

	bitmap2->Unmap();
#endif
#if 0
	HRESULT hr;

	ID2D1DCRenderTarget* dcRenderTarget;
	hr = GL::Direct10::get_D2DFactory()->CreateDCRenderTarget(
		//&D2D1::RenderTargetProperties(),
		&D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM/*DXGI_FORMAT_UNKNOWN*/, D2D1_ALPHA_MODE_IGNORE/*D2D1_ALPHA_MODE_PREMULTIPLIED*/),
			fLogPelsX2, fLogPelsY2),

		&dcRenderTarget);

	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = 2000;
	rc.bottom = 1000;
	hr = dcRenderTarget->BindDC(hdcPrint, &rc);

	GL::RenderTarget rt(dcRenderTarget);
	ImmediateRenderContext renderContext(&rt);
	visual->Render_(&renderContext);
#endif

//	graphics = new Graphics(hdcPrint);
//	graphics->DrawRectangle(pen, 50, 50, 200, 300);
//	delete graphics;

	EndPage(hdcPrint);

	EndDoc(hdcPrint);

	DeleteDC(hdcPrint);

//	dcRenderTarget->Release();

	return true;
}

GUIEXT Window* Show(Geometry* geometry)
{
	StrokeGeometryVisual* vis = new StrokeGeometryVisual(geometry);

	Gui::Window* win = new Gui::Window(vis, gm::SizeF(600, 500));
	win->Show();

	return win;
}

GUIEXT Window* Show(Visual* visual)
{
	Gui::Window* win = new Gui::Window(visual);
	win->set_Width(600);
	win->set_Height(500);
	win->Show();

	return win;
}

class Init
{
public:
	CTOR Init();
};

physx::PxFoundation* gPhysicsFoundation;
physx::PxPhysics* gPhysics;

Init init;

Init::Init()
{
	
	// TODO, not this

	////////////////////////

	RAWINPUTDEVICE Rid[1];

	Rid[0].usUsagePage = 0x01; 
	Rid[0].usUsage = 0x02; 
	Rid[0].dwFlags = 0;
//	Rid[0].dwFlags = RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
	Rid[0].hwndTarget = 0;

	/*
	Rid[1].usUsagePage = 0x01; 
	Rid[1].usUsage = 0x06; 
	Rid[1].dwFlags = RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
	Rid[1].hwndTarget = 0;
*/
	if (RegisterRawInputDevices(Rid, 1, sizeof(Rid[0])) == FALSE)
	{
		//registration failed. Call GetLastError for the cause of the error
		DWORD error = GetLastError();
	}

	UINT numDevices;
	UINT count = GetRawInputDeviceList(NULL, &numDevices, sizeof(RAWINPUTDEVICELIST));

	RAWINPUTDEVICELIST* deviceList = new RAWINPUTDEVICELIST[numDevices];

	count = GetRawInputDeviceList(deviceList, &numDevices, sizeof(RAWINPUTDEVICELIST));
	for (size_t i = 0; i < numDevices; ++i)
	{
		RAWINPUTDEVICELIST& rawDevice = deviceList[i];

		WCHAR name_buffer[512];
		UINT size = _countof(name_buffer);
		GetRawInputDeviceInfoW(rawDevice.hDevice, RIDI_DEVICENAME, name_buffer, &size);

		DebugTrace(name_buffer << "\n");

		RID_DEVICE_INFO deviceInfo;
		size = sizeof(deviceInfo);
		GetRawInputDeviceInfoW(rawDevice.hDevice, RIDI_DEVICEINFO, &deviceInfo, &size);
		switch (deviceInfo.dwType)
		{
		case RIM_TYPEMOUSE:
			DebugTrace("Mouse " << deviceInfo.mouse.dwId << "," << deviceInfo.mouse.dwNumberOfButtons << " buttons\n");
			break;

		case RIM_TYPEKEYBOARD:
			DebugTrace("Keyboard " << deviceInfo.keyboard.dwNumberOfFunctionKeys << "function keys\n");
			break;

		case RIM_TYPEHID:
			DebugTrace("HID ProductID: " << deviceInfo.hid.dwProductId << "\n");
			break;
		}

		DebugTrace("\n");
	}
}

static physx::PxDefaultErrorCallback gDefaultErrorCallback;
static physx::PxDefaultAllocator gDefaultAllocatorCallback;

GUIEXT void InitPhysics()
{
#if defined(PX_PHYSICS_NXPHYSICS_API)

//	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, &myAllocator, &myOutputStream);
	gPhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if (gPhysicsFoundation == nullptr)
	{
		MessageBox(nullptr, L"Wrong SDK DLL version?", L"", MB_OK | MB_ICONWARNING);
	}

//	auto mProfileZoneManager = &physx::PxProfileZoneManager::createProfileZoneManager(mFoundation);

	bool recordMemoryAllocations = true;
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gPhysicsFoundation,
		physx::PxTolerancesScale(), recordMemoryAllocations);
	if (gPhysics == nullptr)
	{
		MessageBox(nullptr, L"Wrong SDK DLL version?", L"", MB_OK | MB_ICONWARNING);
	}

#else

#endif
}

GUIEXT void ReleasePhysics()
{
	gPhysics->release();
	gPhysics = nullptr;

	gPhysicsFoundation->release();
	gPhysicsFoundation = nullptr;
}

GUIEXT IO::TextReader& ReadFromStream(IO::TextReader& stream, ComBSTR& str)
{
	OLECHAR buffer[4096];
	uint nchars = stream.ReadChars32(buffer, _countof(buffer));
	str.Attach(SysAllocStringLen(buffer, nchars));

	return stream;
}

Directory::Directory()
{
	WCHAR buffer[512];
	GetCurrentDirectoryW(512, buffer);
	m_path = buffer;
}

// static
Directory* Directory::get_Current()
{
	return &s_Current;
}

// static
Directory Directory::s_Current;

/*
struct Field_cl
{
	unsigned int offset;
};

struct BITMAPINFOHEADER_class
{
	static const unsigned int size = sizeof(BITMAPINFOHEADER);
	static const unsigned int nfields = 11;
	static Field_cl* fields[nfields];
};

template<class T> Write(T* p)
{
	for (size_t n = 0; T::class_info::nfields; ++n)
	{
		(byte*)T::class_info::fields[n].offset
	}
}
*/

GUIEXT bool SaveBMP(Graphics::Bitmap* bitmap, StringIn filename)
{
	ThrowHr hr;

	D3D10_TEXTURE2D_DESC desc;
	bitmap->m_d3d10_texture->GetDesc(&desc);

	ASSERT(0);
#if 0
	Graphics::Bitmap::Data mapped;// = bitmap->MapRead();

	int width = bitmap->GetWidth();
	int height = bitmap->GetHeight();
	int rowbytes = ROWBYTES_DWORD(width, 24);

	byte padbytes[3] = {0};
	uint npadbytes = rowbytes - (width*3);

	IO::FileStream file(filename, IO::FileMode_Create, IO::FileAccess_Write);
	IO::BinaryWriter stream(&file);

	stream << uint16(0x4d42);
	stream << uint32(0);
	stream << uint16(0);// bfReserved1;
	stream << uint16(0);// bfReserved2;
	stream << uint32(14/*sizeof(BITMAPFILEINFO)*/ + sizeof(BITMAPINFOHEADER));// bfOffBits;

	stream << uint32(sizeof(BITMAPINFOHEADER));
	stream << int32(width);
	stream << int32(height);
	stream << int16(1);	// nplanes
	stream << int16(24);	// bitcount
	stream << uint32(BI_RGB);	// compression
	stream << uint32(0);	// biSizeImage
	stream << int32(0);	// biXPelsPerMeter
	stream << int32(0);	// biYPelsPerMeter
	stream << uint32(0);	// biClrUsed
	stream << uint32(0);	// biClrImportant

	/*
	uint32 biSize;
	int32 biWidth;
	int32 biHeight;
	uint16 biPlanes;
	uint16 biBitCount;
	uint32 biCompression;
	uint32 biSizeImage;
	int32 biXPelsPerMeter;
	int32 biYPelsPerMeter;
	uint32 biClrUsed;
	uint32 biClrImportant;
	*/
	for (size_t y = 0; y < height; ++y)
	{
		byte* src = (byte*)mapped.pData + mapped.RowPitch * (height-y-1);

		switch (desc.Format)
		{
		case DXGI_FORMAT_A8_UNORM:
			{
				ASSERT(0);

				for (size_t x = 0; x < width; ++x)
				{
					stream << src[0];
					stream << src[0];
					stream << src[0];

					src += 1;
				}
			}
			break;

		case DXGI_FORMAT_R8G8B8A8_UNORM:
			{
				for (size_t x = 0; x < width; ++x)
				{
					stream << src[2];
					stream << src[1];
					stream << src[0];

					src += 4;
				}
			}
			break;

		case DXGI_FORMAT_B8G8R8X8_UNORM:
			{
				for (size_t x = 0; x < width; ++x)
				{
					stream << src[0];
					stream << src[1];
					stream << src[2];

					src += 4;
				}
			}
			break;

		default:
			__assume(0);
			ASSERT(0);
		}

		stream.Write(padbytes, npadbytes);
	}
#endif

	return true;
}

DXEffect::DXEffect()
{
}

DXEffect::DXEffect(StringIn filename)
{
	bool success = Load(filename);
}

bool DXEffect::Load(StringIn filename)
{
	HRESULT hr;

	ID3D10Blob* errors = NULL;

	UINT hlslFlags = 0;
	hlslFlags |= D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
	hlslFlags |= D3D10_SHADER_DEBUG;
	hlslFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	hr = D3DX10CreateEffectFromFileW(CStringw(filename).c_str(), NULL, NULL, "fx_4_0", hlslFlags, 0, Graphics::Direct10::get_D3DDevice(), NULL, NULL, &m_effect, &errors, NULL);
	if (FAILED(hr))
	{
		switch (hr)
		{
		case D3D10_ERROR_FILE_NOT_FOUND:
			MessageBox(NULL, L"fx file not found\n", L"Draw", MB_OK);
			break;
		}

		String errormsg;

		if (errors)
		{
			SIZE_T size = errors->GetBufferSize();
			errormsg = (char*)errors->GetBufferPointer();
			errors->Release();
		}

		return false;
		//raise(Exception("effect err: " + errormsg));
	}

	m_effect->GetDesc(&m_desc);

//		m_RenderTextureTechnique = m_effect->GetTechniqueByName("RenderTexture");

	return true;
}

ClassType* DXEffect::GenerateClass(StringIn name)
{
#if 0
	ClassType* pEffType = new ClassType;
	pEffType->m_name = name;
	pEffType->m_kwType = ClassKey_class;
	pEffType->m_bases.push_back(new BaseClass(typeid(EffectBase).GetType()->GetClass()));

	for (uint i = 0; i < m_desc.Techniques; ++i)
	{
		ID3DX11EffectTechnique* technique = m_effect->GetTechniqueByIndex(i);

		D3DX11_TECHNIQUE_DESC desc;
		technique->GetDesc(&desc);

		ClassType* pTechType = new ClassType;
		pTechType->m_name = desc.Name;
		pTechType->m_kwType = ClassKey_class;
		pTechType->m_bases.push_back(new BaseClass(typeid(EffectTechniqueBase).GetType()->GetClass()));

		Declarator* decl = new Declarator;
		decl->m_pType = pTechType;
		decl->m_name = pTechType->m_name;
		decl->m_typedef = true;

		pEffType->m_pScope->AddDeclarator(decl);
	}

	for (uint i = 0; i < m_desc.GlobalVariables; ++i)
	{
		ID3DX11EffectVariable* pVariable = m_effect->GetVariableByIndex(i);

		D3DX11_EFFECT_VARIABLE_DESC vardesc;
		pVariable->GetDesc(&vardesc);

		ID3DX11EffectType* pVarType = pVariable->GetType();
		D3DX11_EFFECT_TYPE_DESC typedesc;
		pVarType->GetDesc(&typedesc);

		Type* pType;
		if (typedesc.TypeName == StringIn("int"))
		{
			pType = typeid(int);
		}
		else if (typedesc.TypeName == StringIn("float"))
		{
			pType = typeid(float);
		}
		else if (typedesc.TypeName == StringIn("double"))
		{
			pType = typeid(double);
		}
		else if (typedesc.TypeName == StringIn("Texture2D"))
		{
			pType = typeid(ID3D10ShaderResourceView*);
		}
		else if (typedesc.Type == D3D10_SVT_TEXTURE)
		{
			pType = typeid(ID3D10ShaderResourceView*);
		}
		else if (typedesc.Type == D3D10_SVT_TEXTURE2D)
		{
			pType = typeid(ID3D10ShaderResourceView*);
		}
		else
		{
			pType = TypeDatabase::pD->m_namedTypesM.find(typedesc.TypeName)->second;
			/*
			if (pType == NULL)
			{
				pType = typeid(void).GetType();
			}
			*/
		}

		if (pType == NULL)
		{
			MessageBeep(-1);
		}

		if (pType)
		{
			FunctionType* pFun = new FunctionType();
			pFun->m_pReturnType = pType;
			IO::StringWriter stream;
			stream << typedesc.TypeName << " value;m_" << vardesc.Name << "->";

			if (typedesc.Class == D3D10_SVC_SCALAR)
			{
				switch (typedesc.Type)
				{
				case D3D10_SVT_BOOL:	stream << "GetBool"; break;
				case D3D10_SVT_INT:		stream << "GetInt"; break;
				case D3D10_SVT_FLOAT:	stream << "GetFloat"; break;
				}
				stream << "(&value);";
			}
			else if (typedesc.Class == D3D10_SVC_VECTOR)
			{
				switch (typedesc.Type)
				{
				case D3D10_SVT_BOOL:	stream << "GetBoolVector(&value);"; break;
				case D3D10_SVT_INT:		stream << "GetIntVector((int*)&value);"; break;
				case D3D10_SVT_FLOAT:	stream << "GetFloatVector((float*)&value);"; break;
				case D3D10_SVT_TEXTURE:	stream << "GetResource(&value);"; break;
				}
			}
			else if (typedesc.Class == D3D10_SVC_MATRIX_COLUMNS ||
				typedesc.Class == D3D10_SVC_MATRIX_ROWS)
			{
				stream << "GetMatrix((float*)&value);";
			}

			stream << "return value;";

			pFun->m_body = stream.str();

			Declarator* decl = new Declarator(pFun, String("get_") + vardesc.Name);

			pEffType->m_pScope->AddDeclarator(decl);
		}

		if (pType)
		{
			FunctionType* pFun = new FunctionType();
			pFun->m_pReturnType = typeid(void).GetType();
			pFun->m_parameters.m_parameters.push_back(FunctionParameters::Param(pType, "value"));

			IO::StringWriter stream;
			stream << "m_" << vardesc.Name << "->";

			if (typedesc.Class == D3D10_SVC_SCALAR)
			{
				switch (typedesc.Type)
				{
				case D3D10_SVT_BOOL:	stream << "SetBool"; break;
				case D3D10_SVT_INT:		stream << "SetInt"; break;
				case D3D10_SVT_FLOAT:	stream << "SetFloat"; break;
				}
			}
			else if (typedesc.Class == D3D10_SVC_VECTOR)
			{
				switch (typedesc.Type)
				{
				case D3D10_SVT_BOOL:	stream << "SetBoolVector"; break;
				case D3D10_SVT_INT:		stream << "SetIntVector"; break;
				case D3D10_SVT_FLOAT:	stream << "SetFloatVector"; break;
				}
			}
			else if (typedesc.Class == D3D10_SVC_MATRIX_COLUMNS)
			{
				stream << "SetMatrix";
			}
			else if (typedesc.Class == D3D10_SVC_MATRIX_ROWS)
			{
				stream << "SetMatrixTranspose";
			}
			else
			{
				switch (typedesc.Type)
				{
				case D3D10_SVT_TEXTURE2D:	stream << "SetResource"; break;
				}
			}

			stream << "(value);";

			pFun->m_body = stream.str();

			Declarator* decl = new Declarator(pFun, String("set_") + vardesc.Name);
			pEffType->m_pScope->AddDeclarator(decl);
		}

		if (pType)
		{
			Type* pT2;

			/*
			if (typedesc.Class == D3D10_SVC_SCALAR)
			{
				switch (typedesc.Type)
				{
				case D3D10_SVT_BOOL:	pT2 = typeid(bool).GetType(); break;
				case D3D10_SVT_INT:		pT2 = typeid(int).GetType(); break;
				case D3D10_SVT_FLOAT:	pT2 = typeid(float).GetType(); break;
				case D3D11_SVT_DOUBLE:	pT2 = typeid(double).GetType(); break;
				}
			}
			else
			*/
			if (typedesc.Class == D3D10_SVC_MATRIX_COLUMNS || typedesc.Class == D3D10_SVC_MATRIX_ROWS)
			{
				pT2 = typeid(ID3D10EffectMatrixVariable*).GetType();
			}
			else if (typedesc.Class == D3D10_SVC_VECTOR)
			{
				pT2 = typeid(ID3D10EffectVectorVariable*).GetType();
			}
			else if (typedesc.Class == D3D10_SVC_SCALAR)
			{
				pT2 = typeid(ID3D10EffectScalarVariable*).GetType();
			}
			else if (typedesc.Class == D3D10_SVC_OBJECT)
			{
				pT2 = typeid(ID3D10EffectShaderResourceVariable*).GetType();
			}
			else
			{
				// TODO
				pT2 = typeid(ID3D10EffectShaderResourceVariable*).GetType();
			}

			Declarator* decl = new Declarator(pT2, String("m_") + vardesc.Name);
			pEffType->m_pScope->AddDeclarator(decl);
		}
	}

	{
		IO::FileStream file(L"D:\\temp.cpp", IO::FileMode_Create, IO::FileAccess_Write);
		IO::StreamWriter fs(&file);

		fs << "#include \"LFC/LFC.h\"\n";
		fs << "#include \"GUI/GUI.h\"\n";

		printClass(fs, pEffType, 0);
	}

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;

	SECURITY_ATTRIBUTES sa;
	// Set up the security attributes struct.
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	HANDLE hOutputRead;
	HANDLE hOutputWrite;
	CreatePipe(&hOutputRead, &hOutputWrite, &sa, 0);

	HANDLE hErrorWrite;

// Create a duplicate of the output write handle for the std error
  // write handle. This is necessary in case the child application
  // closes one of its std output handles.
  if (!DuplicateHandle(GetCurrentProcess(),hOutputWrite,
                       GetCurrentProcess(),&hErrorWrite,0,
                       TRUE,DUPLICATE_SAME_ACCESS))
								::MessageBox(NULL, L"DuplicateHandle", L"", MB_OK);

	HANDLE hInputWrite;
	HANDLE hInputRead;
	CreatePipe(&hInputRead, &hInputWrite, &sa, 0);

	/*
  if (!DuplicateHandle(GetCurrentProcess(),GetStdHandle(STD_INPUT_HANDLE),
                       GetCurrentProcess(),&hInputRead,0,
                       TRUE,DUPLICATE_SAME_ACCESS))
								::MessageBox(NULL, "DuplicateHandle", "", MB_OK);
								*/

	// = GetStdHandle(STD_ERROR_HANDLE);
	si.hStdOutput = hOutputWrite;
	si.hStdError = hErrorWrite;
	si.hStdInput = hInputRead;

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	wchar_t* env =
		L"VSINSTALLDIR=C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\0"
		L"VCINSTALLDIR=C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\0"
		L"FrameworkDir=C:\\Windows\\Microsoft.NET\\Framework\0"
		L"FrameworkVersion=v2.0.50727\0"
		L"DevEnvDir=C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\Common7\\IDE\0"

		L"INCLUDE=C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\Include;"
			L"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.0\\Include;"
			L"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.0\\Include\\gl;"
			L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\ATLMFC\\INCLUDE;"
			L"C:\\Program Files (x86)\\Microsoft DirectX SDK (March 2009)\\Include;"
			L"D:\\users\\sigurd\\documents\\vsprojects\\mmstudio\\include"
			L"\0"
		L"CL=/DWIN32 /D_DEBUG /D_WINDOWS /DUNICODE D:\\temp.cpp"
		L"\0"

		L"PATH=C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\Common7\\IDE;"
			L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\BIN;"
			L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\Common7\\Tools;"
			L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\Common7\\Tools\bin;"
			L"%%FrameworkDir%%\\%%Framework35Version%%;"
			L"%%FrameworkDir%%\\%%Framework35Version%%\\Microsoft .NET Framework 3.5 (Pre-Release Version);"
			L"%%FrameworkDir%%\\%%FrameworkVersion%%;"
			L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\VCPackages;"
			L"%%PATH%%\0";

	/*
	SetEnvironmentVariable(L"VSINSTALLDIR", L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0");
	SetEnvironmentVariable(L"VCINSTALLDIR", L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC");
	SetEnvironmentVariable(L"FrameworkDir", L"C:\\Windows\\Microsoft.NET\\Framework");
	SetEnvironmentVariable(L"FrameworkVersion", L"v2.0.50727");
	SetEnvironmentVariable(L"DevEnvDir", L"%VSINSTALLDIR%\\Common7\\IDE");
	SetEnvironmentVariable(L"PATH",
		L"PATH=%DevEnvDir%;"
		L"%%VCINSTALLDIR%\BIN;"
		L"%%VSINSTALLDIR%\Common7\Tools;"
		L"%%VSINSTALLDIR%\Common7\Tools\bin;
		L"%%FrameworkDir%\%Framework35Version%;"
		L"%FrameworkDir%\%Framework35Version%\Microsoft .NET Framework 3.5 (Pre-Release Version);"
		L"%FrameworkDir%\%FrameworkVersion%;"
		L"%VCINSTALLDIR%\VCPackages;"
		L"%PATH%\0");
*/
	WCHAR arg[4000];
	wcscpy_s(arg,
		
	//	L"\"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\bin\\cl.exe\" "

	//	L"/I\"D:\\users\\sigurd\\documents\\vsprojects\\mmstudio\\include\" "
//		L"/D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"UNICODE\" /D \"_USRDLL\" /D \"_WINDLL\" "
		L"/TpD:\\temp.cpp");

	// Start the child process. 
	if( !CreateProcess(
		L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\bin\\cl.exe",
	//	"C:\\WINNT\\Microsoft.NET\\Framework\\v1.1.4322\\csc.exe",
	//	"/debug+ /out:C:\\HelloCS.exe \"C:\\Program Files\\Microsoft.NET\\SDK\\v1.1\\Samples\\Tutorials\\PlatformIntroduction\\HelloWorld\\CS\\helloCS.cs\"", // Command line. 
	//	"c:\\MinGW\\bin\\gcc.exe c:\\test.cpp",

		arg,

		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		TRUE,            // Set handle inheritance to TRUE. 
		CREATE_UNICODE_ENVIRONMENT,// | CREATE_NEW_CONSOLE,                // No creation flags. 
		env, 
		NULL,//L"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\bin",             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi)             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		int lastError = ::GetLastError();
		::MessageBox(NULL, L"CreateProcess failed.", L"", MB_OK);
		return NULL;
	}

// Close pipe handles (do not continue to modify the parent).
	// You need to make sure that no handles to the write end of the
	// output pipe are maintained in this process or else the pipe will
	// not close when the child process exits and the ReadFile will hang.
	if (!CloseHandle(hOutputWrite)) ::MessageBox(NULL, L"CloseHandle", L"", MB_OK);
  if (!CloseHandle(hInputRead )) ::MessageBox(NULL, L"CloseHandle", L"", MB_OK);
  if (!CloseHandle(hErrorWrite)) ::MessageBox(NULL, L"CloseHandle", L"", MB_OK);

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	IO::StringWriter str;

	while (TRUE)
	{
		char buf[61];
		DWORD nRead;
		if (!ReadFile(hOutputRead, buf, 60, &nRead, NULL) || nRead == 0)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE)
				break; // pipe done - normal exit path.
			else
				::MessageBox(NULL, L"ReadFile", L"", MB_OK); // Something bad happened.
		}
		buf[nRead] = 0;

		str << buf;
	}
	
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	Std::Out << str.str();

	return pEffType;
#endif
	return NULL;
}

template class GUIEXT typed<int>;
template class GUIEXT typed<float>;
template class GUIEXT typed<UIElement*>;

// Vector2
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector2<T>, X, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector2<T>, Y, T(0))

template<class T>
DependencyClass* Vector2<T>::get_Class()
{
	static DependencyClass depclass(typeid(Vector2<T>), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_XProperty(),
		get_YProperty(),
	};

	return &depclass;
}

template<class T>
DependencyClass* Vector2<T>::pClass(get_Class());

template class DECLSPEC_DLLEXPORT Vector2<unsigned char>;
template class DECLSPEC_DLLEXPORT Vector2<int>;
template class DECLSPEC_DLLEXPORT Vector2<float>;
template class DECLSPEC_DLLEXPORT Vector2<double>;

// Vector3
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector3<T>, X, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector3<T>, Y, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector3<T>, Z, T(0))

template<class T>
DependencyClass* Vector3<T>::get_Class()
{
	static DependencyClass depclass(typeid(Vector3<T>), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_XProperty(),
		get_YProperty(),
		get_ZProperty(),
	};

	return &depclass;
}

template<class T>
DependencyClass* Vector3<T>::pClass(get_Class());

template class DECLSPEC_DLLEXPORT Vector3<unsigned char>;
template class DECLSPEC_DLLEXPORT Vector3<int>;
template class DECLSPEC_DLLEXPORT Vector3<float>;
template class DECLSPEC_DLLEXPORT Vector3<double>;

// Vector4
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector4<T>, X, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector4<T>, Y, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector4<T>, Z, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector4<T>, W, T(1))

template<class T>
DependencyClass* Vector4<T>::get_Class()
{
	static DependencyClass depclass(typeid(Vector4<T>), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_XProperty(),
		get_YProperty(),
		get_ZProperty(),
		get_WProperty(),
	};

	return &depclass;
}

template<class T>
DependencyClass* Vector4<T>::pClass(get_Class());

template class DECLSPEC_DLLEXPORT Vector4<unsigned char>;
template class DECLSPEC_DLLEXPORT Vector4<int>;
template class DECLSPEC_DLLEXPORT Vector4<float>;
template class DECLSPEC_DLLEXPORT Vector4<double>;

}	// Gui
}	// System

namespace System
{

GUIEXT map<String, Object*> g_files;

GUIEXT void SaveAs(Object* obj, StringIn name)
{
	g_files[name] = obj;
}

GUIEXT Object* GetFile(StringIn name)
{
	return g_files.find(name)->second;
}

namespace Gui
{
	
Gui::ColorF ColorDialog::ChooseColor()
{
	CHOOSECOLOR cc = {0};
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = NULL;
	cc.hInstance = NULL;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.lpCustColors = customColors;

	BOOL success = ::ChooseColorW(&cc);

	return Gui::ColorF::FromCOLORREF(cc.rgbResult);
}

COLORREF ColorDialog::customColors[16];

ColorF ColorF::Transparent(0,0,0,0);
ColorF ColorF::Black;
ColorF ColorF::White(1,1,1);
ColorF ColorF::Red(1,0,0);
ColorF ColorF::Green(0,1,0);
ColorF ColorF::Blue(0,0,1);
ColorF ColorF::Yellow(1,1,0);

}

}	// System
