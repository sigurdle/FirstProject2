// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "GUI2.h"

namespace System
{

Module _Module;

namespace Gui
{

extern "C"
{

class type_info
{
public:
	virtual ~type_info()
	{
	}

	void*_m_data;
	char _m_d_name[1];
};

#define make_ptr_typeid(x)		do { ((type_info*)&typeid(x*))->_m_data = typeid(x)->get_pointerToThis(); } while(0)
#define make_ref_typeid(x)		do { ((type_info*)&typeid(x&))->_m_data = typeid(x)->get_referenceToThis(); } while(0)
#define make_const_typeid(x)	do { ((type_info*)&typeid(const x))->_m_data = typeid(x)->get_constToThis(); } while(0)

BOOL WINAPI RawDllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		try
		{
			_Module.Init(hModule);
		}
		catch (Exception* e)
		{
			MessageBoxW(NULL, e->get_Reason().c_strw(), L"GUI", MB_OK | MB_ICONERROR);
			return FALSE;
		}

		// TODO: Hack
		/*
		((type_info*)&typeid(void))->_m_data = Types::get_void();
		((type_info*)&typeid(bool))->_m_data = Types::get_bool();

		((type_info*)&typeid(char))->_m_data = Types::get_char();
		((type_info*)&typeid(wchar_t))->_m_data = Types::get_wchar();
		((type_info*)&typeid(signed char))->_m_data = Types::get_signed_char();
		((type_info*)&typeid(unsigned char))->_m_data = Types::get_unsigned_char();

		((type_info*)&typeid(short))->_m_data = &Types::type_short;
		((type_info*)&typeid(unsigned short))->_m_data = &Types::type_unsigned_short;

		((type_info*)&typeid(int))->_m_data = &Types::type_int;
		((type_info*)&typeid(unsigned int))->_m_data = &Types::type_unsigned_int;

		((type_info*)&typeid(long))->_m_data = &Types::type_long;
		((type_info*)&typeid(unsigned long))->_m_data = &Types::type_unsigned_long;

		((type_info*)&typeid(long long))->_m_data = &Types::type_long_long;
		((type_info*)&typeid(unsigned long long))->_m_data = &Types::type_unsigned_long_long;

		((type_info*)&typeid(float))->_m_data = Types::get_float();
		((type_info*)&typeid(double))->_m_data = Types::get_double();
		((type_info*)&typeid(long double))->_m_data = Types::get_long_double();

		make_ptr_typeid(char);
		make_ptr_typeid(char);
		make_ptr_typeid(signed char);
		make_ptr_typeid(unsigned char);
		make_ptr_typeid(short);
		make_ptr_typeid(unsigned short);
		make_ptr_typeid(int);
		make_ptr_typeid(unsigned int);
		make_ptr_typeid(long);
		make_ptr_typeid(unsigned long);
		make_ptr_typeid(long long);
		make_ptr_typeid(unsigned long long);

		make_ref_typeid(char);
		make_ref_typeid(signed char);
		make_ref_typeid(unsigned char);
		make_ref_typeid(short);
		make_ref_typeid(unsigned short);
		make_ref_typeid(int);
		make_ref_typeid(unsigned int);
		make_ref_typeid(long);
		make_ref_typeid(unsigned long);
		make_ref_typeid(long long);
		make_ref_typeid(unsigned long long);

		make_ptr_typeid(Object);
		make_ptr_typeid(StringObject);
		make_ptr_typeid(StringW);
		make_ptr_typeid(Geometry);
		make_ptr_typeid(RectangleGeometry);
		make_ptr_typeid(Color);
		make_ptr_typeid(Brush);
		make_ptr_typeid(UIElement);
		make_ptr_typeid(Button);
		make_ptr_typeid(Window);
		make_ptr_typeid(Visual);
		((type_info*)&typeid(Cursor*))->_m_data = new PointerType(typeof(Cursor)->GetClass());
		((type_info*)&typeid(ContentElement*))->_m_data = new PointerType(typeof(ContentElement)->GetClass());
		((type_info*)&typeid(FillGeometryVisual*))->_m_data = new PointerType(typeof(FillGeometryVisual)->GetClass());
		((type_info*)&typeid(StrokeGeometryVisual*))->_m_data = new PointerType(typeof(StrokeGeometryVisual)->GetClass());
		((type_info*)&typeid(TextVisual*))->_m_data = new PointerType(typeof(TextVisual)->GetClass());
		((type_info*)&typeid(WindowVisual*))->_m_data = new PointerType(typeof(WindowVisual)->GetClass());
		((type_info*)&typeid(FontFamily*))->_m_data = new PointerType(typeof(FontFamily)->GetClass());
		((type_info*)&typeid(VisualCollection*))->_m_data = new PointerType(typeof(VisualCollection)->GetClass());
		((type_info*)&typeid(Transform*))->_m_data = new PointerType(typeof(Transform)->GetClass());
		((type_info*)&typeid(Clock*))->_m_data = new PointerType(typeof(Clock)->GetClass());
		((type_info*)&typeid(Element*))->_m_data = new PointerType(typeof(Element)->GetClass());
		((type_info*)&typeid(BitmapSource*))->_m_data = new PointerType(typeof(BitmapSource)->GetClass());
		((type_info*)&typeid(StrokeStyle*))->_m_data = new PointerType(typeof(StrokeStyle)->GetClass());
	//	((type_info*)&typeid(BitmapElement*))->_m_data = new PointerType(typeof(BitmapElement)->GetClass());
		((type_info*)&typeid(Vector3<float>*))->_m_data = new PointerType(typeof(Vector3<float>)->GetClass());
		((type_info*)&typeid(Vector4<float>*))->_m_data = new PointerType(typeof(Vector4<float>)->GetClass());
		((type_info*)&typeid(Media3D::Visual3D*))->_m_data = new PointerType(typeof(Media3D::Visual3D)->GetClass());
		((type_info*)&typeid(Media3D::Camera*))->_m_data = new PointerType(typeof(Media3D::Camera)->GetClass());
		((type_info*)&typeid(Media3D::Transform3D*))->_m_data = new PointerType(typeof(Media3D::Transform3D)->GetClass());
		((type_info*)&typeid(Media3D::Geometry3D*))->_m_data = new PointerType(typeof(Media3D::Geometry3D)->GetClass());
		((type_info*)&typeid(Media3D::Material*))->_m_data = new PointerType(typeof(Media3D::Material)->GetClass());

		((type_info*)&typeid(IBitmapSource*))->_m_data = new PointerType(typeof(IBitmapSource)->GetClass());
		((type_info*)&typeid(ITextSource*))->_m_data = new PointerType(typeof(ITextSource)->GetClass());
		((type_info*)&typeid(ID3D10EffectScalarVariable*))->_m_data = new PointerType(typeof(ID3D10EffectScalarVariable)->GetClass());
		((type_info*)&typeid(ID3D10EffectVectorVariable*))->_m_data = new PointerType(typeof(ID3D10EffectVectorVariable)->GetClass());
		((type_info*)&typeid(ID3D10EffectMatrixVariable*))->_m_data = new PointerType(typeof(ID3D10EffectMatrixVariable)->GetClass());
		((type_info*)&typeid(ID3D10EffectShaderResourceVariable*))->_m_data = new PointerType(typeof(ID3D10EffectShaderResourceVariable)->GetClass());

		((type_info*)&typeid(ID3D10ShaderResourceView*))->_m_data = new PointerType(typeof(ID3D10ShaderResourceView)->GetClass());
		*/
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HMODULE, DWORD, LPVOID) = RawDllMain;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	_Module.DllMain(hModule, ul_reason_for_call, lpReserved);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hModule);
			Gui::PlatformWindow::RegisterWndClass(hModule);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		{
		}
		break;

	case DLL_PROCESS_DETACH:
		{
		}
		break;
	}
	return TRUE;
}

}	// extern "C"
}	// Gui
}	// System
